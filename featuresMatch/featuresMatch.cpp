#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class SURFDetector
{
public:
	Ptr<Feature2D> surf;
	SURFDetector(double hessian = 3500)
	{
		surf = SURF::create(hessian);
	}
	void operator()(const Mat& input,const Mat& mask,vector<KeyPoint>& pts,Mat& descriptors)
	{
		surf->detectAndCompute(input,mask,pts,descriptors);
	}
};

int main()
{
	Mat _img1 = imread("1.jpg");
	Mat _img2 = imread("2.jpg");
	Mat img1,img2;
	cvtColor(_img1,img1,COLOR_BGR2GRAY);
	cvtColor(_img2,img2,COLOR_BGR2GRAY);
	
	Mat des1;
	Mat des2;
	
	vector<KeyPoint> kp1;
	vector<KeyPoint> kp2;
	
	vector<DMatch> matches;
	
	SURFDetector surf;
	BFMatcher matcher;
	surf(img1,Mat(),kp1,des1);
	surf(img2,Mat(),kp2,des2);
	matcher.match(des1,des2,matches);
	Mat img_matches;
	
	drawMatches(_img1,kp1,_img2,kp2,matches,img_matches);
	imshow("match",img_matches);
	imwrite("tmp.jpg", img_matches);
	waitKey(0);
	return 0;
}