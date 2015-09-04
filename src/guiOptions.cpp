#include "guiOptions.h"

void GuiOption::setup(){

    optionParameters.add(gOtoggleOnOff.set("live On/Off",false));
    optionParameters.add(gOtoggleResync.set("live resync",false));
    optionParameters.add(gOtoggleFs.set("fullscreen on/off", false));;
    optionProjectParameters.add(gOtoggleDirectS.set("Direct Save",false));
    optionProjectParameters.add(gOtoggleDirectL.set("Direct Load",false));
    optionProjectParameters.add(gOtoggleSFile.set("Save File",false));
    optionProjectParameters.add(gOtoggleLFile.set("Load File",false));
    optionProjectParameters.setName("Project options");

}

void GuiOption::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}

