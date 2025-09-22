#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>

cv::Mat imgGray;
cv::Mat imgBlur;
cv::Mat imgCanny;
cv::Mat imgDil;
cv::Mat imgErod;

void getContours(cv::Mat imgDil, cv::Mat img)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::string objectType;
    
    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 4);
    
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    for(int i = 0; i<  contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        std::cout<< area << std::endl;
        if(area > 1000)
        {
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);

            int objCor = (int)conPoly[i].size();
            
            if(objCor == 3){
                objectType = "Tri";
            }
            else if (objCor == 4){
                double ratio = (double)boundRect[i].width / (double)boundRect[i].height;
                if(ratio > 0.95 && ratio < 1.05)
                    objectType = "Square";
                else
                    objectType = "Rect";
            }
            else{
                objectType = "Circle";
            }
            
            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
            cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 4);
            cv::putText(img, objectType,{ boundRect[i].x, boundRect[i].y-5}, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(0, 69, 255), 1);
        }
    }
}


int main()
{
    std::string path = "Resources/shapes.png";
    cv::Mat img = cv::imread(path);

    //preprocessing img
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    cv::imshow("Image" , img);
    // cv::imshow("Image Gray" , imgGray);
    // cv::imshow("Image Blur" , imgBlur);
    // cv::imshow("Image Canny" , imgCanny);
    // cv::imshow("Image Dil" , imgDil);
    cv::waitKey(0);

    return 0;
}
