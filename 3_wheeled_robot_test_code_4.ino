#include <Servo.h>
Servo myservo;
int pos = 0;


#include <PS2X_lib.h>

#define IN1 2
#define IN2 7
#define IN3 4
#define IN4 A0
#define IN5 A1
#define IN6 8
#define ENA 6
#define ENB 3
#define ENC 5
 
PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
 Serial.begin(57600);
 Serial.println("hello");
  myservo.attach(9);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN5, OUTPUT);
  pinMode (IN6, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (ENC, OUTPUT);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void loop(){

  
    ps2x.read_gamepad(false, vibrate); // disable vibration of the controller

    int nJoyR = ps2x.Analog(PSS_RX); // read right stick
    int nJoyLY = ps2x.Analog(PSS_LY); // read left stick
    int nJoyLX = ps2x.Analog(PSS_LX); // read left stick
   
    nJoyR = float(map(nJoyR, 0, 255, -1023, 1023));
    nJoyLY = float(map(nJoyLY, 0, 255, -1023, 1023));
    nJoyLX = float(map(nJoyLX, 0, 255, -1023, 1023));
    
    //nJoyR = (nJoyR-4)
    float percentage = abs(nJoyR/1023.00);
    // Perform movements based on both analog sticks
     if(nJoyR>50) {
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        digitalWrite(IN5,LOW);
        digitalWrite(IN6,HIGH);
      
        analogWrite(ENA, 255*percentage);
        analogWrite(ENB, 255*percentage);
        analogWrite(ENC, 255*percentage);
        Serial.println(float(nJoyR));
        Serial.println(percentage);
        
        Serial.println("moters spining right");

        
     }

     if(nJoyR<-50) {
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN5,HIGH);
        digitalWrite(IN6,LOW);
        analogWrite(ENA, 255*percentage);
        analogWrite(ENB, 255*percentage);
        analogWrite(ENC, 255*percentage);
        Serial.println(255*percentage);
        Serial.println("moters spining left");
    }  







    if((nJoyLY>80) && (nJoyLX<80) && (nJoyLX>-80)){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
      
        analogWrite(ENA, 255);
        analogWrite(ENB, 255);
        analogWrite(ENC, 0);
        Serial.println("forward");


//        Serial.println(float(nJoyR));

     }





 if((nJoyLY<-80) && (nJoyLX<80) && (nJoyLX>-80)){
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
      
        analogWrite(ENA, 255);
        analogWrite(ENB, 255);
        analogWrite(ENC, 0);
        Serial.println("backward");
//        Serial.println(float(nJoyR));

     }

    if((nJoyLX<-80) && (nJoyLY<80) && (nJoyLY>-80)){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        digitalWrite(IN5,LOW);
        digitalWrite(IN6,HIGH);
        analogWrite(ENA, 95);
        analogWrite(ENB, 95);
        analogWrite(ENC, 230);
//        Serial.println(float(nJoyR));

     }


    if((nJoyLX>80) && (nJoyLY<80) && (nJoyLY>-80)){
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        digitalWrite(IN5,HIGH);
        digitalWrite(IN6,LOW);
        analogWrite(ENA, 95);
        analogWrite(ENB, 95);
        analogWrite(ENC, 230);
 
//        Serial.println(float(nJoyR));

     }
     


    if((nJoyLY>80) && (nJoyLX>80)){
        digitalWrite(IN5,HIGH);
        digitalWrite(IN6,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
      
        analogWrite(ENA, 0);
        analogWrite(ENB, 255);
        analogWrite(ENC, 255);
        Serial.println("diagonal");

        
//        Serial.println(float(nJoyR));

     }

    if((nJoyLY<-80) && (nJoyLX<-80)){
        digitalWrite(IN5,LOW);
        digitalWrite(IN6,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
      
        analogWrite(ENA, 0);
        analogWrite(ENB, 255);
        analogWrite(ENC, 255);

//        Serial.println(float(nJoyR));

     }


    if((nJoyLY>80) && (nJoyLX<-80)){
        digitalWrite(IN5,LOW);
        digitalWrite(IN6,HIGH);
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
      
        analogWrite(ENA, 255);
        analogWrite(ENB, 0);
        analogWrite(ENC, 255);

//        Serial.println(float(nJoyR));

     }


    if((nJoyLY<-80) && (nJoyLX>80)){
        digitalWrite(IN5,HIGH);
        digitalWrite(IN6,LOW);
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
      
        analogWrite(ENA, 255);
        analogWrite(ENB, 0);
        analogWrite(ENC, 255);

//        Serial.println(float(nJoyR));

     }


   if (((abs(nJoyR) > -50) && (abs(nJoyR) < 50)) && ((abs(nJoyLY) > -80) && (abs(nJoyLY) < 80) && (nJoyLX < 80) && (nJoyLX > -80))){
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        analogWrite(ENC, 0);
        Serial.println(nJoyR);
        Serial.println("moters have stoped");
     }
     
   if(ps2x.ButtonPressed(PSB_R1)){
        //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(90);
        //}
     }

   if(ps2x.ButtonPressed(PSB_R2)){
        //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        myservo.write(180);
        //
     }
   ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

   vibrate = ps2x.Analog(PSAB_BLUE); 

 
 delay(50);
 }    



   
