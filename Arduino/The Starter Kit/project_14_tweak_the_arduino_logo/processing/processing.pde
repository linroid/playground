import processing.serial.*;

Serial port;

PImage logo;

int backgroundColor = 0;

void setup() {
  size(640, 480);
  colorMode(HSB, 255);
  logo = loadImage("http://arduino.cc/logo.png");
  println("Available serial ports:");
  println(Serial.list());
  port = new Serial(this, Serial.list()[1], 9600);
  println("Selected : " + Serial.list()[1]);
}

void draw() {
  if (port.available() > 0) {
    backgroundColor = port.read();
    println("value: " + backgroundColor);
  }
  background(backgroundColor, 255, 255);
  image(logo, 0, 0);
}
