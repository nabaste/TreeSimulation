//
//  AllBirdStates.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "AllBirdStates.hpp"
#include "Bird.hpp"
class Bird;

void LookingState::update(Bird& bird) {
    bird.eat();
    if (elapsedTurns_ >= BIRD_TURNS_WAITING_FOR_MATE){
        std::shared_ptr<Branch> destination = bird.getOfApp().getRandomViableBranch(bird.id());
        BirdState* nextStatePtr = new LookingState();
        BirdState* newStatePtr = new MovingState(bird , nextStatePtr, destination);
        bird.setState(newStatePtr);
        elapsedTurns_ = 0;
    }
    if (bird.life() > BIRD_MATING_POINT) {
        lookForMate(bird);
    }
    elapsedTurns_++;
}

void LookingState::lookForMate(Bird& bird){
    std::shared_ptr<Bird> result;
    for(const auto& p : bird.getOfApp().getBirds()){
        if (p->id() == bird.id()) return;
        if (p->life() > BIRD_MATING_POINT && bird.isMale() != p->isMale()){
            if( bird.branch()->id() == p->branch()->id() && p->getState()->id() == 4){
                BirdState* newStatePtr = new MatingState(p);
                BirdState* newStateForPartner = new MatingState(std::make_shared<Bird>(bird));
                bird.setState(newStatePtr);
                p->setState(newStatePtr);
                return;
            }
            else if (bird.branch()->id() == p->branch()->id() && p->getState()->id() == 0){
                BirdState* newStatePtr = new MatingState(p);
                BirdState* newStateForPartner = new MatingState(std::make_shared<Bird>(bird));
                bird.setState(newStatePtr);
                p->setState(newStatePtr);
                return;
            }
            else if (bird.branch()->id() != p->branch()->id() && p->getState()->id() == 0){
                BirdState* nextStatePtr = new LookingState();
                BirdState* newStatePtr = new MovingState(bird, nextStatePtr, p->branch());
                bird.setState(newStatePtr);
                
                //set the other bird to waiting so that they don't leave.
                BirdState* newStateOtherBirdPtr = new WaitingForMateState();
                p->setState(newStateOtherBirdPtr);
                return;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------
void WaitingForMateState::update(Bird& bird){
    bird.eat();
}

//----------------------------------------------------------------------------------------------------
void MatingState::update(Bird& bird){
    bird.eat();
    if (!bird.isMale()){
        spawnChild(bird);
        if(rand() % 2){ //50% chance to keep spawning or start raising
            BirdState* newState = new RaisingState(children_);
            bird.setState(newState);
            partner_->setState(newState);
        }
    }
}

void MatingState::spawnChild(Bird& bird){
    std::shared_ptr<Bird> birdPtr = std::make_shared<Bird>(bird.getOfApp(), bird.branch());
    bird.getOfApp().subscribeAliveEntity(birdPtr);
    children_.push_back(birdPtr);
}

//----------------------------------------------------------------------------------------------------
void RaisingState::update(Bird& bird){
    bird.eat();
    bird.eat();
    
    int childrenLeft = 0;
    for(const auto& p : children_){
        if( p->getState()->id() == 3){
            p->eat();
            childrenLeft++;
        }
    }
    if(childrenLeft == 0){
        BirdState* newState = new LookingState();
        bird.setState(newState);
    }
}

//----------------------------------------------------------------------------------------------------
void GrowingState::update(Bird& bird){
    if( bird.age() >= BIRD_INFANCY_PERCENTAGE * BIRD_LIFE_EXPECTANCY ){
        BirdState* newState = new LookingState();
        bird.setState(newState);
    }
}


//----------------------------------------------------------------------------------------------------
MovingState::MovingState(Bird& bird, BirdState* nextState, std::shared_ptr<Branch> destination):
BirdState(5), bird_(bird), nextState_(nextState), destination_(destination), elapsedTurns_(0) {
    
    glm::vec3 travel = destination->position - bird.position;
    travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
    glm::vec3 mpt{(destination->position.x - bird.position.x)/travelDuration_, (destination->position.y - bird.position.y)/travelDuration_, 0} ;
    movementPerTurn_ = mpt;
}

void MovingState::update(Bird& bird){
    bird.position += movementPerTurn_;
    elapsedTurns_++;
    if (elapsedTurns_ == travelDuration_){
        bird.setBranch(destination_);
        bird.position = destination_->position;
        BirdState* newStatePtr = nextState_;
        bird.setState(newStatePtr);
    }
}

void MovingState::recheckDestination(){
    if(destination_->markedForDeath){
        destination_ = bird_.getOfApp().getRandomViableBranch(bird_.id());
        elapsedTurns_ = 0;
        
        glm::vec3 travel = destination_->position - bird_.position;
        travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
        glm::vec3 mpt{(destination_->position.x - bird_.position.x)/travelDuration_, (destination_->position.y - bird_.position.y)/travelDuration_, 0} ;
        movementPerTurn_ = mpt;
    }
    else{ //in case the branch has relocated // Should branches relocate?
        elapsedTurns_ = 0;
        
        glm::vec3 travel = destination_->position - bird_.position;
        travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
        glm::vec3 mpt{(destination_->position.x - bird_.position.x)/travelDuration_, (destination_->position.y - bird_.position.y)/travelDuration_, 0} ;
        movementPerTurn_ = mpt;
    }
}
