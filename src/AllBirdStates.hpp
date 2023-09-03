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
//class BirdState;


class LookingState : public BirdState
{
public:
    LookingState() : BirdState(0){}
    
    virtual void update(Bird& bird);
    void lookForMate(Bird& bird);
};

//--------------------------------------------------------------
class MatingState : public BirdState
{
public:
    MatingState() : BirdState(1){}
    
    virtual void update(Bird& bird);
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
    MovingState(Bird& bird, BirdState* nextState, float destinationX, float destinationY);
    
    virtual void update(Bird& bird);
    
private:
    Bird& bird_;
    BirdState* nextState_;
    int elapsedTurns_;
    float destinationX_;
    float destinationY_;
    int travelDuration_;
    float movementPerTurnX_;
    float movementPerTurnY_;
    
};
#endif /* AllBirdStates_hpp */
