#include "ofApp.h"
vector <ofPoint> points;
float radius;


// only control track levels and return(reverb) amount

//--------------------------------------------------------------
void ofApp::setup(){
    numTracks = 1;
    threshold = 1;
    effect = 0;
    radius = 200;
    gui.setup();
    gui.add(volMax.setup("max volume", 0.8, 0, 1));
    gui.add(volRange.setup("volume reduction", 0.25, 0, 0.8));
//    gui.add(loopStart.setup("clip start point", ofRandom(10), 0, 200));
//    gui.add(loopLength.setup("loop length", ofRandom(20,40), 0, 200));
//    gui.add(loopStartRandom.setup("randomize start point?", ofRandom(10), 0, 100));
//    gui.add(loopLengthRandom.setup("randomize loop length?", ofRandom(10), 0, 100));
//    gui.add(pan.setup("randomize track pan", ofRandom(1), 0, 1));
//    gui.add(detune.setup("randomize clip detune", ofRandom(30), 0, 50));
    live.setup();
//    live.setVolume(volMin);
}

//--------------------------------------------------------------
void ofApp::update(){
    live.update();
    radius = radius + ofRandom(-1, 1);
}

//--------------------------------------------------------------
void ofApp::draw(){
    float xorig = 400;
    float yorig = 500;

    
    float x = xorig + radius * sin(ofGetElapsedTimef()*(effect+0.01)*10);
    float y = yorig + radius * cos(ofGetElapsedTimef()*threshold*0.1);
    
    ofPoint temp;
    temp.x = x;
    temp.y = y;
    points.push_back(temp);
    if (points.size() > 300){
        points.erase(points.begin());
    }
    
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255,255,255);
    ofFill();
    ofDrawCircle(x,y,5);
    
    ofSetColor(255,255,255);
    
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < points.size(); i++){
        ofVertex(points[i].x, points[i].y);
    }
    ofEndShape();
    
    ofSetColor(0);
    gui.draw();
    
    
    // you can check if Live has finished loading all parameters since setup was called
    if (!live.isLoaded()) {
        ofDrawBitmapString("Wait without moving the mouse", 100, 100);
        ofDrawBitmapString("Ableton Live has not loaded yet!", 100, 120);
        return;
    }
    
    ofDrawBitmapString("", 250, 25);
    ofDrawBitmapString("On the channel called Recorder, start recording a clip", 250, 45);
    ofDrawBitmapString("If you made changes to Ableton Live, press R to refresh this app", 250, 65);
    ofDrawBitmapString("mouseY controls number of whispers", 250, 85);
    ofDrawBitmapString("mouseX controls amount of reverb", 250, 105);
    ofDrawBitmapString("When you are done, stop the recording in Ableton Live", 250, 125);
    
    ofDrawBitmapString(ofToString(min(threshold, numTracks-1)) + " tracks now playing", 250, 200);
    ofDrawBitmapString("effect amount: " + ofToString(effect), 250, 220);
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // get info
//    if (key=='1')
//    {
//        for (int i = 0; i < live.getNumTracks(); i++) {
//            ofxAbletonLiveTrack *track = live.getTrack(i);
//            ofxAbletonLiveClip *clip = track->getClip(0);
//            float start = loopStart + ofRandom(-loopStartRandom, loopStartRandom);
//            clip->setLoopStart(start);
//            clip->setLooping(true);
//            float length = loopLength + ofRandom(-loopLengthRandom, loopLengthRandom);
//            clip->setLoopEnd(start+length);
//            clip->setDetune(ofRandom(-detune,detune));
//            track->setPan(ofRandom(-pan,pan));
//        }
//    }
//    
//    // live's global properties
//    else if (key=='2')
//    {
//        live.selectScene(0);
//    }
//    
//    // global playback controls
//    else if (key=='3')
//    {
//        live.stop();
//    }
    
    // working with track properties
    if (key=='r' || key=='R')
    {
        live.refresh();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    numTracks = live.getNumTracks();
    threshold = ofMap(y, 800, 0, 1, numTracks, true);
    effect = ofMap(x, 200, 800, 0, 1, true);
    for (int i = 0; i < numTracks-1; i++) {
        ofxAbletonLiveTrack *track = live.getTrack(i);
        if (i < threshold) {
            track->setMute(false);
        } else {
            track->setMute(true);
        }
        track->setSend(0, effect);
    }
    live.setVolume(ofMap(y, 800, 0, volMax , (volMax-volRange*volRange), true));
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
