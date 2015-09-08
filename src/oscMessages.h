#include "ofMain.h"
#include "ofxOsc.h"

class oscMessages {
public:
	void setOscMessageInputs(ofAbstractParameter &e,ofxOscMessage &m,int quad);
	void setOscMessageQuadOptions(ofAbstractParameter &e,ofxOscMessage &m, int quad);
	void setOscMessage(ofAbstractParameter &e,ofxOscMessage &m,int quad);

	void setActiveQuad(ofxOscMessage &m,int quad);
	void setVideo(ofAbstractParameter &e,ofxOscMessage &m,string adress);
	void setImage(ofAbstractParameter &e,ofxOscMessage &m,string adress);
	void setKinect(ofAbstractParameter &e,ofxOscMessage &m,string adress);
	void setCamera(ofAbstractParameter &e,ofxOscMessage &m,string adress);
	void set3d(ofAbstractParameter &e,ofxOscMessage &m,string adress);
	void setSlideshow(ofAbstractParameter &e,ofxOscMessage &m,string adress);

	bool sendOSC;
private:
	bool setParameters;
	void setTheParameters(ofAbstractParameter &e,ofxOscMessage &m);

};