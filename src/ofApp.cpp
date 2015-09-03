#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
	ofBackground(50, 100, 50, 255);
	//ofEnableSmoothing();
    ofSetCircleResolution(60);

    sender.setup(HOST, PORT);

    bgImage.loadImage("image/bg.png");

    video_color_r = 10; video_color_g = 10; video_color_b = 10; video_color_a = 10;
    drawPadding = false;

    ///the setups
    
    videoGroup.setup();
    imageGroup.setup();
    kinectGroup.setup();
    cameraGroup.setup();
    Group3d.setup();

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
    guiKinectPanel2.setup(kinectParametersSecondClass,"", 260);
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
    guiCameraPanel2.setup(cameraParametersSecondClass,"", 260);
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
    cameraPage.setup("Camera");
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
    //input pages
    inputPages.setup("Inputs", "",20,20);
    inputPages.setSize(480, 330);
    inputPages.add(&videoPage);
    inputPages.add(&imagePage);
    inputPages.add(&kinectPage);
    inputPages.add(&cameraPage);
    inputPages.add(&Page3d);

    ofAddListener(videoParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(imageParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(kinectParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(kinectParametersSecondClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(cameraParametersClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(cameraParametersSecondClass.parameterChangedE(),this,&ofApp::guiEvent2);
    ofAddListener(Parameters3dClass.parameterChangedE(),this,&ofApp::guiEvent2);






    //--GUI2--------------------------------------------------------

    gui2 = new ofxUISuperCanvas("Global");
    gui2->setPosition(840, 50);
    gui2->setVisible(true);
    gui2->addSpacer();
    gui2->addLabel("Live Projection");
    gui2->addSpacer();
    gui2->addToggle("live stop/start", false);
    gui2->addToggle("live resync", false);
    gui2->addToggle("live fc on/off", false);
    gui2->addToggle("display gui", true);
//    gui2->addToggle("modesetup on/off", false);
    gui2->addToggle("mpe", false);
    gui2->addSpacer();
    gui2->addLabel("Project");
    gui2->addSpacer();
    gui2->addButton("direct save", false);
    gui2->addButton("direct load", false);
    gui2->addToggle("save file", false);
    gui2->addToggle("load file", false);
    gui2->addSpacer();
    gui2->addLabel("Edge Blend");
    gui2->addSpacer();
    gui2->addToggle( "eb on/off", false);
    gui2->addMinimalSlider("power", 0.0, 4.0, 1.0);
    gui2->addMinimalSlider("gamma", 0.0, 4.0, 1.8);
    gui2->addMinimalSlider("luminance", -4.0, 4.0, 1.0);
    gui2->addMinimalSlider("left edge", 0.0, 0.5, 0.3);
    gui2->addMinimalSlider("right edge", 0.0, 0.5, 0.3);
    gui2->addMinimalSlider("top edge", 0.0, 0.5, 0.3);
    gui2->addMinimalSlider("bottom edge", 0.0, 0.5, 0.3);
    gui2->addSpacer();
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&ofApp::guiEvent);



//--GUI3--------------------------------------------------------

    gui3 = new ofxUISuperCanvas("Quad");
    gui3->setPosition(630, 50);
    gui3->setVisible(true);
    gui3->addMinimalSlider("active quad", 0.0, 72.0, 3.0);
    //textinput->setAutoUnfocus(false);
    gui3->addSpacer();
    gui3->addLabel("Surface");
    gui3->addSpacer();
    gui3->addToggle( "show/hide", true);
    gui3->addToggle( "use timeline", true);
    gui3->addMinimalSlider("seconds", 10, 3600, 100);
    gui3->addToggle( "tl tint", false);
    gui3->addToggle( "tl color", false);
    gui3->addToggle( "tl alpha", false);
    gui3->addToggle( "tl 4 slides", false);

    float dim = (gui3->getGlobalCanvasWidth() - gui3->getPadding()*7.0)*0.5;

    gui3->addSpacer();
    gui3->addLabel("Blending modes");
    gui3->addSpacer();
    gui3->addToggle( "bm on/off", false);

    vector<string> items;
    items.push_back("screen");
    items.push_back("add");
    items.push_back("subtract");
    items.push_back("multiply");

    gui3->addDropDownList("blending mode", items, dim);
    gui3->addLabel("");
    gui3->addLabel("");
    gui3->addLabel("");
    gui3->addLabel("");
    gui3->addSpacer();
    gui3->addLabel("Mask");
    gui3->addSpacer();
    gui3->addToggle("m on/off", false);
    gui3->addToggle("m invert", false);
    gui3->addToggle("mask edit on/off", false);
    gui3->addSpacer();
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&ofApp::guiEvent);


//----GUI4--------------------------------------------------------

    gui4 = new ofxUISuperCanvas("Capture & CV");
    gui4->addLabel("Greenscreen");
    gui4->addSpacer();
    gui4->setPosition(420, 50);
    gui4->setVisible(true);
	gui4->addMinimalSlider("threshold", 0.0, 255.0, 10.0);
    gui4->addMinimalSlider("gs red", 0.0, 1.0, 0.0);
    gui4->addMinimalSlider("gs green", 0.0, 1.0, 0.0);
    gui4->addMinimalSlider("gs blue", 0.0, 1.0, 0.0);
    gui4->addMinimalSlider("gs alpha", 0.0, 1.0, 0.0);
    gui4->addSpacer();
    gui4->autoSizeToFitWidgets();
    //gui4->getRect()->setWidth(ofGetWidth());
    ofAddListener(gui4->newGUIEvent,this,&ofApp::guiEvent);


//----GUI5------------------------------------------------------

    gui5 = new ofxUISuperCanvas("Active Quad");
    gui5->setDimensions(750, 50);
    gui5->setPosition(0, 0);
    gui5->setVisible(false);
    gui5->addMinimalSlider("Number", 0.0, 72.0, 3.0 , 350 , 20);
    gui5->addSpacer();
    gui5->autoSizeToFitWidgets();
    //gui5->getRect()->setWidth(ofGetWidth());
    ofAddListener(gui5->newGUIEvent,this,&ofApp::guiEvent);

//----GUI6------------------------------------------------------



//----GUI7------------------------------------------------------

    gui7 = new ofxUISuperCanvas("Draw");
    gui7->setPosition(1000, 50);
//    gui7->setDimensions(150, ofGetHeight());
    gui7->setVisible(true);
    gui7->addSpacer();
    gui7->addLabel("Slideshow");
    gui7->addSpacer();
    gui7->addToggle("sh on/off", false);
    gui7->addToggle("sh load", false);
    gui7->addMinimalSlider("sh duration", 0.1, 15.0, 1.0);
    gui7->addToggle("sh fit", false);
    gui7->addToggle("sh aspect ratio", false);
    gui7->addToggle("sh greenscreen", false);
    gui7->addSpacer();
    gui7->addLabel("Solid Color");
    gui7->addSpacer();
    gui7->addToggle( "sc on/off", false);
    gui7->addMinimalSlider("sc red", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("sc green", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("sc blue", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("sc alpha", 0.0, 1.0, 0.0);
    gui7->addSpacer();
    gui7->addLabel("Transition");
    gui7->addSpacer();
    gui7->addToggle("tr on/off",false);
    gui7->addMinimalSlider("tr red", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("tr green", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("tr blue", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("tr alpha", 0.0, 1.0, 0.0);
    gui7->addMinimalSlider("tr duration", 0.1, 60.0, 1.0);
    gui7->addSpacer();
    gui7->autoSizeToFitWidgets();
    ofAddListener(gui7->newGUIEvent,this,&ofApp::guiEvent);

//----GUI8------------------------------------------------------
    gui8 = new ofxUISuperCanvas("Quad");
//    gui8->setDimensions(150, ofGetHeight());
//    gui3->setScrollAreaToScreen();
    gui8->setPosition(1470, 50);
    gui8->setVisible(true);
    gui8->addMinimalSlider("active quad", 0.0, 72.0, 3.0);
    gui8->addSpacer();
    gui8->addLabel("rectangular crop");
    gui8->addSpacer();
    gui8->addMinimalSlider("top", 0.0, 1.0, 0.0 );
    gui8->addMinimalSlider("right", 0.0, 1.0, 0.0 );
    gui8->addMinimalSlider("left", 0.0, 1.0, 0.0 );
    gui8->addMinimalSlider("bottom", 0.0, 1.0, 0.0 );
    gui8->addSpacer();
    gui8->addLabel("circular crop");
    gui8->addSpacer();
    gui8->addMinimalSlider("x", 0.0, 1.0, 0.5 );
    gui8->addMinimalSlider("y", 0.0, 1.0, 0.5 );
    gui8->addMinimalSlider("radius", 0.0, 2.0, 0.0 );
    gui8->addSpacer();
    gui8->addLabel("Deform");
    gui8->addSpacer();
    gui8->addToggle("d on/off", false);
    gui8->addToggle("bezier", false);
    gui8->addButton("spherize light", false);
    gui8->addButton("spherize strong", false);
    gui8->addButton("bezier reset", false);
    gui8->addToggle("grid", false);
    gui8->addMinimalSlider("rows num", 2, 15, 5 );
    gui8->addMinimalSlider("columns num", 2, 20, 5 );
    gui8->addToggle("edit", false);
    gui8->addSpacer();
    gui8->autoSizeToFitWidgets();
    ofAddListener(gui8->newGUIEvent,this,&ofApp::guiEvent);

//----GUI9------------------------------------------------------

    gui9 = new ofxUISuperCanvas("Global");
    //gui9->setDimensions(150, ofGetHeight());
    gui9->setPosition(1300, 50);
    gui9->setVisible(true);
    gui9->addSpacer();
    gui9->addLabel("Placement");
    gui9->addSpacer();
    gui9->addMinimalSlider("move x", -1600.0, 1600.0, 0.0);
    gui9->addMinimalSlider("move y", -1600.0, 1600.0, 0.0);
    gui9->addMinimalSlider("width", 0.0, 2400.0, 1280.0);
    gui9->addMinimalSlider("height", 0.0, 2400.0, 1024.0);
    gui9->addButton( "reset", false);
    gui9->addSpacer();
    gui9->addLabel("Help");
    gui9->addSpacer();
    string texthere = "Here all the shortcuts will be presented.";
    gui9->addTextArea("Help text",texthere, OFX_UI_FONT_SMALL);
    gui9->autoSizeToFitWidgets();
    ofAddListener(gui9->newGUIEvent,this,&ofApp::guiEvent);
   // guiTabBar->loadSettings("settings/", "ui-");


    
   // guiTabBar->loadSettings("settings/", "ui-");

   //----gui12--------------------------------------------------------

    gui12 = new ofxUISuperCanvas("Capture & CV");
    gui12->setPosition(210, 650);
    gui12->setVisible(true);
    gui12->addSpacer();
    gui12->addLabel("Sampler");
    gui12->addSpacer();



    gui12->addLabel("cam to record from");
    //gui12->addRadio("s sampnum",capture,OFX_UI_ORIENTATION_HORIZONTAL);


    gui12->addLabel("buffer to record to");
    //gui12->addRadio("b recnum",capture,OFX_UI_ORIENTATION_HORIZONTAL);
    gui12->addSpacer();
    gui12->addToggle( "s record", false);
    gui12->addToggle( "s playany", false);
    gui12->addToggle( "s pause", false);
    gui12->addToggle( "b clear", false);
    gui12->addToggle( "b play0", false);
    gui12->addToggle( "b play1", false);
    gui12->addToggle( "b play2", false);
    gui12->addToggle( "b play3", false);
    gui12->addSpacer();
    gui12->autoSizeToFitWidgets();
    //gui12->getRect()->setWidth(ofGetWidth());
    ofAddListener(gui12->newGUIEvent,this,&ofApp::guiEvent);


}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    inputPages.draw();

}

void ofApp::guiEvent2(ofAbstractParameter &e){
cout << "Ev2"+e.getName() << endl;

}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
/*    string canvasParent = e.widget->getCanvasParent()->getName();
    cout << canvasParent << endl;
*/
    cout << e.widget->getName() << endl;
    if(name == "active quad")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/set");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v load")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/load");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v x scale")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/mult/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v y scale")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/mult/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v fit")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/fit");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v keep aspect")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/keepaspect");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v hflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/hmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v vflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/vmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "audio")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/volume");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "speed")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/speed");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v loop")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/loop");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "v greenscreen")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/video/greenscreen");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
        //greenscreen

    else if(name == "threshold")
    {
    ofxUICircleSlider *csliderValue = (ofxUICircleSlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/greenscreen/threshold");
    m.addFloatArg(csliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "gs red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/greenscreen/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "gs green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/greenscreen/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "gs blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/greenscreen/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "gs alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/greenscreen/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }

    //Kinect
    else if(name == "k on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/show");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k close/open")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/close");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k show img")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/show/image");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k grayscale")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/show/grayscale");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k mask")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/mask");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k detect")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/contour");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k scale x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/mult/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k scale y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/mult/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k threshold near")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/threshold/near");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k threshold far")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/threshold/far");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k angle")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/angle");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k blur")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/blur");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k smooth")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/contour/smooth");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k simplelse ify")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/contour/simplelse ify");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k min blob")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/contour/area/min");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k max blob")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/contour/area/max");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "k alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/kinect/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }




    //slideshow
    else if(name == "sh on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/show");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sh load")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/folder");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }

    else if(name == "sh fit")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/fit");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sh aspect ratio")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/keep_aspect");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sh greenscreen")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/greenscreen");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }


    else if(name == "sh duration")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/slideshow/duration");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "show/hide")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/show");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }

    //timeline

    else if(name == "use timeline")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/timeline/toggle");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "seconds")
    {
    ofxUIMinimalSlider *sliderValue = (ofxUIMinimalSlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/timeline/duration");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tl tint")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/timeline/tint");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tl color")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/timeline/color");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tl alpha")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/timeline/alpha");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tl 4 slides")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/timeline/slides");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }

    //camera

    else if(name == "c on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c load")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c scale x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/mult/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c scale y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/mult/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c fit")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/fit");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c aspect ratio")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/keepaspect");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c hflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/hmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c vflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/vmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "cam audio")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/volume");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "c greenscreen")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/greenscreen");
    m.addFloatArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "camera 0")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/num");
    m.addIntArg(0);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "camera 1")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/num");
    m.addIntArg(1);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "camera 2")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/num");
    m.addIntArg(2);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "camera 3")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/cam/num");
    m.addIntArg(3);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }


    //image

    else if(name == "i on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i load")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/load");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i fit")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/fit");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i aspect ratio")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/keepaspect");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i scale x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/mult/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i scale y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/mult/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i hflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/hmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i vflip")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/vmirror");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i greenscreen")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/greenscreen");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "i alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/img/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }

    //placement
    else if(name == "move x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/placement/x");
    m.addIntArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
     else if(name == "move y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/placement/y");
    m.addIntArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "width")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/placement/w");
    m.addIntArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "height")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/placement/h");
    m.addIntArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "reset")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/placement/reset");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }

    //edge blend

    else if(name == "eb on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
     else if(name == "power")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/power");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "gamma")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/gamma");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "luminance")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/luminance");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "left edge")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/amount/left");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "right edge")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/amount/right");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "top edge")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/amount/top");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "bottom edge")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/edgeblend/amount/bottom");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }

     //blend modes

     else if(name == "bm on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/blendmodes/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
     else if(name == "screen")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/blendmodes/mode");
    m.addIntArg(0);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "add")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/blendmodes/mode");
    m.addIntArg(1);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "subtract")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/blendmodes/mode");
    m.addIntArg(2);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "multiply")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/blendmodes/mode");
    m.addIntArg(3);
    //m.addIntArg(1);
    //m.addIntArg(3);
    //m.addIntArg(4);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }

    //solid color

    else if(name == "sc on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sc red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sc green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sc blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sc alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }

    //Projection

    else if(name == "live resync")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/resync");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "live stop/start")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/stop");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "direct save")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/save");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }
    else if(name == "direct load")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/load");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }
    else if(name == "load file")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/loadfile");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "save file")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/savefile");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "live fc on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/fullscreen/toggle");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "display gui")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/gui/toggle");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }

