const int analogInPin1 = A0;
const int analogInPin2 = A1;

const int ledPin1 = 7;
const int ledPin2 = 6;
const int pumpPin1 = 9;
const int pumpPin2 = 8;

int sensorValue1 = 0;
int sensorValue2 = 0;
const int numReadings = 10;
int readings1[numReadings];
int readings2[numReadings];
int total1 = 0;
int total2 = 0;
const int threshold1 = 500;
const int threshold2 = 500;
const int pumpOnFor1 = 600;
const int pumpOnFor2 = 600;
const int pumpOffFor1 = 1200;
const int pumpOffFor2 = 1200;

int pumpTriggered1 = 0;
int pumpTriggered2 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(pumpPin1, OUTPUT);
  pinMode(pumpPin2, OUTPUT);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
  }
}

void loop() {
  for (int readIndex = 0; readIndex < numReadings; readIndex++) {
    total1 = total1 - readings1[readIndex];
    total2 = total2 - readings2[readIndex];
    readings1[readIndex] = analogRead(analogInPin1); 
    readings2[readIndex] = analogRead(analogInPin2);
    
    total1 = total1 + readings1[readIndex];
    total2 = total2 + readings2[readIndex];
    
    delay(2);
  }
    
  sensorValue1 = total1 / numReadings;
  sensorValue2 = total2 / numReadings;

  Serial.print("sensor1 = " );                       
  Serial.print(sensorValue1);    
  Serial.print("\t sensor2 = " );                       
  Serial.print(sensorValue2); 
  Serial.print("\t pumpTriggered1 = " );                       
  Serial.print(pumpTriggered1); 
  Serial.print("\t pumpTriggered2 = " );                       
  Serial.println(pumpTriggered2);

  if(sensorValue1 < threshold1){
    digitalWrite(ledPin1, HIGH);
    if(pumpTriggered1==0){
      pumpTriggered1 = 1;
    }
  }else{
    digitalWrite(ledPin1, LOW);
  }
  if(sensorValue2 < threshold2){
    digitalWrite(ledPin2, HIGH);
    if(pumpTriggered2==0){
      pumpTriggered2 = 1;
    }
  }else{
    digitalWrite(ledPin2, LOW);
  }
  
  if(pumpTriggered1 > 0 && pumpTriggered1 < pumpOnFor1){
    digitalWrite(pumpPin1, HIGH);
  }else{
    digitalWrite(pumpPin1, LOW);
  }
  if(pumpTriggered1 >= pumpOffFor1){
    pumpTriggered1 = 0;
  }
  if(pumpTriggered2 > 0 && pumpTriggered2 < pumpOnFor2){
    digitalWrite(pumpPin2, HIGH);
  }else{
    digitalWrite(pumpPin2, LOW);
  }
  if(pumpTriggered2 >= pumpOffFor2){
    pumpTriggered2 = 0;
  }
  
  if(pumpTriggered1 > 0){
    pumpTriggered1++;
  }
  if(pumpTriggered2 > 0){
    pumpTriggered2++;
  }

  delay(1000);                     
}
