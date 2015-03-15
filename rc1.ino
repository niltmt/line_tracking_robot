//Left wheels
int const in1 = 2;
int const in2 = 3;
int const ena = 5;
int const sena = A1;

//Right Wheels
int const in3 = 4;
int const in4 = 7;
int const enb = 6;
int const senb = A0;

int const but = A2;

int const speedhigh = 240;
int const speednormal = 190;
int const speedlow = 140;
int const acdetime = 50;
boolean ison = 1;
boolean reach = 0;

void setup()
{
   Serial.begin(9600);
  
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(ena, OUTPUT);
   pinMode(enb, OUTPUT);
   pinMode(sena, INPUT);
   pinMode(senb, INPUT);
   pinMode(but, INPUT);
}

void loop()
{
  if (analogRead(but) == 1023)
    ison = 1;
  else {
    ison = 0;
    reach = 0;
  }
  delay(1000);
  if (ison == 1 && reach == 0) {
    if (sensorstate() == 1) {
      gocar();
    } else {
      stopcar();
      reach = 1;
    }
  } else {
    stopcar();
  }
}

void accelerate()
{
  for (int i = speedlow; i <= speedhigh; i++) {
    analogWrite(ena, i);
    analogWrite(enb, i);
    delay(acdetime);
  } 
}

void decelerate()
{
  for (int i = speedhigh; i >= speedlow; i--) {
    analogWrite(ena, i);
    analogWrite(enb, i);
    delay(acdetime);
  } 
}

void gocar()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(ena, speednormal);
  analogWrite(enb, speednormal);
}

void stopcar()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void goback()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(ena, speednormal);
  analogWrite(enb, speednormal);
}

int sensorstate()
{
  int state;
  float a = analogRead(sena);
  float b = analogRead(senb);
  Serial.print("sensor1: ");
  Serial.print(a);
  Serial.print("  ||  sensor2: ");
  Serial.println(b);
  
  if (a > 100.0 && b > 100.0)
    state = 1;
  else if (a < 100.0 && b > 100.0)
    state = 2;
  else if (a > 100.0 && b < 100.0)
    state = 3;
  else
    state = 0;
  return state;
}
