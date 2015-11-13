
#ifndef ___24ofParameterGUIClass__guiVideo__
#define ___24ofParameterGUIClass__guiVideo__

#include "ofMain.h"

class GuiVideo {
public:
    void setup();
    void draw();

    ofParameterGroup videoParameters;
    ofParameter<bool> gVtoggleOnOff;
    ofParameter<bool> gVtoggleLoad;
    ofParameter<ofVec2f> gV2SliderScale;
    ofParameter<bool> gVtoggFit;
    ofParameter<bool> gVtoggKeepAspect;
    ofParameter<bool> gVtoggHflip;
    ofParameter<bool> gVtoggVflip;
    ofParameter<ofFloatColor> gVcolor;
    ofParameter<float>  gVfsliderSpeed;
    ofParameter<bool> gVtoggLoop;
    ofParameter<bool> gVtoggGreenscreen;
    ofParameter<float>  gVfsliderVolume;
};
#endif
