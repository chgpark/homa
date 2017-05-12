#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int ac, char **av)
{
	Mat	image;
	Mat	gray_image;
	Mat	gaus_image;
	Mat	gaus1_image;
	int	i;

	image = imread(av[1], CV_LOAD_IMAGE_COLOR);
//	cout << image.cols << endl << image.rows << endl;
	cvtColor(image, gray_image, CV_BGR2GRAY);
	i = 1;
	while (i < 50)
	{
		GaussianBlur(image, gaus_image, Size(i, i), 0, 0);
		i += 2;
	}
	i = 1;
	while (i < 50)
	{
		GaussianBlur(gray_image, gaus1_image, Size(i, i), 0, 0);
		i += 2;
	}
	i = -1;
	while (gray_image.data[++i])
		image.data[3 * i] = gray_image.data[i] - image.data[3 * i];
	imshow("hey", gaus_image);
	imshow("hey1", gaus1_image);
	imshow("hey2", image);
//	namedWindow("hey", WINDOW_AUTOSIZE);
//	imshow("hey", image);

	waitKey(0);
	return 0;
}
