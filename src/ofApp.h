#pragma once

#include <iostream>
#include "ofMain.h"
#include "Branch.hpp"
#include "Bird.hpp"

class ofApp : public ofBaseApp{
    
public:
    
    ofApp() {}
    //update loop
		void setup();
		void update();
		void draw();
    
    //openFrameworks event member functions
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //simulation
        
    //render
    
    
private:
    
    int totalBirdCounter_;
    int totalBranchCounter_;
    std::list<Entity*> aliveEntities_; //maybe here we do want a smart ptr
    std::map<Bird, Branch> birdPositions_;
		
};
