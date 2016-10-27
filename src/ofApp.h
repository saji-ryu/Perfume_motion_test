#pragma once

#include "ofMain.h"
#include "SphereGroup.hpp"
#include "ofxBvh.h"
#include "ofxGui.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
        void setupJoints();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    ofxToggle atoggle, ktoggle, ntoggle;
    
    vector<ofxBvh> bvh;
    ofSoundPlayer player;
    ofEasyCam cam;
    
    bool click = false;
    
    vector<ofVec3f> Ajoints, AprevJoints, Kjoints, KprevJoints, Njoints, NprevJoints;
    
    ofVec3f r1[27],r2[27],r3[27];
    
    string msg;
    
    ofSoundPlayer Sound;
    float * fft;
    int Bands;
    float Low = 0;
    float Low2 = 0;
    float a;
    
    float rotate;
    float play_rate, play_rate_t;
    
    SphereGroup spheres[12];

};
