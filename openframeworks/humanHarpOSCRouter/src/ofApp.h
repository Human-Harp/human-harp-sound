#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define SEND_PORT 9000
#define NUM_PORTS 2
#define NUM_MSG_STRINGS 35

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void handleMessage(ofxOscMessage m);
        void sendBattery(string ip, float value);
        void sendDistance(string ip, int value);
        void sendVelocity(string ip, int value);
        void sendAzimuth(string ip, int value);
        void sendElevation(string ip, int value);
        void sendAngularRate(string ip, float value);

		ofTrueTypeFont font;
        int sendMessages;
    
        ofxOscReceiver receiver8001;
        ofxOscReceiver receiver8002;
        ofxOscReceiver receiver8003;
        ofxOscReceiver receiver8004;
        ofxOscReceiver receiver8005;
        ofxOscReceiver receiver8006;
        ofxOscReceiver receiver8007;
        ofxOscReceiver receiver8008;
        ofxOscReceiver receiver8009;
        ofxOscReceiver receiver8010;
        ofxOscReceiver receiver8011;
        ofxOscReceiver receiver8012;
    
        ofxOscSender sender;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;
    
        ofImage receivedImage;
};
