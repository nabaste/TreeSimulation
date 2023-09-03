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
    virtual ~BirdState() {}
    virtual void update(Bird& bird) {}
    virtual void lateUpdate(Bird& bird) {}
};

#endif /* BirdState_hpp */
