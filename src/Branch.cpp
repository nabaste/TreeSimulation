//
//  Branch.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "Branch.hpp"

Branch::Branch(ofApp& ofApp, int id) : Entity(id, BRANCH_STARTING_LIFE), ofApp_(ofApp) {
    
};

void Branch::update(){
    grow();
};

void Branch::grow(){
    life_ += ofApp_.branchGrowthPerTurn();
};

void Branch::spawnChild(){
    
};
