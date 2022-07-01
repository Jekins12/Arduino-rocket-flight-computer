#include <MPU6050_tockn.h>
#include <Servo.h>
#include<Wire.h>


int valX[3];
int val_filterX;
byte indexX;

int valY[3];
int val_filterY;
byte indexY;

int AngleX,AngleY,AngleZ;
boolean Ready=true;                              //countdown before the start (YES-true) (NO-false)
const int buttonPin = 10; 
int buttonState = 0; 
const int ign=11;
const int ign_res=12;
const int zumer=5;
int i=0;
unsigned long currentMillis=0;
boolean flag=false;
boolean start=false;  
const int interval_flight = 10000;     //flight duration (milisecond)

Servo servoX1;
Servo servoY1;
Servo servoX2;
Servo servoY2;

MPU6050 mpu6050(Wire);

void setup(){

  pinMode(ign,OUTPUT);
  pinMode(buttonPin, INPUT); 
  pinMode(ign_res,OUTPUT);
  pinMode(zumer,OUTPUT);
  servoX1.attach(9);
  servoX2.attach(8);
  servoY1.attach(7);
  servoY2.attach(6);
  
  servoX1.write(90);
  servoY1.write(90);
  servoX2.write(90);
  servoY2.write(90);
  delay(1000);
  servoX1.write(0);
  servoY1.write(0);
  servoX2.write(0);
  servoY2.write(0);
  delay(1000);
  servoX1.write(180);
  servoY1.write(180);
  servoX2.write(180);
  servoY2.write(180);
  delay(1000);
  servoX1.write(90);
  servoY1.write(90);
  servoX2.write(90);
  servoY2.write(90);

  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  tone(5, 600, 800);

 
}
void loop(){
 
  buttonState = digitalRead(buttonPin);
  if((buttonState == LOW)&&(Ready==true)) {
  
  
   
 
 while(i!=10){
  tone(zumer,400,300);
  i++;
  delay(1000);
  start=true;
 } 
  }
 if(start==true){
 digitalWrite(ign,HIGH);
 flag=true; 
 start=false;
 Ready=false;
 currentMillis=millis();
}

 
if((millis()-currentMillis >=interval_flight)&&(flag==true)) {
  digitalWrite(ign,LOW);
  digitalWrite(ign_res,HIGH);
  delay(2000);
  digitalWrite(ign_res,LOW);
  start=false;
  flag=false;
  i++;
  }
 
   mpu6050.update();
   AngleX=round(mpu6050.getAngleX()); 
   AngleY=round(mpu6050.getAngleY());
   //AngleZ=round(mpu6050.getAngleZ());                                                           
  

                                                                                                                                                                                                                                                                                                             ; 
  


    if (++indexX > 2) indexX = 0; 
    valX[indexX] = AngleX;
    val_filterX = middle_of_3X(valX[0], valX[1], valX[2]);
    
    if (++indexY > 2) indexY = 0; 
    valY[indexY] = AngleY;
    val_filterY = middle_of_3Y(valY[0], valY[1], valY[2]);



    AngleX=val_filterX;
    //int AcX2=val_filterX;
    
    AngleY=val_filterY;
    //int AcY2=val_filterY;
        

 //   servoX1.write(AcX);
 //   servoY1.write(AcY);
 //   servoX2.write(AcX2);
 //   servoY2.write(AcY2);

    int AngleX1=map(AngleX,-180,180,0,180);
    int AngleY1=map(AngleY,-180,180,0,180);
    int AngleX2=map(AngleX,-180,180,180,0);
    int AngleY2=map(AngleY,-180,180,180,0);
     

 //   AngleX=constrain(AngleX,30,150);
 //   AngleY=constrain(AngleY,30,150);

     

    servoX1.write(AngleX1);
    servoY1.write(AngleY1);
    servoX2.write(AngleX2);
    servoY2.write(AngleY2);
    


   Serial.print("X:");   
   Serial.print(AngleX1); 
   Serial.print(" ");
   Serial.print("Y:");
   Serial.print(AngleY1); 
   Serial.println(" ");
  
  delay(50);
}


float middle_of_3X(float ax, float bx, float cx) {
int middleX;
if ((ax <= bx) && (ax <= cx)) {
middleX = (bx <= cx) ? bx : cx;
}
else {
if ((bx <= ax) && (bx <= cx)) {
middleX = (ax <= cx) ? ax : cx;
}
else {
middleX = (ax <= bx) ? ax : bx;
}
}
return middleX;
}

float middle_of_3Y(float ay, float by, float cy) {
int middleY;
if ((ay <= by) && (ay <= cy)) {
middleY = (by <= cy) ? by : cy;
}
else {
if ((by <= ay) && (by <= cy)) {
middleY = (ay <= cy) ? ay : cy;
}
else {
middleY = (ay <= by) ? ay : by;
}
}
return middleY;
}
