#include <iostream>
#include "AnimatedPixel.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


cv::String folder = "/Users/eric/ClionProjects/PixelSort/images/";
cv::String folderAnimations = "/Users/eric/ClionProjects/PixelSort/animations/";

int AnimatedPixel::numIter;

bool comparePixel(const AnimatedPixel &L,
                  const AnimatedPixel &R) {
    return L.getH() < R.getH() ? true : L.getS() < R.getS() ? true : L.getV() < R.getV() ? true : false;
}

void animatePixel(std::vector<AnimatedPixel> &animatedPixels,
                  cv::Mat &image, int step) {

        for (auto a : animatedPixels) {
            auto i = rand() % 3;
            if (i == 0) {
                a.animateY(step);
                a.animateX(AnimatedPixel::numIter);
                image.at<cv::Vec3b>(a.getCurrentX(), a.getCurrentY()) =
                        cv::Vec3b(a.getH(),
                                  a.getS(),
                                  a.getV());
            }
            else if (i == 1) {
                a.animateY(AnimatedPixel::numIter);
                a.animateX(step);
                image.at<cv::Vec3b>(a.getCurrentX(), a.getCurrentY()) =
                        cv::Vec3b(a.getH(),
                                  a.getS(),
                                  a.getV());
            }
        }

        for (auto a : animatedPixels) {
            a.animate(step);
            image.at<cv::Vec3b>(a.getCurrentX(), a.getCurrentY()) =
                    cv::Vec3b(a.getH(),
                              a.getS(),
                              a.getV());
        }

}

int main() {
    auto t = clock();
    cv::Mat image;
    cv::String videoname = "IMG_0136";
    image = imread(folder + videoname + ".jpg", CV_LOAD_IMAGE_COLOR);

    int numIter = 200;

    AnimatedPixel::numIter = numIter;

    std::vector<AnimatedPixel> animatedPixels;

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            animatedPixels.push_back(AnimatedPixel(i, j,
                                                   int(pixel[0]),
                                                   int(pixel[1]),
                                                   int(pixel[2])));

        }
    }
    std::cout << "Time: " << clock() - t << std::endl;

    sort(animatedPixels.begin(), animatedPixels.end(), comparePixel);
    std::cout << "Time: " << clock() - t << std::endl;
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            animatedPixels[image.cols * i + j].setEndX(i);
            animatedPixels[image.cols * i + j].setEndY(j);
            animatedPixels[image.cols * i + j].update();
        }
    }
    std::cout << "Time: " << clock() - t << std::endl;

    cv::VideoWriter out_capture(folderAnimations + videoname + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), 30,
                                cv::Size(image.cols, image.rows));

    animatePixel(animatedPixels, image, numIter);

    for (int i = 0; i < 25; i++) {
        out_capture.write(image);
    }
    for (int i = numIter; i >= 0; --i) {
        animatePixel(animatedPixels, image, i);
        out_capture.write(image);
        if (i < 30) {
            out_capture.write(image);
            if (i < 10){
                out_capture.write(image);
            }
        }
        std::cout << "Iter: " << i + 1 << std::endl;
    }
    for (int i = 0; i < 35; i++) {
        out_capture.write(image);
    }

    std::cout << "Time: " << clock() - t << std::endl;

    system(("ffmpeg -i " + folderAnimations + videoname + ".avi -c:v libx264 -crf 23 -preset veryslow -c:a libfaac -b:a 192k -ac 2 "
                                                          + folderAnimations + videoname + ".mp4").c_str());

    system(("rm " + folderAnimations + videoname + ".avi").c_str());

    return 0;
}