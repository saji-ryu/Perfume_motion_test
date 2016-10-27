#include "ofApp.h"

const float trackDuration = 64.28;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    ofBackground(0);
    
    play_rate = play_rate_t = 1;
    rotate = 0;
    
    Bands = 1024;
    
    gui.setup("person");
    gui.add(atoggle.setup("A-CHAN",true));
    gui.add(ktoggle.setup("KASHIYUKA",true));
    gui.add(ntoggle.setup("NOCCHi",true));;
    
    Sound.loadSound("Perfume_globalsite_sound.wav");
    Sound.play();
    Sound.setLoop(true);
    
    bvh.resize(3);
    // setup bvh
    bvh[0].load("aachan.bvh");
    bvh[1].load("kashiyuka.bvh");
    bvh[2].load("nocchi.bvh");
    
    for (int i = 0; i < bvh.size(); i++)
    {
        bvh[i].play();
        bvh[i].setLoop(true);
    }
    
    
    for (int i = 0; i<12; i++) {
        spheres[i].init();
    }
    
    for (int i=0; i<27; i++) {
        r1[i] = ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
        r2[i] = ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
        r3[i] = ofVec3f(ofRandom(-15,15),ofRandom(-15,15),ofRandom(-15,15));
        }
    
    setupJoints();
    
    

}

