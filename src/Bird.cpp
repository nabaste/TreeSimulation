//
//  Bird.cpp
//  TreeSimulation
//
//  Created by Nahuel Basterretche on 03/09/2023.
//

#include "Bird.hpp"

Bird::Bird(ofApp& ofApp): Entity(BIRD_STARTING_LIFE), ofApp_(ofApp), age_(0)
{
    id_ = ofApp.getNewBirdId();
    isMale_ = rand() % 2;
}

void Bird::update(){
    grow();
}

void Bird::grow(){
    age_++;
    if(age_ > BIRD_LIFE_EXPECTANCY){
        die();
    }
}
