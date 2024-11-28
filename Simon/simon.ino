const int pins[] = {8, 9, 10, 11};  // Array for pin numbers

const int pin8 = 8;
const int pin9 = 9;
const int pin10 = 10;
const int pin11 = 11;

void setup() {
  // Initialize serial communication and pin modes
  Serial.begin(9600);
  pinMode(pin8, OUTPUT); 
  pinMode(pin9, OUTPUT); 
  pinMode(pin10, OUTPUT); 
  pinMode(pin11, OUTPUT);
}

void turnOnPins() {
  // Set all pins to HIGH
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], HIGH);
  }
}

void turnOffPins() {
  // Set all pins to LOW
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  // Main game loop
  bool signalReceived = false;

  // Wait for signal or serial input
  while (!signalReceived) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(pins[i]) == HIGH) {
        Serial.print("Pin ");
        Serial.print(pins[i]);
        Serial.println("Received a HIGH signal.");
        signalReceived = true;  
        turnOnPins();
        delay(2000);
        turnOffPins();
        break;
      }
    }

    if (Serial.available() > 0) {
      Serial.read();  // Consume input
      Serial.println("Key pressed via Serial. Continuing...");
      signalReceived = true;
      break;
    }

    delay(30); // Wait briefly
  }

  // Print elapsed time
  Serial.print("Time: ");
  Serial.print(millis());

  // Generate random pin sequence
  randomSeed(millis());
  int pos[30];
  for (int i = 0; i < 30; i++) {
    pos[i] = random(8,12);
    Serial.println(pos[i]);
  }
  
  int speed = 600;  // Initial speed

  // Game sequence
  for (int i = 0; i < 30; i++) {
    // Show pattern up to the current round
    for (int j = 0; j <= i; j++) {
      digitalWrite(pos[j], HIGH);
      delay(speed);
      digitalWrite(pos[j], LOW);
      delay(speed / 1.5);
    }

    // Verify user input
    for (int k = 0; k <= i; k++) {
      bool validInput = false;

      while (!validInput) {
        // Check if the correct button is pressed
        if (digitalRead(pin8) == HIGH && pos[k] == 8) {
          Serial.println("True");
          while (digitalRead(pin8) == HIGH) {
            delay(30);
          }
          validInput = true;
        } else if (digitalRead(pin9) == HIGH && pos[k] == 9) {
          Serial.println("True");
          while (digitalRead(pin9) == HIGH) {
            delay(20);
          }
          validInput = true;
        } else if (digitalRead(pin10) == HIGH && pos[k] == 10) {
          Serial.println("True");
          while (digitalRead(pin10) == HIGH) {
            delay(20);
          }
          validInput = true;
        } else if (digitalRead(pin11) == HIGH && pos[k] == 11) {
          Serial.println("True");
          while (digitalRead(pin11) == HIGH) {
            delay(20);
          }
          validInput = true;
        } else if (digitalRead(pin8) == HIGH || digitalRead(pin9) == HIGH || digitalRead(pin10) == HIGH || digitalRead(pin11) == HIGH) {
          speed = 600; // Initial value
          Serial.println("Game Over");
          return;  // Exit if wrong input
        }

        delay(40); // Debounce
      }
    }
    speed -= 35; // Increase difficulty
    delay(800);  // Pause between rounds
  }
}
