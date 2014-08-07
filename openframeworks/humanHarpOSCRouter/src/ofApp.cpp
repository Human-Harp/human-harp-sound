#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on " << NUM_PORTS << " ports\n";
    
    // sending port to PD
    // open an outgoing connection to HOST:PORT
	sender.setup(HOST, SEND_PORT);
    
    
    // would be much better if this was in a data structure
    // but time was pressing and it wasn't working
    // so this is what exists for now
    receiver8001.setup(8001);
	receiver8002.setup(8002);
    receiver8003.setup(8003);
	receiver8004.setup(8004);
    receiver8005.setup(8005);
	receiver8006.setup(8006);
    receiver8007.setup(8007);
	receiver8008.setup(8008);
    receiver8009.setup(8009);
    receiver8010.setup(8010);
    receiver8011.setup(8011);
    receiver8012.setup(8012);

	current_msg_string = 0;
    
    sendMessages = 1; // start by broadcasting messages

	ofBackground(130, 30, 130);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if( sendMessages )
    {
        // check for waiting messages
        
        //----8001----
        while(receiver8001.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8001.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8002----
        while(receiver8002.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8002.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8003----
        while(receiver8003.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8003.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8004----
        while(receiver8004.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8004.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8005----
        while(receiver8005.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8005.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8006----
        while(receiver8006.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8006.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8007----
        while(receiver8007.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8007.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8008----
        while(receiver8008.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8008.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8009----
        while(receiver8009.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8009.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8010----
        while(receiver8010.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8010.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8011----
        while(receiver8011.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8011.getNextMessage(&mess);
            
            handleMessage(mess);
        }
        
        //----8012----
        while(receiver8012.hasWaitingMessages()){
            // get the next message
            ofxOscMessage mess;
            receiver8012.getNextMessage(&mess);
            
            handleMessage(mess);
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    // display messages being sent
    ofSetColor(255, 255, 255);
	string buf;
	buf = "Sending the following OSC messages";
	ofDrawBitmapString(buf, 20, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 60, 60 + 15 * i);
	}
    
    if( sendMessages) {
        // pause button
        ofSetColor(255, 255, 255);
        ofRect(200, 505, 130, 30);
        ofSetColor(50, 50, 50);
        buf = "Click to Pause";
        ofDrawBitmapString(buf, 209, 525);
    } else {
        // pause button
        ofSetColor(10, 10, 10);
        ofRect(200, 505, 130, 30);
        ofSetColor(255, 255, 255);
        buf = "Click to Resume";
        ofDrawBitmapString(buf, 205, 525);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if( x < 330 && x > 200 && y < 535 && y > 500) {
        sendMessages = !sendMessages;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//-------------------------------------------------------------
void ofApp::handleMessage(ofxOscMessage m) {
    string send_string;
    string address_string;
    string ip_string;
    
    ip_string = "/" + ofSplitString( ofToString(m.getRemoteIp()), ".")[3];
    
    // check for battery message
    if(m.getAddress() == "/battery"){
        if(m.getArgType(0) == OFXOSC_TYPE_FLOAT){
            // construct OSC message to send
            sendBattery( ip_string, m.getArgAsFloat(0));
        }
    }
    
    // check for blob message
    else if(m.getAddress() == "/inputs/serial/1") {
        for(int i = 0; i < m.getNumArgs(); i++){
            // get the argument type
            if(m.getArgType(i) == OFXOSC_TYPE_BLOB){
                string blob = m.getArgAsBlob(0);
                vector<string> parameters = ofSplitString(blob, ",");
                if( parameters.size() >= 5 ) {
                    int distance = ofToInt(parameters[0]);
                    int velocity = ofToInt(parameters[1]);
                    int azimuth = ofToInt(parameters[2]);
                    int elevation = ofToInt(parameters[3]);
                    float angularRate = ofToFloat(parameters[4]);
                    
                    // send osc messages
                    sendDistance(ip_string, distance);
                    sendVelocity(ip_string, velocity);
                    sendAzimuth(ip_string, azimuth);
                    sendElevation(ip_string, elevation);
                    sendAngularRate(ip_string, angularRate);
                }
            }
        }
    }
}
//-------------------------------------------------------------
void ofApp::sendBattery(string ip, float value) {
    string address_string = ip + "/battery";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addFloatArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

//-------------------------------------------------------------
void ofApp::sendDistance(string ip, int value) {
    string address_string = ip + "/distance";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

//-------------------------------------------------------------
void ofApp::sendVelocity(string ip, int value) {
    string address_string = ip + "/velocity";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

//-------------------------------------------------------------
void ofApp::sendAzimuth(string ip, int value){
    string address_string = ip + "/azimuth";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

//-------------------------------------------------------------
void ofApp::sendElevation(string ip, int value) {
    string address_string = ip + "/elevation";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}

//-------------------------------------------------------------
void ofApp::sendAngularRate(string ip, float value) {
    string address_string = ip + "/angularRate";
    
    ofxOscMessage m;
    m.setAddress(address_string);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = address_string + ofToString(value);
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}
