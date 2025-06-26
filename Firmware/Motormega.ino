const int dirPins[4]  = {32, 30, 28, 26};  // FL, FR, RL, RR
const int stepPins[4] = {33, 31, 29, 27};

// Set direction for all motors
bool motorDirections[4] = {false, true, false, true}; // Flip as needed

const int stepsPerRevolution = 200;
const int microstepping = 1;

const float frontRPM = 100.0;
const float rearRPM = (frontRPM * 6.5) / 11.5; // ≈ 28.26

const int frontDelay = 1000000 / ((stepsPerRevolution * microstepping * frontRPM) / 60.0); // ~6000 µs
const int rearDelay  = 1000000 / ((stepsPerRevolution * microstepping * rearRPM) / 60.0);  // ~10618 µs

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(dirPins[i], OUTPUT);
    pinMode(stepPins[i], OUTPUT);
    digitalWrite(dirPins[i], motorDirections[i] ? HIGH : LOW);
  }
}

void loop() {
  // Move front motors (0,1) faster, rear motors (2,3) slower
  for (int step = 0; step < stepsPerRevolution; step++) {
    // Step HIGH
    digitalWrite(stepPins[0], HIGH); // FL
    digitalWrite(stepPins[1], HIGH); // FR
    digitalWrite(stepPins[2], HIGH); // RL
    digitalWrite(stepPins[3], HIGH); // RR

    delayMicroseconds(frontDelay); // Front step ends sooner
    digitalWrite(stepPins[0], LOW);
    digitalWrite(stepPins[1], LOW);

    delayMicroseconds(rearDelay - frontDelay); // Wait rest of rear delay
    digitalWrite(stepPins[2], LOW);
    digitalWrite(stepPins[3], LOW);

    delayMicroseconds(rearDelay); // Finish full step cycle
  }

  //delay(1000); // Pause before next movement
}
