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
    
    for(int i=1; i<STARTING_BRANCHES; i++){
        std::shared_ptr<Branch> branchPtr = std::make_shared<Branch>(*this);
        aliveEntities_.push_back(branchPtr);
        rootPtr->addChild(branchPtr);
    }
    
    //-------- INITIAL BIRDS CREATION
    for(int i=0; i<STARTING_BIRDS; i++){
        std::shared_ptr<Bird> birdPtr = std::make_shared<Bird>(*this, getLiveliestBranch());
        aliveEntities_.push_back(birdPtr);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    std::for_each(aliveEntities_.begin(), aliveEntities_.end(), [this](std::shared_ptr<Entity>& e) {
        branchGrowthPerTurn_ = TREE_GROWTH / getAliveBranchAmount();
        //this is not yet working as inteded for some reason. each time a new branch grows, the rest should immediately grow less
        e->update();
    });
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::list<shared_ptr<Branch>> branches = getBranches();
    std::list<shared_ptr<Bird>> birds = getBirds();
    
    std::cout << "There are " << getAliveBranchAmount() << " branches alive." << std::endl;
    std::for_each(branches.begin(), branches.end(), [](std::shared_ptr<Branch>& e) {
        std:cout << "Branch number " << e->id() << " has a life of " << e->life() << std::endl;
    });
    std::for_each(birds.begin(), birds.end(), [](std::shared_ptr<Bird>& e) {
        std:cout << "Bird number " << e->id() << " has a life of " << e->life() << std::endl;
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

void ofApp::subscribeAliveEntity(std::shared_ptr<Entity> entity){
    aliveEntities_.push_back(entity);
}

std::shared_ptr<Branch> ofApp::getLiveliestBranch(){
    
    std::shared_ptr<Branch> result = nullptr;
    
    for (auto& entityPtr : aliveEntities_) {
        if (auto branchPtr = std::dynamic_pointer_cast<Branch>(entityPtr)) {
            if (!result || branchPtr->life() > result->life()) {
                result = branchPtr;
            }
        }
    }
    return result;
}

std::list<shared_ptr<Branch>> ofApp::getBranches(){
    std::list<shared_ptr<Branch>> result;
    for (const auto& entityPtr : aliveEntities_) {
        // Check if the dynamic type of the object pointed to by entityPtr is Branch
        if (dynamic_cast<Branch*>(entityPtr.get()) != nullptr) {
            result.push_back(std::dynamic_pointer_cast<Branch>(entityPtr));
        }
    }
    return result;
}

std::list<shared_ptr<Bird>> ofApp::getBirds(){
    std::list<shared_ptr<Bird>> result;
    for (const auto& entityPtr : aliveEntities_) {
        // Check if the dynamic type of the object pointed to by entityPtr is Branch
        if (dynamic_cast<Bird*>(entityPtr.get()) != nullptr) {
            result.push_back(std::dynamic_pointer_cast<Bird>(entityPtr));
        }
    }
    return result;
}
