
int pot1 = 0;
int pot2 = 0;

int inByte;

int led1 = 9;
int led2 = 8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // setup LEDs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {

    inByte = Serial.read();

    if (inByte == 'P') sensorPositions();

    if (inByte == 'R') 
    {
      digitalWrite(led1, HIGH);
      delay(100);
      digitalWrite(led1, LOW);
     }

    if (inByte == 'L')
    {
      digitalWrite(led2, HIGH);
      delay(100);
      digitalWrite(led2, LOW);
    }
  }
  delay(20);
}

void sensorPositions(){
  pot1 = analogRead(A0);
  pot2 = analogRead(A1);
  
  Serial.print(getPadded(pot1));
  Serial.print("-");
  Serial.println(getPadded(pot2));
}

String getPadded(int num){
  
  char buff[5];
  char padded[6];

  sprintf(buff, "%.4u", num);

  padded[0] = buff[0];
  padded[1] = buff[1];
  padded[2] = buff[2];
  padded[3] = buff[3];
  padded[4] = buff[4];
  padded[5] = '\0';

  return String(padded);
}



