#include "gui3d.h"

void Gui3d::setup(){

    Parameters3d.add(g3toggleOnOff.set("3d On/Off",false));
    Parameters3d.add(g3toggleLoad.set("Load 3d",false));
    Parameters3d.add(g33SliderScale.set("3d Scale",ofVec3f(1,1,1), ofVec3f(0.1, 0.1,0.1), ofVec3f(20,20,20)));
    Parameters3d.add(g33SliderRotate.set("3d Rotate",ofVec3f(1,1,1), ofVec3f(0.0, 0.0,0.0), ofVec3f(360,360,360)));
    Parameters3d.add(g33SliderMove.set("3d Move",ofVec3f(612.0,612.0,0), ofVec3f(0.0, 0.0,-3600.0), ofVec3f(3600.0,3600.0,3600.0)));
    Parameters3d.add(g3toggAnimation.set("3d toggle Animation",false));

}

void Gui3d::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}





