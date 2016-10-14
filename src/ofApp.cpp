#include "ofApp.h"

#define RAIN_COUNT 1000
#define VIDEO_W 320
#define VIDEO_H 240

//--------------------------------------------------------------
void ofApp::setup(){
    //image.load("Dog.gif");
    
    image.allocate(VIDEO_W, VIDEO_H, OF_IMAGE_COLOR);
    grabber.setup(VIDEO_W, VIDEO_H);
    
    showGui = true;
    gui.setup();
    gui.add(thresh.setup("Thresh", 20, 0, 255));
    
    for(int i = 0; i < RAIN_COUNT; ++i){
        ofPoint point = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        rain.push_back(point);
        velocity.push_back(0);
        text.push_back(ofRandom('A', 'Z'));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
//    unsigned char thresh = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
    
    unsigned char *vidPixels = grabber.getPixels().getData();
    unsigned char *imgPixels = image.getPixels().getData();
    
    for (int i = 0; i < VIDEO_W * VIDEO_H; ++i) {
        unsigned char gray = (vidPixels[i * 3 + 0] + vidPixels[i * 3 + 1] + vidPixels[i * 3 + 2]) / 3.0;
        imgPixels[i * 3 + 0] = imgPixels[i * 3 + 1] = imgPixels[i * 3 + 2] = (gray > thresh) * 255;
    }
    
//    for(int i = 0; i < VIDEO_W*VIDEO_H; i++) {
//        imgPixels[i*3+0] = ofRandom(255);
//        imgPixels[i*3+1] = ofRandom(255);
//        imgPixels[i*3+2] = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
//    }
    
    image.update();
    
    // rain
    for(int i = 0; i < RAIN_COUNT; ++i){
        int smW = rain[i].x / ofGetWidth() * VIDEO_W;
        int smH = rain[i].y / ofGetHeight() * VIDEO_H;
        int p = (smW + smH*VIDEO_W)*3;
        
        velocity[i] += 0.2;
        rain[i].y += velocity[i];
        
        bool dead = false;
        if (imgPixels[p] < thresh && velocity[i] > 0) {
            velocity[i] *= -0.5;
            dead = (ABS(velocity[i]) < 0.2);
        }
        
        if (dead || rain[i].y > ofGetHeight()) {
            rain[i].x = ofRandom(ofGetWidth());
            rain[i].y = -ofRandom(ofGetHeight());
            velocity[i] = 0;
            text[i] = ofRandom('A', 'Z');
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0xff, 0xff, 0xff);
    image.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(0x00, 0x00, 0x00);
    for(int i = 0; i < RAIN_COUNT; ++i){
        //ofDrawCircle(rain[i], 5);
        ofDrawBitmapString(text[i], rain[i]);
    }
    
    if (showGui) gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') showGui = !showGui;
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
