//
//  SphereGroup.cpp
//  of_bvh_test
//
//  Created by 左治木　隆成 on 2016/07/19.
//
//

#include "SphereGroup.hpp"



void SphereGroup::init(){
    for (int  i=0; i<100; i++) {
        //ofVec3f r = ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
        ofVec3f r = ofVec3f(0,0,0);
        spheregroup.push_back(r);
    }

}

void SphereGroup::update(ofVec3f _goalpos){
    if(count == 0){
        for (int i = 0; i<100; i++) {
            spheregroup[i] = _goalpos;
        }
    }
    count += 1;
    
    for (int i=0; i<100; i++) {
        spheregroup[i] = spheregroup[i+1];
    }
    spheregroup[100] = _goalpos;
}

void SphereGroup::display(ofColor _color){
    
    ofSetColor(_color);
    for (int j = 0; j<spheregroup.size(); j++) {
        for (int i = 0 ; i < 3 ; i++) {
            ofVec3f random = ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
            ofDrawSphere(spheregroup[j] + random * (100- j) * (100- j) /80 , j*2/85);
        }
    }
    
    
    
}
