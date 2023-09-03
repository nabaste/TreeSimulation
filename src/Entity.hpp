//
//  Entity.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <iostream>
#include "Constants.h"

class Entity{
  
public:
    Entity(int id, float life) : id_(id), life_(life) {}
    virtual ~Entity() {}
    
    int id() const { return id_; }
    float life() const { return life_; }
    
    virtual void update() = 0;
    
    
protected:
    int id_;
    float life_;
};
#endif /* Entity_hpp */
