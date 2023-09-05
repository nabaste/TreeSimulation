//
//  Bird.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Bird_hpp
#define Bird_hpp

#include <stdio.h>
#include "Entity.hpp"
#include "Constants.h"
#include "ofApp.h"
#include "Branch.hpp"
#include "BirdState.hpp"
#include "AllBirdStates.hpp"
class ofApp;
class Branch;
class BirdState;

class Bird : public Entity {

public:
    
    Bird(ofApp& ofApp, std::shared_ptr<Branch> branch);
    Bird(ofApp& ofApp, std::shared_ptr<Branch> branch, int state, int age);

    // Getters && Setters
    int age() const { return age_; }
    bool isMale() const { return isMale_; }
    std::shared_ptr<Branch> branch() { return branch_; }
    ofApp& getOfApp() { return ofApp_; }
    std::shared_ptr<BirdState> getState() {  return state_; }
    void setState(std::shared_ptr<BirdState> state) { state_ = state; }
    void setBranch(std::shared_ptr<Branch> branch) { branch_ = branch; }
    //std::shared_ptr<Bird> getObjectSharedPtr() { return shared_from_this(); }
    
    // Simulation
    virtual void update() override;
    void grow();
    void eat();
    void onBranchDeath();
    void die() override;
    
    // Render
    void refreshPosition();
    
private:
    int age_;
    bool isMale_;
    
    ofApp& ofApp_;
    
    std::shared_ptr<Branch> branch_;
    std::shared_ptr<BirdState> state_;
};

#endif /* Bird_hpp */
