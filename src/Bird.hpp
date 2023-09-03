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
    int id() const { return id_; }
    int age() const { return age_; }
    float life() const { return life_; }
    bool isMale() const { return isMale_; }
    
    virtual void update();
    
private:
    int id_;
    int age_;
    float life_;
    bool isMale_;
};

#endif /* Bird_hpp */
