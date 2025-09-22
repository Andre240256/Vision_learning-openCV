#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>

float w = 250, h = 350;
cv::Mat matrix, imgWarp;



//Warp Images

int main()
{
    std::string path = "Resources/cards.jpg";
    cv::Mat img = cv::imread(path);

    cv::Point2f src [4] = {
        {529,142}, {771,190}, {405,395}, {674,457}
    };
    cv::Point2f dst [4] = {
        {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w,h}
    };

    matrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(img, imgWarp, matrix, cv::Point(w,h));

    for(int i  =0 ; i<4; i++)
    {
        cv::circle(img, src[i], 10, cv::Scalar(0,0,255), cv::FILLED);
    }
   
    cv::imshow("Image" , img);
    cv::imshow("Image Warp" , imgWarp);
    cv::waitKey(0);
}