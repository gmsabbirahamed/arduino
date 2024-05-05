int r = 13;
int g = 12;
int b = 11;
int btn = 2;
int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() {
  Serial.println(state);

  if(state == 0) {
    digitalWrite(r, 1);
    digitalWrite(g, 1);
    digitalWrite(b, 1);
  }

  if(digitalRead(btn) == HIGH) {
    state = state + 1;
    if(state == 1) { // for red
      digitalWrite(r, 0);
      digitalWrite(g, 1);
      digitalWrite(b, 1);
    }
    else if(state == 2) { // for green
      digitalWrite(r, 1);
      digitalWrite(g, 0);
      digitalWrite(b, 1);
    }
    else if(state == 3) { // for blue
      digitalWrite(r, 1);
      digitalWrite(g, 1);
      digitalWrite(b, 0);
    }
    else if(state == 4) { // for blue + green
      digitalWrite(r, 1);
      digitalWrite(g, 0);
      digitalWrite(b, 0);
    }

    else if(state == 5) { // for automatic
    while(1)
    {
      Serial.println(state);

      digitalWrite(r, 0);
      digitalWrite(g, 1);
      digitalWrite(b, 1);
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
     
      digitalWrite(r, 1);
      digitalWrite(g, 0);
      digitalWrite(b, 1);
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
      
      digitalWrite(r, 1);
      digitalWrite(g, 1);
      digitalWrite(b, 0);
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
    
      digitalWrite(r, 1);
      digitalWrite(g, 0);
      digitalWrite(b, 0);
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
      delay(200);
      if(digitalRead(btn) == HIGH){return;}
    
    }
      
    }
    delay(200);
  }
  if(state == 6) {
    state = 0;
  }
}
