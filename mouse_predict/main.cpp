/*
参与：林梓扬
注意事项：用识别出的坐标代替鼠标坐标调参后即可投入使用

内容：卡尔曼滤波（非线性情况）鼠标画点实验
第几次修改：第一次
修改内容：状态向量改为4维，加入速度预测解决二维情况下震荡问题。更改了死区参数，系统过程噪声矩阵。
*/

#include "kalman.h"

#define ANTI_RANGE 1.7
#define DEAD_BAND 10


using namespace std;
using namespace cv;
using namespace kalman;


Point2f g_predict_pt;

Mat measurement;
Mat control;

float g_runtime;
int g_x_widht = 0;
int g_y_height = 0;

Point2f g_current_point;

void on_MouseHandle(int event, int x, int y, int flags, void* param);
//void Init_Kalman(KalmanFilter kalman, int x, int y);
//void My_Predict(KalmanFilter kkalman, Mat measurement, Point2f predict_pt);


int main()
{
    Mat src_img(480, 640, CV_8UC3, Scalar(255,255,255));
    kalman::KalmanFilter kalman(g_x_widht, g_y_height);

    measurement = Mat::zeros(4, 1, CV_32F);
    //control = Mat::zeros(2, 1, CV_32F);

    g_current_point = Point2f(g_x_widht, g_y_height);
    Point2f last_point;
    Point2f kalman_point(g_x_widht, g_y_height);
    Point2f anti_kalman_point(g_x_widht, g_y_height);



    float size_x = 640;//cols of side
    float size_y = 480;//rows of side
    int color = 0;//gradually varied color

    //Init_Kalman(kalman, X_Widht, Y_height);
    for (;;)
    {
        g_runtime = static_cast<float>(getTickCount());

        setMouseCallback("test", on_MouseHandle);
        kalman_point = kalman.point_Predict(last_point, g_current_point);

        float temp_x=g_current_point.x + ANTI_RANGE*(g_current_point.x - kalman_point.x);
        float temp_y=g_current_point.y + ANTI_RANGE*(g_current_point.y - kalman_point.y);

        if ( temp_x <= size_x && temp_x >= 0)//防止预测点出屏
        {
            if (abs(g_current_point.x - kalman_point.x) > DEAD_BAND)//死区设置
            {
                anti_kalman_point.x = temp_x;
            }
            else
            {
                anti_kalman_point.x = g_current_point.x;
            }
        }
        else
        {
            anti_kalman_point.x = g_current_point.x;
        }

        if (temp_y <= size_y && temp_y >= 0)//防止预测点出屏
        {
            if (abs(g_current_point.y - kalman_point.y) > DEAD_BAND)//死区设置
            {
                anti_kalman_point.y =temp_y;
            }
            else
            {
                anti_kalman_point.y = g_current_point.y;
            }
        }
        else
        {
            anti_kalman_point.y = g_current_point.y;
        }

        last_point = g_current_point;

        circle(src_img, anti_kalman_point, 3, Scalar(0, 255, 0 + color), 2);
        circle(src_img, g_current_point, 3, Scalar(255, 0, 0 + color), 2);

        cout << "latst x:" << g_current_point.x << "  latest y:" << g_current_point.y << endl;
        cout << "predict x:" << anti_kalman_point.x << "  predict y:" << anti_kalman_point.y << endl;

        imshow("test", src_img);
        src_img.setTo(Scalar(255, 255, 255, 0));
        g_runtime = ((float)getTickCount() - g_runtime) / getTickFrequency();
        if (waitKey(1) == ' '){ src_img.setTo(Scalar(255, 255, 255, 0)); }
        if (waitKey(1) == 27)
        {
            break;
        }
    }
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
    //鼠标移动消息
    if (event == EVENT_MOUSEMOVE)
    {
        g_current_point = Point(x, y);
        g_x_widht = x;
        g_y_height = y;
    }

}



