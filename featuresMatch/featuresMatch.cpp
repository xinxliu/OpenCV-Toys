#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("1.jpg");
	Mat dst = imread("2.jpg");
	Mat imgMatches;
	vector<KeyPoint> keyPoint1, keyPoint2;
	Mat descriptor1;
	Mat descriptor2;
	FastFeatureDetector detector;
	detector.detect(src, keyPoint1);
	detector.detect(dst, keyPoint1);
	DescriptorExtractor extractor;
	extractor.compute(src, keyPoint1, descriptor1);
	extractor.compute(dst, keyPoint2, descriptor2);
	vector<DMatch> matches;
	BFMatcher matcher(NORM_L2);
	matcher.match(descriptor1, descriptor2, matches);
	drawMatches(src, keyPoint1, dst, keyPoint2, matches, imgMatches);
	imshow("matches", imgMatches);
	while (char(waitKey(0)) == 'q')
	{
		return 0;
	}

}