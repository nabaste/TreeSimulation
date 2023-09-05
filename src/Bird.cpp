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
    state_ = new GrowingState();
    position = branch_->position;
}

Bird::Bird(ofApp& ofApp, std::shared_ptr<Branch> branch, BirdState* state, int age) :
Entity(BIRD_STARTING_LIFE), ofApp_(ofApp), branch_(branch), state_(state), age_(age){
    id_ = ofApp.getNewBirdId();
    isMale_ = rand() % 2;
}

void Bird::update(){
    grow();
    state_->update(*this);
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
    int status = state_->id();

    switch (status) {
        case 0:
        case 1:
        case 2:
        case 3: {
            std::shared_ptr<Branch> destination = ofApp_.getRandomViableBranch(id_);
            BirdState* nextStatePtr = new LookingState();
            BirdState* newStatePtr = new MovingState(*this , nextStatePtr, destination);
            setState(newStatePtr);
            break;
        }
        case 4:{
            die();
            break;
        }
        case 5:{
            MovingState* movingState = dynamic_cast<MovingState*>(state_);
            if (movingState) {
                movingState->recheckDestination();
            }
            break;
        }
        default:
            //maybe it should be the first one.
            break;
    }
}

void Bird::die(){
    markedForDeath = true;
    switch(state_->id()){
        case 0: //looking
        case 3: //growing
        case 4: //waiting
        case 5: { //moving
            //siga siga
            break;
        }
        case 1:{ //mating
            
            break;
        }
        case 2: {//raising
            
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
        MovingState* movingState = dynamic_cast<MovingState*>(state_);
        if (movingState) {
            movingState->recheckDestination();
        }
    }
}
