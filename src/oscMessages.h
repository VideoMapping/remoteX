#include "ofMain.h"
#include "ofxOsc.h"

class oscMessages {
public:
	void setup(ofParameterGroup g);
	void setOscMessage(ofAbstractParameter &e,ofxOscMessage &m);
	void setActiveQuad(ofxOscMessage &m,int quad);
	void setVideo(ofAbstractParameter &e,ofxOscMessage &m);
	void setImage(ofAbstractParameter &e,ofxOscMessage &m);
	void setKinect(ofAbstractParameter &e,ofxOscMessage &m);
	void setCamera(ofAbstractParameter &e,ofxOscMessage &m);
	void set3d(ofAbstractParameter &e,ofxOscMessage &m);
	void setSlideshow(ofAbstractParameter &e,ofxOscMessage &m);
	ofParameterGroup allParameters;
};