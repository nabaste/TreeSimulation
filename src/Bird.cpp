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
    state_ = std::make_shared<GrowingState>();
    //state_==nullptr;
    position = branch_->position;
}

Bird::Bird(ofApp& ofApp, std::shared_ptr<Branch> branch, std::shared_ptr<BirdState> state, int age) :
Entity(BIRD_STARTING_LIFE), ofApp_(ofApp), branch_(branch), state_(state), age_(age){
    id_ = ofApp.getNewBirdId();
    isMale_ = rand() % 2;
    //if(state == 0){
        //std::shared_ptr<BirdState> newState = std::make_shared<LookingState>(getObjectSharedPtr());
        //state_ = nullptr;
    //}
}

void Bird::update(std::shared_ptr<Entity> e){
    grow();
    std::shared_ptr<Bird> bird_ = std::dynamic_pointer_cast<Bird>( e );
    state_->update(bird_);
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

void Bird::onBranchDeath(std::shared_ptr<Bird> birdPtr){
    int status = state_->id();

    switch (status) {
        case 0: //looking
        case 1: //waiting
        case 2: {
            std::shared_ptr<Branch> destination = ofApp_.getRandomViableBranch(id_);
            std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>();
            std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(birdPtr , nextStatePtr, destination); //MMMMM
            setState(newStatePtr);
            break;
        }
        case 3: { //raising
            std::shared_ptr<RaisingState> raisingState = std::dynamic_pointer_cast<RaisingState>(state_);
            if(raisingState) {
//                raisingState->looseChildren();
                std::shared_ptr<Branch> destination = ofApp_.getRandomViableBranch(id_);
                std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>();
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(birdPtr , nextStatePtr, destination);
                setState(newStatePtr);
            }
        }
        case 4:{ //growing
            die();
            break;
        }
        case 5:{ //moving
            std::shared_ptr<MovingState> movingState = std::dynamic_pointer_cast<MovingState>(state_);
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
        case 1: //waiting
        case 3: //raising
        case 4:
        case 5: { //moving
            std::shared_ptr<BirdState> newStatePtr = std::make_shared<DyingState>();
            setState(newStatePtr);
            break;
        }
        case 2:{ //mating
            std::shared_ptr<MatingState> matingState = std::dynamic_pointer_cast<MatingState>(state_);
            if (matingState) {
                matingState->onPartnerDeath();
            }
            
            std::shared_ptr<BirdState> newStatePtr = std::make_shared<DyingState>();
            setState(newStatePtr);
            break;
        }
            
//        case 4: {
//            std::shared_ptr<GrowingState> growingState = std::dynamic_pointer_cast<GrowingState>(state_);
//            if (growingState) {
//              growingState->onDeath(id_);
//            }
//        }
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
