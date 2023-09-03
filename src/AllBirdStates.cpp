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
