#include "regression.h"

Regression::Regression()
{

}


Regression::~Regression()
{
}

Regression::Regression(int rm, int cm, int wt, int ht,
    int wb, int hb, int bsize, float scale, string path) :
    row_min(rm), col_min(cm), width_topcon(wt), height_topcon(ht),
    width_basler(wb), height_basler(hb),
    block_size(bsize),
    train_scale(scale),
    model_path(path)
{

}


/************************************************************************/
/* 初始化函数                                                           */
/* model文件存在则初始化成功，不存在返回false提示用户载入文件或重新训练 */
/************************************************************************/
bool Regression::init()
{

    if (model_path != "")
    {
        ifstream fin(model_path);
        if (fin)
        {
            cout << "load_svm..." << endl;
            svm = cv::ml::SVM::load(model_path);
            TrainFlag = true;
            cout << "Success" << endl;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Regression::init(string path)
{
    model_path = path;
    return this->init();
}

vector<vector<float>> Regression::readCSV(string csvpath)
{
    vector<vector<float> > data;
    ifstream fin(csvpath);

    if (fin)
    {
        string line;
        getline(fin, line);
        while (getline(fin, line))
        {
            vector<float> row;
            stringstream ss(line);
            string tmp;
            while (getline(ss, tmp, ','))
            {
                row.push_back(MY_UTILS::s2n<float>(tmp));
            }
            if (row.size() > 0)
            {
                data.push_back(row);
            }
        }
    }
    else {
        cout << csvpath << ": File not exist" << endl;
    }

    fin.close();
    return data;
}

vector<vector<uchar>> Regression::getData(const cv::Mat &img)
{
    cv::Mat img_gray;

    if (img.type() == CV_8UC3)
    {
        cv::cvtColor(img, img_gray, CV_RGB2GRAY);
    }


    vector<vector<uchar> > data;

    int m = img_gray.rows;
    int n = img_gray.cols;

    vector<int> row_indexs;
    vector<int> col_indexs;

    for (int i = 0; i <= m - block_size; i += step_basler)
    {
        row_indexs.push_back(i);
    }

    for (int i = 0; i <= n - block_size; i += step_basler)
    {
        col_indexs.push_back(i);
    }

    for (int i : row_indexs)
    {
        for (int j : col_indexs)
        {
            vector<uchar> foo;
            for (int ci = 0; ci < block_size; ci++)
            {
                for (int ri = 0; ri < block_size; ri++)
                {
                    foo.push_back(img_gray.at<uchar>(i + ri, j + ci));
                }
            }
            data.push_back(foo);
        }
    }
    return data;
}

vector<float> Regression::getLable(vector<vector<float>> &csvData)
{
    vector<vector<float> > tData;

    cv::Mat csvImg = MY_UTILS::vecf2mat(csvData);

    cv::Mat csv_roi;

    csvImg(cv::Range(row_min, row_min + height_topcon), cv::Range(col_min, col_min + width_topcon)).copyTo(csv_roi);

    cv::Mat dstImg, dsttemp;

    cv::blur(csv_roi, dsttemp, cv::Size(block_size / 2, block_size / 2), cv::Point(-1, -1), cv::BORDER_REPLICATE);

    dsttemp(cv::Range(2, dsttemp.rows - 2), cv::Range(2, dsttemp.cols - 2)).copyTo(dstImg);

    vector<float> Indexs((float *)dstImg.datastart, (float*)dstImg.dataend);

    return Indexs;
}

vector<int> Regression::getTrainIndex(vector<vector<uchar>>& data)
{

    int data_num = data.size();

    vector<int> indexs;
    for (int i = 0; i < data_num; i++)
    {
        indexs.push_back(i);
    }

    random_shuffle(indexs.begin(), indexs.end());

    vector<int> train_index(indexs.begin(), indexs.begin() + floor(train_scale*data_num));

    return train_index;
}

vector<vector<uchar>> Regression::getTrainData(const vector<vector<uchar>> &data, const vector<int> &index)
{

    vector<vector<uchar> > train_data;

    for (int ind : index)
    {
        train_data.push_back(data[ind]);
    }

    return train_data;
}

vector<float> Regression::getTrainLable(const vector<float> labels, vector<int>& index)
{
    vector<float> train_label;
    for (int ind : index)
    {
        train_label.push_back(labels[ind]);
    }

    return train_label;
}

cv::Mat Regression::scaleForSVM(cv::Mat train_data)
{
    train_data.convertTo(train_data, CV_32FC1, 1);
    cv::Mat res = MY_UTILS::LMapping(train_data);
    return res;
}


/************************************************************************
*   训练模型
*	basler_img_path:Basler相机拍摄图像
*	topcon_csv_path:拓普康计算标准图像
************************************************************************/
cv::Ptr<cv::ml::SVM> Regression::train(string basler_img_path, string topcon_csv_path)
{

    //获取Basler数据
    cv::Mat balser_img = cv::imread(basler_img_path);

    cv::resize(balser_img, balser_img, cv::Size(width_basler, height_basler));

    vector<vector<uchar> > basler_data_vec = getData(balser_img);

    //获取拓普康数据
    vector<vector<float> > Topcon_data = readCSV(topcon_csv_path);
    vector<float> Labels = getLable(Topcon_data);


    //随机选取训练样本

    vector<int> index = getTrainIndex(basler_data_vec);

    vector<vector<uchar> > train_data = getTrainData(basler_data_vec, index);
    cv::Mat train_mat_tmp = MY_UTILS::vecu2mat(train_data);		//vector转Mat 每一行为一个样本
    cv::Mat train_data_mat = scaleForSVM(train_mat_tmp);				//归一化

    vector<float> train_label = getTrainLable(Labels, index);
    cv::Mat train_label_mat(train_label.size(), 1, CV_32FC1, &train_label[0]);

    svm = train(train_data_mat, train_label_mat);

    TrainFlag = true;

    return svm;
}

cv::Ptr<cv::ml::SVM> Regression::train(cv::Mat train_data, cv::Mat labels)
{
    svm = cv::ml::SVM::create();

    cv::Ptr<cv::ml::TrainData> trainData = cv::ml::TrainData::create(train_data, cv::ml::SampleTypes::ROW_SAMPLE, labels);

    svm->setType(cv::ml::SVM::EPS_SVR);		//设置为回归训练

    svm->setP(0.01);

    svm->trainAuto(trainData);

    svm->save(model_path);

    return svm;
}

cv::Mat Regression::predictAll(cv::Mat &img)
{

    cv::resize(img, img, cv::Size(width_basler, height_basler));

    if (img.dims > 2)
    {
        cv::cvtColor(img, img, CV_RGB2GRAY);
    }

    vector<vector<uchar> > basler_data = getData(img);

    cv::Mat predictMat_tmp = MY_UTILS::vecu2mat(basler_data);

    cv::Mat predictMat = scaleForSVM(predictMat_tmp);

    vector<float> resVec;

    for (size_t i = 0; i < predictMat.rows; i++)
    {
        cv::Mat sample;
        predictMat(cv::Range(i, i + 1), cv::Range::all()).copyTo(sample);
        float res = svm->predict(sample);
        resVec.push_back(res);
    }

    int res_row = height_topcon - block_size / 2 + 1;
    int res_col = width_topcon - block_size / 2 + 1;

    cv::Mat resMat(res_row, res_col, CV_32FC1);

    memcpy(resMat.data, &resVec[0], resVec.size() * sizeof(float));

    return resMat;
}


vector<float> Regression::predict(cv::Mat basler_img, vector<cv::Rect> rects)
{

    vector<cv::Mat> blockVec;

    for (cv::Rect rect : rects)
    {
        cv::Mat block;
        basler_img(rect).copyTo(block);
        blockVec.push_back(block);
    }

    vector<float> resVec;

    for (cv::Mat block : blockVec)
    {
        resVec.push_back(predict(block));
    }

    return resVec;
}

float Regression::predict(cv::Mat block)
{

    vector<vector<uchar> > data = getData(block);
    cv::Mat predictData_tmp = MY_UTILS::vecu2mat(data);
    cv::Mat predictData = scaleForSVM(predictData_tmp);

    vector<float> resVec;

    for (int i = 0; i < predictData.rows; i++)
    {
        cv::Mat sample;
        predictData(cv::Range(i, i + 1), cv::Range::all()).copyTo(sample);
        float res = svm->predict(sample);
        resVec.push_back(res);
    }

    return accumulate(resVec.begin(), resVec.end(), 0) / resVec.size();

}
