/*
 * test.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */


#include "../src/detector/ACFDetector.h"
#include "../src/Util/common.h"
#include "../src//features/chnsCompute/Channel.h"
#include "../src/features/pyramid.h"
#include "../src/Util/IODetector.h"

using namespace std;
using namespace acf;

//use case 1 : load detector and detect image
void testLoadUseCase(){
	ACFDetector detector  =  loadDetectorFromMat("test.mat");
	vector<BoundingBox> bbs;
	Mat image;
	detector.detectImg(bbs,image);
}

class ChnCustom: public Chn{
public:
	void compute(){
		OUT("Custom compute");
	}
};
//use case 2 :
void testTrainTestUseCase(){
	ACFDetector detector = ACFDetector::Builder("conf/detector.conf").build();
	Mat img;
	ChnsManager chnsManager;
	Pyramid pyramid(chnsManager);
	Chn* chn  = new ChnCustom();
	chnsManager.addChn(chn);
	vector<vector<Mat*> > datas;
	pyramid.computeData(img,datas);
	detector.train();
	detector.test();
}




#if NOW_TESTING == TEST_ALL
int main( int argc, char** argv ){
	testLoadUseCase();
//	testTrainTestUseCase();
}
#endif