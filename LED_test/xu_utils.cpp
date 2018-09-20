#include "xu_utils.h"

//-------------------vector<char> תΪstring---------------
string MY_UTILS::vc2s(const vector<char> &vec)
{
	string ss(vec.cbegin(), vec.cend());
	return ss;
}

//-------------------vector<string> תΪstring---------------
string MY_UTILS::vs2s(const vector<string> &vec)
{
	string ss = accumulate(vec.cbegin(), vec.cend(), string(""));
	return ss;
}

cv::Mat MY_UTILS::vecf2mat( vector<vector<float>> &vec)
{

	int m = vec.size();
	int n = vec[0].size();

	cv::Mat img(m, n, CV_32FC1);

	for (int i = 0; i < m; i++)
	{
		float * img_ptr = img.ptr<float>(i);
		memcpy(img_ptr, &vec[i][0], n * sizeof(float));
	}

	return img;
}

cv::Mat MY_UTILS::vecu2mat(vector<vector<uchar>> &vec)
{

	int m = vec.size();
	int n = vec[0].size();

	cv::Mat res(m, n, CV_8UC1);

	for (int i = 0; i < m; i++)
	{
		uchar * img_ptr = res.ptr<uchar>(i);
		memcpy(img_ptr, &vec[i][0], n * sizeof(uchar));
	}

	return res;

}

cv::Mat MY_UTILS::LMapping(cv::Mat & img)
{
	double minv = 0.0, maxv = 0.0;
	double * minp = &minv;
	double * maxp = &maxv;
	cv::minMaxIdx(img, minp, maxp);

	cv::Mat res = img;

	res = res - minv;
	
	double alpha = 1.0 / (maxv - minv);

	res = res.mul(alpha);

	return res;
}



