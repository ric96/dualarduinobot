#include <NewPing.h>
#include <Wire.h>
int x=0,us1=1,us2=1,us3=1,us4=1,us5=1,us6=1;

NewPing s1(13, 12, 200);
NewPing s2(11, 10, 200);
NewPing s3(9, 8, 200);
NewPing s4(7, 6, 200);
NewPing s5(5, 4, 200);
NewPing s6(3, 2, 200);


void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event // register event
  Serial.begin(9600);
  //delay(100);  // start serial for output
}

void loop() {
  
  us1=s1.ping_cm();
  us2=s2.ping_cm();
  us3=s3.ping_cm();
  us4=s4.ping_cm();
  us5=s5.ping_cm();
  us6=s6.ping_cm();
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
x = Wire.read();    // receive byte as an integer

}
void requestEvent() {
  switch(x)
 {
   case 1: Wire.write(us1);
           break;
   case 2: Wire.write(us2);
           break;
   case 3: Wire.write(us3);
           break;
   case 4: Wire.write(us4);
           break;
   case 5: Wire.write(us5);
           break;
   case 6: Wire.write(us6);
           break;
   default: Wire.write(100);
           break;   
 } // respond with message of 6
  // as expected by master
}
