//Program written for Senior Design Project Cal State LA
//Code by Francis Xavier Liri

//Program controls three pairs of claws and a shaft powered by 
//a DC motor used to move the robot body up and down a tree


#include <Servo.h>


#define enA 11 
#define in1 2 
#define in2 5 



Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


int sweepTime=20; 

int motorSpeed=150; 
int rotationDirection=0; 
int motorDuration=1000; 


int servo_position = 0; 
int servo_position2 = 0;

int position_center = 90;
int position_left = 5;
int position_right = 175;

int pair1_status=1;
int pair2_status=0;



int sweep2(unsigned long sweepTime, Servo &servoc, Servo &servod)
{
   
   int current_positionc=servoc.read();
   int current_positiond=servod.read();
   
   
if(pair2_status==1){  
  
  servo_position2=current_positiond;
  
     for (servo_position = current_positionc;servo_position >= position_left; servo_position -= 1 ){
       servoc.write(servo_position);
      
      servo_position2=servo_position2+1;
      servod.write(servo_position2);
      
      delay(sweepTime);
  }
 
  delay(2000);
 
  
  pair2_status=0; 


  return 3;
} 


if(pair2_status==0) { 

servo_position2=current_positiond;
    for (servo_position = current_positionc;servo_position <= position_center; servo_position += 1 ){
       servoc.write(servo_position);

       servo_position2=servo_position2-1;
      servod.write(servo_position2);
      
      delay(sweepTime);
  }
  
  delay(2000);

   
   pair2_status=1; 


return 2;
}
    
}



int sweep1(unsigned long sweepTime, Servo &servoa, Servo &servob,Servo &servoe, Servo &servof)
{  

if(pair1_status==1){  
  servo_position2=position_center;
  
  for (servo_position = position_center;servo_position >= position_left; servo_position -= 1 ){
       servoa.write(servo_position);
      servoe.write(servo_position);

      servo_position2=servo_position2+1;
      servob.write(servo_position2);
      servof.write(servo_position2);
      
      delay(sweepTime);
  }
  
  delay(2000);

   
  pair1_status=0; 
  

  return 3;
} 

if(pair1_status==0) { 
servo_position2=position_right;
  for (servo_position = position_left;servo_position <= position_center; servo_position += 1 ){

     servoa.write(servo_position);
      servoe.write(servo_position);

      servo_position2=servo_position2-1;
      servob.write(servo_position2);
      servof.write(servo_position2);
      
      delay(sweepTime);
  }
  delay(2000);
  
  
pair1_status=1; 
return 2;
}
    
}

void rotateShaft(int mSpeed, int rDirection,int mDuration){

  analogWrite(enA, mSpeed);
  delay(20);
  
  
  if(rDirection==0){
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(mDuration);
    
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    
  } else {
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(mDuration);

    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  
}

void setup() {
 
  Serial.begin(9600);

  servo1.attach(4);
  servo2.attach(6);
  servo3.attach(7);
  servo4.attach(8);
  servo5.attach(9);
  servo6.attach(10);

  servo1.write(position_center);
  servo2.write(position_center);
  servo3.write(position_center);
  servo4.write(position_center);
  servo5.write(position_center);
  servo6.write(position_center);

       
  int pair1_status=1;
  int pair2_status=0;
  
 int s2 = sweep2(20, servo3, servo4);
 int s1 = sweep1(20, servo1, servo2, servo5, servo6);
     }


void loop(){
  
int sweeping1, sweeping2;

do
  {
   
      sweeping1 = 0;
      sweeping2 = 1;

      if(pair2_status==1 && pair1_status==0){ 
               
        rotationDirection=0;
        rotateShaft(motorSpeed,rotationDirection,motorDuration);
         delay(2000);
      } 

     
      sweeping1 += sweep1(20, servo1, servo2, servo5, servo6);
      sweeping2 += sweep2(20, servo3, servo4);
     
      if(pair2_status==0 && pair1_status==1){
        
        rotationDirection=1;
        rotateShaft(motorSpeed,rotationDirection,motorDuration);
         delay(2000);
      }    

       sweeping2 += sweep2(20, servo3, servo4);
      sweeping1 += sweep1(20, servo1, servo2, servo5, servo6);

      
            
   } while (sweeping1 > 5 && sweeping2 > 5);


}
