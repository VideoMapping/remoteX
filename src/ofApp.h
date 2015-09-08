#include "ofMain.h"
#include "ofxOsc.h"
#include "oscMessages.h"
#include "ofxGui.h"
#include "ofxGuiExtended.h"
#include "guiVideo.h"
#include "guiImage.h"
#include "guiKinect.h"
#include "guiCamera.h"
#include "gui3d.h"
#include "guiSlideshow.h"
#include "guiSampler.h"
#include "guiOptions.h"
#include "guiQuadOptions.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp
{
	public:

    void setup();
    void setupInputPages();
    void setupQuadOptionsPages();
    void setupQuadSelectionPages();
    void setupPreviewVideo();
	void update();
	void draw();
	void exit();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofImage bgImage;
    ofParameterGroup allParameters;
    //VideoPanel
    ofxPanelExtended guiVideoPanel;
    ofParameterGroup videoParametersClass;
    GuiVideo videoGroup;
    ofxGuiPage videoPage; 
    //ImagePanel
    ofxPanelExtended guiImagePanel;
    ofParameterGroup imageParametersClass;
    GuiImage imageGroup;
    ofxGuiPage imagePage;
    //KinectPanel
    ofParameterGroup kinectParametersClass;
    ofxPanelExtended guiKinectPanel;
    ofParameterGroup kinectParametersSecondClass;
    ofxPanelExtended guiKinectPanel2;
    GuiKinect kinectGroup;
    ofxGuiPage kinectPage; 
    //CameraPanel
    ofParameterGroup cameraParametersClass;
    ofxPanelExtended guiCameraPanel;
    ofParameterGroup cameraParametersSecondClass;
    ofxPanelExtended guiCameraPanel2;
    GuiCamera cameraGroup;
    ofxGuiPage cameraPage;
    ofxGuiMatrix matrixCam;
    //CameraMatrix
    ofParameter<bool> cam0;
    ofParameter<bool> cam1;
    ofParameter<bool> cam2;
    ofParameter<bool> cam3;
    ofParameterGroup camMatrixParameters;
    ofxGuiMatrix matrixSampler; 
    ofxGuiMatrix matrixBuffer; 
    //3dPanel
    ofParameterGroup Parameters3dClass;
    ofxPanelExtended gui3dPanel;
    Gui3d Group3d;
    ofxGuiPage Page3d;
    ofxGuiMatrix matrix3dRenderModes;
    //SlideshowPanel
    ofxPanelExtended guiSlideshowPanel;
    ofParameterGroup slideshowParametersClass;
    ofxPanelExtended guiSlideshowPanelSC;
    ofParameterGroup slideshowParametersClassSC;
    ofxPanelExtended guiSlideshowPanelTS;
    ofParameterGroup slideshowParametersClassTS;
    GuiSlideshow slideshowGroup;
    ofxGuiPage slideshowPage;
    //Input pages
    ofxTabbedPages inputPages; 

    //optionsPanel
    ofxPanelExtended guiOptionPanel;
    ofParameterGroup optionParametersClass;
    GuiOption optionGroup;
    //QuadSelectionPanel
    ofxPanelExtended guiQuadSelectionPanel;
    ofxPanelExtended guiQuadSelectionPanelSecond;
    ofxPanelExtended guiQuadSelectionPanelGroup;
    ofParameterGroup quadSelectionParametersClass;
    ofParameterGroup quadSelectionGroupParametersClass;
    ofxGuiMatrix matrixQuadSelection;
    ofxGuiPage quadSelectionPage;
    unsigned int activeQuad;
    //QuadOptionsPanel
    ofxPanelExtended guiQuadOptionsPanel;
    ofParameterGroup quadOptionsParametersClass;
    ofxPanelExtended guiQuadOptionsPanel2;
    ofParameterGroup quadOptionsParametersClassSecond;
    ofxGuiMatrix matrixBlendingModes;
    ofParameterGroup quadOptionsParametersClassGlobalQuad;
    ofxPanelExtended guiQuadOptionsPanelGlobalQuad;
    ofxGuiPage quadOptionsGlobalQuadPage;
    ofxGuiPage quadOptionsTransformPage;
    ofxGuiPage quadOptionsEffectsPage;
    ofxTabbedPages quadOptionsPages; 
    GuiQuadOptions quadOptionsGroup;
    //SamplerPanel
    ofxPanelExtended guiSamplerPanel;
    ofParameterGroup samplerParametersClass;
    ofxPanelExtended guiSamplerPanel2;
    ofParameterGroup samplerParametersClassSecond;
    ofParameterGroup samplerParametersClassCamBuf;
    ofxGuiMatrix matrixSamCam;
    ofxGuiMatrix matrixBufferSam;
    ofxGuiPage  samplerPage; 
    GuiSampler samplerGroup;
    //previewVideo

    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    //osc
    void guiEvent(ofAbstractParameter &e);
    void guiEventInputs(ofAbstractParameter &e);
    void guiEventQuad(ofAbstractParameter &e);
    ofxOscSender sender;
    oscMessages  msg;
    bool drawPadding;
    bool bFullscreen;

	float red, green, blue;
	float videox;
    float videoy;
    float video_color_r;
    float video_color_g;
    float video_color_b;
    float video_color_a;
    float video_speed;

    int video_volume;

    //global config vars
    int nbOfCam=4;
    int SharedSamplerIndex,SharedSamplerBufferIndex=0;


    ofTrueTypeFont font;

};