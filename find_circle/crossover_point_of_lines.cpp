#include "crossover_point_of_lines.h"

void findCrossoverPointOfLines(vector<Point2f> &points,Point2f &output_point)
{
    Point temp_point1_1,temp_point1_2,temp_point2_1,temp_point2_2;
    temp_point1_1=points[0];
    temp_point1_2=points[1];
    temp_point2_1=points[2];
    temp_point2_2=points[3];

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

        output_point.x=xy_matrix.at<double>(0,0);
        output_point.y=xy_matrix.at<double>(0,1);

    }
    else
    {
        cout<<"Two lines are coincide."<<endl;
    }
}
