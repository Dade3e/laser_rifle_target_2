// LASER RIFLE Attiny shot
// Davide Barchetta 2024

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0   -> laser
//                  +----+

#define AnalogPin 3 //ATTINY 3, NANO A0
#define ding 0 //ATTINY 0, NANO 2
#define dingTime 30
#define debounce 250
#define theshold 10 // max * theshold; 0 < theshold < 1

#define bufferSize 6

#define debug false
#define info false

int buffer[bufferSize];
int index = 0;
int media = 10;

void setup() {

  pinMode(AnalogPin,INPUT);
  pinMode(ding,OUTPUT);
  digitalWrite(ding, LOW);
  for(int i = 0;i< bufferSize;i++){
    buffer[i] =  analogRead(AnalogPin);
  }
  if(info || debug)
    Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(AnalogPin);
  if(sensorValue > media + theshold){
    if(debug){
      Serial.print(media);
      Serial.print(",");
      Serial.print(sensorValue);
      Serial.print(",");
      Serial.println(sensorValue-media);
    }
    if(info){
      Serial.println("HIT");
    }
    dong();
    delay(debounce);
  }
  buffer[index] = sensorValue;
  index += 1;
  if(index >= bufferSize) { index = 0; }
  int sum = 0;
  for (int i = 0; i<bufferSize; i++){
    sum += buffer[i];
  }
  media = (sum/bufferSize);
  /*
  if(sensorValue > media +( media * theshold)){
    Serial.println("HIT");
  }
  if(sensorValue > media + ( media * theshold)){
    buffer[index] = sensorValue;
    index += 1;
    if(index >= bufferSize) { index = 0; }
    int sum = 0;
    for (int i = 0; i<bufferSize; i++){
      sum += buffer[i];
    }
    media = (sum/bufferSize);
  }
  if(debug){
    Serial.print(sensorValue);
    Serial.print(" | ");
    for (int i = 0; i<bufferSize; i++){
      Serial.print(buffer[i]);
      Serial.print(" ");
    }
    Serial.print("| ");
    Serial.print(media);
    Serial.print("| ");
    Serial.println(media + media*theshold);
  }*/
  delay(1);
}

void dong(){
  digitalWrite(ding, HIGH);
  delay(dingTime);
  digitalWrite(ding, LOW);
}
