// LASER RIFLE Attiny shot
// Davide Barchetta 2024

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0   -> gong
//                  +----+

#define analogPin 3 //ATTINY Ain3, NANO A0
#define potPin 2 //ATTINY Ain2, NANO A1
#define ding 0 //ATTINY 0, NANO 2
#define dingTime 30
#define debounce 250

#define bufferSize 6

#define debug false
#define info false

int buffer[bufferSize];
int index = 0;
int media = 10;
int treshold = 80;

void setup() {
  ADMUX |= (6<<MUX0);
  pinMode(analogPin,INPUT);
  pinMode(potPin,INPUT);
  pinMode(ding,OUTPUT);
  digitalWrite(ding, LOW);
  for(int i = 0;i< bufferSize;i++){
    buffer[i] =  analogRead(analogPin);
  }
  if(info || debug)
    Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  int tmp = analogRead(potPin);
  treshold = map(tmp, 0, 1023, 0, 255);
  if(debug){
    Serial.print(tmp);
    Serial.print(" ");
    Serial.println(treshold);
  }
  if(sensorValue > media + treshold){
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

  delay(1);
}

void dong(){
  digitalWrite(ding, HIGH);
  delay(dingTime);
  digitalWrite(ding, LOW);
}
