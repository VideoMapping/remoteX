#include "guiSlideshow.h"

void GuiSlideshow::setup(){

    slideshowParameters.add(gStoggleOnOff.set("Slideshow On_Off",false));
    slideshowParameters.add(gStoggleLoad.set("Load Slideshow",false));
    slideshowParameters.add(gS2SliderScale.set("Scale Slideshow",ofVec2f(1,1), ofVec2f(0.1, 0.1), ofVec2f(10,10)));
    slideshowParameters.add(gStoggFit.set("Fit Slideshow to quad",false));
    slideshowParameters.add(gStoggKeepAspect.set("Keep Slideshow aspect ratio",false));
    slideshowParameters.add(gStoggHflip.set("sh horizontal flip",false));
    slideshowParameters.add(gStoggVflip.set("sh vertical flip",false));
    slideshowParameters.add(gScolor.set("sh color",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowParameters.add(gStoggGreenscreen.set("sh Greenscreen",false));
    slideshowSCParameters.add(gStoggTSOnOff.set("solid colors on_off",false));
    slideshowSCParameters.add(gScolorSC.set("Solid Colors",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowTSParameters.add(gStoggTSOnOff.set("Transition colors on_off",false));
    slideshowTSParameters.add(gScolorTS.set("Transition Colors",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    slideshowTSParameters.add(gSfsliderTSduration.set("ts duration",1.0,0.1,60));
}
void GuiSlideshow::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}
