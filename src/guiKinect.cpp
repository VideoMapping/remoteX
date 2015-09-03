#include "guiKinect.h"

void GuiKinect::setup(){
    kinectParameters.add(gKtoggleOnOff.set("Kinect  On/Off",false));
    kinectParameters.add(gKtoggleLoad.set("Load Kinect ",false));
    kinectParameters.add(gKtoggleShowImage.set("Kinect show image",false));
    kinectParameters.add(gKtoggleGrayscale.set("Kinect grayscale",false));
    kinectParameters.add(gKtoggleMask.set("Kinect mask",false));
    kinectParameters.add(gKtoggleDetect.set("Kinect detect",false));
    kinectParameters.add(gK2SliderScale.set("Scale Kinect ",ofVec2f(1,1), ofVec2f(0.1, 0.1), ofVec2f(10,10)));
    kinectParameters.add(gKtoggFit.set("Fit Kinect  to quad",false));
    kinectParameters.add(gKtoggKeepAspect.set("Keep Kinect  aspect ratio",false));
    kinectParameters.add(gKtoggHflip.set("Kinect  horizontal flip",false));
    kinectParameters.add(gKtoggVflip.set("Kinect  vertical flip",false));
    kinectParameters.add(gKcolor.set("Kinect  color",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    kinectParameters.add(gKtoggGreenscreen.set("Kinect  Greenscreen",false));

    kinectParametersSecond.add(gKfsliderTrshNear.set("k threshold near", 255.0, 0.0, 255.0));
    kinectParametersSecond.add(gKfsliderTrshFar.set("k threshold far", 0.0,0.0, 255.0));
    kinectParametersSecond.add(gKfsliderAngle.set("k angle",0.0,-30.0, 30.0));
    kinectParametersSecond.add(gKfsliderBlur.set("k blur",  3.0,0.0, 10.0));
    kinectParametersSecond.add(gKfsliderBlobiMin.set("k min blob", 0.01,  0.01,1.0));
    kinectParametersSecond.add(gKfsliderBlobMax.set("k max blob",  1.0, 0.01,1.0));
    kinectParametersSecond.add(gKfsliderSmooth.set("k smooth", 10.0,0.0, 20.0));
    kinectParametersSecond.add(gKfsliderSimplify.set("k simplify", 0.0, 2.0, 0.0));
}

void GuiKinect::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}


