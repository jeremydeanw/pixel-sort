//
// Created by Eric Liu on 2/23/16.
//

#ifndef PIXELSORT_ANIMATEDPIXEL_H
#define PIXELSORT_ANIMATEDPIXEL_H
#include <cmath>
#include <vector>

class AnimatedPixel{

private:
    int startX, startY, endX, endY;
    int H, S, V;
    double xStep, yStep;
    double currentX, currentY;

public:


    AnimatedPixel() = default;

    AnimatedPixel(int startX, int startY, int H, int S, int V) : startX(startX), startY(startY), H(H), S(S), V(V) {
    };

    AnimatedPixel(const AnimatedPixel &obj);

    void animate(int stepNum);

    void animateX(int stepNum);

    void animateY(int stepNum);

    void update();

    static int numIter;

    void setEndX(int endX) {this->endX = endX;}
    void setEndY(int endY) {this->endY = endY;}

    int getH() const {return this->H;}
    int getS() const {return this->S;}
    int getV() const {return this->V;}
    int getCurrentX() const {return round(this->currentX);}
    int getCurrentY() const {return round(this->currentY);}
};

#endif //PIXELSORT_ANIMATEDPIXEL_H
