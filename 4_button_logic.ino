
////////////////////////////////FUNCTIONALITY of 4 buttons/////////////////////
long randNum2; // DECLARES OUR Random num for this subprocess
//////////////////////TIME LIMIT FOR DECISION
const unsigned long timeLimit = 8000; // 8 seconds
////////////////////////////

//////Score Tracker//////
int score = 0;
bool gameOver = false;
bool winner = false;
///////////////////////

void setup() {
/////RANDOM NUMBER SETUP/////////////////////////////////////////
Serial.begin(9600);

randomSeed(analogRead(A5)); // uses analog pin 5 which is unused so that we can have a random number each time
///////////////////////////////////////////////////////////////////

//////////////////ENCODER PINS//////////////////////
  pinMode(9, INPUT_PULLUP); // Encoder A for rotary
  pinMode(10, INPUT_PULLUP); // Encoder B for rotary

  ////////////////////////////////////////////////

  //////THIS IS FOR THE 4 buttons for option 1//////////
  // DECLARES OUR INPUT AND OUTPUT PINS////////////////////////////
  pinMode(5, INPUT_PULLUP); // declares all pins 
  // this is X
  pinMode(6, INPUT_PULLUP); // this is Y
  pinMode(7, INPUT_PULLUP); // this is triangle
  pinMode(2,INPUT_PULLUP); // this is square
  //////////////////////////////////////////////
  pinMode(4,OUTPUT); // this is showing that it was correct
  pinMode(8,OUTPUT); // this shows that it was WRONG?!!!!
}




// the loop function runs over and over again forever

void loop() {

  //////////GAME ENDER CHECK///////////////
  if (gameOver) {

    if (winner)
      Serial.println("YOU WIN!");
    else
      Serial.println("GAME OVER!");

    digitalWrite(4, HIGH);
    digitalWrite(8, HIGH);

    while (true); // stop program forever
  }
  ////////////////////////////////////////

  int operation = random(2); // 0-buttons, 1-rotary, 2-triggers
  /////////////////
  for (int i = 0; i <= operation; i++) {
    digitalWrite(8, HIGH);
    delay(300);
    digitalWrite(8, LOW);
    delay(300);
    ///////////////////////////////// bottom light blinks for what operation to do
  }
  delay(500); // small delay


  if (operation == 0){

  ////////RANDOM BUTTON///////////////
  randNum2 = random(4); // a random number from 0-3: 0 - X,1-Y,2-triangle,3-square

   // Flash lights for which operation to do
  for (int i = 0; i <= randNum2; i++) {
    digitalWrite(4, HIGH);
    delay(300);
    digitalWrite(4, LOW);
    delay(300);
  }



  if (randNum2 == 0) Serial.println("PRESS X");
  if (randNum2 == 1) Serial.println("PRESS Y");
  if (randNum2 == 2) Serial.println("PRESS TRIANGLE");
  if (randNum2 == 3) Serial.println("PRESS SQUARE");

  delay(500); // small delay
  ///////////////////////////////////////

  //////////STARTING TIMER//////
  unsigned long startTime = millis();
  bool finished = false;
  bool correct = false;
  ////////////////////////////////////////

  int encoderStep = digitalRead(9);  // the dial position before

  ///WAITING FOR INPUT
  while (!finished) {

    // timeout check
    if (millis() - startTime >= timeLimit) {
      Serial.println("ran out of time");
      finished = true;
      correct = false;
      break;
    }
  ///////////////////////////////////

  if (digitalRead(9) != encoderStep) {
            correct = false;
            finished = true;
            break;
        }               //making sure that you did not spin the dial


  //////CHECK BUTTONS///////////


  // button checks
    if (digitalRead(5) == LOW) {
      correct = (randNum2 == 0);
      finished = true;
    }
    else if (digitalRead(6) == LOW) {
      correct = (randNum2 == 1);
      finished = true;
    }
    else if (digitalRead(7) == LOW) {
      correct = (randNum2 == 2);
      finished = true;
    }
    else if (digitalRead(2) == LOW) {
      correct = (randNum2 == 3);
      finished = true;
    }
  }

  if (correct) {

    score++;

    Serial.println("CORRECT!");
    Serial.print("Score: ");
    Serial.println(score);

    digitalWrite(4, HIGH);
    delay(500);
    digitalWrite(4, LOW);

    // win condition
    if (score >= 100) {
      winner = true;
      gameOver = true;
    }
  }
  else {

    Serial.println("WRONG INPUT OR TIME OUT!");
    gameOver = true;

    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
  }



  delay(1000); // pause before next round
}

if (operation == 1){

  bool finished = false;
  bool correct = false;
  long movement = 0; // initial movement is set at 0 
   

  long target = 2; // 2 revolutions which is our goal


    unsigned long startTime = millis();
    int previousStep = digitalRead(9);

    while (millis() - startTime < timeLimit) {

    int step = digitalRead(9);

    if (step != previousStep) {
        movement++;
        previousStep = step;
        // NO delay here — keep looping fast
    }

    if (movement >= target) {
        correct = true;
        break;
    }

    if (digitalRead(5)==LOW || digitalRead(6)==LOW ||
        digitalRead(7)==LOW || digitalRead(2)==LOW) {
        correct = false;
        break;
    }
    // No delay at all in this loop
}

    if (correct) {
      score++;
      Serial.println("CORRECT!");
      Serial.print("Score: ");
      Serial.println(score);

      digitalWrite(4, HIGH);
      delay(500);
      digitalWrite(4, LOW);

      if (score >= 100) {
        winner = true;
        gameOver = true;
      }
    }
    else {
      Serial.println("WRONG INPUT OR TIME OUT!");
      gameOver = true;

      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
    }

    delay(1000);
  }

}
///////////////////////////
