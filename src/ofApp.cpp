#include "ofApp.h"


ofApp::ofApp() : totalBirdCounter_(0), totalBranchCounter_(0), branchGrowthPerTurn_(0) {
    
}
//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(23,56,35);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetWindowTitle("Tree System");
        
    ofSetRectMode(OF_RECTMODE_CENTER);
        
    ofSetFrameRate(30);
        
    float middleW = ofGetWidth()/2;
    float middleH = ofGetHeight()/2;
    
    //-------- INITIAL BRANCH CREATION
    std::shared_ptr<Branch> rootPtr = std::make_shared<Branch>(*this);
    aliveEntities_.push_back(rootPtr);
    
    for(int i=1; i<4; i++){
        std::shared_ptr<Branch> branchPtr = std::make_shared<Branch>(*this);
        aliveEntities_.push_back(branchPtr);
        rootPtr->addChild(branchPtr);
    }
    
    //-------- INITIAL BIRDS CREATION
 
}

//--------------------------------------------------------------
void ofApp::update(){
    
    branchGrowthPerTurn_ = TREE_GROWTH / aliveEntities_.size();
    
    std::for_each(aliveEntities_.begin(), aliveEntities_.end(), [](std::shared_ptr<Entity>& e) {
        e->update();
    });
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::cout << "There are " << getAliveBranchAmount() << " branches alive." << std::endl;
    std::for_each(aliveEntities_.begin(), aliveEntities_.end(), [](std::shared_ptr<Entity>& e) {
        std:cout << "Branch number " << e->id() << " has a life of " << e->life() << std::endl;
    });
    
//    for(auto& p : birdPositions_){
//        std::cout << "Bird number "<< p.first.id() << " is on branch " << p.second.id() << " with life " << p.first.life() <<"." << std::endl;
//    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
int ofApp::getAliveBranchAmount() {
    int branchCount = 0;
    for (const auto& entityPtr : aliveEntities_) {
        // Check if the dynamic type of the object pointed to by entityPtr is Branch
        if (dynamic_cast<Branch*>(entityPtr.get()) != nullptr) {
            branchCount++;
        }
    }
    return branchCount;
}

int ofApp::getNewBranchId(){
    totalBranchCounter_++;
    return totalBranchCounter_ - 1; //so that it is 0 indexed
}

int ofApp::getNewBirdId(){
    totalBirdCounter_++;
    return totalBirdCounter_ - 1;
}
