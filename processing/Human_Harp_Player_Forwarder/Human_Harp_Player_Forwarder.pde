/*
 * File:   Human_Harp_Player_Data_Forwarding.pde
 * Author: Seb Madgwick, modified by Becky Stewart and Yuli Levtov
 *
 * Signal monitor and OSC aggregator for Human Harp.
 *
 * Tested with Processing 2.2.1 and oscP5 0.9.8
 */

//------------------------------------------------------------------------------
// Imported libraries

import oscP5.*;
import netP5.*;

//------------------------------------------------------------------------------
// Variables

OscP5 oscP5 = new OscP5(this, 8001); // specific port of Player (8001-8012)
NetAddress myRemoteLocation = new NetAddress("192.168.1.101", 9000); // IP address of Player (192.168.1.101-112)
float battery, distance, velocity, azimuth, elevation, angularRate;
String[] rowTitles = { "Distance", "Velocity", "Azimuth", "Elevation", "Angular rate" };
float rowHeight;
float x = 0;
int previousWidth, previousHeigth;  // used to detect window resize

//------------------------------------------------------------------------------
// Main functions

void setup() {
  size(1280, 720);
  if (frame != null) {
    frame.setResizable(true);
  }
  drawBackground(-1); // draw all rows
}

void draw() {
  drawDistance();
  drawBattery(); 
  drawVelocity();
  drawAzimuth();
  drawElevation();
  drawAngularRate();

  // Restart if graph full or window resized
  if (++x >= width || previousWidth != width || previousHeigth != height) {
    previousWidth = width;
    previousHeigth = height;
    rowHeight = height / rowTitles.length;
    x = 0;
    drawBackground(-1);
  }
}

//------------------------------------------------------------------------------
// Draw functions

void drawBackground(int selectedRow) {
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  for (int i = 0; i < rowTitles.length; i++) {
    if(selectedRow == -1 || selectedRow == i) {

      // Draw rectangle for each row
      fill(0);
      strokeWeight(1); // rectangle border width
      stroke(64);
      rect(0, i * rowHeight, width, rowHeight);

      // Print row title
      fill(64);
      textAlign (LEFT);
      textFont(f, (int)rowHeight * 0.2);
      text(rowTitles[i], 10, (i * rowHeight) + (0.2 * rowHeight));
    }
  }
}

void drawBattery() {
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(RIGHT);
  textFont(f, (int)rowHeight / 8);
  text("Battery: " + nf(battery, 1, 2) + " V", width * 0.99, rowHeight / 8);
}

void drawDistance() {
  drawBackground(0);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf((int)distance, 1), width * 0.5, rowHeight * 0.9);
}

void drawVelocity() {
  strokeWeight(1);
  if(velocity < 0) {
    stroke(192, 64, 64);
  }
  else {
    stroke(64, 64, 192);
  }
  float y = mapAndClip(velocity, 50000, -50000, 1 * rowHeight, 2 * rowHeight);
  line(x, 1.5 * rowHeight, x, y);
}

void drawAzimuth() {
  drawBackground(2);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf(azimuth, 1, 2), width * 0.5, 2 * rowHeight + rowHeight * 0.9);
}

void drawElevation() {
  drawBackground(3);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf(elevation, 1, 2), width * 0.5, 3 * rowHeight + rowHeight * 0.9);
}

void drawAngularRate() {
  strokeWeight(1);
  stroke(64, 192, 64);
  float y = mapAndClip(angularRate, 2000, 0, 4 * rowHeight, 5 * rowHeight);
  line(x, 5 * rowHeight, x, y);
}

float mapAndClip(float value, float start1, float stop1, float start2, float stop2) {
  float result = map(value, start1, stop1, start2, stop2);
  if(result < start2) {
    result = start2;
  }
  else if(result > stop2) {
    result = stop2;
  }
  return result;
}

//------------------------------------------------------------------------------
// 'Zero' command

void mousePressed() {
  OscMessage myMessage = new OscMessage("/outputs/serial/1");
  byte[] blob = {0};
  myMessage.add(blob);
  oscP5.send(myMessage, myRemoteLocation);   
}

//------------------------------------------------------------------------------
// OSC receive event

void oscEvent(OscMessage theOscMessage) {
  String addressPattern = theOscMessage.addrPattern();
  //print(addressPattern + " "); // print message for debugging

  // Process battery voltage
  if (addressPattern.equals("/battery")) {
    battery = theOscMessage.get(0).floatValue();
  }

  // Process serial blob
  if (addressPattern.equals("/inputs/serial/1")) {

    // Fetch string
    byte[] blob;
    String string = "";
    blob = theOscMessage.get(0).blobValue();
    for (int i = 0; i < blob.length; i++ ) {
      string += (char)blob[i];
    }
    //print(string); // print message for debugging

    // Process arguments
    String values[] = split(string, ',');
    if(values.length == 5) { // fetch values if measurement data
      distance = float(values[0]);
      velocity = float(values[1]);
      azimuth = float(values[2]) / 100;
      elevation = float(values[3]) / 100;
      angularRate = float(values[4]) / 100;
    }
    else { // else print reacieved message, e.g. "Reset", "Zero", "Sleep", "Firmware: vX.X"
      print(string);
    }
  }
}

//------------------------------------------------------------------------------
// End of file

