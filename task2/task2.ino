#define LED_PIN1 5
#define LED_PIN2 6
#define SENSOR_PIN1 A0
#define SENSOR_PIN2 A1

int lightSensor1 = 0;
int lightSensor2 = 0;

void setup() {
  initializeHardware();
}

void loop() {
  readSensors();
  adjustLEDs();
  checkLightConditions();
  delay(100); // Обновление каждые 100 мс
}

void initializeHardware() {
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  Serial.begin(9600);
}

void readSensors() {
  lightSensor1 = analogRead(SENSOR_PIN1);
  lightSensor2 = analogRead(SENSOR_PIN2);
}

void adjustLEDs() {
  int brightness1 = calculateBrightness(lightSensor1);
  int brightness2 = calculateBrightness(lightSensor2);

  analogWrite(LED_PIN1, brightness1);
  analogWrite(LED_PIN2, brightness2);
}

int calculateBrightness(int sensorValue) {
  return map(sensorValue, 0, 1023, 0, 255);
}

void checkLightConditions() {
  if (lightSensor1 < 900 || lightSensor2 < 900) {
    sendAnimationCommand("separate", 5000);
  } else if (lightSensor1 >= 900 && lightSensor2 >= 900) {
    sendAnimationCommand("together", 3000);
  }
}

void sendAnimationCommand(String mode, int duration) {
  String command = "launchAnimation;" + mode + ";" + String(duration) + "#";
  Serial.print(command);
}
