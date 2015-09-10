
#include "ofMain.h"

class Gui3d {
public:
    void setup();
    void draw();
    
    ofParameterGroup Parameters3d;
    ofParameter<bool> g3toggleOnOff;
    ofParameter<bool> g3toggleLoad;
    ofParameter<ofVec3f> g33SliderScale;
    ofParameter<ofVec3f> g33SliderRotate;
    ofParameter<ofVec3f> g33SliderMove;
    ofParameter<bool> g3toggAnimation;

};
