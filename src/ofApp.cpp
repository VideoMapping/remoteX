#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetLogLevel(OF_LOG_VERBOSE);

    ofSetFrameRate(35);
    sender.setup(HOST, PORT);
    //Colors
    ofBackground(0xad,0x46,0x01,100);
    ofxGuiSetFillColor(ofColor(0xff,0x4f,0x20,100));
    ofxGuiSetBackgroundColor(ofColor(0xff,0xa5,0x8d,100));
    ofxGuiSetTextColor(ofColor(0xff,0xff,0xff,255));
    ofxGuiSetHeaderColor(ofColor(0x64,0x54,0x44));
    ofxGuiSetBorderColor(ofColor(0x30,0x5b,0x74));
    bgImage.load("image/bg.png");
    //ofEnableSmoothing();
    ofSetCircleResolution(60);

    

    video_color_r = 10; video_color_g = 10; video_color_b = 10; video_color_a = 10;

    //setupPreviewVideo();
    setupInputPages();
    setupQuadOptionsPages();
    setupQuadSelectionPages();
    //Options----------------------------------------------
    optionGroup.setup();
    optionParametersClass.add(optionGroup.optionParameters);
    optionParametersClass.add(optionGroup.optionProjectParameters);    
    guiOptionPanel.setup(optionParametersClass,"",900,100);
    guiOptionPanel.setName("Options");
    ofAddListener(optionParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);

   
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

    matrixSamBuf.setElementHeight(26);
    matrixSamBuf.allowMultipleActiveToggles(false);
    guiSamplerPanelMatrixBuf.add(&matrixSamBuf);
    guiSamplerPanelMatrixBuf.setup("","",220,125);
    //guiSamplerPanelMatrixBuf.setShowHeader(false);
    //page
    samplerPage.setup("sampler", "", 470,440);
    samplerPage.setSize(440,200);
    samplerPage.add(&guiSamplerPanel);
    samplerPage.add(&guiSamplerPanel2);
    samplerPage.add(&guiSamplerPanelMatrixCam);
    samplerPage.add(&guiSamplerPanelMatrixBuf);
    ofAddListener(samplerParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(samplerParametersClassSecond.parameterChangedE(),this,&ofApp::guiEvent2);

    allParameters.add(videoParametersClass);
    allParameters.add(imageParametersClass);
    allParameters.add(kinectParametersClass);
    allParameters.add(kinectParametersSecondClass);
    allParameters.add(cameraParametersClass);
    allParameters.add(cameraParametersSecondClass);
    allParameters.add(camMatrixParameters);
    allParameters.add(Parameters3dClass);
    allParameters.add(slideshowParametersClass);
    allParameters.add(slideshowParametersClassSC);
    allParameters.add(slideshowParametersClassTS);
    allParameters.add(optionParametersClass);
    allParameters.add(quadSelectionParametersClass);
    allParameters.add(quadSelectionGroupParametersClass);
    allParameters.add(quadOptionsParametersClass);
    allParameters.add(quadOptionsParametersClassSecond);
    allParameters.add(quadOptionsParametersClassGlobalQuad);
    allParameters.add(samplerParametersClass);
    allParameters.add(samplerParametersClassSecond);
    msg.setup(allParameters);



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
    vidGrabber.setVerbose(false);
    //vidGrabber.setPixelFormat(parseDesiredPixelFormat("RGB"));
    //vidGrabber.initGrabber(camWidth, camHeight);
}
void ofApp::setupQuadSelectionPages(){
     //QuadSelection----------------------------------------

    //guiQuadSelectionPanel.setup("Quad Selection");
    guiQuadSelectionPanel.setAlignHorizontal();
    guiQuadSelectionPanel.setShowHeader(false);
    guiQuadSelectionPanelSecond.setAlignHorizontal();
    guiQuadSelectionPanelSecond.setup("","",0,25);
    guiQuadSelectionPanelSecond.setShowHeader(false);

    vector<ofParameter<bool>> quads;
    for(int i=0;i<72;i++){
        quads.push_back(ofParameter<bool>("q"+to_string(i),false));
    }
    for(unsigned int i = 0; i < 36; i++) {
        if (i==3)guiQuadSelectionPanel.add(new ofxMinimalToggle(quads.at(i).set("q3",true),24, 24));
        else guiQuadSelectionPanel.add(new ofxMinimalToggle(quads.at(i),24, 24));
        //guiQuadSelectionPanel.add(new ofxToggle(quads.at(i).set(to_string(i),false),20, 20));
    }
    for(unsigned int i = 36; i < quads.size(); i++) {
        //guiQuadSelectionPanelSecond.add(new ofxToggle(quads.at(i).set(to_string(i),false),20, 20));
        guiQuadSelectionPanelSecond.add(new ofxMinimalToggle(quads.at(i),24, 24));
    }
    for(unsigned int i = 0; i < quads.size(); i++) {
        quadSelectionParametersClass.add(quads.at(i));
    }
    //Groups
    guiQuadSelectionPanelGroup.setup("Groups","",770,00);
    guiQuadSelectionPanelGroup.setAlignHorizontal();
    guiQuadSelectionPanelGroup.setShowHeader(false);
    vector<ofParameter<bool>> quadsGroups;
    for(int i=0;i<9;i++){
        quadsGroups.push_back(ofParameter<bool>("group"+to_string(i),false));
    }
    for(unsigned int i = 36; i < quadsGroups.size(); i++) {
        guiQuadSelectionPanelGroup.add(new ofxMinimalToggle(quadsGroups.at(i).set("group"+to_string(i),false),20, 60));
    }
    for(unsigned int i = 0; i < quadsGroups.size(); i++) {
        quadSelectionGroupParametersClass.add(quadsGroups.at(i));
    }
    quadSelectionPage.setup("Quad Selection");
    quadSelectionPage.add(&guiQuadSelectionPanel);
    quadSelectionPage.add(&guiQuadSelectionPanelSecond);
    quadSelectionPage.add(&guiQuadSelectionPanelGroup);
    quadSelectionPage.setDefaultBackgroundColor(ofColor(0xff,0xa5,0x8d,100));
    quadSelectionPage.setDefaultFillColor(ofColor(0xff,0xa5,0x8d,100));
    quadSelectionPage.setSize(1090,90);
    ofAddListener(quadSelectionParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(quadSelectionGroupParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);


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
    quadOptionsPages.setDefaultBackgroundColor(ofColor(0xff,0xa5,0x8d,100));

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
    matrix_cams.push_back(ofParameter<bool>("Cam0",false));
    matrix_cams.push_back(ofParameter<bool>("Cam1",false));
    matrix_cams.push_back(ofParameter<bool>("Cam2",false));
    matrix_cams.push_back(ofParameter<bool>("Cam3",false));
    for(unsigned int i = 0; i < matrix_cams.size(); i++) {
        matrixCam.add(new ofxMinimalToggle(matrix_cams.at(i)));
    }

    matrixCam.setElementHeight(26);
    matrixCam.allowMultipleActiveToggles(false);
    guiCameraPanel.add(&matrixCam);
    //Panel2 guiCamera
    guiCameraPanel2.setup(cameraParametersSecondClass,"", 220);
    guiCameraPanel2.setName("Camera Sampler");
    //matrix sampler
    vector<ofParameter<bool>> matrix_sampler;
    matrix_sampler.push_back(ofParameter<bool>("Sam0",false));
    matrix_sampler.push_back(ofParameter<bool>("Sam1",false));
    matrix_sampler.push_back(ofParameter<bool>("Sam2",false));
    matrix_sampler.push_back(ofParameter<bool>("Sam3",false));
    matrixSampler.setup("c Sampler Slot",4);
    for(unsigned int i = 0; i < matrix_sampler.size(); i++) {
        matrixSampler.add(new ofxMinimalToggle(matrix_sampler.at(i)));
    }

    matrixSampler.setElementHeight(26);
    matrixSampler.allowMultipleActiveToggles(false);
    guiCameraPanel2.add(&matrixSampler);
    //sampler buffer
    vector<ofParameter<bool>> matrix_buffer;
    matrix_buffer.push_back(ofParameter<bool>("Buf0",false));
    matrix_buffer.push_back(ofParameter<bool>("Buf1",false));
    matrix_buffer.push_back(ofParameter<bool>("Buf2",false));
    matrix_buffer.push_back(ofParameter<bool>("Buf3",false));
    matrixBuffer.setup("c Buffer Slot",4);
    for(unsigned int i = 0; i < matrix_buffer.size(); i++) {
        matrixBuffer.add(new ofxMinimalToggle(matrix_buffer.at(i)));
    }

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
    matrix_renderModes.push_back(ofParameter<bool>("3d smooth",false));
    matrix_renderModes.push_back(ofParameter<bool>("3d wire",false));
    matrix_renderModes.push_back(ofParameter<bool>("3d dots",false));
    matrix3dRenderModes.setup("3d animation type",3);
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
    inputPages.setSize(440, 500);
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
    bgImage.draw(400,200);
    quadSelectionPage.draw();
    inputPages.draw();
    guiOptionPanel.draw();
    quadOptionsPages.draw();
    //vidGrabber.draw(460,100);
    samplerPage.draw();

}

void ofApp::guiEvent2(ofAbstractParameter &e){
ofxOscMessage m;
msg.setOscMessage(e,m);
cout<<e.cast<bool>().get()<<endl;
for(unsigned int i=0;i<quadSelectionParametersClass.size();i++){
    if (e.getName().find("Load") != string::npos){
        sender.sendMessage(m);
    }
    else if(quadSelectionParametersClass.getBool(i)){
        ofxOscMessage q;
        msg.setActiveQuad(q,i);
        sender.sendMessage(q);
        sender.sendMessage(m);
        cout << m.getAddress() +" " +m.getArgAsString(0)<< endl;
    }
}


}
  
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
