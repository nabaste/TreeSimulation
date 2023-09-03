//
//  Entity.hpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>

class Entity{
  
public:
    virtual ~Entity() {}
    
    virtual void update() = 0;
    
    
private:
    
};
#endif /* Entity_hpp */
