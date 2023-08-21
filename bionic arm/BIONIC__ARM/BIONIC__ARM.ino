#include <Servo.h>
#include<IRremote.h>
Servo s;
IRrecv r(9);
decode_results results;

void setup() {
  Serial.begin(9600);
  
  pinMode(12,OUTPUT);//S-
  pinMode(11,OUTPUT);//S+
  digitalWrite(12,LOW);//S-
  digitalWrite(11,HIGH);//S+
  
  pinMode(8,OUTPUT);//IR+
  pinMode(7,OUTPUT);//IR-
  digitalWrite(8,HIGH);//IR+
  digitalWrite(7,LOW);//IR-
   
  pinMode(6,OUTPUT);//L+
  pinMode(5,OUTPUT);//L-
  digitalWrite(5,LOW);//L-
   
  pinMode(4,OUTPUT);//M-+
  pinMode(3,OUTPUT);//M+-
  
  pinMode(2,OUTPUT);//G+

  r.enableIRIn();
  s.attach(10);
  s.write(180);

}

int x=180,l=0;
void loop() {
 
if ( r.decode(&results)){
  Serial.println("***************");
  Serial.println(results.value,HEX);
  Serial.println("***************");

  
  if(results.value==16718055||results.value==0xA20){
  if(x==0){x=180;}
  x-=5;
  }

  
  if(results.value==16730805||results.value==0xA10){
  if(x==180){x=0;}
  x+=5;
  }

  
  if(results.value==16726215 ||results.value==0xA50){
  if(l==0){digitalWrite(6,LOW);l=1;}
  else{digitalWrite(6,HIGH);l=0;}
  }


  if(results.value==16716015||results.value==0xA30){
  digitalWrite(4,LOW);
  digitalWrite(3,HIGH);
  delay(2000);
  digitalWrite(3,LOW);
  }


  if(results.value==16734885||results.value==0xA40){
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(2000);
  digitalWrite(4,LOW);
  }

  
  s.write(x);
  r.resume();
  results.value=0;
  }
  delay(100);
}

//16718055 UP
//16730805 DOWN
//16726215 OK
//16716015 LEFT
//16734885 RIGHT
//16738455 *
//16756815 #
//16750695 0
