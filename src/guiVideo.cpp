#include "guiVideo.h"

void GuiVideo::setup(){

    videoParameters.add(gVtoggleOnOff.set("Video On/Off",false));
    videoParameters.add(gVtoggleLoad.set("Load Video",false));
    videoParameters.add(gV2SliderScale.set("Scale",ofVec2f(1,1), ofVec2f(0.1, 0.1), ofVec2f(10,10)));
    videoParameters.add(gVtoggFit.set("Fit to quad",false));
    videoParameters.add(gVtoggKeepAspect.set("Keep aspect ratio",false));
    videoParameters.add(gVtoggHflip.set("Horizontal flip",false));
    videoParameters.add(gVtoggVflip.set("Vertical flip",false));
    videoParameters.add(gVcolor.set("color",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    videoParameters.add(gVfsliderSpeed.set("Video Speed", 1.0,-2.0, 4.0));
    videoParameters.add(gVtoggLoop.set("Video Loop",false));
    videoParameters.add(gVtoggGreenscreen.set("Video Greenscreen",false));
    videoParameters.add(gVfsliderVolume.set("Video Audio Volume",0.0, 0.0, 1.0 ));
}

void GuiVideo::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}


