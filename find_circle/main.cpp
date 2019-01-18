/*
参与：林梓扬
注意事项：无

内容：鼠标确定三个点，过三个点找圆并画出
修改内容：无
*/
#include "perpendicular_line.h"
#include "crossover_point_of_lines.h"

int my_count=0;
bool flag=true;

vector<Point2f> mouse_points(3);
vector<Point2f> input_points;

Mat g_src_img;

void on_MouseHandle(int event, int x, int y, int flags, void* param);

int main()
{
    g_src_img=Mat(480, 640, CV_8UC3, Scalar(255,255,255));
    namedWindow("TEST");
    Point2f temp_input_point1,temp_input_point2,temp_output_point1,temp_output_point2;
    Point2f center_of_the_circle;

    //等待鼠标定好三个点
    for(;;)
    {
        imshow("TEST",g_src_img);
        setMouseCallback("TEST",on_MouseHandle);
        if(my_count>2) break;
        waitKey(1);
    }

    //寻找两条中垂线
    for(int i=0;i<2;++i)
    {
        temp_input_point1=mouse_points[i];
        temp_input_point2=mouse_points[i+1];

        findPerpendicularLine(temp_input_point1,temp_input_point2, temp_output_point1, temp_output_point2);

        input_points.push_back(temp_output_point1);
        input_points.push_back(temp_output_point2);
    }

    //寻找两条中垂线交点
    findCrossoverPointOfLines(input_points,center_of_the_circle);

    //以交点为圆心过三点画圆
    Point2f temp_point=mouse_points[1];
    double r=sqrt(pow((center_of_the_circle.x-temp_point.x),2)+pow((center_of_the_circle.y-temp_point.y),2));
    circle(g_src_img,center_of_the_circle,r,Scalar(0,0,255));

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
