#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
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

	Mat gray_image;
	cvtColor(image, gray_image, CV_BGR2GRAY);


	imwrite("../gray_lena.jpg", gray_image);
	String window_name_2 = "Gray image";
	namedWindow(window_name_2, WINDOW_AUTOSIZE);
	imshow(window_name_2, gray_image);

	waitKey(0);

	imshow(window_name_1, image);
	imshow(window_name_2, gray_image);

	String window_name_3r = "Red image";
	String window_name_3g = "Green image";
	String window_name_3b = "Blue image";

	namedWindow(window_name_3r, WINDOW_AUTOSIZE);
	namedWindow(window_name_3g, WINDOW_AUTOSIZE);
	namedWindow(window_name_3b, WINDOW_AUTOSIZE);

	Mat color_layers[3];
	split(image, color_layers);

	imshow(window_name_3b, color_layers[0]);
	imshow(window_name_3g, color_layers[1]);
	imshow(window_name_3r, color_layers[2]);

	waitKey(0);

	return 0;
}
