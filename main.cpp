#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    /* Try to open the video: */
    if (!cap.open(0))
    {
        cout << "Cannot open the video stream!" << endl;
    }

    /* Create a background subtractor: */
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
    Ptr<BackgroundSubtractorKNN> fgbg = createBackgroundSubtractorKNN();
    /* Loop for image processing: */
    Mat frame, mask;
    while(true)
    {
        cap.read(frame);
        fgbg->apply(frame, mask);
        morphologyEx(mask, mask, MORPH_OPEN, kernel);
        imshow("Result", mask);
        int k = waitKey(1);
        if (k == 27)
        {
           break;
        }
    }
    return 0;
}
