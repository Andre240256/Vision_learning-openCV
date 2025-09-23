#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>


//functions declarations
cv::Mat preprocessingImg(cv::Mat img);
std::vector<cv::Point> findPoly(cv::Mat mask);
cv::Mat warpImg(cv::Mat img, std::vector<cv::Point> points);



int main()
{
    std::string path = "Resources/paper.jpg";
    cv::Mat img = cv::imread(path);
    if(img.empty()){
        std::cout<<"image not found"<<std::endl;
        return -1;
    }
    cv::resize(img, img, cv::Size(), 0.5, 0.5);
    
    cv::Mat mask = preprocessingImg(img);
    
    std::vector<cv::Point> biggestContour = findPoly(mask);
    if(biggestContour.size() == 0){
        std::cout<<"no contour found"<<std::endl;
        return -1;
    }
    
    // std::vector<std::vector<cv::Point>> biggestContourVector = {biggestContour};
    // cv::drawContours(img, biggestContourVector, -1, cv::Scalar(0, 255, 0), 4);
    // cv::circle(img, biggestContour[2], 10, cv::Scalar(255, 0, 255), cv::FILLED);

    cv::Mat warpedImg = warpImg(img, biggestContour);

    //crop
    int cropval = 10;
    cv::Rect roi(cropval, cropval, warpedImg.size().width - cropval*2, warpedImg.size().height - cropval*2);
    warpedImg = warpedImg(roi);

    cv::imshow("Warped Image", warpedImg);
    // cv::imshow("Image", img);
    // cv::imshow("Mask", mask);
    cv::waitKey(0);
    
    return 0;
}



//functions implementations
cv::Mat preprocessingImg(cv::Mat img)
{
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);
    
    return imgDil;
}

std::vector<cv::Point> findPoly(cv::Mat mask)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    int areaMax = 0;
    int j = 0;

    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if(contours.size() == 0){
        std::cout<<"no contours found"<<std::endl;
        return {};
    }

    std::vector<std::vector<cv::Point>> conPoly(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(contours[i], conPoly[i], 0.02*cv::arcLength(contours[i], true), true);
        
        if(cv::contourArea(conPoly[i])> areaMax  && conPoly[i].size() == 4){
            areaMax = cv::contourArea(conPoly[i]);
            j = i;
        }
    }
    return conPoly[j];
}

cv::Mat warpImg(cv::Mat img, std::vector<cv::Point> points)
{
    int w = img.size().width;
    int h = img.size().height;
    cv::Point2f src[4] = {points[0], points[3], points[1], points[2]};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {float(w), 0.0f}, {0.0f, float(h)}, {float(w), float(h)}};
    
    cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
    cv::Mat imgWarp;
    cv::warpPerspective(img, imgWarp, matrix, cv::Size(w, h));
    
    return imgWarp;
}