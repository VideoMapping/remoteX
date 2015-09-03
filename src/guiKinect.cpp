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

}

void GuiKinect::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}


