#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    const string about =
        "This sample demonstrates Canny Image Processing.\n";

    const string keys = 
        "{ h help |      | print this help message }"
        "{ @image | vtest.avi | path to image file }";
    
    CommandLineParser parser(argc, argv, keys);
    parser.about(about);


    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }
    string filename = samples::findFile(parser.get<string>("@image"));
    if (!parser.check()){
        parser.printErrors();
        return 0;
    }
    VideoCapture cap("/home/josue/code/edge_detection/Minirover.mp4"); 
    // VideoCapture cap(0);
    
    // if(!stream1.isOpened()){
    // cout << "cannot open video file" << endl;
    // }

    while (true) {
        Mat blurredImage;
        Mat cannyImage;
        Mat cameraFrame;
        Mat houghImage;
        Mat cdstP;
        
        cap.read(cameraFrame);
        //imshow("Source Input", cameraFrame);

        cameraFrame = cameraFrame(Range(80,1000),Range(300,1620)); 
        //imshow("cropped", cameraFrame_cut);
        cdstP = cameraFrame.clone();
        GaussianBlur(cameraFrame, blurredImage, Size(9, 9), 0);
        //imshow("Gaussian Blur", blurredImage);
        cvtColor(cameraFrame, cannyImage, COLOR_BGR2GRAY);
        Canny( cannyImage, cannyImage, 1396, 973, 5 );
        imshow("Canny", cannyImage);
        
        std::vector<Vec4i> lines;
        HoughLinesP(cannyImage, lines, 1, CV_PI/180, 50, 30, 10 );
        for( size_t i = 0; i < lines.size(); i++ )
        {
        Vec4i l = lines[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
        imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);


        int keyboard = waitKey(30);
        if (keyboard = 'q' || keyboard == 27)
            break;
        }
return 0;
}
