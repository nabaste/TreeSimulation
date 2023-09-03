#include "ofApp.h"

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
    
    std::shared_ptr<Branch> rootPtr = std::make_shared<Branch>(0);
    aliveEntities_.push_back(rootPtr);
    
    for(int i=1; i<4; i++){
        std::shared_ptr<Branch> branchPtr = std::make_shared<Branch>(i);
        aliveEntities_.push_back(branchPtr);
        rootPtr->addChild(branchPtr);
    }
 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto& p : birdPositions_){
        std::cout << "Bird number "<< p.first.id() << " is on branch " << p.second.id() << " with life " << p.first.life() <<"." << std::endl;
    }
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
