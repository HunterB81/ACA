;;# ACA (Autonomous Carrier Assistant)
Created by Hunter Busa, Amine Chahli, Richard Garces, Muhammad Khan.

## Project Description
In today’s world of modern technology life is becoming more and more automated.
Conserving energy has been a human trait since the days of hunter gatherers.
Our laziness has brought about ingenious ways to get things done.
This project is derived from this concept. Why carry something when you can just
make something to do it for you. The A.C.A. will be designed to carry your belonging for
you and give you the ability to conserve your energy. This project creates an autonomous
robot which leads and follows the user with obstacle avoidance and it also will have a
joystick function for when the GPS connection is low, it is versatile and efficient as well as being low
cost to both produce and sell on the market. The hardware and software chosen to complete
this project were all extensively researched to produce the most cost-efficient product
to go to market.
  
### Website
Inside of this folder contains all of the website's files wehere all of the ACA's information and documentation is gathered together and put together for display. The index.html file is the website that puts everything together on display. 

### Joystick
This file is the C++ code for the Arduino that allows the user to control the ACA using a Joystick that is setup on the Blynk app that the user will be using.

### BTGPS
This file is how we make the ACA follow the user by calculating the ACA's gps coordinates and the user's phones coordinates and finding the heading, bearing, and Distance. The user's phones coordinates are streamed through the Blynk mobile app. 
 
### Mobile App
This is an attempt at creating a mobile application through React Native that uses Bluetooth connectivity and controls the ACA. I may go back in the future to complete it but for now we ended up using the mobile application called Blynk to control the ACA. 
