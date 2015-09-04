#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxGuiExtended.h"
#include "guiVideo.h"
#include "guiImage.h"
#include "guiKinect.h"
#include "guiCamera.h"
#include "gui3d.h"
#include "guiSlideshow.h"
#include "guiOptions.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp
{
	public:

    void setup();
    void setupInputPages();
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

	ofxUISuperCanvas *gui0;
	ofxUISuperCanvas *gui1;
    ofxUISuperCanvas *gui2;
    ofxUISuperCanvas *gui3;
    ofxUISuperCanvas *gui4;
    ofxUISuperCanvas *gui5;
    ofxUISuperCanvas *gui6;
    ofxUISuperCanvas *gui7;
    ofxUISuperCanvas *gui8;
    ofxUISuperCanvas *gui9;
    ofxUISuperCanvas *gui10;
    ofxUISuperCanvas *gui11;
    ofxUISuperCanvas *gui12;
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
    ofParameter<bool> cam2;
    ofParameter<bool> cam3;
    ofParameter<bool> cam1;
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
    ofParameterGroup quadSelectionParametersClass;
    ofxGuiMatrix matrixQuadSelection;


	void guiEvent(ofxUIEventArgs &e);
    void guiEvent2(ofAbstractParameter &e);

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

    ofxOscSender sender;
    ofTrueTypeFont font;

};