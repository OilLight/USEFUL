/*
参与：林梓扬
注意事项：无

内容：输入确定两条直线的四个点，求两直线交点
修改内容：无
*/

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main()
{
    Mat src_img(480, 640, CV_8UC3, Scalar(255,255,255));

    Point temp_point1_1,temp_point1_2,temp_point2_1,temp_point2_2;
    temp_point1_1=Point(233,300);
    temp_point1_2=Point(100,400);
    temp_point2_1=Point(500,260);
    temp_point2_2=Point(600,400);

    double A1,B1,A2,B2,C1,C2;
    A1=temp_point1_2.y-temp_point1_1.y;
    B1=temp_point1_1.x-temp_point1_2.x;
    C1=temp_point1_2.x*temp_point1_1.y-temp_point1_2.y*temp_point1_1.x;
    A2=temp_point2_2.y-temp_point2_1.y;
    B2=temp_point2_1.x-temp_point2_2.x;
    C2=temp_point2_2.x*temp_point2_1.y-temp_point2_2.y*temp_point2_1.x;

    Mat ab_matrix = (Mat_<double>(2, 2) << A1,B1,A2,B2);//两条直线的系数矩阵2*
    if(determinant(ab_matrix)!=0)
    {
        Mat c_matrix = (Mat_<double>(2, 1) << -C1,-C2);//两条直线的C参数矩
        Mat xy_matrix = (Mat_<double>(2, 1));//两条直线的交点坐标矩阵2*1
        xy_matrix = ab_matrix.inv()*c_matrix;
        line(src_img,temp_point1_1,temp_point1_2,Scalar(255,0,0),2,8);
        line(src_img,temp_point2_1,temp_point2_2,Scalar(0,0,255),2,8);

        circle(src_img,Point(xy_matrix.at<double>(0,0),xy_matrix.at<double>(0,1)),2,Scalar(0,255,0),-1,8);
        imshow("TEST",src_img);
    }

    else
    {
        cout<<"Two lines are Coincidence."<<endl;
    }

    waitKey();
}