/*    else if(name == "modesetup on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/mode/setup/toggle");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
*/
    //mask

    else if(name == "m on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/mask/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "m invert")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/mask/invert");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "mask edit on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/projection/mode/masksetup/toggle");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }

    //Deform
    else if(name == "d on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "bezier")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/bezier");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "spherize light")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/bezier/spherize/light");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }
    else if(name == "spherize strong")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/bezier/spherize/strong");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }
    else if(name == "bezier reset")
    {
    ofxUIButton *button = (ofxUIButton *) e.getButton();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/bezier/reset");
    m.addIntArg(button->getValue());
    sender.sendMessage(m);
    }
    else if(name == "grid")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/grid");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "rows num")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/grid/rows");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "columns num")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/grid/columns");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "edit")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/deform/edit");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }

    //crop

    else if(name == "top")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/rectangular/top");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "right")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/rectangular/right");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "left")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/rectangular/left");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "bottom")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/rectangular/bottom");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/circular/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/circular/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "radius")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/crop/circular/radius");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    //active surface
    else if(name == "Number")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/set");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    //transition
    else if(name == "tr on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tr red")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/color/1");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tr green")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/color/2");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tr blue")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/color/3");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tr alpha")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/color/4");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "tr duration")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/solid/trans/duration");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    //3d model
    else if(name == "3d load")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/load");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d scale x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/scale/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d scale y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/scale/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d scale z")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/scale/z");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d rotate x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/rotate/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d rotate y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/rotate/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d rotate z")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/rotate/z");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d move x")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/move/x");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d move y")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/move/y");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "3d move z")
    {
    ofxUISlider *sliderValue = (ofxUISlider *) e.getSlider();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/move/z");
    m.addFloatArg(sliderValue->getValue());
    sender.sendMessage(m);
    }
    else if(name == "animation")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/animation");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
        else if(name == "smooth")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/texture/mode");
    m.addIntArg(0);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "wire")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/texture/mode");
    m.addIntArg(1);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
    else if(name == "dots")
    {
    ofxUIDropDownList *ddl = (ofxUIDropDownList *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/3d/texture/mode");
    m.addIntArg(2);
    m.addIntArg(ddl->getValue());
    sender.sendMessage(m);
    }
     //sampler
    else if(name == "s on/off")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/sampler/show");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "sampler num")
    {
    ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/sampler/num");
    m.addIntArg(radio->getValue());
    sender.sendMessage(m);
    }
    else if(name == "buffer num")
    {
    ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/active/sampler/buffernum");
    m.addIntArg(radio->getValue());
    sender.sendMessage(m);
    }
    else if(name == "s record")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "s playany")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/play");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "s pause")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/pause");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "b clear")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/clear");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "b play0")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/0");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "b play1")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/1");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "b play2")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/2");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "b play3")
    {
    ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
    cout << "got event from: " << name << endl;
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/playbuffer/3");
    m.addIntArg(toggle->getValue());
    sender.sendMessage(m);
    }
    else if(name == "s sampnum")
    {
    ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
    cout << "got event from: " << name << endl;
    SharedSamplerIndex=radio->getValue();
    cout<<"SharedSamplerIndex"<<SharedSamplerIndex<<endl;

    }
    else if(name == "b recnum")
    {
    ofxUIRadio *radio = (ofxUIRadio *) e.getToggle();
    cout << "got event from: " << name << endl;
    SharedSamplerBufferIndex=radio->getValue();
    ofxOscMessage m;
    m.setAddress("/sharedsampler/"+ofToString(SharedSamplerIndex)+"/record/"+ofToString(SharedSamplerBufferIndex));

    m.addIntArg(0);

    sender.sendMessage(m);
    cout<<"message "<<m.getAddress()<<endl;
    }
}
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

    case 'p':
        {
            drawPadding = !drawPadding;

            gui1->setDrawWidgetPadding(drawPadding);
            gui2->setDrawWidgetPadding(drawPadding);
            gui3->setDrawWidgetPadding(drawPadding);
            gui4->setDrawWidgetPadding(drawPadding);
            gui5->setDrawWidgetPadding(drawPadding);
            gui6->setDrawWidgetPadding(drawPadding);
            gui7->setDrawWidgetPadding(drawPadding);
            gui8->setDrawWidgetPadding(drawPadding);
            gui9->setDrawWidgetPadding(drawPadding);

        }
            break;

        case 'a':
        {

        gui1->setVisible(true);
        gui4->setVisible(true);
        gui3->setVisible(true);
        gui2->setVisible(true);
        gui5->setVisible(true);
        gui6->setVisible(false);
        gui7->setVisible(false);
        gui8->setVisible(false);
        gui9->setVisible(false);
        gui11->setVisible(false);

        }
            break;

        case 'q':
        {

        gui1->setVisible(false);
        gui4->setVisible(false);
        gui3->setVisible(false);
        gui2->setVisible(false);
        gui5->setVisible(true);
        gui6->setVisible(true);
        gui7->setVisible(true);
        gui8->setVisible(true);
        gui9->setVisible(true);
        gui11->setVisible(true);
        }

             break;
        case 's':
            {
            //gui0->saveSettings("gui0Settings.xml");
            gui1->saveSettings("gui1Settings.xml");
            gui2->saveSettings("gui2Settings.xml");
            gui3->saveSettings("gui3Settings.xml");
            gui4->saveSettings("gui4Settings.xml");
            gui5->saveSettings("gui5Settings.xml");
            gui6->saveSettings("gui6Settings.xml");
            gui7->saveSettings("gui7Settings.xml");
            gui8->saveSettings("gui8Settings.xml");
            gui9->saveSettings("gui9Settings.xml");
            }
        case 'l':
            {
                //gui0->loadSettings("gui0Settings.xml");
                gui1->loadSettings("gui1Settings.xml");
                gui2->loadSettings("gui2Settings.xml");
                gui3->loadSettings("gui3Settings.xml");
                gui4->loadSettings("gui4Settings.xml");
                gui5->loadSettings("gui5Settings.xml");
                gui6->loadSettings("gui6Settings.xml");
                gui7->loadSettings("gui7Settings.xml");
                gui8->loadSettings("gui8Settings.xml");
                gui9->loadSettings("gui9Settings.xml");
            }
              break;
        case '1':
            {
                //gui0->setMinified(true);
                gui1->setMinified(true);
                gui2->setMinified(true);
                gui3->setMinified(true);
                gui4->setMinified(true);
//                gui5->setMinified(true);
                gui6->setMinified(true);
                gui7->setMinified(true);
                gui8->setMinified(true);
                gui9->setMinified(true);
                gui11->setMinified(true);
            }
                  break;

            case '2':
            {
                //gui0->setMinified(false);
                gui1->setMinified(false);
                gui2->setMinified(false);
                gui3->setMinified(false);
                gui4->setMinified(false);
//                gui5->setMinified(false);
                gui6->setMinified(false);
                gui7->setMinified(false);
                gui8->setMinified(false);
                gui9->setMinified(false);
                gui11->setMinified(false);

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
