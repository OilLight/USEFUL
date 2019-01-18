#ifndef CROSSOVER_POINT_OF_LINES_H
#define CROSSOVER_POINT_OF_LINES_H

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

void findCrossoverPointOfLines(vector<Point2f> &input_points, Point2f &output_point);


#endif // CROSSOVER_POINT_OF_LINES_H
