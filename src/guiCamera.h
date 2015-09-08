
#ifndef ___24ofParameterGUIClass__guiCamera__
#define ___24ofParameterGUIClass__guiCamera__

#include "ofMain.h"


class GuiCamera {
public:
    void setup();
    void draw();
    
    ofParameterGroup cameraParameters;
    ofParameter<bool> gCtoggleOnOff;
    ofParameter<bool> gCtoggleShowImage;
    ofParameter<bool> gCtoggleGrayscale;
    ofParameter<bool> gCtoggleMask;
    ofParameter<bool> gCtoggleDetect;
    ofParameter<ofVec2f> gC2SliderScale;
    ofParameter<bool> gCtoggFit;
    ofParameter<bool> gCtoggKeepAspect;
    ofParameter<bool> gCtoggHflip;
    ofParameter<bool> gCtoggVflip;
    ofParameter<ofColor> gCcolor;
    ofParameter<bool> gCtoggGreenscreen;
    ofParameter<float>  gCfsliderVolume;
    ofParameterGroup cameraParametersSecond;
    ofParameter<bool>  gCtoggleSampler;
    ofParameterGroup cameraMatrixParameters;
    ofParameter<bool> cam0;
    ofParameter<bool> cam2;
    ofParameter<bool> cam3;
    ofParameter<bool> cam1;
    ofParameterGroup samplerMatrixParameters;
    ofParameter<bool> sam0,sam1,sam2,sam3;
    ofParameterGroup bufferMatrixParameters;
    ofParameter<bool> buf0,buf1,buf2,buf3;

};
#endif
