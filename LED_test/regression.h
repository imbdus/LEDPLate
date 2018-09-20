#ifndef REGRESSION_H
#define REGRESSION_H

#endif // REGRESSION_H
#pragma once
#include <opencv2/opencv.hpp>
#include <ostream>
#include <vector>
#include <numeric>
#include <QObject>
#include <assert.h>
#include "xu_utils.h"


using namespace std;
//using namespace cv;


class Regression : public QObject
{
    Q_OBJECT
private:
    cv::Ptr<cv::ml::SVM> svm;
    string model_path = "";

    //Topcon面板位置
    int row_min = 226,
        col_min = 438,
        width_topcon = 480,
        height_topcon = 535,
        step_topcon = 1;

    //Basler图片尺寸
    int width_basler = 960,
        height_basler = 1070,
        step_basler = 2;

    //区域大小
    int block_size = 10;

    //训练比例
    float train_scale = 0.01;

    bool TrainFlag = false;


    vector<vector<float> > readCSV(string csvpath);

    vector<vector<uchar> > getData(const cv::Mat &img);

    vector<float> getLable(vector<vector<float>> &csvData);

    vector<int> getTrainIndex(vector<vector<uchar>> &data);

    vector<vector<uchar> > getTrainData(const vector<vector<uchar>> &data, const vector<int> &index);

    vector<float> getTrainLable(const vector<float> labels, vector<int> &index);

    cv::Ptr<cv::ml::SVM> train(cv::Mat train_data, cv::Mat labels);

    cv::Mat scaleForSVM(cv::Mat train_data);

    float predict(cv::Mat block);


public:
    Regression();
    ~Regression();

    Regression(int rm, int cm, int wt, int ht, int wb, int hb, int bsize, float scale, string path = "");


    /*
    默认初始化
    加载模型成功返回True，失败返回false
    */
    bool init();

    /*
    初始化函数,参数为模型的路径
    加载模型成功返回True，失败返回false
    */
    bool init(string path);


    /*
    训练函数
    basler_img_path：Basler图像路径（仅包含面板位置，需手动划分）
    topcon_csv_path：Topcon CSV文件路径
    */
    cv::Ptr<cv::ml::SVM> train(string basler_img_path, string topcon_csv_path);

    /*
    预测整幅图像
    img：Basler图像（面板区域）
    */
    cv::Mat predictAll(cv::Mat &img);

    /*
    预测图像块
    basler_img：Basler图像（面板区域）
    rects：划分区域的Vector
    */
    vector<float> predict(cv::Mat basler_img, vector<cv::Rect> rects);


};

