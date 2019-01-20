#ifndef PREDICT_FOR_CIRCLE_H
#define PREDICT_FOR_CIRCLE_H

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

void predictPointOnCircle(vector<Point2f> &input_points,Point2f center_point,double r,Point2f &output_point);

#endif // PREDICT_FOR_CIRCLE_H
