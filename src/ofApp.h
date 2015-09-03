#ifndef OF APP
#define OF APP

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp
{
	public:

    void setup();
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
    //GuiVideo Section
    ofxPanel guiVideo;
    ofxLabel gVlabelVideo;
    ofxToggle gVtoggleOnOff;
    ofxToggle gVtoggleLoad;
    ofxVec2Slider gV2SliderScale;
    ofxToggle gVtoggFit;
    ofxToggle gVtoggKeepAspect;
    ofxToggle gVtoggHflip;
    ofxToggle gVtoggVflip;
    ofxColorSlider gVcolor;
    ofxFloatSlider gVfsliderSpeed;
    ofxToggle gVtoggLoop;
    ofxToggle gVtoggGreenscreen;
    ofxLabel gVlabelAudio;
    ofxFloatSlider gVfsliderVolume;
    ofParameterGroup videoParameters;
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

#endif
