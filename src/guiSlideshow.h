
#include "ofMain.h"

class GuiSlideshow {
public:
    void setup();
    void draw();
    
    ofParameterGroup slideshowParameters;
    ofParameter<bool> gStoggleOnOff;
    ofParameter<bool> gStoggleLoad;
    ofParameter<ofVec2f> gS2SliderScale;
    ofParameter<bool> gStoggFit;
    ofParameter<bool> gStoggKeepAspect;
    ofParameter<bool> gStoggHflip;
    ofParameter<bool> gStoggVflip;
    ofParameter<ofColor> gScolor;
    ofParameter<bool> gStoggGreenscreen;
    ofParameterGroup slideshowSCParameters;
    ofParameter<bool> gStoggSCOnOff;
    ofParameter<ofColor> gScolorSC;
    ofParameterGroup slideshowTSParameters;
    ofParameter<bool> gStoggTSOnOff;
    ofParameter<ofColor> gScolorTS;
    ofParameter<float>  gSfsliderTSduration;

};
