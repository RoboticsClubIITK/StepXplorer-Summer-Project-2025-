// === Sensor Pin Setup ===
// Bottom Front Sensors
const int frontBottomTrig[2] = {35, 37};
const int frontBottomEcho[2] = {34, 36};

// Top Front Sensors
const int frontTopTrig[2] = {27, 29};
const int frontTopEcho[2] = {26, 28};

// Side Sensors
const int leftTrig = 39, leftEcho = 38;
const int rightTrig = 41, rightEcho = 40;

const int NUM_SAMPLES = 20;  // Number of readings per sensor

// === Command Output Pins to Second Mega ===
const int CMD_FWD       = 1;
const int CMD_LEFT      = 2;
const int CMD_RIGHT     = 2;
const int CMD_TURNLEFT  = 4;
const int CMD_CLIMB     = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("Bot starting with 20-sample averaging...");

  pinMode(CMD_FWD, OUTPUT);
  pinMode(CMD_LEFT, OUTPUT);
  pinMode(CMD_RIGHT, OUTPUT);
  pinMode(CMD_TURNLEFT, OUTPUT);
  pinMode(CMD_CLIMB, OUTPUT);
}

void loop() {
  Serial.println("====== New Loop ======");

  // === Step 1: Side Sensor Readings (20-sample average) ===
  float leftDist = averageSensor(leftTrig, leftEcho);
  float rightDist = averageSensor(rightTrig, rightEcho);

  Serial.print("Left Distance  = "); Serial.print(leftDist); Serial.println(" cm");
  Serial.print("Right Distance = "); Serial.print(rightDist); Serial.println(" cm");

  // === Step 2: Side Obstacle Avoidance ===
  if (leftDist < 10) {
    Serial.println("Too close to LEFT wall → Shifting RIGHT");
    moveRight();
    delay(300);
  } else if (rightDist < 10) {
    Serial.println("Too close to RIGHT wall → Shifting LEFT");
    moveLeft();
    delay(300);
  }

  // === Step 3: Bottom Front Sensor Average ===
  float bottomAvg = getAverage(frontBottomTrig, frontBottomEcho, 2);
  Serial.print("Front Bottom Average = "); Serial.print(bottomAvg); Serial.println(" cm");

  // === Step 4: Decision Based on Front Sensors ===
  if (bottomAvg > 35) {
    Serial.println("Flat ground ahead → Moving Forward");
    moveForward();
  } else {
    float topAvg = getAverage(frontTopTrig, frontTopEcho, 2);
    float diff = abs(topAvg - bottomAvg);

    Serial.print("Front Top Average    = "); Serial.print(topAvg); Serial.println(" cm");
    Serial.print("Top - Bottom Diff    = "); Serial.print(diff); Serial.println(" cm");

    if (diff > 5) {
      Serial.println("Stair detected → Climbing Step");
      climbStep();
    } else {
      Serial.println("Not a stair → Turning Left");
      turnLeft();
    }
  }

  delay(300);
}

// === Average one ultrasonic sensor over NUM_SAMPLES ===
float averageSensor(int trigPin, int echoPin) {
  float total = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    total += readUltrasonic(trigPin, echoPin);
    delay(2);  // small delay to stabilize
  }
  return total / NUM_SAMPLES;
}

// === Average across multiple sensors ===
float getAverage(const int trigPins[], const int echoPins[], int count) {
  float total = 0;
  for (int i = 0; i < count; i++) {
    total += averageSensor(trigPins[i], echoPins[i]);
  }
  return total / count;
}

// === Read one ultrasonic sensor ===
float readUltrasonic(int trigPin, int echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  float distance = duration * 0.034 / 2.0;
  return constrain(distance, 0, 300);  // Cap to valid range
}

// === Movement Functions with Pin Signaling ===
void clearCommandPins() {
  digitalWrite(CMD_FWD, LOW);
  digitalWrite(CMD_LEFT, LOW);
  digitalWrite(CMD_RIGHT, LOW);
  digitalWrite(CMD_TURNLEFT, LOW);
  digitalWrite(CMD_CLIMB, LOW);
}

void moveForward() {
  Serial.println("Motor: Moving Forward");
  clearCommandPins();
  digitalWrite(CMD_FWD, HIGH);
}

void moveLeft() {
  Serial.println("Motor: Shifting Left");
  clearCommandPins();
  digitalWrite(CMD_LEFT, HIGH);
}

void moveRight() {
  Serial.println("Motor: Shifting Right");
  clearCommandPins();
  digitalWrite(CMD_RIGHT, HIGH);
}

void turnLeft() {
  Serial.println("Motor: Turning Left");
  clearCommandPins();
  digitalWrite(CMD_TURNLEFT, HIGH);
}

void climbStep() {
  Serial.println("Motor: Climbing Step");
  clearCommandPins();
  digitalWrite(CMD_CLIMB, HIGH);
}