void ofApp::setupJoints() {
    for (int i = 0; i < bvh.size(); i++) {
        if(i==0){
            Ajoints.assign(bvh[i].getNumJoints(), ofVec3f());
            AprevJoints.assign(bvh[i].getNumJoints(), ofVec3f());
        }else if(i==1){
            Kjoints.assign(bvh[i].getNumJoints(), ofVec3f());
            KprevJoints.assign(bvh[i].getNumJoints(), ofVec3f());
        }else if(i==2){
            Njoints.assign(bvh[i].getNumJoints(), ofVec3f());
            NprevJoints.assign(bvh[i].getNumJoints(), ofVec3f());
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    
    fft = ofSoundGetSpectrum(Bands);
    Low = ((fft[3]+fft[4])*2+(fft[5]/8+1)*(fft[6]/8+1)*(fft[7]/8+1))/4;
    Low2 = (fft[10]+fft[11]+fft[12])/2;
    
    play_rate += (play_rate_t - play_rate) * 0.3;
    Sound.setSpeed(play_rate);
    
    float t = (Sound.getPosition() * trackDuration);
    t = t / bvh[0].getDuration();
    
    
    
    for (int i = 0; i < bvh.size(); i++){
        bvh[i].update();
        bvh[i].setPosition(t);
        if (bvh[i].isFrameNew()) {
            if(i==0){
                for (int j = 0; j < bvh[i].getNumJoints(); j++) {
                    AprevJoints[j] = Ajoints[j];
                    Ajoints[j] = bvh[i].getJoint(j)->getPosition();
                }
            }else if(i==1){
                for (int j = 0; j < bvh[i].getNumJoints(); j++) {
                    KprevJoints[j] = Kjoints[j];
                    Kjoints[j] = bvh[i].getJoint(j)->getPosition();
                }
            }else if(i==2){
                for (int j = 0; j < bvh[i].getNumJoints(); j++) {
                    NprevJoints[j] = Njoints[j];
                    Njoints[j] = bvh[i].getJoint(j)->getPosition();
                }
            }
            
        }
    }
    
    
        spheres[0].update(Ajoints[12]);
        spheres[1].update(Ajoints[17]);
        spheres[2].update(Ajoints[22]);
        spheres[3].update(Ajoints[26]);
        spheres[4].update(Kjoints[12]);
        spheres[5].update(Kjoints[17]);
        spheres[6].update(Kjoints[22]);
        spheres[7].update(Kjoints[26]);
        spheres[8].update(Njoints[12]);
        spheres[9].update(Njoints[17]);
        spheres[10].update(Njoints[22]);
        spheres[11].update(Njoints[26]);
    
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    glEnable(GL_DEPTH_TEST);
    
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    cam.begin();
    
    for (int i = 0; i < bvh.size(); i++)
    {
        //bvh[i].draw();
    }
    
    //A-CHAN
    if(atoggle){
        ofSetColor(255, 98, 206);
        ofDrawSphere(Ajoints[7], Low*7);
        ofDrawSphere(Ajoints[12], 7);
        ofDrawSphere(Ajoints[17], 7);
        ofDrawSphere(Ajoints[22], 7);
        ofDrawSphere(Ajoints[27], 7);
        
        ofSetColor(255);
        for (int i = 0; i<6; i++) {
            ofDrawTriangle(Ajoints[i]+r1[i],Ajoints[i]+r2[i],Ajoints[i+1]);
        }
        for (int i = 12; i>8; i--) {
            ofDrawTriangle(Ajoints[i]+r1[i],Ajoints[i]+r2[i],Ajoints[i-1]);
        }
        for (int i = 17; i>13; i--) {
            ofDrawTriangle(Ajoints[i]+r1[i],Ajoints[i]+r2[i],Ajoints[i-1]);
        }
        for (int i = 18; i<21; i++) {
            ofDrawTriangle(Ajoints[i]+r1[i],Ajoints[i]+r2[i],Ajoints[i+1]);
        }
        for (int i = 23; i<26; i++) {
            ofDrawTriangle(Ajoints[i]+r1[i],Ajoints[i]+r2[i],Ajoints[i+1]);
        }
        ofDrawTriangle(Ajoints[7]+ofVec3f(6,0,0),Ajoints[7]+ofVec3f(-6,0,0),Ajoints[6]);
    }
    
    
    if (ktoggle) {
        ofSetColor(123, 247, 85);
        ofDrawSphere(Kjoints[7], Low*7);
        ofDrawSphere(Kjoints[12], 7);
        ofDrawSphere(Kjoints[17], 7);
        ofDrawSphere(Kjoints[22], 7);
        ofDrawSphere(Kjoints[27], 7);
        
        ofSetColor(255);
        for (int i = 0; i<6; i++) {
            ofDrawTriangle(Kjoints[i]+r1[i],Kjoints[i]+r2[i],Kjoints[i+1]);
        }
        for (int i = 12; i>8; i--) {
            ofDrawTriangle(Kjoints[i]+r1[i],Kjoints[i]+r2[i],Kjoints[i-1]);
        }
        for (int i = 17; i>13; i--) {
            ofDrawTriangle(Kjoints[i]+r1[i],Kjoints[i]+r2[i],Kjoints[i-1]);
        }
        for (int i = 18; i<21; i++) {
            ofDrawTriangle(Kjoints[i]+r1[i],Kjoints[i]+r2[i],Kjoints[i+1]);
        }
        for (int i = 23; i<26; i++) {
            ofDrawTriangle(Kjoints[i]+r1[i],Kjoints[i]+r2[i],Kjoints[i+1]);
        }
        ofDrawTriangle(Kjoints[7]+ofVec3f(6,0,0),Kjoints[7]+ofVec3f(-6,0,0),Kjoints[6]);
    }
    
    
    if (ntoggle) {
        ofSetColor(124, 212, 255);
        ofDrawSphere(Njoints[7], Low*7);
        ofDrawSphere(Njoints[12], 7);
        ofDrawSphere(Njoints[17], 7);
        ofDrawSphere(Njoints[22], 7);
        ofDrawSphere(Njoints[27], 7);
        
        ofSetColor(255);
        for (int i = 0; i<6; i++) {
            ofDrawTriangle(Njoints[i]+r1[i],Njoints[i]+r2[i],Njoints[i+1]);
        }
        for (int i = 12; i>8; i--) {
            ofDrawTriangle(Njoints[i]+r1[i],Njoints[i]+r2[i],Njoints[i-1]);
        }
        for (int i = 17; i>13; i--) {
            ofDrawTriangle(Njoints[i]+r1[i],Njoints[i]+r2[i],Njoints[i-1]);
        }
        for (int i = 18; i<21; i++) {
            ofDrawTriangle(Njoints[i]+r1[i],Njoints[i]+r2[i],Njoints[i+1]);
        }
        for (int i = 23; i<26; i++) {
            ofDrawTriangle(Njoints[i]+r1[i],Njoints[i]+r2[i],Njoints[i+1]);
        }
        ofDrawTriangle(Njoints[7]+ofVec3f(6,0,0),Njoints[7]+ofVec3f(-6,0,0),Njoints[6]);
    }
    
    
    for (int i = 0; i<12; i++) {
        if(i<4 && atoggle){
            spheres[i].display(ofColor(255, 98, 206));
        }
        if(i>=4 && i<8 && ktoggle){
            spheres[i].display(ofColor(123, 247, 85));
        }
        if(i>=8 && ntoggle){
            spheres[i].display(ofColor(124, 212, 255));
        }
            
        
    }
    
    
    cam.end();
    
    glDisable(GL_DEPTH_TEST);
    gui.draw();
    
    
    //ofSetWindowTitle(ofToString(ofGetFrameRate()));
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    click = !click;
    if(click){
        for (int i = 0; i<bvh.size(); i++) {
            bvh[i].stop();
        }
    }else{
        for (int i = 0; i<bvh.size(); i++) {
            bvh[i].play();
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
