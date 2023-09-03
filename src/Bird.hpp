//
//  Bird.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Bird_hpp
#define Bird_hpp

#include <stdio.h>
#include "Entity.hpp"

class Bird : public Entity {

public:
    // Getters
    int id() { return id_; }
    const int age() { return age_; }
    const float life() { return life_; }
    const bool isMale() { return isMale_; }
    
    virtual void update();
    
private:
    int id_;
    int age_;
    float life_;
    bool isMale_;
};

#endif /* Bird_hpp */
