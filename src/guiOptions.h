
#include "ofMain.h"

class GuiOption {
public:
    void setup();
    void draw();
    
    ofParameterGroup optionParameters;
    ofParameter<bool> gOtoggleOnOff;
    ofParameter<bool> gOtoggleResync;
    ofParameter<bool> gOtoggleFs;
    ofParameter<bool> gOtoggleMpe;
    ofParameter<bool> gOtoggleGuiOnOff;
    ofParameterGroup optionProjectParameters;
    ofParameter<bool> gOtoggleDirectS;
    ofParameter<bool> gOtoggleDirectL;
    ofParameter<bool> gOtoggleSFile;
    ofParameter<bool> gOtoggleLFile;


};
