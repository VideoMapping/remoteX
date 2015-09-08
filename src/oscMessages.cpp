#include "oscMessages.h"

void oscMessages::setup(ofParameterGroup g){
	allParameters.add(g);

}
void oscMessages::setActiveQuad(ofxOscMessage &m,int quad){
	m.setAddress("/active/set");
	m.addFloatArg(quad);

}
void oscMessages::setOscMessage(ofAbstractParameter &e,ofxOscMessage &m){


	string name=e.getName();
	cout << "got event from: "+e.getName() +" " +e.toString()<< endl;
     //set the Values
     if(e.type() == typeid(ofParameter<bool>).name()){
          m.addIntArg((int)e.cast<bool>().get());
     }
     else if(e.type() == typeid(ofParameter<float>).name()){
          m.addFloatArg(e.cast<float>().get());
     }
     else if(e.type() == typeid(ofParameter<ofVec2f>).name()){
          ofVec2f tmp=e.cast<ofVec2f>();         
          m.addFloatArg(tmp.x);
          m.addFloatArg(tmp.y);
     }
     else if(e.type() == typeid(ofParameter<ofVec3f>).name()){
      
          ofVec3f tmp=e.cast<ofVec3f>();         
          m.addFloatArg(tmp.x);
          m.addFloatArg(tmp.y);
          m.addFloatArg(tmp.z);
     }
     else if(e.type() == typeid(ofParameter<ofColor>).name()){
          ofColor tmp=e.cast<ofColor>();
          m.addFloatArg(tmp.r);
          m.addFloatArg(tmp.g);
          m.addFloatArg(tmp.b);
          m.addFloatArg(tmp.a);
     }

//INPUTPAGES	
//Set the Adresses
if(name.find("Video") != std::string::npos){
     setVideo(e,m);
}
else if(name.find("Image") != std::string::npos){
     setImage(e,m);
}
else if(name.find("Kinectinect") != std::string::npos){
     setKinect(e,m);
}
else if(name.find("Cam") != std::string::npos||name.find("Sam") != std::string::npos||name.find("Buf") != std::string::npos){
     setCamera(e,m);
}
else if(name.find("3d") != std::string::npos){
     set3d(e,m);
}
else if(name.find("Slideshow") != std::string::npos||name.find("sh ") != std::string::npos){
     setSlideshow(e,m);
}
//greenscreen---------------------------------------------------

//     else if(name == "threshold")
//     {
//     ofxUICircleSlider *csliderValue = (ofxUICircleSlider *) e.getSlider();
//     m.setAddress("/active/greenscreen/threshold");
//     m.addFloatArg(csliderValue->getValue());
//     }
//     else if(name == "gs red")
//     {
//     m.setAddress("/active/greenscreen/color/1");
//     //     }
//     else if(name == "gs green")
//     {
//     m.setAddress("/active/greenscreen/color/2");
//     //     }
//     else if(name == "gs blue")
//     {
//     m.setAddress("/active/greenscreen/color/3");
//     //     }
//     else if(name == "gs alpha")
//     {
//     m.setAddress("/active/greenscreen/color/4");
//     //     }

//     //timeline

//     else if(name == "use timeline")
//     {
//     m.setAddress("/projection/timeline/toggle");
//     }
//     else if(name == "seconds")
//     {
//     ofxUIMinimalSlider *sliderValue = (ofxUIMinimalSlider *) e.getSlider();
//     m.setAddress("/projection/timeline/duration");
//     //     }
//     else if(name == "tl tint")
//     {
//     m.setAddress("/active/timeline/tint");
//     }
//     else if(name == "tl color")
//     {
//     m.setAddress("/active/timeline/color");
//     }
//     else if(name == "tl alpha")
//     {
//     m.setAddress("/active/timeline/alpha");
//     }
//     else if(name == "tl 4 slides")
//     {
//     m.setAddress("/active/timeline/slides");
//     }






//     //placement
//     else if(name == "move x")
//     {
//     m.setAddress("/active/placement/x");
//     m.addIntArg(sliderValue->getValue());
//     }
//      else if(name == "move y")
//     {
//     m.setAddress("/active/placement/y");
//     m.addIntArg(sliderValue->getValue());
//     }
//     else if(name == "width")
//     {
//     m.setAddress("/active/placement/w");
//     m.addIntArg(sliderValue->getValue());
//     }
//     else if(name == "height")
//     {
//     m.setAddress("/active/placement/h");
//     m.addIntArg(sliderValue->getValue());
//     }
//     else if(name == "reset")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/active/placement/reset");
//     m.addIntArg(button->getValue());
//     }

//     //edge blend

//     else if(name == "eb on/off")
//     {
//     m.setAddress("/active/edgeblend/show");
//     }
//      else if(name == "power")
//     {
//     m.setAddress("/active/edgeblend/power");
//     //     }
//     else if(name == "gamma")
//     {
//     m.setAddress("/active/edgeblend/gamma");
//     //     }
//     else if(name == "luminance")
//     {
//     m.setAddress("/active/edgeblend/luminance");
//     //     }
//     else if(name == "left edge")
//     {
//     m.setAddress("/active/edgeblend/amount/left");
//     //     }
//     else if(name == "right edge")
//     {
//     m.setAddress("/active/edgeblend/amount/right");
//     //     }
//     else if(name == "top edge")
//     {
//     m.setAddress("/active/edgeblend/amount/top");
//     //     }
//     else if(name == "bottom edge")
//     {
//     m.setAddress("/active/edgeblend/amount/bottom");
//     //     }

//      //blend modes

//      else if(name == "bm on/off")
//     {
//     m.setAddress("/active/blendmodes/show");
//     }
//      else if(name == "screen")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(0);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "add")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(1);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "subtract")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(2);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "multiply")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(3);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }

//     //solid color

//     else if(name == "sc on/off")
//     {
//     m.setAddress("/active/solid/show");
//     }
//     else if(name == "sc red")
//     {
//     m.setAddress("/active/solid/color/1");
//     //     }
//     else if(name == "sc green")
//     {
//     m.setAddress("/active/solid/color/2");
//     //     }
//     else if(name == "sc blue")
//     {
//     m.setAddress("/active/solid/color/3");
//     //     }
//     else if(name == "sc alpha")
//     {
//     m.setAddress("/active/solid/color/4");
//     //     }

//     //Projection

//     else if(name == "live resync")
//     {
//     m.setAddress("/projection/resync");
//     }
//     else if(name == "live stop/start")
//     {
//     m.setAddress("/projection/stop");
//     }
//     else if(name == "direct save")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/projection/save");
//     m.addIntArg(button->getValue());
//     }
//     else if(name == "direct load")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/projection/load");
//     m.addIntArg(button->getValue());
//     }
//     else if(name == "load file")
//     {
//     m.setAddress("/projection/loadfile");
//     }
//     else if(name == "save file")
//     {
//     m.setAddress("/projection/savefile");
//     }
//     else if(name == "live fc on/off")
//     {
//     m.setAddress("/projection/fullscreen/toggle");
//     }
//     else if(name == "display gui")
//     {
//     m.setAddress("/projection/gui/toggle");
//     }

// /*    else if(name == "modesetup on/off")
//     {
//     m.setAddress("/projection/mode/setup/toggle");
//     }
// */
//     //mask

//     else if(name == "m on/off")
//     {
//     m.setAddress("/active/mask/show");
//     }
//     else if(name == "m invert")
//     {
//     m.setAddress("/active/mask/invert");
//     }
//     else if(name == "mask edit on/off")
//     {
//     m.setAddress("/projection/mode/masksetup/toggle");
//     }

//     //Deform
//     else if(name == "d on/off")
//     {
//     m.setAddress("/active/deform/show");
//     }
//     else if(name == "bezier")
//     {
//     m.setAddress("/active/deform/bezier");
//     }
//     else if(name == "spherize light")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/active/deform/bezier/spherize/light");
//     m.addIntArg(button->getValue());
//     }
//     else if(name == "spherize strong")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/active/deform/bezier/spherize/strong");
//     m.addIntArg(button->getValue());
//     }
//     else if(name == "bezier reset")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     m.setAddress("/active/deform/bezier/reset");
//     m.addIntArg(button->getValue());
//     }
//     else if(name == "grid")
//     {
//     m.setAddress("/active/deform/grid");
//     }
//     else if(name == "rows num")
//     {
//     m.setAddress("/active/deform/grid/rows");
//     //     }
//     else if(name == "columns num")
//     {
//     m.setAddress("/active/deform/grid/columns");
//     //     }
//     else if(name == "edit")
//     {
//     m.setAddress("/active/deform/edit");
//     }

//     //crop

//     else if(name == "top")
//     {
//     m.setAddress("/active/crop/rectangular/top");
//     //     }
//     else if(name == "right")
//     {
//     m.setAddress("/active/crop/rectangular/right");
//     //     }
//     else if(name == "left")
//     {
//     m.setAddress("/active/crop/rectangular/left");
//     //     }
//     else if(name == "bottom")
//     {
//     m.setAddress("/active/crop/rectangular/bottom");
//     //     }
//     else if(name == "x")
//     {
//     m.setAddress("/active/crop/circular/x");
//     //     }
//     else if(name == "y")
//     {
//     m.setAddress("/active/crop/circular/y");
//     //     }
//     else if(name == "radius")
//     {
//     m.setAddress("/active/crop/circular/radius");
//     //     }
//     //active surface
//     else if(name == "Number")
//     {
//     m.setAddress("/active/set");
//     //     }
//     //transition
//     else if(name == "tr on/off")
//     {
//     m.setAddress("/active/solid/trans/show");
//     }
//     else if(name == "tr red")
//     {
//     m.setAddress("/active/solid/trans/color/1");
//     //     }
//     else if(name == "tr green")
//     {
//     m.setAddress("/active/solid/trans/color/2");
//     //     }
//     else if(name == "tr blue")
//     {
//     m.setAddress("/active/solid/trans/color/3");
//     //     }
//     else if(name == "tr alpha")
//     {
//     m.setAddress("/active/solid/trans/color/4");
//     //     }
//     else if(name == "tr duration")
//     {
//     m.setAddress("/active/solid/trans/duration");
//     //     }

//      //sampler
//     else if(name == "s on/off")
//     {
//     m.setAddress("/active/sampler/show");
//     }
//     else if(name == "sampler num")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     m.setAddress("/active/sampler/num");
//     m.addIntArg(radio->getValue());
//     }
//     else if(name == "buffer num")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     m.setAddress("/active/sampler/buffernum");
//     m.addIntArg(radio->getValue());
//     }
//     else if(name == "s record")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));
//     }
//     else if(name == "s playany")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/play");
//     }
//     else if(name == "s pause")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/pause");
//     }
//     else if(name == "b clear")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/clear");
//     }
//     else if(name == "b play0")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/0");
//     }
//     else if(name == "b play1")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/1");
//     }
//     else if(name == "b play2")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/2");
//     }
//     else if(name == "b play3")
//     {
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/3");
//     }
//     else if(name == "s sampnum")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     SharedSamplerIndex=radio->getValue();
//     cout<<"SharedSamplerIndex"<<SharedSamplerIndex<<endl;

//     }
//     else if(name == "b recnum")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     SharedSamplerBufferIndex=radio->getValue();
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));

