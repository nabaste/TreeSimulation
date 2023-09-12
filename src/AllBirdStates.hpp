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
    LookingState() : BirdState(0), elapsedTurns_(0) {} //Ya se, podria hacer un enum
    
    virtual void update(std::shared_ptr<Bird> bird_);
    void lookForMate(std::shared_ptr<Bird> bird_);
    void getMated();
    
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class WaitingForMateState : public BirdState
{
public:
    WaitingForMateState() : BirdState(1), elapsedTurns_(0) {}
    
    virtual void update(std::shared_ptr<Bird> bird_);
    
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class MatingState : public BirdState
{
public:
    MatingState(std::shared_ptr<Bird> partner) : BirdState(2), partner_(partner){}
    
    virtual void update(std::shared_ptr<Bird> bird_);
    void spawnChild(std::shared_ptr<Bird> bird_);
    void onPartnerDeath();
    
private:
    std::shared_ptr<Bird> partner_;
    std::list<shared_ptr<Bird>> children_;
};

//--------------------------------------------------------------
class RaisingState : public BirdState
{
public:
//    RaisingState(std::list<shared_ptr<Bird>> children) : BirdState(3), elapsedTurns_(0), children_(children) {}
    RaisingState() : BirdState(3), elapsedTurns_(0) {}

    virtual void update(std::shared_ptr<Bird> bird_);
//    void looseChildren();
//    void onChildDeath(int id);
    
private:
    int elapsedTurns_;
//    std::list<shared_ptr<Bird>> children_;
};

//--------------------------------------------------------------
class GrowingState : public BirdState
{
public:
    GrowingState() : BirdState(4), turnsWithoutEating_(0), previousLife_(1) {}
    
    virtual void update(std::shared_ptr<Bird> bird_);
//    void addParent(std::shared_ptr<Bird>);
//    void onDeath(int id);
    
private:
    int turnsWithoutEating_;
    float previousLife_;
//    std::list<shared_ptr<Bird>> parents_;
};

//--------------------------------------------------------------
class MovingState : public BirdState
{
public:
    MovingState(std::shared_ptr<Bird> bird, std::shared_ptr<BirdState> nextState, std::shared_ptr<Branch> destination);
    
    virtual void update(std::shared_ptr<Bird> bird_);
    std::shared_ptr<Branch> destination() { return destination_; };
    void recheckDestination();
    
private:
    std::shared_ptr<BirdState> nextState_;
    std::shared_ptr<Branch> destination_;
    int elapsedTurns_;
    int travelDuration_;
    glm::vec3 movementPerTurn_;
    std::shared_ptr<Bird> bird_;
    
};
//--------------------------------------------------------------
class DyingState : public BirdState
{
public:
    DyingState() : BirdState(6) {}
    
    virtual void update(std::shared_ptr<Bird> bird_);
};
#endif /* AllBirdStates_hpp */
