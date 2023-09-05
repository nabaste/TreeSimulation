//
//  AllBirdStates.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "AllBirdStates.hpp"
#include "Bird.hpp"
class Bird;

void LookingState::update() {
    bird_->eat();
    if (elapsedTurns_ >= BIRD_TURNS_LOOKING_FOR_MATE){
        std::shared_ptr<Branch> destination = bird_->getOfApp().getRandomViableBranch(bird_->id());
        std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>(bird_);
        std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(bird_ , nextStatePtr, destination);
        bird_->setState(newStatePtr);
        elapsedTurns_ = 0;
    }
    if (bird_->life() > BIRD_MATING_POINT) {
        lookForMate();
    }
    elapsedTurns_++;
}

void LookingState::lookForMate(){
    std::shared_ptr<Bird> result;
    for(const auto& p : bird_->getOfApp().getBirds()){
        if (p->id() == bird_->id()) return;
        if (p->life() > BIRD_MATING_POINT && bird_->isMale() != p->isMale()){
            if( bird_->branch()->id() == p->branch()->id() && p->getState()->id() == 1){
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MatingState>(bird_, p);
                std::shared_ptr<BirdState> newStateForPartner = std::make_shared<MatingState>(p, bird_);
                bird_->setState(newStatePtr);
                p->setState(newStatePtr);
                return;
            }
            else if (bird_->branch()->id() == p->branch()->id() && p->getState()->id() == 0){
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MatingState>(bird_, p);
                std::shared_ptr<BirdState> newStateForPartner = std::make_shared<MatingState>(p, bird_);
                bird_->setState(newStatePtr);
                p->setState(newStatePtr);
                return;
            }
            else if (bird_->branch()->id() != p->branch()->id() && p->getState()->id() == 0){
                std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>(bird_);
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(bird_, nextStatePtr, p->branch());
                bird_->setState(newStatePtr);
                
                //set the other bird to waiting so that they don't leave.
                std::shared_ptr<BirdState> newStateOtherBirdPtr = std::make_shared<WaitingForMateState>(p);
                p->setState(newStateOtherBirdPtr);
                return;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------
void WaitingForMateState::update(){
    bird_->eat();
    elapsedTurns_++;
    if(elapsedTurns_ > BIRD_TURNS_WAITING_FOR_MATE){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>(bird_);
        bird_->setState(newState);
    }
}

//----------------------------------------------------------------------------------------------------
void MatingState::update(){
    bird_->eat();
    if (!bird_->isMale()){
        spawnChild();
        if(rand() % 2){ //50% chance to keep spawning or start raising
            std::shared_ptr<BirdState> newState = std::make_shared<RaisingState>(bird_, children_);
            bird_->setState(newState);
            if(partner_ != nullptr){
                partner_->setState(newState);

            }
        }
    }
}

void MatingState::spawnChild(){
    std::shared_ptr<Bird> birdPtr = std::make_shared<Bird>(bird_->getOfApp(), bird_->branch());
    bird_->getOfApp().subscribeAliveEntity(birdPtr);
    children_.push_back(birdPtr);
    std::shared_ptr<BirdState> initState = std::make_shared<GrowingState>(birdPtr);
    birdPtr->setState(initState);
}

void MatingState::onPartnerDeath(){
    partner_=nullptr;
}
//----------------------------------------------------------------------------------------------------
void RaisingState::update(){
    bird_->eat();
    bird_->eat();
    
    int childrenLeft = 0;
    for(const auto& p : children_){
        if( p->getState()->id() == 4){
            p->eat();
            childrenLeft++;
        }
    }
    if(childrenLeft == 0){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>(bird_);
        bird_->setState(newState);
    }
}

//----------------------------------------------------------------------------------------------------
void GrowingState::update(){
    if( bird_->age() >= BIRD_INFANCY_PERCENTAGE * BIRD_LIFE_EXPECTANCY ){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>(bird_);
        bird_->setState(newState);
    }
    if( bird_->life() == previousLife_ ){
        turnsWithoutEating_++;
    } else {
        turnsWithoutEating_ = 0;
    }
    if (turnsWithoutEating_ > 4 ){
        bird_->die();
    }
}


//----------------------------------------------------------------------------------------------------
MovingState::MovingState(std::shared_ptr<Bird> bird, std::shared_ptr<BirdState> nextState, std::shared_ptr<Branch> destination):
BirdState(5, bird), nextState_(nextState), destination_(destination), elapsedTurns_(0) {
    
    glm::vec3 travel = destination->position - bird_->position;
    travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
    glm::vec3 mpt{(destination->position.x - bird_->position.x)/travelDuration_, (destination->position.y - bird_->position.y)/travelDuration_, 0} ;
    movementPerTurn_ = mpt;
}

void MovingState::update(){
    bird_->position += movementPerTurn_;
    elapsedTurns_++;
    if (elapsedTurns_ == travelDuration_){
        bird_->setBranch(destination_);
        bird_->position = destination_->position;
        std::shared_ptr<BirdState> newStatePtr = nextState_;
        bird_->setState(newStatePtr);
    }
}

void MovingState::recheckDestination(){
    if(destination_->markedForDeath){
        destination_ = bird_->getOfApp().getRandomViableBranch(bird_->id());
        elapsedTurns_ = 0;
        
        glm::vec3 travel = destination_->position - bird_->position;
        travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
        glm::vec3 mpt{(destination_->position.x - bird_->position.x)/travelDuration_, (destination_->position.y - bird_->position.y)/travelDuration_, 0} ;
        movementPerTurn_ = mpt;
    }
    else{ //in case the branch has relocated // Should branches relocate?
        elapsedTurns_ = 0;
        
        glm::vec3 travel = destination_->position - bird_->position;
        travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
        glm::vec3 mpt{(destination_->position.x - bird_->position.x)/travelDuration_, (destination_->position.y - bird_->position.y)/travelDuration_, 0} ;
        movementPerTurn_ = mpt;
    }
}
