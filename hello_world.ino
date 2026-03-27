//COMMENT FOR MY NAME ASHER



// the setup function runs once when you press reset or power the board
//Connor Rosenberg GitHub edit
void setup() {
  pinMode(9, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}
int currentLight = 8;

// the loop function runs over and over again forever
void loop() {
  /////  CODE FOR SINGLE LED  /////
  // if (digitalRead(9) == HIGH){
  //   nextLight(currentLight);
  // }

  /////  CODE FOR THREE LEDS  /////
  if (digitalRead(9) == HIGH){
    nextLight(currentLight);  // Blink LED
    currentLight -= 1;        // decrement output pin
    if (currentLight == 5){   // Keep light output 6, 7, or 8
      currentLight = 8;
    }
  } else{
    currentLight = 8; // Reset to leftmost LED (#8)
  }
}

void nextLight(int light){
  digitalWrite(light, HIGH);  // Turn on LED
  delay(500);                 // half second pause
  digitalWrite(light, LOW);   // Turn off LED
  delay(500);                 // half second pause
}
