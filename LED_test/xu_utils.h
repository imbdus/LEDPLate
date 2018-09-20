#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include <iterator>
#include <opencv2/opencv.hpp>

using namespace std;

namespace MY_UTILS {

	template <typename T>
	void printVec(const vector<T>& vec)
	{
		copy(vec.cbegin(), vec.cend(), ostream_iterator<T>(cout, " "));
	}

	template<typename T1,typename T2>
	void printVec2(const vector<T1>& vec)
	{
		copy(vec.cbegin(), vec.cend(), ostream_iterator<T2>(cout, " "));
	}
	template<typename T>
	string n2s(T foo)
	{
		stringstream ss;
		ss << foo;
		return ss.str();
	}

	template<typename T>
	T s2n(string foo)
	{
		stringstream ss(foo);
		T bar = 0;
		ss >> bar;
		return bar;
	}

	string vc2s(const vector<char> &vec);

	string vs2s(const vector<string> &vec);

	cv::Mat vecf2mat(vector<vector<float>> &vec);

	cv::Mat vecu2mat(vector<vector<uchar>> &vec);

	cv::Mat LMapping(cv::Mat &img);
	
}

