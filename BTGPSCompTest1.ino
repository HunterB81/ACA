// For GPS
#include <Adafruit_GPS.h> // Install libray
#include <SoftwareSerial.h>// load software variable
SoftwareSerial mySerial(2,3);// Initialize software serial port for GPS
Adafruit_GPS GPS(&mySerial);//Create GPS object

//Stuff for the motors
#define enA 9 //motorleft
#define in1 8
#define in2 11
#define enB 10//motorright
#define in3 6
#define in4 7

//float Dist; 
float ACA_Lat;
float ACA_Lon;
//int counter = 0;
#define GPS_UPDATE_INTERVAL 1000


// For Bluetooth
#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>
//SoftwareSerial SwSerial(4, 5); // RX, TX

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0RtI-LSMaPLAV4eUBuxlOa0aCUfMtPSm";
SoftwareSerial SerialBLE(4, 5); // RX, TX.
// Variable for Bluetooth
float Phone_Lat ;
float Phone_Lon ;
// for bearing
//float bearing;



// For Compass
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define DECLINATION_ANGLE 0.112864625f
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup() { 

  //Setting up motors
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  //GPS
  //Serial.begin(4800);
  Serial.begin(9600); // turn on serial monitor
 /* while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
  GPS.begin(9600); // turn on GPS at 9600 buad
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // request RMS and GGA sentence only
 
  // Bluetooth
 SerialBLE.begin(9600);
 Blynk.begin(SerialBLE, auth);
 //Serial.println(Dist);
//Serial.print("Lat: ");

// Compass
 /*Serial.println("Magnetometer Test");
  Serial.println("");*/

//   Initialise the sensor 
  if (!mag.begin()) {
   //  There was a problem detecting the LSM303 ... check your connections 
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }
}

BLYNK_WRITE(V4) {// Get Long and Lat from Phone
  
  GpsParam gps(param);
  Phone_Lat = gps.getLat();
  //Phone_Lat = 28.4300251;
  Phone_Lon = gps.getLon();
  //Phone_Lon = -81.4932022;
 /* Serial.println("Data from BT");
  Serial.println(Phone_Lat, 7);
  Serial.println(Phone_Lon, 7);
  */
    mySerial.listen();
   
  checkGPS();
 /* Serial.println("Data from GPS");
   Serial.println(ACA_Lat, 7);
    Serial.println(ACA_Lon, 7);
    */
  //  char inByte = SerialBLE.read();
    //Serial.write(inByte);
 //distance();
 SerialBLE.listen();
 //Bearing();

 //Heading();

 driveTo();

  }

void loop() {
   Blynk.run();
   
}


void readGPS(){// function reads 2 NMEA sentences
  
String NMEA1; // Variable for first nema sentence
String NMEA2; // variable for second sentence
char c; //to read charchters coming from GPS  
float deg; // hold position data in siple degree format
float degWhole; // Variable for the whole part of position
float degDec; //variable for decimal part
  
  clearGPS();
  while(!GPS.newNMEAreceived()){// lop until you have a good nmea sentence
    c=GPS.read();
  }
GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence
NMEA1=GPS.lastNMEA();

  while(!GPS.newNMEAreceived()){// lop until you have a good nmea sentence
    c=GPS.read();
  }
GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence
NMEA2=GPS.lastNMEA();

GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence
degWhole = float(int(GPS.latitude/100));// gives the whole degree part of longitude
degDec = (GPS.latitude - degWhole*100)/60; // gives me fractional part of longitude
deg = degWhole + degDec; // Gives complete decimal form of longitude degrees
if (GPS.lat == 'S'){//if in southern hemisphere latitude should be negative
  deg = (-1)*deg;
  
} 
ACA_Lat = deg;

degWhole = float(int(GPS.longitude/100));// gives the whole degree part of longitude
degDec = (GPS.longitude - degWhole*100)/60; // gives me fractional part of longitude
deg = degWhole + degDec; // Gives complete decimal form of longitude degrees
if (GPS.lon == 'W'){// if in West Hemisphere longitude should be negative
  deg = (-1)*deg;
  
}
ACA_Lon = deg;
}

void clearGPS() {// clear old and corrupt data from serial port

char c; //to read charchters coming from GPS
 while(!GPS.newNMEAreceived()){// lop until you have a good nmea sentence
    c=GPS.read();
  }
GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence

 while(!GPS.newNMEAreceived()){// lop until you have a good nmea sentence
    c=GPS.read();
  }
GPS.parse(GPS.lastNMEA()); // Parse that last good NMEA sentence

  while(!GPS.newNMEAreceived()){// lop until you have a good nmea sentence
    c=GPS.read();
  }

}

float distance(){
// Variables for distance function  
float Dist;


Bearing();

Heading();

float dp = (Phone_Lat - ACA_Lat)*(M_PI/180);
float d1 = (Phone_Lon - ACA_Lon)* (M_PI/180);



ACA_Lat = ACA_Lat * (M_PI/180);
ACA_Lon = ACA_Lon * (M_PI/180);
Phone_Lat =  Phone_Lat * (M_PI/180);
Phone_Lon = Phone_Lon *(M_PI/180);


//Dist = 6371000 * acos(sin(ACA_Lat)*sin(Phone_Lat)+ cos(ACA_Lat)* cos(Phone_Lat)* cos(Phone_Lon - ACA_Lon));
float x = sin((Phone_Lat - ACA_Lat)/2) * sin((Phone_Lat - ACA_Lat)/2)+ cos(ACA_Lat)* cos(Phone_Lat) * sin((Phone_Lon - ACA_Lon)/2) * sin((Phone_Lon - ACA_Lon)/2); 
float y = 2 * atan2(sqrt(x), sqrt(1-x));
Dist = 6371000.0 * y;


Serial.println("Distance");
Serial.println(Dist);

return Dist;

}

void checkGPS(){
  unsigned long start = millis();
while (millis() - start < GPS_UPDATE_INTERVAL) {

readGPS();
  
}
}


float Heading(){// Get heading for ACA

   /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

 // float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / M_PI;

  // Normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }

   
  Serial.print("Compass Heading: ");
  Serial.println(heading);

  return heading;
}

float Bearing(){// from ACA and Phone

  float y = sin(Phone_Lon - ACA_Lon) * cos(Phone_Lat);
  float x = cos(ACA_Lat)*sin(Phone_Lat) - sin(ACA_Lat)*cos(Phone_Lat)*cos(Phone_Lon - ACA_Lon);
  float bearing = atan2(y,x)*(180/M_PI);
if(bearing<0){

  bearing+=360;   //if the heading is negative then add 360 to make it positive

}
   Serial.print("Bearing: ");
  Serial.println(bearing);

  return bearing;
  
}

void driveTo()
{
  //int counter = 0;
  //Waypoints
  float Dist;
  float bearing;
  float heading;


  
   Dist = distance();
   bearing = Bearing();
   heading = Heading();

  
  
  float turn = bearing - heading;

  //Serial.println("This is the turn angle");
  //Serial.println(turn);
  while (turn < -180) turn += 360;
  while (turn >  180) turn -= 360;

  Serial.println("Turn angle after while loops");
  Serial.println(turn);
  //It will stop of the distance is less than 1 meter.
  if (Dist > 10)
  {
    if(turn > 5)
    {
      //Making it turn right
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 128);
      analogWrite(enB, 80);
    }
    else if (turn < -5)
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 80);
      analogWrite(enB, 128);
    }

    else 
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 128);
      analogWrite(enB, 128);
    }
  }
  else if (Dist <10)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);

    
  }

  
}
