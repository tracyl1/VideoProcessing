#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "opencv.hpp"
#include "core.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "features2d.hpp"
#include "xfeatures2d.hpp"
#include "imgcodecs.hpp"

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int, char**)
{
	Mat frame1;
	Mat frame2;
	VideoCapture cap;
	cap.open("video.avi");
	cap.read(frame1);
	cap.read(frame2);
	
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create();
	detector->setHessianThreshold(minHessian);
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;
	detector->detectAndCompute(frame1, Mat(), keypoints_1, descriptors_1);
	detector->detectAndCompute(frame2, Mat(), keypoints_2, descriptors_2);
	std::ofstream output_file1("position_vector1", std::ios::binary);
	std::ofstream output_file2("position_vector2", std::ios::binary);

	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);
	double max_dist = 0;
	double min_dist = 100;

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	std::vector<DMatch> good_matches;
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 0.02))
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(frame1, keypoints_1, frame2, keypoints_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("Good Matches", img_matches);
	for (int i = 0; i < (int)good_matches.size(); i++)
	{
		printf("-- Good Match [%d] Keypoint 1: %d -- Keypoint 2: %d \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	}
	waitKey(0);
	return 0;
}
