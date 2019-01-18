#ifndef KALMAN_H
#define KALMAN_H


#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <math.h>

using namespace std;
using namespace cv;

extern float g_runtime;

namespace kalman
{

    class KalmanFilter
    {
    public:
        KalmanFilter(int x, int y) :
            kalman_img(4, 4)//状态向量和测量向量都是4维。板不受控制，无控制向量，为默认0维
        {
            measurement_img = Mat::zeros(4, 1, CV_32F);
            kalman_img.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, g_runtime, 0,  //下一步长的计算值为当前坐标加上当前速度乘以步长
                                                                0, 1, 0, g_runtime,
                                                                0, 0, 1, 0,
                                                                0, 0, 0, 1);
            setIdentity(kalman_img.measurementMatrix, Scalar::all(1));//测量值也是坐标，不需要线性的变化
            setIdentity(kalman_img.processNoiseCov, Scalar::all(1e-2));//过程噪声，w(k)，更大会有更慢的回归
            setIdentity(kalman_img.measurementNoiseCov, Scalar::all(1e-1));//测量噪声，v(k),更大会有更快的回归
            setIdentity(kalman_img.errorCovPost, Scalar::all(1)); //后验协方差矩阵P，设为无，方便迭代

            kalman_img.statePost = (Mat_<float>(4, 1) << x, y, 0, 0);//后验更新值(迭代起点)
        }

        Point2f point_Predict(Point2f last_Point, Point2f current_Point)
        {
            /*Mat prediction = kalman_img.predict();*/

            measurement_img.at<float>(0, 0) = current_Point.x;
            measurement_img.at<float>(1, 0) = current_Point.y;
            measurement_img.at<float>(2, 0) = (current_Point.x - last_Point.x) / g_runtime;
            measurement_img.at<float>(3, 0) = (current_Point.y - last_Point.y) / g_runtime;

            Mat prediction =kalman_img.predict();//至此完成了对下一帧单纯计算的预测，得出的点更加平稳。如果保证测量值够准，可以直接取这里算出的点
            kalman_img.correct(measurement_img);//至此完成了对下一帧的最优估计，得出的点理论上更接近真实值。同时用于迭代，得出statePost供下一帧predict计算
            Point2f predict_pt = Point2f(prediction.at<float>(0), prediction.at<float>(1));

            return predict_pt;
        }

    private:
        Mat measurement_img;//测量矩阵
        cv::KalmanFilter kalman_img;

    };
}
#endif // KALMAN_H
