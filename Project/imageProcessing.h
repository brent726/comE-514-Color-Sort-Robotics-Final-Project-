

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include "cxcore.h"
#include "robotMove.h"

void captureImage();

IplImage* convertImageRGBtoHSV(const IplImage *imageRGB);

void mouseEvent(int event, int x, int y, int flags, void * param);

int RGBColorOutput(int aveR, int aveG, int aveB);

void evaluateColor(const IplImage *imageRGB,int * color);
