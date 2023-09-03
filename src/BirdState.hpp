//
//  BirdState.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef BirdState_hpp
#define BirdState_hpp

#include <stdio.h>
//#include "Bird.hpp"
class Bird;

class BirdState
{
public:
    BirdState(int id) : id_(id) {}
    virtual ~BirdState() {}
    virtual void update(Bird& bird) {}
    virtual void lateUpdate(Bird& bird) {}
    int id() {return id_; }
    
private:
    int id_;
};

#endif /* BirdState_hpp */
