#include "guiCamera.h"

void GuiCamera::setup(){
    cameraParameters.add(gCtoggleOnOff.set("Camera  On/Off",false));
    cameraParameters.add(gCtoggleShowImage.set("Camera show image",false));
    cameraParameters.add(gCtoggleGrayscale.set("Camera grayscale",false));
    cameraParameters.add(gCtoggleMask.set("Camera mask",false));
    cameraParameters.add(gCtoggleDetect.set("Camera detect",false));
    cameraParameters.add(gC2SliderScale.set("Scale Camera ",ofVec2f(1,1), ofVec2f(0.1, 0.1), ofVec2f(10,10)));
    cameraParameters.add(gCtoggFit.set("Fit Camera  to quad",false));
    cameraParameters.add(gCtoggKeepAspect.set("Keep Camera  aspect ratio",false));
    cameraParameters.add(gCtoggHflip.set("Camera  horizontal flip",false));
    cameraParameters.add(gCtoggVflip.set("Camera  vertical flip",false));
    cameraParameters.add(gCcolor.set("Camera  color",ofColor(255,255,255), ofColor(0, 0), ofColor(255, 255)));
    cameraParameters.add(gCtoggGreenscreen.set("Camera  Greenscreen",false));
    cameraParametersSecond.add(gCtoggleSampler.set("k sampler playback", 255.0, 0.0, 255.0));
    cameraMatrixParameters.add(cam0.set("cam0",false));
    cameraMatrixParameters.add(cam1.set("cam1",false));
    cameraMatrixParameters.add(cam2.set("cam2",false));
    cameraMatrixParameters.add(cam3.set("cam3",false));

}

void GuiCamera::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}


    // gui4->addDropDownList("device num", itemos, dime);

    // gui4->addSpacer();
    // gui4->addLabel("sampler playback");

    // gui4->addRadio("sampler num",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    // gui4->addRadio("buffer num",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    // gui4->addSpacer();

    // gui4->addLabel("Greenscreen");
    // gui4->addSpacer();
    // gui4->addMinimalSlider("gs threshold", 0.0, 255.0, 10.0);
    // gui4->addMinimalSlider("gs red", 0.0, 1.0, 0.0);
    // gui4->addMinimalSlider("gs green", 0.0, 1.0, 0.0);
    // gui4->addMinimalSlider("gs blue", 0.0, 1.0, 0.0);
    // gui4->addMinimalSlider("gs alpha", 0.0, 1.0, 0.0);