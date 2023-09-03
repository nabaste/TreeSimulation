//
//  Branch.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Branch_hpp
#define Branch_hpp

#include <stdio.h>
#include "Entity.hpp"

class Branch : public Entity{
    
public:
    
    //getters
    int id() { return id_; }
    const int life() { return life_; }
    const int stepsFromRoot() { return stepsFromRoot_; }
    
    virtual void update();
    
private:
    int id_;
    int life_;
    int stepsFromRoot_;
};

#endif /* Branch_hpp */
