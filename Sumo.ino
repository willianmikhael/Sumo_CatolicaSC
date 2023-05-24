class MotorController {
  private:
    int startPin;
    int pin1;
    int pin2;
  
  public:
    MotorController(int startPin, int pin1, int pin2) {
      this->startPin = startPin;
      this->pin1 = pin1;
      this->pin2 = pin2;

      pinMode(startPin, OUTPUT);
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
    }

    void setSpeed(int speed) {
      if (speed >= 0) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
      } else {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        speed = abs(speed);
      }
      
      analogWrite(startPin, speed);
    }
};

// Function to read distance from Sharp sensor
int getDistance(int sensorPin) {
  float volts = analogRead(sensorPin) * 0.0048828125;
  int distance = 26 * pow(volts, -1);
  return distance;
}

// Constants
const int START_MOTOR_1 = 3;
const int LEFT_MOTOR_PIN_1 = 5;
const int LEFT_MOTOR_PIN_2 = 4;
const int START_MOTOR_2 = 9;
const int RIGHT_MOTOR_PIN_1 = 7;
const int RIGHT_MOTOR_PIN_2 = 8;
const int S1 = A1;
const int S2 = A2;
const int THRESHOLD = 600;
const int SENSOR_PIN = A3;

// Motor instances
MotorController motor1(START_MOTOR_1, LEFT_MOTOR_PIN_1, LEFT_MOTOR_PIN_2);
MotorController motor2(START_MOTOR_2, RIGHT_MOTOR_PIN_1, RIGHT_MOTOR_PIN_2);

void setup() {
  Serial.begin(9600);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int sensor1 = analogRead(S1);
  int sensor2 = analogRead(S2);
  int distance = getDistance(SENSOR_PIN);

  if (sensor1 <= THRESHOLD) {
    for (int i = 0; i < 24000; i++) {
      motor1.setSpeed(-72);
      motor2.setSpeed(-180);
    }
  } else if (sensor2 <= THRESHOLD) {
    for (int j = 0; j < 24000; j++) {
      motor1.setSpeed(-180);
      motor2.setSpeed(-72);
    }
  } else if (sensor1 <= THRESHOLD && sensor2 <= THRESHOLD) {
    for (int j = 0; j < 30000; j++) {
      motor1.setSpeed(-120);
      motor2.setSpeed(-120);
    }
    for (int j = 0; j < 2000; j++) {
      motor1.setSpeed(-120);
      motor2.setSpeed(-90);
    }
  } else if (distance <= 20) {
    motor1.setSpeed(250);
    motor2.setSpeed(250);
  } else {
    motor1.setSpeed(120);
    motor2.setSpeed(120);
  }
}
