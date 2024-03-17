int sts = false;

void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if(digitalRead(2) == 1)
  {
    sts = !sts;
    digitalWrite(13, sts);
    delay(200);
  }
}
//G.M.SABBIR AHAMED