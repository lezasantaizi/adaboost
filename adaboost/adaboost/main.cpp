#include <iostream>
#include <string>
#include <vector>

using namespace std;

void stumpClassify(vector<float>& retArray, vector<vector<float>>& dataMatrix, int dimen, int threshVal, string threshIneq)
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

int main()
{
	return 0;
}