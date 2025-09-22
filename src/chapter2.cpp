#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>

int main()
{
    std::string path = "Resources/test.png";
    cv::Mat img = cv::imread(path);
    cv::Mat imgResize;
    cv::Mat imgCrop;

    std::cout << img.size() << std::endl;
    cv::resize(img, imgResize,cv::Size(), 0.5, 0.5);

    cv::Rect roi(0,0,300,250);
    imgCrop = img(roi);

    cv::imshow("Image" , img);
    cv::imshow("Image Crop", imgCrop);

    cv::waitKey(0);
}