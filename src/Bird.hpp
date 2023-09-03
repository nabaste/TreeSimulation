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
#include "Constants.h"
#include "ofApp.h"
class ofApp;

class Bird : public Entity {

public:
    
    Bird(ofApp& ofApp);

    // Getters
    int age() const { return age_; }
    bool isMale() const { return isMale_; }
    
    virtual void update();
    
private:
    int age_;
    bool isMale_;
    
    ofApp& ofApp_;
};

#endif /* Bird_hpp */
