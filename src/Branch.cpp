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
    if (life_ > BRANCH_GROWTH_POINT)
      {
          spawnChild();
          life_ = BRANCH_GROWTH_RESULT;
      }
};

void Branch::grow(){
    life_ += ofApp_.branchGrowthPerTurn();
};

void Branch::spawnChild(){
//   std::shared_ptr<Branch> childBranchPtr = std::make_shared<Branch>(ofApp_, i);
//    ofApp_.aliveEntities_.push_back(branchPtr);
//    addChild(newBranchPtr);
//    totalBranchCounter_++;
};
