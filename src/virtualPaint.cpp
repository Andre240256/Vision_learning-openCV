#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>


//functions declarations
std::vector<cv::Mat> findColour(cv::Mat& img);
void calibrateColor(cv::VideoCapture& cap);
std::vector<std::vector<cv::Point>> findContours(cv::Mat& img);



//global variables
std::vector<std::vector<int>> myColors {{0, 134, 63, 4, 255, 112},
                                        {111, 103, 0, 127, 171, 111},
                                        {24, 42, 41, 55, 255, 255}}; //hmin, smin, vmin, hmax, smax, vmax
std::vector<cv::Scalar> myColorValues {{0,0,255},
                                        {255, 0 ,0},
                                        {255,255,255}}; //BGR values
std::vector<std::pair<cv::Point, int>> coloredPoints;

int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    cv::Mat imgInverted;
    std::vector<std::vector<cv::Point>> contours;
    
    
    // calibrateColor(cap);
    
    while(true)
    {
        cap.read(img);

        std::vector<cv::Mat> masks = findColour(img);
        for (int j = 0; j < masks.size(); j++)
        {
            contours = findContours(masks[j]);
            std::vector<std::vector<cv::Point>> conPoly(contours.size());
            std::vector<cv::Rect> boundRect(contours.size());


            for (int i = 0; i < contours.size(); i++)
            {
                if (cv::contourArea(contours[i]) > 2000) 
                {
                    double peri = cv::arcLength(contours[i], true);
                    cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

                    boundRect[i] = cv::boundingRect(conPoly[i]);


                    cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 2);
                    cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 3);
                    cv::circle(img, cv::Point(boundRect[i].tl().x + boundRect[i].width/2, boundRect[i].tl().y), 15, myColorValues[j], cv::FILLED);

                    coloredPoints.push_back({cv::Point(boundRect[i].tl().x + boundRect[i].width/2, boundRect[i].tl().y), j});
                }
            }
    }

    for(int i = 0; i < coloredPoints.size(); i++)
    {
        cv::circle(img, coloredPoints[i].first, 10, myColorValues[coloredPoints[i].second], cv::FILLED);
    }
        cv::flip(img, imgInverted, 1);
        cv::imshow("image inverted", imgInverted);
        cv::waitKey(1);
    }

    return 0;
}

std::vector<std::vector<cv::Point>> findContours(cv::Mat& img)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::Mat imgBlur, imgCanny, imgDil;

    cv::GaussianBlur(img, imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    return contours;
}

            
std::vector<cv::Mat> findColour(cv::Mat& img)
{
    cv::Mat imgHSV;
    std::vector<cv::Mat> mask(myColors.size());
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    for(int i =0; i< myColors.size(); i++)
    {
        cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        cv::inRange(imgHSV, lower, upper, mask[i]);
    }

    return mask;
}


void calibrateColor(cv::VideoCapture& cap)
{
    int hmin =0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    cv::Mat img;
    cv::Mat imgHSV;
    cv::Mat mask;
    
    cv::namedWindow("Trackers", (640,200));
    cv::createTrackbar("Hue Min", "Trackers", &hmin, 179);
    cv::createTrackbar("Hue Max", "Trackers", &hmax, 179);
    cv::createTrackbar("Sat Min", "Trackers", &smin, 255);
    cv::createTrackbar("Sat Max", "Trackers", &smax, 255);
    cv::createTrackbar("Val Min", "Trackers", &vmin, 255);
    cv::createTrackbar("Val Max", "Trackers", &vmax, 255);

    while(true)
    {
        cap.read(img);
        cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("image", img);
        cv::imshow("mask", mask);
        cv::waitKey(1);
    }

}
