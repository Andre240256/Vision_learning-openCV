#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>
#include <opencv2/objdetect.hpp>



int main()
{
    cv::VideoCapture cap(0);


    cv::Mat img;
    
    cv::CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
    
    if(plateCascade.empty())
    {
        std::cout << "XML file not loaded" << std::endl;
        return -1;
    }

    std::vector<cv::Rect> plates;
    while(true)
    {
        cap.read(img);

        plateCascade.detectMultiScale(img, plates, 1.1, 10);

        for(int i = 0; i< plates.size(); i++)
        {
            cv::Mat imgCrop = img(plates[i]);
            // cv::imshow(std::to_string(i), imgCrop);
            cv::imwrite("Resources/Plates/plate_" + std::string(std::to_string(i)) + ".jpg", imgCrop);
            cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(255, 0 ,255), 3);
        }
        
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
    return 0;
}