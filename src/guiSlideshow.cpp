#include "guiSlideshow.h"

void GuiSlideshow::setup(){

    slideshowParameters.add(gStoggleOnOff.set("Slideshow On/Off",false));
    slideshowParameters.add(gStoggleLoad.set("Load Slideshow",false));
    slideshowParameters.add(gS2SliderScale.set("Scale Slideshow",ofVec2f(1,1), ofVec2f(0.1, 0.1), ofVec2f(10,10)));
    slideshowParameters.add(gStoggFit.set("Fit Slideshow to quad",false));
    slideshowParameters.add(gStoggKeepAspect.set("Keep Slideshow aspect ratio",false));
    slideshowParameters.add(gStoggHflip.set("sh horizontal flip",false));
    slideshowParameters.add(gStoggVflip.set("sh vertical flip",false));
    slideshowParameters.add(gScolor.set("sh color",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowParameters.add(gStoggGreenscreen.set("sh Greenscreen",false));
    slideshowSCParameters.add(gStoggSCOnOff.set("sh solid colors onOff",false));
    slideshowSCParameters.add(gScolorSC.set("sh Solid Colors",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowTSParameters.add(gStoggTSOnOff.set("sh Trans colors onOff",false));
    slideshowTSParameters.add(gScolorTS.set("sh ransition Colors",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowTSParameters.add(gSfsliderTSduration.set("sh ts duration",1.0,0.1,60));
}
void GuiSlideshow::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}
