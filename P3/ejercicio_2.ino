// C++ code
//
int state;
void setup()
{
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  state = digitalRead(7);
  
  if (state == HIGH) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
  } else {
    delay(1500); // Wait for 1500 millisecond(s)
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(1500); // Wait for 1500 millisecond(s)
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);

  }

}