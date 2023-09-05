//
//  AllBirdStates.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef AllBirdStates_hpp
#define AllBirdStates_hpp



#include <stdio.h>
#include "BirdState.hpp"
#include "Branch.hpp"
class Branch;

class LookingState : public BirdState
{
public:
    LookingState(std::shared_ptr<Bird> bird) : BirdState(0, bird), elapsedTurns_(0) {} //Ya se, podria hacer un enum
    
    virtual void update();
    void lookForMate();
    void getMated();
    
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class WaitingForMateState : public BirdState
{
public:
    WaitingForMateState(std::shared_ptr<Bird> bird) : BirdState(1, bird), elapsedTurns_(0) {}
    
    virtual void update();
    
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class MatingState : public BirdState
{
public:
    MatingState(std::shared_ptr<Bird> bird, std::shared_ptr<Bird> partner) : BirdState(2, bird), partner_(partner){}
    
    virtual void update();
    void spawnChild();
    void onPartnerDeath();
    
private:
    std::shared_ptr<Bird> partner_;
    std::list<shared_ptr<Bird>> children_;
};

//--------------------------------------------------------------
class RaisingState : public BirdState
{
public:
    RaisingState(std::shared_ptr<Bird> bird, std::list<shared_ptr<Bird>> children) : BirdState(3, bird), elapsedTurns_(0), children_(children) {}
    
    virtual void update();
private:
    int elapsedTurns_;
    std::list<shared_ptr<Bird>> children_;
};

//--------------------------------------------------------------
class GrowingState : public BirdState
{
public:
    GrowingState(std::shared_ptr<Bird> bird) : BirdState(4, bird), turnsWithoutEating_(0), previousLife_(1) {}
    
    virtual void update();
    
private:
    int turnsWithoutEating_;
    float previousLife_;
};

//--------------------------------------------------------------
class MovingState : public BirdState
{
public:
    MovingState(std::shared_ptr<Bird> bird, std::shared_ptr<BirdState> nextState, std::shared_ptr<Branch> destination);
    
    virtual void update();
    void recheckDestination();
    
private:
    std::shared_ptr<BirdState> nextState_;
    std::shared_ptr<Branch> destination_;
    int elapsedTurns_;
    int travelDuration_;
    glm::vec3 movementPerTurn_;
    
};
#endif /* AllBirdStates_hpp */
