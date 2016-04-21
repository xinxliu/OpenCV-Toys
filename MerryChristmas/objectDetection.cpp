#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame,Mat &hat );

/** Global variables */
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/** @function main */
int main( void )
{
    VideoCapture capture(0);
    Mat frame;
    Mat hat = imread("2.png");

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream
    /*capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
*/
	while(1)
	{
        //-- 3. Apply the classifier to the frame
		capture >> frame;
        detectAndDisplay( frame,hat );

        int c = waitKey(30);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame ,Mat &hat)
{
    Mat _hat = imread("2.jpg",0);
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //wear a hat
        
        //wear a hat

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
		
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            
        }
		int unitx = frame.cols/20;
		int unity = frame.rows/20;
		int ax = faces[i].x-unitx;
		int ay = faces[i].y - faces[i].height / 2-unity;
		int bx = ax + hat.cols;
		int by = ay;
		int cx = ax;
		int cy = ay + hat.rows;
		int dx = bx;
		int dy = cy;

		int xLimit = frame.cols;
		int yLimit = frame.rows;
        
        if(ax>(0+1)&&ax<(xLimit-1)&&bx<(xLimit-1)&&by>1&&by<yLimit&&dy<yLimit-1)
        {
        	Rect roi = Rect(ax,ay,hat.cols,hat.rows);
    		Mat img_ROI = frame(roi);
    		//hat.copyTo(img_ROI,_hat);
			Mat_<Vec3b>::iterator it1 = img_ROI.begin<Vec3b>();
			Mat_<Vec3b>::iterator itend1 = img_ROI.end<Vec3b>();
			Mat_<Vec3b>::iterator it2 = hat.begin<Vec3b>();
			Mat_<Vec3b>::iterator itend2 = hat.end<Vec3b>();
			for (; it2 != itend2||it1 != itend1; ++it1, ++it2)
			{
				if (!(((*it2)[0] == 0)&&((*it2)[1] == 0)&&((*it2)[2] == 0)))
				{
					(*it1)[0] = (*it2)[0];
					(*it1)[1] = (*it2)[1];
					(*it1)[2] = (*it2)[2];
				}
			}
    	}
    }
    //-- Show what you got
    
    imshow( window_name, frame );
}
