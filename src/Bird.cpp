//
//  Bird.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "Bird.hpp"

Bird::Bird(ofApp& ofApp, std::shared_ptr<Branch> branch): Entity(BIRD_STARTING_LIFE), ofApp_(ofApp), branch_(branch), age_(0)
{
    id_ = ofApp.getNewBirdId();
    isMale_ = rand() % 2;
    //state_ = std::make_shared<GrowingState>(getObjectSharedPtr());
    state_==nullptr;
    position = branch_->position;
}

Bird::Bird(ofApp& ofApp, std::shared_ptr<Branch> branch, int state, int age) :
Entity(BIRD_STARTING_LIFE), ofApp_(ofApp), branch_(branch), age_(age){
    id_ = ofApp.getNewBirdId();
    isMale_ = rand() % 2;
    //if(state == 0){
        //std::shared_ptr<BirdState> newState = std::make_shared<LookingState>(getObjectSharedPtr());
        state_ = nullptr;
    //}
}

void Bird::update(){
    grow();
    state_->update();
    position = branch_->position;
}

void Bird::grow(){
    age_++;
    if(age_ > BIRD_LIFE_EXPECTANCY){
        die();
    }
}

void Bird::eat(){
    branch_->looseLife(BIRD_FOOD_CONSUMPTION);
    life_ += BIRD_LIFE_GROWTH;
}

void Bird::onBranchDeath(){
//    int status = state_->id();
//
//    switch (status) {
//        case 0: //looking
//        case 1: //waiting
//        case 2: //mating
//        case 3: { //raising
//            std::shared_ptr<Branch> destination = ofApp_.getRandomViableBranch(id_);
//            std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>(std::make_shared<Bird>(this));
//            std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(std::make_shared<Bird>(this) , nextStatePtr, destination);
//            setState(newStatePtr);
//            break;
//        }
//        case 4:{ //growing
//            die();
//            break;
//        }
//        case 5:{ //moving
//            std::shared_ptr<MovingState> movingState = std::dynamic_pointer_cast<MovingState>(state_);
//            if (movingState) {
//                movingState->recheckDestination();
//            }
//            break;
//        }
//        default:
//            //maybe it should be the first one.
//            break;
//    }
}

void Bird::die(){
    markedForDeath = true;
    switch(state_->id()){
        case 0: //looking
        case 1: //waiting
        case 4: //growing
        case 5: { //moving
            //siga siga
            break;
        }
        case 2:{ //mating
            
            break;
        }
        case 3: {//raising
            
            break;
        }
        default:
            break;
        
    }
}

void Bird::refreshPosition(){
    if(state_->id() != 5){
        position = branch_->position;
    }
    else {
        std::shared_ptr<MovingState> movingState = std::dynamic_pointer_cast<MovingState>(state_);
        if (movingState) {
            movingState->recheckDestination();
        }
    }
}