//     m.addIntArg(0);

//     cout<<"message "<<m.getAddress()<<endl;
//     }
//}
//[--------------------------------------------------------------
}
void oscMessages::setVideo(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     if(name == "Video On/Off")m.setAddress("/active/video/show");     
     else if(name == "Load Video")m.setAddress("/active/video/load");

//     else if(name == "v x scale")
//     {
//     m.setAddress("/active/video/mult/x");
//     //     }
//     else if(name == "v y scale")
//     {
//     m.setAddress("/active/video/mult/y");
//     //     }
     else if(name == "Fit Video to quad")m.setAddress("/active/video/fit");
     else if(name == "Keep Video aspect ratio")m.setAddress("/active/video/keepaspect");     
     else if(name == "Video Horizontal flip")m.setAddress("/active/video/hmirror");     
     else if(name == "Video Vertical flip")m.setAddress("/active/video/vmirror");
     
//     else if(name == "v red")
//     {
//     m.setAddress("/active/video/color/1");
//     //     }
//     else if(name == "v green")
//     {
//     m.setAddress("/active/video/color/2");
//     //     }
//     else if(name == "v blue")
//     {
//     m.setAddress("/active/video/color/3");
//     //     }
//     else if(name == "v alpha")
//     {
//     m.setAddress("/active/video/color/4");
//     //     }
     else if(name == "Video Audio Volume")m.setAddress("/active/video/volume");
     else if(name == "Video Speed")m.setAddress("/active/video/speed");
     else if(name == "Video Loop")m.setAddress("/active/video/loop");
     else if(name == "Video Greenscreen")m.setAddress("/active/video/greenscreen");

}
void oscMessages::setImage(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     //     //image

     if(name == "Image On/Off")m.setAddress("/active/img/show");     
     else if(name == "Load Image")m.setAddress("/active/img/load");     
     else if(name == "Fit image to quad")m.setAddress("/active/img/fit");     
     else if(name == "Keep image aspect ratio")m.setAddress("/active/img/keepaspect");
     
//     else if(name == "i scale x")
//     {
//     m.setAddress("/active/img/mult/x");
//     //     }
//     else if(name == "i scale y")
//     {
//     m.setAddress("/active/img/mult/y");
//     //     }
     else if(name == "Image horizontal flip")m.setAddress("/active/img/hmirror");     
     else if(name == "Image vertical flip")m.setAddress("/active/img/vmirror");     
     else if(name == "Image Greenscreen")m.setAddress("/active/img/greenscreen");
     
//     else if(name == "i red")
//     {
//     m.setAddress("/active/img/color/1");
//     //     }
//     else if(name == "i green")
//     {
//     m.setAddress("/active/img/color/2");
//     //     }
//     else if(name == "i blue")
//     {
//     m.setAddress("/active/img/color/3");
//     //     }
//     else if(name == "i alpha")
//     {
//     m.setAddress("/active/img/color/4");
//     //     }
}
void oscMessages::setKinect(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     //Kinect------------------------------------------------------------------
     if(name == "Kinect On/Off")m.setAddress("/active/kinect/show");
     else if(name == "Kinect close/open")m.setAddress("/active/kinect/close");     
     else if(name == "Kinect show image")m.setAddress("/active/kinect/show/image");     
     else if(name == "Kinect grayscale")m.setAddress("/active/kinect/show/grayscale");     
     else if(name == "Kinect mask")m.setAddress("/active/kinect/mask");     
     else if(name == "Kinect detect")m.setAddress("/active/kinect/contour");     
     else if(name == "Scale Kinect")m.setAddress("/active/kinect/mult/xy");     
     else if(name == "Kinect threshold near")m.setAddress("/active/kinect/threshold/near");
     else if(name == "Kinect threshold far")m.setAddress("/active/kinect/threshold/far");
     else if(name == "Kinect angle")m.setAddress("/active/kinect/angle");
     else if(name == "Kinect blur")m.setAddress("/active/kinect/blur");     
     else if(name == "Kinect smooth")m.setAddress("/active/kinect/contour/smooth");
     else if(name == "Kinect simplify")m.setAddress("/active/kinect/contour/simplelse ify");
     else if(name == "Kinect min blob")m.setAddress("/active/kinect/contour/area/min");
     else if(name == "Kinect max blob")m.setAddress("/active/kinect/contour/area/max");
     else if(name == "Kinect color")m.setAddress("/active/kinect//color/1234");
}
void oscMessages::setCamera(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     //--camera----------------------------------------------------------

     if(name == "Camera On/Off")m.setAddress("/active/cam/show");
//     else if(name == "c load")
//     {
//     m.setAddress("/active/cam/show");
//     }
     else if(name == "Scale Camera")m.setAddress("/active/cam/mult/xy");     
     else if(name == "Fit Camera  to quad")m.setAddress("/active/cam/fit");     
     else if(name == "Kinecteep Camera  aspect ratio")m.setAddress("/active/cam/keepaspect");     
     else if(name == "Camera  horizontal flip")m.setAddress("/active/cam/hmirror");     
     else if(name == "Camera  vertical flip")m.setAddress("/active/cam/vmirror");     
     else if(name == "Camera color")m.setAddress("/active/cam/color/1234");
     else if(name == "Camera Volume")m.setAddress("/active/cam/volume");
     else if(name == "Camera  Greenscreen")m.setAddress("/active/cam/greenscreen");

//     else if(name == "camera 0")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/cam/num");
//     m.addIntArg(0);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "camera 1")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/cam/num");
//     m.addIntArg(1);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "camera 2")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/cam/num");
//     m.addIntArg(2);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "camera 3")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/cam/num");
//     m.addIntArg(3);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     }
}
void oscMessages::set3d(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     //     //3d model
     if(name == "Load 3d")m.setAddress("/active/3d/load");     
     else if(name == "3d Scale")m.setAddress("/active/3d/scale/xyz");
     else if(name == "3d Rotate")m.setAddress("/active/3d/rotate/xyz");
     else if(name == "3d Move")m.setAddress("/active/3d/move/xyz");
     else if(name == "animation")m.setAddress("/active/3d/animation");
//         else if(name == "smooth")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(0);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "wire")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(1);
//     m.addIntArg(ddl->getValue());
//     }
//     else if(name == "dots")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(2);
//     m.addIntArg(ddl->getValue());
//     }
}
void oscMessages::setSlideshow(ofAbstractParameter &e,ofxOscMessage &m){
     string name=e.getName();
     if(name == "Slideshow On/Off")m.setAddress("/active/slideshow/show");
     else if(name == "Load Slideshow")m.setAddress("/active/slideshow/folder");     
     else if(name == "Fit Slideshow to quad")m.setAddress("/active/slideshow/fit");     
     else if(name == "Kinecteep Slideshow aspect ratio")m.setAddress("/active/slideshow/keep_aspect");     
     else if(name == "sh Greenscreen")m.setAddress("/active/slideshow/greenscreen");     
     else if(name == "sh ts duration")m.setAddress("/active/slideshow/duration");
//     else if(name == "show/hide")
//     {
//     m.setAddress("/active/show");
//     m.addFloatArg((float)e.cast<bool>().get());
//     }
}