
#include "ofMain.h"

class GuiSampler {
public:
    void setup();
    void draw();
    
    ofParameterGroup samplerParameters;
    ofParameter<bool> gSatoggleOnOff;
    ofParameter<bool> gSatoggleRecord;
    ofParameter<bool> gSatogglePlayAny;
    ofParameter<bool> gSatogglePause;

    ofParameterGroup bufferParameters;
    ofParameter<bool> gSatoggleClear;
    ofParameter<bool> gSatoggleP0;
    ofParameter<bool> gSatoggleP1;
    ofParameter<bool> gSatoggleP2;
    ofParameter<bool> gSatoggleP3;
};
