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
#include "ofMain.h"

class Entity {
  
public:
    Entity(float life) : id_(0), life_(life), position(0.5), markedForDeath(false) {}
    Entity(float life, glm::vec3 pos) : id_(0), life_(life), position(pos), markedForDeath(false) {}
    virtual ~Entity() {}
    
    int id() const { return id_; }
    float life() const { return life_; }
    
    virtual void update(std::shared_ptr<Entity> e) = 0;
    virtual void die();
    
    bool markedForDeath;
    glm::vec3 position;
    
protected:
    int id_;
    float life_;
};
#endif /* Entity_hpp */
