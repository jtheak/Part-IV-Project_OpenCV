#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace cv;
using namespace std;

#define PI 3.14159265
/// Global variables
char* source_window = "Source image";
char* warp_window = "Warp";
char* warp_rotate_window = "Warp + Rotate";

/** @function main */
int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst, warp_rotate_dst2;
	Rect box;
	
	/// Load the image
	
	src = imread("DSC_0031.jpg");

	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50;
	double scale = 1;


	int l, w, xval;
	double radians;

	double sina, cosa, x, wr, hr;



	if (src.rows > src.cols) {
		l = src.rows;
		w = src.cols;
	}
	else {
		l = src.cols;
		w = src.rows;
	}


	radians = angle*PI / 180;

	sina = abs(sin(radians));
	cosa = abs(cos(radians));

	if (w <= 2.*sina*cosa*l) {
		x = 0.5*w;
		if (src.rows > src.cols) {
			wr = x / sina;
			hr = x / cosa;
		}
		else
		{
			wr = x / cosa;
			hr = x / sina;
		}

	}
	else {
		double cos2a = cosa*cosa - sina*sina;

		wr = (src.cols*cosa - src.rows*sina) / cos2a;
		hr = (src.rows*cosa - src.cols*sina) / cos2a;

	}
	
	/// Set the dst image the same type and size as src
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	// Set your 3 points to calculate the  Affine Transform
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(0.0, 0);
	dstTri[1] = Point2f(src.cols - 1, 0);
	dstTri[2] = Point2f(0, src.rows - 1);

	// Get the Affine Transform
	warp_mat = getAffineTransform(srcTri, dstTri);

	// Apply the Affine Transform just found to the src image
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/** Rotating the image after Warp */

	///// Compute a rotation matrix with respect to the center of the image
	//Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	//double angle = -50;
	//double scale = 1;

	/// Get the rotation matrix with the specifications above
	rot_mat = getRotationMatrix2D(center, angle, scale);





	/// Rotate the warped image
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
	//int width,xval;




	//width = floor(warp_rotate_dst.cols*((1 + 5*abs(cos(angle*PI / 180))) / 6));
	//xval = floor(warp_rotate_dst.cols*((5 - 5*abs(cos(angle*PI / 180))) / 12));
	//box.width = width ;
	//box.height = warp_rotate_dst.rows;
	////double dfs = 0.34 - abs( sin(angle*PI / 180))/3;
	//box.x = xval;
	//box.y = 0;

	//Mat crop(warp_rotate_dst, box);

	//warp_rotate_dst2 = crop;

	/// Show what you got
	namedWindow(source_window, WINDOW_NORMAL);
	imshow(source_window, src);

	//namedWindow(warp_window, WINDOW_NORMAL);
	//imshow(warp_window, warp_rotate_dst2);

	namedWindow(warp_rotate_window, WINDOW_NORMAL);
	imshow(warp_rotate_window, warp_rotate_dst);

	/// Wait until user exits the program
	waitKey(0);

	return 0;
}