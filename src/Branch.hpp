//
//  Branch.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Branch_hpp
#define Branch_hpp

#include <stdio.h>
#include "Entity.hpp"
#include "ofApp.h"
class ofApp;

class Branch : public Entity{
    
public:
    Branch(ofApp& ofApp, int id);
    
    //getters & setters
    int stepsFromRoot() const { return stepsFromRoot_; }
    int addChild(std::shared_ptr<Branch> child) { children_.push_back(child); };
    
    virtual void update();
    void grow();
    void spawnChild();
    
private:
    int stepsFromRoot_;
    
    std::vector<std::shared_ptr<Branch>> children_;
    ofApp& ofApp_;
};

#endif /* Branch_hpp */
