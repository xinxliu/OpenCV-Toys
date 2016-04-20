
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "orignal"		
#define WINDOW_NAME2 "outline"					

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*);


int main(int argc, char** argv)
{

	// ����src
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) { printf("read error \n"); return false; }

	// ת�ɻҶȲ�ģ��������
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// ��������
	namedWindow(WINDOW_NAME1, 0);
	imshow(WINDOW_NAME1, g_srcImage);

	//��������������ʼ��
	createTrackbar("canny��ֵ", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return(0);
}

void on_ThreshChange(int, void*)
{

	// Canny����Ե
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	// Ѱ������
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// �������
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//����ֵ
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	// ��ʾЧ��ͼ
	namedWindow(WINDOW_NAME2, 0);
	imshow(WINDOW_NAME2, drawing);
}
