#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(35);
	ofBackground(50, 100, 50, 255);
	//ofEnableSmoothing();
    ofSetCircleResolution(60);

    sender.setup(HOST, PORT);

    bgImage.load("image/bg.png");

    video_color_r = 10; video_color_g = 10; video_color_b = 10; video_color_a = 10;
    drawPadding = false;

    setupPreviewVideo();
    setupInputPages();
    setupQuadOptionsPages();
    //Options----------------------------------------------
    optionGroup.setup();
    optionParametersClass.add(optionGroup.optionParameters);
    optionParametersClass.add(optionGroup.optionProjectParameters);    
    guiOptionPanel.setup(optionParametersClass,"",800,100);
    guiOptionPanel.setName("Options");
    ofAddListener(optionParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);

    //QuadSelection----------------------------------------

    //guiQuadSelectionPanel.setup("Quad Selection");
    guiQuadSelectionPanel.setAlignHorizontal();
    guiQuadSelectionPanel.setShowHeader(false);
    guiQuadSelectionPanelSecond.setAlignHorizontal();
    guiQuadSelectionPanelSecond.setup("","",0,25);
    guiQuadSelectionPanelSecond.setShowHeader(false);

    vector<ofParameter<bool>> quads;
    for(int i=0;i<72;i++){
        quads.push_back(ofParameter<bool>("quad"+to_string(i),false));
    }
    for(unsigned int i = 0; i < 36; i++) {
        guiQuadSelectionPanel.add(new ofxToggle(quads.at(i).set("q",false),20, 20));
        //guiQuadSelectionPanel.add(new ofxToggle(quads.at(i).set(to_string(i),false),20, 20));
    }
    for(unsigned int i = 36; i < quads.size(); i++) {
        //guiQuadSelectionPanelSecond.add(new ofxToggle(quads.at(i).set(to_string(i),false),20, 20));
        guiQuadSelectionPanelSecond.add(new ofxToggle(quads.at(i).set("",false),20, 20));
    }
    for(unsigned int i = 0; i < quads.size(); i++) {
        quadSelectionParametersClass.add(quads.at(i).set("q"+to_string(i),false));
    }
    quadSelectionPage.setup("Quad Selection");
    quadSelectionPage.add(&guiQuadSelectionPanel);
    quadSelectionPage.add(&guiQuadSelectionPanelSecond);
    ofAddListener(quadSelectionParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    //Sampler --------------------------------------------------------
    samplerGroup.setup();
    samplerParametersClass.add(samplerGroup.samplerParameters);
    samplerParametersClassSecond.add(samplerGroup.bufferParameters);
    guiSamplerPanel.setup(samplerParametersClass,"",0,0);
    guiSamplerPanel2.setup(samplerParametersClassSecond,"", 220,0);
    //cam
    matrixSamCam.setup("cam to record from",4);
    vector<ofParameter<bool>> matrix_sCam;
    matrix_sCam.push_back(ofParameter<bool>("s cam0",false));
    matrix_sCam.push_back(ofParameter<bool>("s cam1",false));
    matrix_sCam.push_back(ofParameter<bool>("s cam2",false));
    matrix_sCam.push_back(ofParameter<bool>("s cam3",false));
    for(unsigned int i = 0; i < matrix_sCam.size(); i++) {
        matrixSamCam.add(new ofxMinimalToggle(matrix_sCam.at(i)));
    }
    matrixSamCam.setBorderColor(ofColor::blue);
    matrixSamCam.setElementHeight(26);
    matrixSamCam.allowMultipleActiveToggles(false);
    guiSamplerPanelMatrixCam.setup("","",0,110);
    guiSamplerPanelMatrixCam.add(&matrixSamCam);
    guiSamplerPanelMatrixCam.setShowHeader(false);
    //buffer
    matrixSamBuf.setup("buffer to record to",4);
    vector<ofParameter<bool>> matrix_sBuf;
    matrix_sBuf.push_back(ofParameter<bool>("s Buf0",false));
    matrix_sBuf.push_back(ofParameter<bool>("s Buf1",false));
    matrix_sBuf.push_back(ofParameter<bool>("s Buf2",false));
    matrix_sBuf.push_back(ofParameter<bool>("s Buf3",false));
    for(unsigned int i = 0; i < matrix_sBuf.size(); i++) {
        matrixSamBuf.add(new ofxMinimalToggle(matrix_sBuf.at(i)));
    }
    //matrixSamBuf.setBorderColor(ofColor::blue);
    matrixSamBuf.setElementHeight(26);
    matrixSamBuf.allowMultipleActiveToggles(false);
    guiSamplerPanelMatrixBuf.add(&matrixSamBuf);
    guiSamplerPanelMatrixBuf.setup("","",220,125);
    //guiSamplerPanelMatrixBuf.setShowHeader(false);
    //page
    samplerPage.setup("sampler", "", 470,440);
    samplerPage.setSize(440,450);
    samplerPage.add(&guiSamplerPanel);
    samplerPage.add(&guiSamplerPanel2);
    samplerPage.add(&guiSamplerPanelMatrixCam);
    samplerPage.add(&guiSamplerPanelMatrixBuf);
    // gui12->addLabel("cam to record from");
    // //gui12->addRadio("s sampnum",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    // gui12->addLabel("buffer to record to");
    // //gui12->addRadio("b recnum",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    ofAddListener(samplerParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(samplerParametersClassSecond.parameterChangedE(),this,&ofApp::guiEvent2);




}
void ofApp::setupPreviewVideo(){
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(unsigned int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    vidGrabber.setDeviceID(4);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.setVerbose(true);
    //vidGrabber.setPixelFormat(parseDesiredPixelFormat("RGB"));
    vidGrabber.initGrabber(camWidth, camHeight);
}
void ofApp::setupQuadOptionsPages(){
    //QuadOptions-------------------------------------------
    quadOptionsGroup.setup();
    //Transform
    quadOptionsParametersClass.add(quadOptionsGroup.quadOptionsParameters);
    guiQuadOptionsPanel.setup(quadOptionsParametersClass);
    guiQuadOptionsPanel.setName("Quad Transform");
    //Effects
    quadOptionsParametersClassSecond.add(quadOptionsGroup.quadOptionsParametersSecond);
    guiQuadOptionsPanel2.setup(quadOptionsParametersClassSecond);
    guiQuadOptionsPanel2.setName("Effects");
    matrixBlendingModes.setup("Mode Selection",4);
    vector<ofParameter<bool>> matrix_bm;
    matrix_bm.push_back(ofParameter<bool>("screen",false));
    matrix_bm.push_back(ofParameter<bool>("add",false));
    matrix_bm.push_back(ofParameter<bool>("sub",false));
    matrix_bm.push_back(ofParameter<bool>("mult",false));
    for(unsigned int i = 0; i < matrix_bm.size(); i++) {
        matrixBlendingModes.add(new ofxMinimalToggle(matrix_bm.at(i)));
    }
    matrixBlendingModes.setElementHeight(26);
    matrixBlendingModes.allowMultipleActiveToggles(false);
    guiQuadOptionsPanel2.add(&matrixBlendingModes);
    //Global
    quadOptionsParametersClassGlobalQuad.add(quadOptionsGroup.quadOptionsGlobalQuadParameters);
    guiQuadOptionsPanelGlobalQuad.setup(quadOptionsParametersClassGlobalQuad);
    //Pages
    quadOptionsTransformPage.setup("Transform");
    quadOptionsTransformPage.add(&guiQuadOptionsPanel);
    quadOptionsEffectsPage.setup("Quad Effects");
    quadOptionsEffectsPage.add(&guiQuadOptionsPanel2);
    quadOptionsGlobalQuadPage.setup("Global");
    quadOptionsGlobalQuadPage.add(&guiQuadOptionsPanelGlobalQuad);
    //tabbedPage
    quadOptionsPages.setup("Quad Effects/Transform","",1100,10);
    quadOptionsPages.add(&quadOptionsTransformPage);
    quadOptionsPages.add(&quadOptionsEffectsPage);
    quadOptionsPages.add(&quadOptionsGlobalQuadPage);
    quadOptionsPages.setSize(240, 660);
    //EventListeners
    ofAddListener(quadOptionsParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(quadOptionsParametersClassSecond.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(quadOptionsParametersClassGlobalQuad.parameterChangedE(),this,&ofApp::guiEvent2);

}
void ofApp::setupInputPages(){
    ///the setups
    
    videoGroup.setup();
    imageGroup.setup();
    kinectGroup.setup();
    cameraGroup.setup();
    Group3d.setup();
    slideshowGroup.setup();

    //video
    videoParametersClass.add(videoGroup.videoParameters);    
    guiVideoPanel.setup(videoParametersClass);
    guiVideoPanel.setName("Video Input");
    videoPage.setup("Video");
    videoPage.add(&guiVideoPanel);
    //image
    imageParametersClass.add(imageGroup.imageParameters);    
    guiImagePanel.setup(imageParametersClass);
    guiImagePanel.setName("Image Input");
    imagePage.setup("Image");
    imagePage.add(&guiImagePanel);
    //kinect
    kinectParametersClass.add(kinectGroup.kinectParameters);
    kinectParametersSecondClass.add(kinectGroup.kinectParametersSecond);    
    guiKinectPanel.setup(kinectParametersClass);
    guiKinectPanel.setName("Kinect Input");
    guiKinectPanel2.setup(kinectParametersSecondClass,"", 220);
    guiKinectPanel2.setName("Kinect More");
    kinectPage.setup("Kinect");
    kinectPage.add(&guiKinectPanel);
    kinectPage.add(&guiKinectPanel2);
    //Camera
    cameraParametersClass.add(cameraGroup.cameraParameters);
    cameraParametersSecondClass.add(cameraGroup.cameraParametersSecond);    
    guiCameraPanel.setup(cameraParametersClass);
    guiCameraPanel.setName("Camera Input");
    //Matrix Cameras

    matrixCam.setup("Cam Selection",4);
    vector<ofParameter<bool>> matrix_cams;
    matrix_cams.push_back(ofParameter<bool>("cam0",false));
    matrix_cams.push_back(ofParameter<bool>("cam1",false));
    matrix_cams.push_back(ofParameter<bool>("cam2",false));
    matrix_cams.push_back(ofParameter<bool>("cam3",false));
    for(unsigned int i = 0; i < matrix_cams.size(); i++) {
        matrixCam.add(new ofxMinimalToggle(matrix_cams.at(i)));
    }
    matrixCam.setBorderColor(ofColor::blue);
    matrixCam.setElementHeight(26);
    matrixCam.allowMultipleActiveToggles(false);
    guiCameraPanel.add(&matrixCam);
    //Panel2 guiCamera
    guiCameraPanel2.setup(cameraParametersSecondClass,"", 220);
    guiCameraPanel2.setName("Camera Sampler");
    //matrix sampler
    vector<ofParameter<bool>> matrix_sampler;
    matrix_sampler.push_back(ofParameter<bool>("sam0",false));
    matrix_sampler.push_back(ofParameter<bool>("sam1",false));
    matrix_sampler.push_back(ofParameter<bool>("sam2",false));
    matrix_sampler.push_back(ofParameter<bool>("sam3",false));
    matrixSampler.setup("c Sampler Slot",4);
    for(unsigned int i = 0; i < matrix_sampler.size(); i++) {
        matrixSampler.add(new ofxMinimalToggle(matrix_sampler.at(i)));
    }
    matrixSampler.setBorderColor(ofColor::blue);
    matrixSampler.setElementHeight(26);
    matrixSampler.allowMultipleActiveToggles(false);
    guiCameraPanel2.add(&matrixSampler);
    //sampler buffer
    vector<ofParameter<bool>> matrix_buffer;
    matrix_buffer.push_back(ofParameter<bool>("buf0",false));
    matrix_buffer.push_back(ofParameter<bool>("buf1",false));
    matrix_buffer.push_back(ofParameter<bool>("buf2",false));
    matrix_buffer.push_back(ofParameter<bool>("buf3",false));
    matrixBuffer.setup("c Buffer Slot",4);
    for(unsigned int i = 0; i < matrix_buffer.size(); i++) {
        matrixBuffer.add(new ofxMinimalToggle(matrix_buffer.at(i)));
    }
    matrixBuffer.setBorderColor(ofColor::blue);
    matrixBuffer.setElementHeight(26);
    matrixBuffer.allowMultipleActiveToggles(false);
    guiCameraPanel2.add(&matrixBuffer);
    //cameraPage
    cameraPage.setup("Camera/v4l2/syphon");
    cameraPage.add(&guiCameraPanel);
    cameraPage.add(&guiCameraPanel2);
    //3d
    Parameters3dClass.add(Group3d.Parameters3d);    
    vector<ofParameter<bool>> matrix_renderModes;
    matrix_renderModes.push_back(ofParameter<bool>("smooth",false));
    matrix_renderModes.push_back(ofParameter<bool>("wire",false));
    matrix_renderModes.push_back(ofParameter<bool>("dots",false));
    matrix3dRenderModes.setup("c Buffer Slot",4);
    for(unsigned int i = 0; i < matrix_renderModes.size(); i++) {
        matrix3dRenderModes.add(new ofxMinimalToggle(matrix_renderModes.at(i)));
    }
    matrix3dRenderModes.setElementHeight(26);
    matrix3dRenderModes.allowMultipleActiveToggles(false);
    gui3dPanel.setup(Parameters3dClass);
    gui3dPanel.setName("3d Input");
    gui3dPanel.add(&matrix3dRenderModes);
    Page3d.setup("3d");
    Page3d.add(&gui3dPanel);
    //Slideshow
    slideshowParametersClass.add(slideshowGroup.slideshowParameters);  
    guiSlideshowPanel.setup(slideshowParametersClass);
    guiSlideshowPanel.setName("Slideshow Input");
    slideshowParametersClassSC.add(slideshowGroup.slideshowSCParameters);  
    guiSlideshowPanelSC.setup(slideshowParametersClassSC,"", 220);
    guiSlideshowPanelSC.setName("Solid Colors");
    slideshowParametersClassTS.add(slideshowGroup.slideshowTSParameters);  
    guiSlideshowPanelTS.setup(slideshowParametersClassTS,"", 220,200);
    guiSlideshowPanelTS.setName("Transition");

    slideshowPage.setup("Slideshow");
    slideshowPage.add(&guiSlideshowPanel);
    slideshowPage.add(&guiSlideshowPanelSC);
    slideshowPage.add(&guiSlideshowPanelTS);
    //input pages
    inputPages.setup("Inputs", "",10,100);
    inputPages.setSize(440, 540);
    inputPages.add(&videoPage);
    inputPages.add(&imagePage);
    inputPages.add(&kinectPage);
    inputPages.add(&cameraPage);
    inputPages.add(&Page3d);
    inputPages.add(&slideshowPage);

    // Input listeners
    ofAddListener(videoParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(imageParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(kinectParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(kinectParametersSecondClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(cameraParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(cameraParametersSecondClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(Parameters3dClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(slideshowParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(slideshowParametersClassSC.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(slideshowParametersClassTS.parameterChangedE(),this,&ofApp::guiEvent2);
}
//--------------------------------------------------------------
void ofApp::update()
{
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    quadSelectionPage.draw();
    inputPages.draw();
    guiOptionPanel.draw();
    quadOptionsPages.draw();
    vidGrabber.draw(460,100);
    samplerPage.draw();

}

void ofApp::guiEvent2(ofAbstractParameter &e){
cout << "Ev2"+e.getName() +" " +e.toString()<< endl;

//e.get();
}
//--------------------------------------------------------------
// void ofApp::guiEvent(ofxUIEventArgs &e)
// {
//     string name = e.widget->getName();
// 	int kind = e.widget->getKind();
// /*    string canvasParent = e.widget->getCanvasParent()->getName();
//     cout << canvasParent << endl;
// */
//     cout << e.widget->getName() << endl;
//     if(name == "active quad")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/set");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v load")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/load");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v x scale")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/mult/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v y scale")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/mult/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v fit")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/fit");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v keep aspect")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/keepaspect");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v hflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/hmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v vflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/vmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "audio")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/volume");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "speed")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/speed");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v loop")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/loop");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "v greenscreen")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/video/greenscreen");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//         //greenscreen

//     else if(name == "threshold")
//     {
//     ofxUICircleSlider *csliderValue = (ofxUICircleSlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/greenscreen/threshold");
//     m.addFloatArg(csliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "gs red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/greenscreen/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "gs green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/greenscreen/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "gs blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/greenscreen/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "gs alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/greenscreen/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }

//     //Kinect
//     else if(name == "k on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/show");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k close/open")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/close");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k show img")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/show/image");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k grayscale")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/show/grayscale");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k mask")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/mask");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k detect")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/contour");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k scale x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/mult/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k scale y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/mult/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k threshold near")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/threshold/near");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k threshold far")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/threshold/far");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k angle")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/angle");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k blur")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/blur");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k smooth")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/contour/smooth");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k simplelse ify")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/contour/simplelse ify");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k min blob")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/contour/area/min");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k max blob")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/contour/area/max");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "k alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/kinect/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }




//     //slideshow
//     else if(name == "sh on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/show");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sh load")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/folder");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

//     else if(name == "sh fit")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/fit");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sh aspect ratio")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/keep_aspect");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sh greenscreen")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/greenscreen");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }


//     else if(name == "sh duration")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/slideshow/duration");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "show/hide")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/show");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

//     //timeline

//     else if(name == "use timeline")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/timeline/toggle");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "seconds")
//     {
//     ofxUIMinimalSlider *sliderValue = (ofxUIMinimalSlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/timeline/duration");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tl tint")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/timeline/tint");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tl color")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/timeline/color");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tl alpha")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/timeline/alpha");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tl 4 slides")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/timeline/slides");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

//     //camera

//     else if(name == "c on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c load")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c scale x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/mult/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c scale y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/mult/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c fit")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/fit");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c aspect ratio")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/keepaspect");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c hflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/hmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c vflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/vmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "cam audio")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/volume");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "c greenscreen")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/greenscreen");
//     m.addFloatArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "camera 0")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/num");
//     m.addIntArg(0);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "camera 1")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/num");
//     m.addIntArg(1);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "camera 2")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/num");
//     m.addIntArg(2);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "camera 3")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/cam/num");
//     m.addIntArg(3);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }


//     //image

//     else if(name == "i on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i load")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/load");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i fit")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/fit");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i aspect ratio")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/keepaspect");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i scale x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/mult/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i scale y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/mult/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i hflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/hmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i vflip")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/vmirror");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i greenscreen")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/greenscreen");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "i alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/img/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }

//     //placement
//     else if(name == "move x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/placement/x");
//     m.addIntArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//      else if(name == "move y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/placement/y");
//     m.addIntArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "width")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/placement/w");
//     m.addIntArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "height")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/placement/h");
//     m.addIntArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "reset")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/placement/reset");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }

//     //edge blend

//     else if(name == "eb on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//      else if(name == "power")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/power");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "gamma")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/gamma");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "luminance")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/luminance");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "left edge")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/amount/left");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "right edge")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/amount/right");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "top edge")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/amount/top");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "bottom edge")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/edgeblend/amount/bottom");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }

//      //blend modes

//      else if(name == "bm on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/blendmodes/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//      else if(name == "screen")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(0);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "add")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(1);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "subtract")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(2);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "multiply")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/blendmodes/mode");
//     m.addIntArg(3);
//     //m.addIntArg(1);
//     //m.addIntArg(3);
//     //m.addIntArg(4);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }

//     //solid color

//     else if(name == "sc on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sc red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sc green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sc blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sc alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }

//     //Projection

//     else if(name == "live resync")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/resync");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "live stop/start")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/stop");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "direct save")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/save");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "direct load")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/load");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "load file")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/loadfile");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "save file")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/savefile");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "live fc on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/fullscreen/toggle");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "display gui")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/gui/toggle");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

// /*    else if(name == "modesetup on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/mode/setup/toggle");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
// */
//     //mask

//     else if(name == "m on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/mask/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "m invert")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/mask/invert");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "mask edit on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/projection/mode/masksetup/toggle");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

//     //Deform
//     else if(name == "d on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "bezier")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/bezier");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "spherize light")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/bezier/spherize/light");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "spherize strong")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/bezier/spherize/strong");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "bezier reset")
//     {
//     ofxUIButton *button = (ofxUIButton *) e.getButton();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/bezier/reset");
//     m.addIntArg(button->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "grid")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/grid");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "rows num")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/grid/rows");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "columns num")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/grid/columns");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "edit")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/deform/edit");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }

//     //crop

//     else if(name == "top")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/rectangular/top");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "right")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/rectangular/right");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "left")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/rectangular/left");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "bottom")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/rectangular/bottom");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/circular/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/circular/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "radius")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/crop/circular/radius");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     //active surface
//     else if(name == "Number")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/set");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     //transition
//     else if(name == "tr on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tr red")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/color/1");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tr green")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/color/2");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tr blue")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/color/3");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tr alpha")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/color/4");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "tr duration")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/solid/trans/duration");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     //3d model
//     else if(name == "3d load")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/load");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d scale x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/scale/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d scale y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/scale/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d scale z")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/scale/z");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d rotate x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/rotate/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d rotate y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/rotate/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d rotate z")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/rotate/z");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d move x")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/move/x");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d move y")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/move/y");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "3d move z")
//     {
//     ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/move/z");
//     m.addFloatArg(sliderValue->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "animation")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/animation");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//         else if(name == "smooth")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(0);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "wire")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(1);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "dots")
//     {
//     ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/3d/texture/mode");
//     m.addIntArg(2);
//     m.addIntArg(ddl->getValue());
//     sender.sendMessage(m);
//     }
//      //sampler
//     else if(name == "s on/off")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/sampler/show");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "sampler num")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/sampler/num");
//     m.addIntArg(radio->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "buffer num")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/active/sampler/buffernum");
//     m.addIntArg(radio->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "s record")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "s playany")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/play");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "s pause")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/pause");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "b clear")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/clear");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "b play0")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/0");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "b play1")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/1");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "b play2")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/2");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "b play3")
//     {
//     ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/3");
//     m.addIntArg(toggle->getValue());
//     sender.sendMessage(m);
//     }
//     else if(name == "s sampnum")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     SharedSamplerIndex=radio->getValue();
//     cout<<"SharedSamplerIndex"<<SharedSamplerIndex<<endl;

//     }
//     else if(name == "b recnum")
//     {
//     ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
//     cout << "got event from: " << name << endl;
//     SharedSamplerBufferIndex=radio->getValue();
//     ofxOscMessage m;
//     m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));

//     m.addIntArg(0);

//     sender.sendMessage(m);
//     cout<<"message "<<m.getAddress()<<endl;
//     }
//}
//[--------------------------------------------------------------
void ofApp::exit()
{
//    delete gui0;
//    delete gui1;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'b':
        {
        ofxOscMessage m;
        m.setAddress("/active/deform/edit");
        sender.sendMessage(m);
        }
        break;
    default:
        break;
    }
/*     // toggles fullscreen mode
    if(key == 'f')

        bFullscreen = !bFullscreen;

        if(!bFullscreen)
        {
            ofSetFullscreen(false);
        }
        else if(bFullscreen == 1)
        {
            ofSetFullscreen(true);
        }
*/
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
