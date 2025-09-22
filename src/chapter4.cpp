#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>

int main()
{
    // Blank Image
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::circle(img, cv::Point(256,256), 155, cv::Scalar(0, 69, 255), cv::FILLED);
    cv::rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255,255,255), cv::FILLED);
    line(img, cv::Point(130,296), cv::Point(382,450), cv::Scalar(255,255,255), 2);

    putText(img, "Murtaza's Workshop", cv::Point(137,262), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.75, cv::Scalar(0, 69, 255), 2);

    cv::imshow("Image" , img);
    cv::waitKey(0);
}