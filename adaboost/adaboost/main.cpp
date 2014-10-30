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


void stumpClassify(vector<float>& retArray, vector<vector<float>> dataMatrix, int dimen, float threshVal, int threshIneq)
{
	if (threshIneq == 0)
	{
		for (int i = 0 ;i < dataMatrix.size(); i++)
		{
			retArray[i] = dataMatrix[i][dimen] <= threshVal?-1.0:1.0;
		}
	}
	else
	{
		for (int i = 0 ;i < dataMatrix.size(); i++)
		{
			retArray[i] = dataMatrix[i][dimen] > threshVal?-1.0:1.0;
		}
	}
}


//def buildStump(dataArr,classLabels,D):
//	dataMatrix = mat(dataArr); labelMat = mat(classLabels).T
//	m,n = shape(dataMatrix)
//	numSteps = 10.0; bestStump = {}; bestClasEst = mat(zeros((m,1)))
//	minError = inf #init error sum, to +infinity
//	for i in range(n):#loop over all dimensions
//		rangeMin = dataMatrix[:,i].min(); rangeMax = dataMatrix[:,i].max();
//stepSize = (rangeMax-rangeMin)/numSteps
//	for j in range(-1,int(numSteps)+1):#loop over all range in current dimension
//		for inequal in ['lt', 'gt']: #go over less than and greater than
//			threshVal = (rangeMin + float(j) * stepSize)
//			predictedVals = stumpClassify(dataMatrix,i,threshVal,inequal)#call stump classify with i, j, lessThan
//			errArr = mat(ones((m,1)))
//			errArr[predictedVals == labelMat] = 0
//			weightedError = D.T*errArr  #calc total error multiplied by D
//#print "split: dim %d, thresh %.2f, thresh ineqal: %s, the weighted error is %.3f" % (i, threshVal, inequal, weightedError)
//			if weightedError < minError:
//minError = weightedError
//	bestClasEst = predictedVals.copy()
//	bestStump['dim'] = i
//	bestStump['thresh'] = threshVal
//	bestStump['ineq'] = inequal
//	return bestStump,minError,bestClasEst


void buildStump(vector<vector<float>> dataArr,vector<int> classLabels,vector<float>& D,vector<float>& bestStump,float& minError,vector<float>& bestClasEst)
{
	int m = dataArr.size();
	int n = dataArr[0].size();
	int numSteps = 10;
	minError = 10000;
	float stepSize;

	for (int i = 0 ;i< n;i++)
	{
		float tempMin = 10000, tempMax = -10000;
		for (int j = 0; j< m; j++)
		{
			tempMin = dataArr[j][i]>tempMin?tempMin:dataArr[j][i];
			tempMax = dataArr[j][i]>tempMax?dataArr[j][i]:tempMax;
		}
		stepSize = (tempMax-tempMin)/numSteps;

		for (int j = -1 ;j < numSteps+1; j++)
		{
			float threshVal = (tempMin + float(j) * stepSize);
			vector<float> predictedVals;
			float weightedError = 0;
			for (int i = 0 ; i< dataArr.size(); i++)
			{
				predictedVals.push_back(1);
			}
			for (int ineq = 0; ineq<2 ; ineq++)
			{
				stumpClassify(predictedVals,dataArr,i,threshVal,ineq);

				for (int k = 0; k < m ; k++)
				{
					weightedError += D[k]*(predictedVals[k] == classLabels[k]?0:1);
				}

				if(weightedError < minError)
				{
					minError = weightedError;
					bestClasEst = predictedVals;
					bestStump[0] = i;//'dim'
					bestStump[1] = threshVal;//'thresh'
					bestStump[2] = ineq;//0 = lt, 1 = gt ;//'ineq'
				}
			}		
		}
	}
}


//def adaBoostTrainDS(dataArr,classLabels,numIt=40):
//    weakClassArr = []
//    m = shape(dataArr)[0]
//    D = mat(ones((m,1))/m)   #init D to all equal
//    aggClassEst = mat(zeros((m,1)))
//    for i in range(numIt):
//        bestStump,error,classEst = buildStump(dataArr,classLabels,D)#build Stump
//        #print "D:",D.T
//        alpha = float(0.5*log((1.0-error)/max(error,1e-16)))#calc alpha, throw in max(error,eps) to account for error=0
//        bestStump['alpha'] = alpha  
//        weakClassArr.append(bestStump)                  #store Stump Params in Array
//        #print "classEst: ",classEst.T
//        expon = multiply(-1*alpha*mat(classLabels).T,classEst) #exponent for D calc, getting messy
//        D = multiply(D,exp(expon))                              #Calc New D for next iteration
//        D = D/D.sum()
//        #calc training error of all classifiers, if this is 0 quit for loop early (use break)
//        aggClassEst += alpha*classEst
//        #print "aggClassEst: ",aggClassEst.T
//        aggErrors = multiply(sign(aggClassEst) != mat(classLabels).T,ones((m,1)))
//        errorRate = aggErrors.sum()/m
//        print "total error: ",errorRate
//        if errorRate == 0.0: break
//    return weakClassArr,aggClassEst
void adaBoostTrainDS(vector<vector<float>> dataArr,vector<int> classLabels,vector<vector<float>>& weakClassArr,vector<float>& aggClassEst, int numIt=40)
{
	int m = dataArr.size();
	vector<float> D;
	float error;
	vector<float> bestStump;
	vector<float> bestClasEst;
	
	for (int i = 0 ;i< m ;i++)
	{
		D.push_back(1.0/m);
		aggClassEst.push_back(0);
		bestClasEst.push_back(0);
		bestStump.push_back(0);
	}

	for (int i = 0 ;i< numIt; i++)
	{
		buildStump(dataArr, classLabels, D, bestStump, error, bestClasEst);
		float alpha = 0.5*log((1.0-error)/MAX(error,1e-16));
		bestStump.push_back(alpha);
		weakClassArr.push_back(bestStump) ;
		float sum_D = 0;
		float sum_E = 0;
		for (int j =0 ;j < classLabels.size();j++)
		{
			float temp = -1*alpha*classLabels[j]*bestClasEst[j];
			D[j] = D[j] * exp(temp);
			sum_D += D[j];
			aggClassEst[j] += alpha * bestClasEst[j];
		}
		for (int j = 0 ;j<classLabels.size();j++)
		{
			D[j] /= sum_D;
			int temp = aggClassEst[j]>0?1:-1;
			sum_E += (temp != classLabels[j]);
		}

		printf("total error: %.4f\n",sum_E/m);
		if(sum_E/m <=1e-4)
			break;

	}

}

void loadSimpData(vector<vector<float>>& datMat,vector<int>& clsLabels)
{
	float datMatArray[] = {1.0,2.1,2.0,1.1,1.3,1.0,1.0,1.0,2.0,1.0};
	
	int classLabels[] = {1,1,-1,-1,1};

	for (int i = 0 ;i < 5; i++)
	{
		vector<float> temp;
		for (int j = 0 ;j<2;j++)
		{
			temp.push_back( datMatArray[i*2 + j] );
		}
		clsLabels.push_back(classLabels[i]);
		datMat.push_back(temp);
	}

}

void loadDataSet(string fileName)
{
	fstream outFile;
	outFile.open(fileName.c_str());


}
int main(int argc, char** argv)
{
	vector<vector<float>> data;
	vector<int> labels;
	vector<vector<float>> weakClassArr;
	vector<float> aggClassEst;
	loadSimpData(data,labels);
	adaBoostTrainDS(data,labels,weakClassArr,aggClassEst);
	return 0;
}