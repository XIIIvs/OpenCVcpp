#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage, Mat& Result)
{
	CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

	Result.create(myImage.size(), myImage.type());
	const int nChannels = myImage.channels();

	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);

		for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}

	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}
	Mat image;
	image = imread(argv[1], IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	String window_name_1 = "Colored image";
	namedWindow(window_name_1, WINDOW_AUTOSIZE); // Create a window for display.
	imshow(window_name_1, image); // Show our image inside it.

	Mat sharpen, blured, kernel;
	Point anchor = Point(-1, -1);
	int ddepth = -1;

	Sharpen(image, sharpen);

	int kernel_size = 13;
	kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
	filter2D(image, blured, ddepth, kernel, anchor, 0, BORDER_DEFAULT);

	String window_name_sharp = "Sharp image";
	String window_name_blur = "Blur image";
	namedWindow(window_name_sharp, WINDOW_AUTOSIZE);
	namedWindow(window_name_blur, WINDOW_AUTOSIZE);

	imshow(window_name_sharp, sharpen);
	imshow(window_name_blur, blured);

	waitKey(0);

	return 0;
}
