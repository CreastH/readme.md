#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

class HSVBook
{
public:
	HSVBook(Mat &image);
	~HSVBook();

private:
	int histSize = 180;
	//define hue rang from 0-179
	float hueRanges[2] = { 0,180 };
	//define the saturation rang from 0-255
	//float saturationRange[2] = { 0,256 };
	const float* ranges[1] = { hueRanges};
	MatND dstHist;
	//ready to calc the 0,1 channel hist
	int channels =0 ;

	Mat hsv_image;

};	 

HSVBook::HSVBook(Mat &image)
{
	hsv_image = image;

	calcHist(&hsv_image,
		1,
		&channels,
		Mat(),
		dstHist,
		1,
		& histSize,
		ranges,
		true,
		false);

	//draw hist
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//seacher for the min
	int scale = 2;

	Mat histImage = Mat::zeros(histSize*scale, histSize * scale, CV_8UC3);

	//double loop
	for (int hue = 0; hue < histSize; hue++) 
		for (int saturation = 0; saturation < histSize; saturation++) {
			float binValue = dstHist.at<float>(hue, saturation);//hist bar number
			int intensity = cvRound(binValue * 255 / maxValue);//强度

			rectangle(histImage, Point(hue*scale, saturation*scale),
				Point((hue + 1)*scale - 1, (saturation + 1)*scale - 1),
				Scalar::all(intensity), FILLED);
		}

	imshow("H ALOGHITN", histImage);
}

HSVBook::~HSVBook()
{
}
