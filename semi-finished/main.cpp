/*
参与：林梓扬
注意事项：该main为找圆和预测圆上的点的两个函数的历程。
        使用两个函数需要包含该cpp包含的两个头文件和对应cpp。
        另外预测函数为半成品，未加入卡尔曼滤波。
        默认步恒定

内容：鼠标取三个点（蓝点），找出过三个点的圆（红圈）并推测下一个点在圆上的位置（绿点）
第几次修改：无修改
修改内容：无
*/
#include "find_circle.h"
#include "predict_for_circle.h"

int my_count=0;
bool flag=true;

vector<Point2f> mouse_points(3);

Mat g_src_img;

void on_MouseHandle(int event, int x, int y, int flags, void* param);

int main()
{
    g_src_img=Mat(480, 640, CV_8UC3, Scalar(255,255,255));

    //等待鼠标选出三个点
    for(;;)
    {
        imshow("TEST",g_src_img);
        setMouseCallback("TEST",on_MouseHandle);
        if(my_count>2) break;
        waitKey(1);
    }

    Point2f center_point,predict_point;
    double r;
    //根据3个点找圆
    findCircle(mouse_points,center_point, r);
    //根据三个点在圆上的位置推测下一个点
    predictPointOnCircle(mouse_points,center_point,r,predict_point);

    circle(g_src_img,center_point,3,Scalar(255,0,255),-1);
    circle(g_src_img,predict_point,5,Scalar(0,255,0),-1);
    circle(g_src_img,center_point,r,Scalar(0,0,255));
    imshow("TEST",g_src_img);
    waitKey();
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
  {
      //鼠标移动消息
      if (event == EVENT_LBUTTONUP)
      {
          if(my_count<=2)
          {
               mouse_points[my_count] = Point(x, y);
               circle(g_src_img, Point(x,y), 4, Scalar(255,0,0), -1);
               ++my_count;
          }
      }

  }

