#include <afstandssensor.h>

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can receive x and y coords for joystick movement within App.

  App project setup:
    Two Axis Joystick on V1 in MERGE output mode.
    MERGE mode means device will receive both x and y within 1 message
 *************************************************************/

/* Comment this out to disable prints and save space */
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>

#define BLYNK_PRINT Serial

//#include "SR04.h"
//#define TRIG1_PIN 12// sensor1
//#define ECHO1_PIN 11//sensor1
//#define TRIG2_PIN 3//sensor2
//#define ECHO2_PIN 8//sensor2
#define enA 9 //motorleft
#define in1 8 //8
#define in2 11 //11
#define enB 10//motorright
#define in3 6
#define in4 7

//en
//SR04 sr041 = SR04(ECHO1_PIN,TRIG1_PIN);//sensor 1
//SR04 sr042 = SR04(ECHO2_PIN,TRIG2_PIN);//sensor 2
long a;//sensor1
long b;//sensor 2

//Flag for different modes
//int flag = 0;

SoftwareSerial SwSerial(4, 5); // RX, TX


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "F5ao90-WHZ82nQnFafKNHJQByAMZ9_Ha";

BLYNK_WRITE(V0) {
  //flag = 1;
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
  
  //Threshholds for joystick
  const int x_thresh_Low = 103;
  const int x_thresh_High = 153;

  const int y_thresh_Low = 103;
  const int y_thresh_High = 153;

  //Variables for direction of movement
  int xDirection = 0;
  int yDirection = 0;

  //Finding the direction
  if(x > x_thresh_High)
  {
    xDirection = 1;
  } else if(x < x_thresh_Low) {
    xDirection = -1;
  }
  if(y < y_thresh_Low) {
    yDirection = -1;
  } else if(y > y_thresh_High) 
  {
    yDirection = 1;
  }


  //Now we start to make the motor move and turn in directions

  if(xDirection == -1)
  {
    if(yDirection == -1)
    {
      Serial.print("Diagonal left backward");

      //Making motors run backwards
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      //Turning left
      analogWrite(enA, 128);
      analogWrite(enB, 255);
    }
    else if(yDirection == 0)
    {
      Serial.print("Turn HARD left");

      //Making motors turn hard left
      digitalWrite(in1, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      //Turning left
      analogWrite(enA, 255);
      analogWrite(enB, 255);
    }
    else {
      Serial.print("Diagonal forward left");

      //Making motors turn forward left
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 128);
      analogWrite(enB, 255);
    }
  } else if( xDirection == 0)
  {
    if(yDirection == -1)
    {
      Serial.print("BACKWARDS");

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      analogWrite(enA, 255);
      analogWrite(enB, 255);
      
    }
    else if(yDirection == 0)
    {
      Serial.print("STOP");

      digitalWrite(in1, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, HIGH);

      analogWrite(enA, 255);
      analogWrite(enB, 255);
    }
    else if(yDirection == 1)
    {
      Serial.print("FORWARD");

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 255);
      analogWrite(enB, 255);
      
    }
  } else if(xDirection == 1)
  {
    if (yDirection == -1)
    {
      Serial.print("Diagonal right backward");

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      analogWrite(enA, 255);
      analogWrite(enB, 128);
    } else if(yDirection == 0)
    {
      Serial.print("HARD RIGHT");

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, HIGH);

      analogWrite(enA, 255);
      analogWrite(enB, 255);
    }
    else if(yDirection == 1)
    {
      Serial.print("Forward Right");

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 255);
      analogWrite(enB, 128);
    }
  }
  
}

void setup()
{
  //Setting up motors
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
  
    
  // Debug console
  Serial.begin(9600);

  //Bluetooth Serial
  SwSerial.begin(9600);

  Blynk.begin(SwSerial, auth);
}

void loop()
{
  Blynk.run();
}


/*
void joystick() {
  
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

}
*/
