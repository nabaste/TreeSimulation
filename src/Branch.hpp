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
    Branch(int id);
    
    //getters & setters
    int id() const { return id_; }
    int life() const { return life_; }
    int stepsFromRoot() const { return stepsFromRoot_; }
    int addChild(std::shared_ptr<Branch> child) { children_.push_back(child); };
    
    virtual void update();
    
private:
    int id_;
    int life_;
    int stepsFromRoot_;
    
    std::vector<std::shared_ptr<Branch>> children_;
};

#endif /* Branch_hpp */
