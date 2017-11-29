#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "opencv.hpp"
#include "core.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "imgcodecs.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open("video.avi");
	for(int i = 0; i < 30; i++)
	{
		Mat frame
		cap.read(frame);
		namedWindow("Frame-by-frame", WINDOW_AUTOSIZE);
		imshow("Frame-by-frame", frame);
		waitKey(0);
	}
	return 0;
}
