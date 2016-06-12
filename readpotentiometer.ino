 // RangeFinder connected to analog A0
const int RangeFinder = A0;

// Potentiometer connected to analog A1
const int Potentiometer = A1;

// Speaker connected to digital D0
const int Sound = D0;

//Green LED connected to digital D1
const int greenLED = D1;
//Red LED connected to digital D1
const int redLED = D2;

// initialize height as a long for use in the map function
long height;

// The setup() method runs once, when the sketch starts
void setup() {
// initialize the Speaker pin as an output:
pinMode(Sound, OUTPUT);
// initialize the Green LED pin as an output:
pinMode(greenLED, OUTPUT);
// initialize the Red LED pin as an output:
pinMode(redLED, OUTPUT);

Serial.begin(9600);
}
// the loop() method runs over and over again,
// as long as the Arduino has power
void loop() {
int value = analogRead(RangeFinder);
float volts = (value/4095.0)*2.3;
long IN = ((70.0/volts)-6.0)*0.393701;//Hand position
Serial.println(IN);

int value_POT = analogRead(Potentiometer);//Potentiometer inches
float volts_POT = (value_POT/4095.0)*2.3;
long INCH_POT = ((70.0/volts_POT)-6.0)*0.393701;//Target
//Serial.println(INCH_POT);

//height is the distance between the your hand and the goal height
height = abs(IN-INCH_POT);
height = map(height,0.0,INCH_POT,0.0,255.0);

if (IN < 2*INCH_POT){
  analogWrite(redLED, LOW); // set the LED off
}
if (IN == INCH_POT){
  digitalWrite(redLED, LOW); // set the LED off
  digitalWrite(greenLED, LOW); // set the LED off
  tone(Sound,1000,1000);
}
if (IN > INCH_POT){
  analogWrite(greenLED, height); // set the LED on
  analogWrite(redLED, LOW); // set the LED off
}
if (IN < INCH_POT){
  analogWrite(redLED, height); // set the LED on
  analogWrite(greenLED, LOW); // set the LED off
}


delay(100);
}
