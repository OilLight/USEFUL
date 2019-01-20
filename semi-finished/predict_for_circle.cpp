#include "predict_for_circle.h"

//输入点集（按顺序的3个点），圆的中心，圆的半径，输出的预测点
void predictPointOnCircle(vector<Point2f> &input_points, Point2f center_point, double r, Point2f &output_point)
{
    //直角坐标转化为以圆心为原点的极坐标
    Mat x = (Mat_<double>(1, 3) <<(input_points[0].x-center_point.x),(input_points[1].x-center_point.x),(input_points[2].x-center_point.x));
    Mat y = (Mat_<double>(1, 3) <<(input_points[0].y-center_point.y),(input_points[1].y-center_point.y),(input_points[2].y-center_point.y));
    Mat magnitude,angle;
    cartToPolar(x,y,magnitude,angle);

    //计算单步长角度增量
    double delta_theta[2];
    delta_theta[0]=(angle.at<double>(0,1)-angle.at<double>(0,0));
    delta_theta[1]=(angle.at<double>(0,2)-angle.at<double>(0,1));
    if(delta_theta[0]<0)
    {
        delta_theta[0]+=6.283184;
    }
    if(delta_theta[1]<0)
    {
        delta_theta[1]+=6.283184;
    }

    //预计下一步长增量
    double temp_angle=(delta_theta[0]+delta_theta[1])/2+angle.at<double>(0,2);

    if(temp_angle>=6.283184)
    {
        temp_angle-=6.283184;
    }

    //推算下一个点相对角度，结合圆的半径转换为直角坐标系
    Mat predict_angle=Mat_<double>(1,1)<<temp_angle;
    Mat predict_magnitude=Mat_<double>(1,1)<<r;
    Mat predict_x_img,predict_y_img;
    polarToCart(predict_magnitude,predict_angle,predict_x_img,predict_y_img);

    double predict_x=predict_x_img.at<double>(0,0);
    double predict_y=predict_y_img.at<double>(0,0);
    predict_x+=center_point.x;
    predict_y+=center_point.y;

    output_point.x=predict_x;
    output_point.y=predict_y;

}
