//
//  AllBirdStates.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "AllBirdStates.hpp"
#include "Bird.hpp"
class Bird;

void LookingState::update(std::shared_ptr<Bird> bird_) {
    bird_->eat();
//    if (elapsedTurns_ >= BIRD_TURNS_LOOKING_FOR_MATE){
//        std::shared_ptr<Branch> destination = bird_->getOfApp().getRandomViableBranch(bird_->id());
//        std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>();
//        std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(bird_ , nextStatePtr, destination);
//        bird_->setState(newStatePtr);
//        elapsedTurns_ = 0;
//    }
    if (bird_->life() > BIRD_MATING_POINT) {
        lookForMate(bird_);
    }
    elapsedTurns_++;
}

void LookingState::lookForMate(std::shared_ptr<Bird> bird_){
    std::shared_ptr<Bird> result;
    for(const auto& p : bird_->getOfApp().getBirds()){
        if (p->id() == bird_->id()) return;
        if (p->life() > BIRD_MATING_POINT && bird_->isMale() != p->isMale()){
            if( bird_->branch()->id() == p->branch()->id() && p->getState()->id() == 1){
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MatingState>(p);
                std::shared_ptr<BirdState> newStateForPartner = std::make_shared<MatingState>(bird_);
                bird_->setState(newStatePtr);
                p->setState(newStateForPartner);
                return;
            }
            else if (bird_->branch()->id() == p->branch()->id() && p->getState()->id() == 0){
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MatingState>(p);
                std::shared_ptr<BirdState> newStateForPartner = std::make_shared<MatingState>(bird_);
                bird_->setState(newStatePtr);
                p->setState(newStateForPartner);
                return;
            }
            else if (bird_->branch()->id() != p->branch()->id() && p->getState()->id() == 0){
                std::shared_ptr<BirdState> nextStatePtr = std::make_shared<LookingState>();
                std::shared_ptr<BirdState> newStatePtr = std::make_shared<MovingState>(bird_, nextStatePtr, p->branch());
                bird_->setState(newStatePtr);
                
                //set the other bird to waiting so that they don't leave.
                std::shared_ptr<BirdState> newStateOtherBirdPtr = std::make_shared<WaitingForMateState>();
                p->setState(newStateOtherBirdPtr);
                return;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------
void WaitingForMateState::update(std::shared_ptr<Bird> bird_){
    bird_->eat();
    elapsedTurns_++;
    if(elapsedTurns_ > BIRD_TURNS_WAITING_FOR_MATE){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>();
        bird_->setState(newState);
    }
}

//----------------------------------------------------------------------------------------------------
void MatingState::update(std::shared_ptr<Bird> bird_){
    bird_->eat();
    if (!bird_->isMale()){
        spawnChild(bird_);
        if(rand() % 2){ //50% chance to keep spawning or start raising
//            std::shared_ptr<BirdState> newState = std::make_shared<RaisingState>(children_);
            std::shared_ptr<BirdState> newState = std::make_shared<RaisingState>();

            if(partner_ != nullptr){
                partner_->setState(newState);
            }
            bird_->setState(newState);
        }
    }
}

void MatingState::spawnChild(std::shared_ptr<Bird> bird_){
    std::shared_ptr<Bird> birdPtr = std::make_shared<Bird>(bird_->getOfApp(), bird_->branch());
    bird_->getOfApp().subscribeAliveEntity(birdPtr);
//    children_.push_back(birdPtr);
    std::shared_ptr<BirdState> initState = std::make_shared<GrowingState>();
    birdPtr->setState(initState);
    
//    std::shared_ptr<GrowingState> growingState = std::dynamic_pointer_cast<GrowingState>(birdPtr->getState());
//    if (growingState) {
//        growingState->addParent(bird_);
//        growingState->addParent(partner_);
//    }
}

void MatingState::onPartnerDeath(){
    partner_ = nullptr;
}
//----------------------------------------------------------------------------------------------------
void RaisingState::update(std::shared_ptr<Bird> bird_){
    bird_->eat();
    bird_->eat();
    
//    int childrenLeft = 0;
//    for(const auto& p : children_){
//        if(p){
//            if( p->getState()->id() == 4){
//                p->eat();
//                childrenLeft++;
//            }
//        }
//    }
//    if(childrenLeft == 0){
//        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>();
//        bird_->setState(newState);
//    }
//}
//
//void RaisingState::looseChildren(){
//    children_.clear();
//}
//
//void RaisingState::onChildDeath(int id){
//
//    children_.erase(std::remove_if(children_.begin(), children_.end(),
//                                   [id](const std::shared_ptr<Bird>& e) { return e->id() == id; }),
//                    children_.end());
    elapsedTurns_++;
    if( elapsedTurns_ >= BIRD_INFANCY_PERCENTAGE * BIRD_LIFE_EXPECTANCY ){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>();
        bird_->setState(newState);
        
    }
    
}
//----------------------------------------------------------------------------------------------------
void GrowingState::update(std::shared_ptr<Bird> bird_){
    bird_->eat();
    if( bird_->age() >= BIRD_INFANCY_PERCENTAGE * BIRD_LIFE_EXPECTANCY ){
        std::shared_ptr<BirdState> newState = std::make_shared<LookingState>();
        bird_->setState(newState);
        
    }
//    if( bird_->life() == previousLife_ ){
//        turnsWithoutEating_++;
//    } else {
//        turnsWithoutEating_ = 0;
//    }
//    if (turnsWithoutEating_ > 4 ){
//        bird_->die();
//    }
//}

//void GrowingState::addParent(std::shared_ptr<Bird> parent){
//    parents_.push_back(parent);
//}
//
//void GrowingState::onDeath(int id){
//        for(const auto& p : parents_){
//            //tecnicamente podrian estar mating tmbn pero la veo dificil
//            std::shared_ptr<RaisingState> raisingState = std::dynamic_pointer_cast<RaisingState>(p->getState());
//            raisingState->onChildDeath(id);
//        }
//
//    parents_.clear();
}

//----------------------------------------------------------------------------------------------------
MovingState::MovingState(std::shared_ptr<Bird> bird, std::shared_ptr<BirdState> nextState, std::shared_ptr<Branch> destination):
BirdState(5), bird_(bird), nextState_(nextState), destination_(destination), elapsedTurns_(0) {
    
    glm::vec3 travel = destination->position - bird->position;
    travelDuration_ = (int)(travel.length() / BIRD_DISTANCE_TRAVELLED_PER_TURN);
    glm::vec3 mpt{(destination->position.x - bird->position.x)/travelDuration_, (destination->position.y - bird->position.y)/travelDuration_, 0} ;
    movementPerTurn_ = mpt;
}

void MovingState::update(std::shared_ptr<Bird> bird_){
    glm::vec3 newPos = bird_->position + movementPerTurn_;
    bird_->position = newPos;
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
//----------------------------------------------------------------------------------------------------
void DyingState::update(std::shared_ptr<Bird> bird_){
    //...
}
