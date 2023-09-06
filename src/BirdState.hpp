//
//  BirdState.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef BirdState_hpp
#define BirdState_hpp

#include <stdio.h>
#include <iostream>
//#include "Bird.hpp"
class Bird;

class BirdState
{
public:
    BirdState(int id) : id_(id) {}
    virtual ~BirdState() {}
    virtual void update(std::shared_ptr<Bird> bird_) {}
    virtual void lateUpdate() {}
    int id() {return id_; }
    
    
protected:
    int id_;
};

#endif /* BirdState_hpp */
