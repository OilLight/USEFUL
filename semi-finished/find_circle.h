#ifndef FIND_CIRCLE_H
#define FIND_CIRCLE_H

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

void findPerpendicularLine(Point2f intput_point1,Point2f intput_point2,Point2f &output_point1,Point2f &output_point2);
void findCrossoverPointOfLines(vector<Point2f> &input_points, Point2f &output_point);
void findCircle(vector<Point2f> &input_points, Point2f &center_point, double &r);

#endif // FIND_CIRCLE_H
