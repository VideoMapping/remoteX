#include "guiQuadOptions.h"

void GuiQuadOptions::setup(){
   
    quadOptionsCropParameters.setName("Crop Quad");
    quadOptionsCropParameters.add(gQSliderCrRcTop.set("rc top",0.0,0.0,1.0));
    quadOptionsCropParameters.add(gQSliderCrRcRight.set("rc right",0.0,0.0,1.0));
    quadOptionsCropParameters.add(gQSliderCrRcLeft.set("rc left",0.0,0.0,1.0));
    quadOptionsCropParameters.add(gQSliderCrRcBottom.set("rc bottom",0.0,0.0,1.0));
    quadOptionsCropParameters.add(gQSliderCrCcX.set("cc X",0.5,0.0, 1.0));
    quadOptionsCropParameters.add(gQSliderCrCcY.set("cc Y",0.5,0.0, 1.0));
    quadOptionsCropParameters.add(gQSliderCrCcRadius.set("cc radius",0.0,0.0,2.0));
    quadOptionsDeformParameters.setName("Deform Quad");
    quadOptionsDeformParameters.add(gQtoggleDeDeformOnOff.set("Deform On/Off",false));
    quadOptionsDeformParameters.add(gQtoggleDeBezier.set("bezier On/Off",false));
    quadOptionsDeformParameters.add(gQtoggleDeBezierReset.set("bezier Reset",false));
    quadOptionsDeformParameters.add(gQtoggleDeSpherizeLight.set("spherize light",false));
    quadOptionsDeformParameters.add(gQtoggleDeSpherizeStrong.set("spherize strong",false));
    quadOptionsDeformParameters.add(gQtoggleDeGrid.set("Grid",false));
    quadOptionsDeformParameters.add(gQSliderDeGridRows.set("Grid rows",5,2,15));
    quadOptionsDeformParameters.add(gQSliderDeGridColumns.set("Grid columns",5,2,20));
    quadOptionsDeformParameters.add(gQtoggleDeEdit.set("edit",false));
    quadOptionsMaskParameters.setName("Quad Mask");
    quadOptionsMaskParameters.add(gQtoggleMaskOnOff.set("m on/off",false));
    quadOptionsMaskParameters.add(gQtoggleMaskInvert.set("m invert",false));
    quadOptionsMaskParameters.add(gQtoggleMaskEdit.set("mask edit on/off",false));
    quadOptionsEdgeBlendParameters.setName("Edge Blend");
    quadOptionsEdgeBlendParameters.add(gQtoggleEbOnOff.set("Edge Blend On/Off",false));
    quadOptionsEdgeBlendParameters.add(gQSliderEbPower.set("eb power",1.0,0.0,4.0));
    quadOptionsEdgeBlendParameters.add(gQSliderEbGamma.set("eb gamma",1.8,0.0,4.0));
    quadOptionsEdgeBlendParameters.add(gQSliderEbLuminance.set("eb luminance",1.0,-4.0,4.0));
    quadOptionsEdgeBlendParameters.add(gQSliderEbEdgesTop.set("eb ",0.3,0.0,0.5));
    quadOptionsEdgeBlendParameters.add(gQSliderEbEdgesRight.set("eb ",0.3,0.0,0.5));
    quadOptionsEdgeBlendParameters.add(gQSliderEbEdgesLeft.set("eb ",0.3,0.0,0.5));
    quadOptionsEdgeBlendParameters.add(gQSliderEbEdgesBottom.set("eb ",0.3,0.0,0.5));
    quadOptionsGreenscreenParameters.setName("Greenscreen");
    quadOptionsGreenscreenParameters.add(gQSliderGsThreshold.set("gs threshold",10.0,0.0,255.0));
    quadOptionsGreenscreenParameters.add(gQSliderGsRed.set("gs red",0.0,0.0,1.0));
    quadOptionsGreenscreenParameters.add(gQSliderGsGreen.set("gs green",0.0,0.0,1.0));
    quadOptionsGreenscreenParameters.add(gQSliderGsBlue.set("gs blue",0.0,0.0,1.0));
    quadOptionsSurfaceParameters.setName("Quad Surface");
    quadOptionsSurfaceParameters.add(gQtoggleSuShowHide.set("Surface show/hide",false));
    quadOptionsSurfaceParameters.add(gQtoggleSuTimeline.set("use Timeline",false));
    quadOptionsSurfaceParameters.add(gQSliderSuSeconds.set("Timeline seconds",100,10, 3600));
    quadOptionsSurfaceParameters.add(gQtoggleSuTlTint.set("tl tint",false));
    quadOptionsSurfaceParameters.add(gQtoggleSuTlColor.set("tl color",false));
    quadOptionsSurfaceParameters.add(gQtoggleSuTlAlpha.set("tl Alpha",false));
    quadOptionsSurfaceParameters.add(gQtoggleSuTl4Slides.set("tl 4slides",false));
    quadOptionsParameters.add(quadOptionsCropParameters);
    quadOptionsParameters.add(quadOptionsDeformParameters);
    quadOptionsParameters.add(quadOptionsMaskParameters);
    quadOptionsParametersSecond.add(quadOptionsGreenscreenParameters);
    quadOptionsParametersSecond.add(quadOptionsSurfaceParameters);
    quadOptionsParametersSecond.add(quadOptionsEdgeBlendParameters);
}

void GuiQuadOptions::draw(){
    //ofSetColor(red, green, blue);
    //ofCircle(posX, posY, radius);
}
