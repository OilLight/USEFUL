/*
参与：林梓扬
注意事项：无

内容：输入个两点，求中垂线（两个点）
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

  Point temp_point1,temp_point2;
  double distance;
  double r;
  double A1,B1,C1;
  double A2,B2,C2;
  double A,B,C;
  double a,b,c;
  double x1,y1,x2,y2;


//  for(int i=0;i>3;++i)
//  {
//      temp_point1=points[i];
//      temp_point2=points[i+1];
      temp_point1=Point(325,216);
      temp_point2=Point(230,400);
      circle(src_img, temp_point1, 1, Scalar(255, 0, 0), -1);
      circle(src_img, temp_point2, 1, Scalar(0, 0, 255), -1);


      distance=sqrt(pow(abs(temp_point1.x-temp_point2.x),2) + pow(abs(temp_point1.y-temp_point2.y),2));
      r=0.75*distance;
      circle(src_img, temp_point1, r, Scalar(255, 0, 0), 2);
      circle(src_img, temp_point2, r, Scalar(0, 0, 255), 2);


      cout<<r<<endl;

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

      cout<<"A:"<<A<<" "<<"B:"<<B<<" "<<"C:"<<C<<" "<<endl;

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
          cout<<"temp1:"<<temp1<<endl;
          cout<<"temp2:"<<temp2<<endl;


          a=pow(temp1,2)+1;
          b=2*temp1*temp2-2*temp_point1.y;
          c=pow(temp2,2)+pow(temp_point1.y,2)-pow(r,2);

          cout<<"a:"<<a<<" "<<"b:"<<b<<" "<<"c:"<<c<<" "<<endl;


          double delta=sqrt((pow(b,2)-(4*a*c)));
          cout<<delta<<endl;



          y1=(-b+delta)/(2*a);
          y2=(-b-delta)/(2*a);
          x1=-(B*y1+C)/A;
          x2=-(B*y2+C)/A;

      }

      circle(src_img, Point(x1,y1), 3, Scalar(0,255,0), -1);
      circle(src_img, Point(x2,y2), 3, Scalar(0,255,0), -1);

      //line(src_img,Point(x1,y1),Point(x2,y2),Scalar(0,255,0),3,8);
      cout<<"x1:"<<x1<<" "<<"y1:"<<y1<<endl;
      cout<<"x2:"<<x2<<" "<<"y2:"<<y2<<endl;

      imshow("TEST",src_img);
      waitKey()==27;
      return 0;
//  }
}
