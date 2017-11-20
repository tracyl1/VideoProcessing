#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "opencv.hpp"
#include "videoio.hpp"
#include "highgui.hpp"

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat frame;
	VideoCapture cap;
	cap.open("video.avi");
	cap.read(frame);
	imshow("Frame", frame);
	waitKey(0);
}
