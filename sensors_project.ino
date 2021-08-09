const int trigger1 =3; //Trigger pin of 1st Sensor
const int echo1 =5; //Echo pin of 1st Sensor
const int trigger2 =6; //Trigger pin of 2nd Sensor
const int echo2 =9;//Echo pin of 2nd Sensor
const int trigger3 =10; //Trigger pin of 3rd Sensor
const int echo3 =11;//Echo pin of 3rd Sensor

long time_taken;
int dist,distL,distC,distR,lint;
  
void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
pinMode(trigger3, OUTPUT); 
pinMode(echo3, INPUT);
}

//###Function to calculate distance###//
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}

void loop() { //infinite loop  


lint=analogRead(A0);
Serial.println(lint);

calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

 calculate_distance(trigger2,echo2);
distC =dist; //get distance of center sensor

calculate_distance(trigger3,echo3);
distR =dist; //get distance of right sensor 

//Play/Pause
if ((distL >10 && distL<40) && (distR >10 && distR<40)) //Detect both hands
{Serial.println("Play/Pause"); delay (500);}

//Full screen
if ((distR >10 && distR<40) && (distC >10 && distC<40)) //Detect both hands
{Serial.println("Fscreen"); delay (500);}

//Snapshot
if ((distL >10 && distL<40) && (distC >10 && distC<40)) //Detect both hands
{Serial.println("Snap"); delay (500);}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distC =dist;

calculate_distance(trigger3,echo3);
distR =dist;

//Control Modes
//Lock Left - Control Mode
  if (distL>=5 && distL<=40)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=5 && distL<=40)
  {
    Serial.println("Left Locked");
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<20) //Hand pushed in 
      {Serial.println ("Vdown"); delay (300);}
      if (distL>20) //Hand pulled out
      {Serial.println ("Vup"); delay (300);}
    }
  }
}

//Lock Center - Control Mode
if (distC>=5 && distC<=40)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distC =dist;
  if (distC>=5 && distC<=40)
  {
    Serial.println("Center Locked");
    while(distC<=40)
    {
      calculate_distance(trigger2,echo2);
      distC =dist;
      if (distC<20) //Hand pushed in 
      {Serial.println ("size"); delay (1000);}
    }
  }
}

//Lock Right - Control Mode
if (distR>=5 && distR<=40)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger3,echo3);
  distR =dist;
  if (distR>=5 && distR<=40)
  {
    Serial.println(" Right Locked");
    while(distR<=40)
    {
      calculate_distance(trigger3,echo3);
      distR =dist;
      if (distR<20) //Right hand pushed in
      {Serial.println ("Rewind"); delay (300);}
      if (distR>20) //Right hand pulled out
      {Serial.println ("Forward"); delay (300);}
  }
}
}

delay(200);
}
