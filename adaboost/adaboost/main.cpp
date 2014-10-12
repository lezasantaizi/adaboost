#include <iostream>
#include <string>
#include <vector>

using namespace std;

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


int main()
{
	return 0;
}