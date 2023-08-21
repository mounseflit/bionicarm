#include <IRremote.h>
#include <IRremoteInt.h>
IRsend irsend;
// Arduino UNO: Output = D3
// Arduino MEGA: Output = D9

void setup()
{
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  analogWrite(A0,0);
  analogWrite(A1,255); 
  analogWrite(A4,255);
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  Serial.begin(9600);
}
float x, y;
int z;
void loop() {

 x = analogRead (A2) * (5.0 / 1023.0);
 y = analogRead (A3) * (5.0 / 1023.0);
 Serial.print ("X-axis:"); Serial.print (x, 4); Serial.print ("V, ");
 Serial.print ("Y-axis:"); Serial.print (y, 4); Serial.print ("V, ");

if(x<1){ irsend.sendRC5(0xA10, 12); }
if(x>3){ irsend.sendRC5(0xA20, 12); }
if(y<1){ irsend.sendRC5(0xA30, 12); }
if(y>3){ irsend.sendRC5(0xA40, 12); }
if(z==1){ irsend.sendRC5(0xA50, 12);z=0; }

Serial.print ("Button:");
 if(analogRead (A4)>800)
 {
 Serial.println ("not pushed");
 z=0;
 }
 else
 {
 Serial.println ("pushed");
 z=1;
 }
 delay (200);

}
