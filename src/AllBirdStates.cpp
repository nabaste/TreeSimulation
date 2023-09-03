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
    if (bird.life() > BIRD_MATING_POINT) {
        lookForMate(bird);
    } else {
        std::shared_ptr<Branch> destination = bird.getOfApp().getLiveliestBranch();
        BirdState* nextStatePtr = new LookingState();
        BirdState* newStatePtr = new MovingState(bird , nextStatePtr, destination);
        bird.setState(newStatePtr);
    }
}

void LookingState::lookForMate(Bird& bird){
    for(const auto& p : bird.getOfApp().getBirds()){
        if (p->id() == bird.id()) return;
        if (p->life() > BIRD_MATING_POINT && bird.isMale() != p->isMale() && p->getState() == 0) {
            //check if they're on different branches
            //moveTo(p.second->data());
            //p.first->getMated();
            
            //BirdState* newStatePtr = new MatingState();
            //setState(newStatePtr);
        }
    }
}

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
        BirdState* newStatePtr = nextState_;
        bird.setState(newStatePtr);
    }
}
