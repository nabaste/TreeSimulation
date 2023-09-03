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
//        std::shared_ptr<Branch> destination = Tree::instance().getRandomViableBranch();
//        BirdState* nextStatePtr = new LookingState();
//        BirdState* newStatePtr = new MovingState(bird , nextStatePtr, destination->X, destination->Y);
//        bird.setState(newStatePtr);
    }
}

void LookingState::lookForMate(Bird& bird){
    
}
