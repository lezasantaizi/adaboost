#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../3rdparty/include/opencv.hpp"
using namespace std;
using namespace cv;
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_core249.lib")
void stumpClassify(vector<float>& retArray, vector<vector<float>>& dataMatrix, int dimen, float threshVal, string threshIneq)
{
	for (int i = 0 ; dataMatrix.size(); i++)
	{
		retArray.push_back(1);
	}
	if (threshIneq == "lt")
	{
		for (int i = 0 ;i < dataMatrix.size(); i++)
		{
			retArray[dataMatrix[i][dimen] <= threshVal] = -1.0;
		}
	}
	else
	{
		for (int i = 0 ;i < dataMatrix.size(); i++)
		{
			retArray[dataMatrix[i][dimen] > threshVal] = -1.0;
		}
	}
}

void buildStump(vector<vector<float>>dataArr,vector<int>classLabels,vector<float>D)
{
	int m = dataArr.size();
	int n = dataArr[0].size();
	int numSteps = 10;
	vector<float> bestStump;
	vector<float> bestClasEst;
	int minError = 10000;

	for (int i = 0 ;i < m; i++)
	{
		bestClasEst[i] = 0;
	}

	for (int i = 0 ;i< n;i++)
	{
		
	}
}

void loadSimpData()
{
	float datMatArray[] = {1.0,2.1,2.0,1.1,1.3,1.0,1.0,1.0,2.0,1.0};
	int classLabels[] = {1,1,-1,-1,1};
	Mat datMat(5, 2, CV_32FC1, datMatArray);

}

void loadDataSet(string fileName)
{
	fstream outFile;
	outFile.open(fileName.c_str());


}
int main(int argc, char** argv)
{
	return 0;
}