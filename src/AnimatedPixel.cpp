//
// Created by Eric Liu on 2/23/16.
//
#include <iostream>
#include "AnimatedPixel.h"

AnimatedPixel::AnimatedPixel(const AnimatedPixel &obj):
        startX(obj.startX), startY(obj.startY), endX(obj.endX),
        endY(obj.endY), H(obj.H), S(obj.S), V(obj.V), xStep(obj.xStep),
        yStep(obj.yStep), currentX(obj.currentX), currentY(obj.currentY)
{}

void AnimatedPixel::animate(int stepNum){
    animateX(stepNum); animateY(stepNum);
}

void AnimatedPixel::animateX(int stepNum){
    this->currentX += xStep * stepNum;
}

void AnimatedPixel::animateY(int stepNum){
    this->currentY += yStep * stepNum;
}

void AnimatedPixel::update(){
    this->xStep = (endX - startX) / double(numIter);
    this->yStep = (endY - startY) / double(numIter);
    this->currentX = startX;
    this->currentY = startY;
}
