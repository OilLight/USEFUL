#include "crossover_point_of_lines.h"

void findPerpendicularLine(Point2f input_point1, Point2f intput_point2, Point2f &output_point1, Point2f &output_point2)
{
    Point temp_point1=input_point1;
    Point temp_point2=intput_point2;

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
