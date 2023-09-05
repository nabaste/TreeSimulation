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
    BirdState(int id, std::shared_ptr<Bird> bird) : id_(id), bird_(bird) {}
    virtual ~BirdState() {}
    virtual void update() {}
    virtual void lateUpdate() {}
    int id() {return id_; }
    
    
protected:
    int id_;
    std::shared_ptr<Bird> bird_;
};

#endif /* BirdState_hpp */
