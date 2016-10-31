#include <Wire.h>
byte x = 1;
int s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, fe=0, be=0;
long previousMillis = 0, interval = 2000, currentMillis = 0;
void setup() {
  Wire.begin();
  //Wire.onReceive(receiveEvent); // join i2c bus (address optional for master)
  pinMode(8,OUTPUT); //input1
  pinMode(9,OUTPUT); //input2
  pinMode(11,OUTPUT); //input3
  pinMode(10,OUTPUT); //input4
  pinMode(7, INPUT);// front edge ir
  pinMode(6, INPUT);// back edge ir
  Serial.begin(9600);
}

void loop() {
  getData();
  drive();
  delay(50);
}

void getData()
{
  fe=digitalRead(7);
  be=digitalRead(6);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(x);              // sends one byte
  Wire.endTransmission();
  Wire.requestFrom(8, 1);    // request one bytes from slave device #8
  int c = Wire.read(); // receive a byte as int
  switch(x)
  {
    case 1: s1=c;
            break;
    case 2: s2=c;
            break;
    case 3: s3=c;
            break;;
    case 4: s4=c;
            break;
    case 5: s5=c;
            break;
    case 6: s6=c;
            break;
    default: break;            
  }
  x++;
  if(x>6)
  {
    x=1;
  }
}

void drive()
{
  if((fe==0 && be==0) || (s1<=10 && s4<=10))
  {
    nutral();
  }
  else if(be==0)
  {
   forward();
  } 
  else if(fe==0)
  {
    unsigned long previousMillis = millis();
    currentMillis = previousMillis;
    while (currentMillis - previousMillis < interval)
    {
      getData();
      if(s6>=15)
      {
        backward_left();
      }
      else if(s4>=15)
      {
        backward_right();
      }
      else if(be==0)
      {
       forward();
      } 
      else if (s5>=15)
      {
        nutral();
      }
      currentMillis = millis();
    }
  }
  else
  {
    if(s2<=15)
    {
      if(s6>=15)
      {
        backward_left();
      }
      else if(s4>=15)
      {
        backward_right();
      }
    }
    
    else if(s1<=15)
    {
      forward_right();
    }
    
    else if(s3<=15)
    {
      forward_left();
    }
    
    else
    {
      forward();
    }
  }
}

void forward_left()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void forward_right()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void backward_left()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void backward_right()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void forward()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void backward()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void left()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void right()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void nutral()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
