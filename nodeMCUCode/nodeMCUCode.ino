int Step = 0; //GPIO0---D3 of Nodemcu--Step of stepper motor driver
int Dir  = 2; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int Trig = 5; //GPIO5 output
int Echo = 4; //GIPO4 input
long duration;
int distance;
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dir,  OUTPUT); //Direcction pin as output
  pinMode(Trig, OUTPUT); //Trigger pin as output
  pinMode(Echo, INPUT);  //Echo pin as input
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dir, LOW);  
  digitalWrite(Trig, LOW);
}
 
void loop() {
//  int i = 0;
//  digitalWrite(Dir, HIGH); //Rotate stepper motor in clock wise direction
//  for( i=1;i<=50;i++)
//  {
//    digitalWrite(Step, HIGH);
//    delayMicroseconds(500);
//    digitalWrite(Step, LOW);
//    delayMicroseconds(500);
//  }
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
}
