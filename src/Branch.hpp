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
    Branch(ofApp& ofApp, int steps);
    
    //getters & setters
    int stepsFromRoot() const { return stepsFromRoot_; }
    void addChild(std::shared_ptr<Branch> child);
    void setParent(std::shared_ptr<Branch> parent) { parent_ = parent; }
    
    //simulation
    virtual void update();
    void grow();
    void spawnChild();
    void looseLife(float amount);
    void removeDeadChildren();
    void die() override;
    
    //render
    void relocateChildren();
    
private:
    int stepsFromRoot_;
    
    std::shared_ptr<Branch> parent_;
    std::vector<std::shared_ptr<Branch>> children_;
    ofApp& ofApp_;
};

#endif /* Branch_hpp */
