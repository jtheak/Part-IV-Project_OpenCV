//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <cmath>
//#include "imwarpfunctions.h"
//
//using namespace std;
//using namespace cv;
//
//
//int main(int argc, char** argv) {
//	Mat src, rotated;
//
//
//	src = imread("DSC_0031.jpg");
//	Rect fromroi;
//
//	fromroi.height = src.rows;
//	fromroi.width = src.cols;
//	fromroi.x = 0;
//	fromroi.y = 0;
//
//	double angle = -90;
//	rotated = rotateImage(src, &rotated, fromroi, angle);
//
//	char* source_window = "Source image";
//	char* rotate_window = "Rotate";
//
//
//
//	namedWindow(source_window, WINDOW_NORMAL);
//	imshow(source_window, src);
//	
//	namedWindow(rotate_window, WINDOW_NORMAL);
//	imshow(rotate_window, rotated);
//	
//	/// Wait until user exits the program
//	waitKey(0);
//	
//	return 0;
//
//}