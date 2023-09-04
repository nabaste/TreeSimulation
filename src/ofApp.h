#pragma once

#include <iostream>
#include "ofMain.h"
#include "Branch.hpp"
#include "Bird.hpp"

class Bird;
class Branch;

class ofApp : public ofBaseApp{
    
public:
    ofApp();
    
    //getters, setters
    void subscribeToUpdate(std::shared_ptr<Entity> entity);
    float branchGrowthPerTurn() { return branchGrowthPerTurn_; };
    int getAliveBranchAmount();
    int getNewBranchId();
    int getNewBirdId();
    std::list<shared_ptr<Branch>> getBranches();
    std::list<shared_ptr<Bird>> getBirds();
    
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
        void subscribeAliveEntity(std::shared_ptr<Entity> entity);
        std::shared_ptr<Branch> getLiveliestBranch();
        std::shared_ptr<Branch> getRandomViableBranch(int seed);
    
    //render
    
private:
    
    int totalBirdCounter_;
    int totalBranchCounter_;
    float branchGrowthPerTurn_;
    std::list<std::shared_ptr<Entity>> aliveEntities_;
		
};
