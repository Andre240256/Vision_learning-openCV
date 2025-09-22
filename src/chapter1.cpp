#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>



//image
// int main()
// {
//     std::string path = "Resources/test.png";

//     std::string complete_path = std::filesystem::current_path().string() + "/" + path;
//     std::cout << "Current path is: " << complete_path << std::endl;

//     cv::Mat img = cv::imread(path);
//     cv::imshow("Image", img);
//     cv::waitKey(0);

//     return 0;
// }

//video
// int main()
// {
//     std::string path = "Resources/test_video.mp4";
//     cv::VideoCapture cap(path);
//     cv::Mat img;

//     while(true)
//     {
//         cap.read(img);

//         cv::imshow("image", img);
//         cv::waitKey(20);
//     }

//     return 0;
// }

//webcam
int main()
{
    cv::VideoCapture cap(0);
    cv::Mat img;

    while(true)
    {
        cap.read(img);

        cv::imshow("image", img);
        cv::waitKey(1);
    }

    return 0;
}
