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
    std::vector<std::shared_ptr<Branch>> children() { return children_; }
    
    //simulation
    virtual void update(std::shared_ptr<Entity> e) override;
    void grow();
    void spawnChild();
    void looseLife(float amount);
    void removeDeadChildren();
    void killChildren();
    void die() override;
    
    //render
    void relocateChildren();
    
private:
    int stepsFromRoot_;
    
    std::vector<std::shared_ptr<Branch>> children_;
    ofApp& ofApp_;
};

#endif /* Branch_hpp */
