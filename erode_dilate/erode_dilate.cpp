#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_structElement = 3;

int g_buttonErode = 0;


//void on_button(int, void *);
static void onMouse(int event, int x, int y, int, void*);
void on_ElementSize(int, void *);
void process();

int main()
{
	g_srcImage = imread("1.tiff");
	namedWindow("the orignal");
	imshow("the orignal", g_srcImage);

	namedWindow("after effect");
	Mat structElement = getStructuringElement(MORPH_RECT, Size(2 * g_structElement + 1, 2 * g_structElement + 1));
	erode(g_srcImage, g_dstImage, structElement);
	imshow("after effect", g_dstImage);
	//createButton("erode/dilate", on_button, &g_buttonErode, CV_PUSH_BUTTON, 0);
	setMouseCallback("after effect", onMouse, &g_buttonErode);
	createTrackbar("size", "after effect", &g_structElement, 30, on_ElementSize);
	while (char(waitKey(1)) != 'q') 
	{
	}
	return 0;
}

void process()
{
	Mat structElement = getStructuringElement(MORPH_RECT, Size(2 * g_structElement + 1, 2 * g_structElement + 1));

	if (g_buttonErode == 0)
	{
		erode(g_srcImage, g_dstImage, structElement);
	}
	else {
		dilate(g_srcImage, g_dstImage, structElement);
	}
	imshow("after effect", g_dstImage);
}


void onMouse(int event, int x, int y, int, void *)
{
	if (event != EVENT_LBUTTONDBLCLK)
	{
		return;
	}
	if (g_buttonErode == 1)
	{
		g_buttonErode = 0;
	}
	else
	{
		g_buttonErode = 1;
	}
	//g_buttonErode = g_buttonErode > 0 ? 0 : 1;
	process();
}

void on_ElementSize(int, void *)
{
	process();
}