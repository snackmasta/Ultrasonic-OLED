#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <afstandssensor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN 13
#define ECHO_PIN 12

long duration;
float distance;
float p4x,x;
float a0l0,a1l1,a2l2,a3l3,a4l4;

float x0=20.1;
float x1=29.7;
float x2=59;
float x3=87.5;
float x4=116.5;

float y0=20;
float y1=30;
float y2=60;
float y3=90;
float y4=120;

void setup() {  
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(1000);
  display.clearDisplay();
}

void loop() {
  jarak();
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  layar();
}

void jarak(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
}

void lagrange(){
  jarak(); //paggil fungsi sensor baca
  x=distance;
  a0l0=((y0*(x-x1)*(x-x2)*(x-x3)*(x-x4))/((x0-x1)*(x0-x2)*(x0-x3)*(x0-x4)));
  a1l1=((y1*(x-x0)*(x-x2)*(x-x3)*(x-x4))/((x1-x0)*(x1-x2)*(x1-x3)*(x1-x4)));
  a2l2=((y2*(x-x0)*(x-x1)*(x-x3)*(x-x4))/((x2-x0)*(x2-x1)*(x2-x3)*(x2-x4)));
  a3l3=((y3*(x-x0)*(x-x1)*(x-x2)*(x-x4))/((x3-x0)*(x3-x1)*(x3-x2)*(x3-x4)));
  a4l4=((y4*(x-x0)*(x-x1)*(x-x2)*(x-x3))/((x4-x0)*(x4-x1)*(x4-x2)*(x4-x3)));
  p4x=a0l0+a1l1+a2l2+a3l3+a4l4;
}

void layar() {
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  display.print("Jarak: ");
  display.print(distance,1);
  display.print(" cm");

  display.setCursor(0,10);
  display.print("tes: ");
  display.print(distance,1);
  display.print(" cm");

  display.setRotation(2); // This line flips the display horizontally
  display.display();
  delay(100);
}
