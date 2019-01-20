#include "find_circle.h"

void findPerpendicularLine(Point2f input_point1,Point2f input_point2,Point2f &output_point1,Point2f &output_point2)
{
    Point2f temp_point1=input_point1;
    Point2f temp_point2=input_point2;

        double distance;
        double r;
        double A1,B1,C1;
        double A2,B2,C2;
        double A,B,C;
        double a,b,c;
        double x1,y1,x2,y2;

        distance=sqrt(pow(abs(temp_point1.x-temp_point2.x),2) + pow(abs(temp_point1.y-temp_point2.y),2));
        r=0.75*distance;

        //将函数展开成一般形式并相减，得出一个二元一次方程的x项系数，y项系数，常数项
        A1=-2*temp_point1.x;
        B1=-2*temp_point1.y;
        C1=pow(temp_point1.x,2)+pow(temp_point1.y,2);
        A2=-2*temp_point2.x;
        B2=-2*temp_point2.y;
        C2=pow(temp_point2.x,2)+pow(temp_point2.y,2);
        A=A1-A2;
        B=B1-B2;
        C=C1-C2;

        //分类讨论，A或B为0时可直接得出y或x的值
        if(A==0)
        {
            y1=y2=-C/B;
            double temp=sqrt(pow(r,2)-pow((y1-temp_point1.y),2));
            x1=temp+temp_point1.x;
            x2=-temp+temp_point1.x;
        }
        else if(B==0)
        {
            x1=x2=-C/A;
            double temp=sqrt(pow(r,2)-pow((x1-temp_point1.y),2));
            y1=temp+temp_point1.y;
            y2=-temp+temp_point1.y;
        }
        //A，B不为零时将二元一次方程带回其中一个圆的函数，然后求解一元二次方程得出x或y，再代回二元一次方程求出点
        else
        {
            double temp1=-B/A;
            double temp2=-C/A-temp_point1.x;

            a=pow(temp1,2)+1;
            b=2*temp1*temp2-2*temp_point1.y;
            c=pow(temp2,2)+pow(temp_point1.y,2)-pow(r,2);

            double delta=sqrt((pow(b,2)-(4*a*c)));

            y1=(-b+delta)/(2*a);
            y2=(-b-delta)/(2*a);
            x1=-(B*y1+C)/A;
            x2=-(B*y2+C)/A;
          }
        output_point1.x=x1;
        output_point1.y=y1;
        output_point2.x=x2;
        output_point2.y=y2;
}


void findCrossoverPointOfLines(vector<Point2f> &input_points, Point2f &output_point)
{
    Point temp_point1_1,temp_point1_2,temp_point2_1,temp_point2_2;
    temp_point1_1=input_points[0];
    temp_point1_2=input_points[1];
    temp_point2_1=input_points[2];
    temp_point2_2=input_points[3];

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

//输入点集（按顺序的3个点），输出的圆的中心，圆的半径
void findCircle(vector<Point2f> &input_points,Point2f &center_point,double &r)
{
    Point2f temp_input_point1,temp_input_point2,temp_output_point1,temp_output_point2;
    vector<Point2f> temp_points;
    Point2f temp_point=input_points[1];

    //寻找两条中垂线
    for(int i=0;i<2;++i)
    {
        temp_input_point1=input_points[i];
        temp_input_point2=input_points[i+1];

        findPerpendicularLine(temp_input_point1,temp_input_point2, temp_output_point1, temp_output_point2);

        temp_points.push_back(temp_output_point1);
        temp_points.push_back(temp_output_point2);
    }

    //寻找两条中垂线交点
    findCrossoverPointOfLines(temp_points,center_point);

    //计算半径
    r=sqrt(pow((center_point.x-temp_point.x),2)+pow((center_point.y-temp_point.y),2));
}
