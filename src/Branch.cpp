//
//  Branch.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "Branch.hpp"

Branch::Branch(ofApp& ofApp) : Entity(BRANCH_STARTING_LIFE), ofApp_(ofApp) {
    id_=ofApp.getNewBranchId();
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
    std::shared_ptr<Branch> childBranchPtr = std::make_shared<Branch>(ofApp_);
    ofApp_.subscribeAliveEntity(childBranchPtr);
    addChild(childBranchPtr);
};

void Branch::looseLife(float amount){
    life_ -= amount;
    if( life_ <0 ){
        die();
        std::for_each(children_.begin(), children_.end(), [](std::shared_ptr<Branch> e) {e->die();});
        //tell parent branch to remove me
        //tell birds to move elsewhere
    }
}

void Branch::removeDeadChildren()
{
    children_.erase(std::remove_if(children_.begin(), children_.end(),
    [](const std::shared_ptr<Branch>& e) {return e->markedForDeath;}),
                    children_.end());
}
