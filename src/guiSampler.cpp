#include "guiSampler.h"

void GuiSampler::setup(){

    samplerParameters.add(gSatoggleOnOff.set("Sampler OnOff",false));
    samplerParameters.add(gSatoggleRecord.set("Record",false));
    samplerParameters.add(gSatogglePlayAny.set("PlayAny",false));
    samplerParameters.add(gSatogglePause.set("Pause",false));
    samplerParameters.setName("Sampler");

    bufferParameters.add(gSatoggleClear.set("Clear Buffer",false));
    bufferParameters.add(gSatoggleP0.set("Play 0",false));
    bufferParameters.add(gSatoggleP1.set("Play 1",false));
    bufferParameters.add(gSatoggleP2.set("Play 2",false));
    bufferParameters.add(gSatoggleP3.set("Play 3",false));
    bufferParameters.setName("Buffer");
}

void GuiSampler::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}



    // gui4->addSpacer();
    // gui4->addLabel("sampler playback");

    // gui4->addRadio("sampler num",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    // gui4->addRadio("buffer num",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    // gui4->addSpacer();