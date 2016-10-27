//
//  SphereGroup.hpp
//  of_bvh_test
//
//  Created by 左治木　隆成 on 2016/07/19.
//
//

#ifndef SphereGroup_hpp
#define SphereGroup_hpp

#include <stdio.h>
#include <ofMain.h>

class SphereGroup {
    
public:
    
    void init();
    void update(ofVec3f _goalpos);
    void display(ofColor _color);
    
    vector<ofVec3f> spheregroup;
    int count = 0;
    
    
private:
    
};

#endif /* SphereGroup_hpp */
