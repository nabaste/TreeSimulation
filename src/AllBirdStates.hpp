//
//  AllBirdStates.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef AllBirdStates_hpp
#define AllBirdStates_hpp


#include <iostream>
#include <stdio.h>
#include "BirdState.hpp"
#include "Branch.hpp"
class Branch;

class LookingState : public BirdState
{
public:
    LookingState() : BirdState(0), elapsedTurns_(0) {}
    
    virtual void update(Bird& bird);
    void lookForMate(Bird& bird);
    void getMated(Bird& bird);
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class MatingState : public BirdState
{
public:
    MatingState(std::shared_ptr<Bird> partner) : BirdState(1), partner_(partner){}
    
    virtual void update(Bird& bird);
    void spawnChild();
    
private:
    std::shared_ptr<Bird> partner_;
};

//--------------------------------------------------------------
class RaisingState : public BirdState
{
public:
    RaisingState() : BirdState(2), elapsedTurns_(0) {}
    
    virtual void update(Bird& bird);
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class GrowingState : public BirdState
{
public:
    GrowingState() : BirdState(3), elapsedTurns_(0) {}
    
    virtual void update(Bird& bird);
private:
    int elapsedTurns_;
};

//--------------------------------------------------------------
class WaitingForMateState : public BirdState
{
public:
    WaitingForMateState() : BirdState(4) {}
    
    virtual void update(Bird& bird);
};

//--------------------------------------------------------------
class MovingState : public BirdState
{
public:
    MovingState(Bird& bird, BirdState* nextState, std::shared_ptr<Branch> destination);
    
    virtual void update(Bird& bird);
    
private:
    Bird& bird_;
    BirdState* nextState_;
    std::shared_ptr<Branch> destination_;
    int elapsedTurns_;
    int travelDuration_;
    glm::vec3 movementPerTurn_;
    
};
#endif /* AllBirdStates_hpp */
