#define LIGHT1 5
#define LIGHT2 6

String receivedData = "";

void setup() {
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    char incomingByte = Serial.read();
    if (incomingByte == '#') {
      handleCommand(receivedData);
      receivedData = "";
    } else {
      receivedData += incomingByte;
    }
  }
}

void handleCommand(String data) {
  int separatorPos = data.indexOf(';');
  String action = data.substring(0, separatorPos);
  String parameters = data.substring(separatorPos + 1);

  if (action == "adjustLevel") {
    changeLightLevel(parameters);
  } else if (action == "adjustFractionalLevel") {
    changeLightLevelFractionally(parameters);
  } else if (action == "runSequence") {
    executeSequence(parameters);
  }
}

void changeLightLevel(String parameters) {
  int splitPos = parameters.indexOf(';');
  int lightId = parameters.substring(0, splitPos).toInt();
  int intensity = parameters.substring(splitPos + 1).toInt();

  if (lightId == 1) {
    analogWrite(LIGHT1, intensity);
  } else if (lightId == 2) {
    analogWrite(LIGHT2, intensity);
  }
}

void changeLightLevelFractionally(String parameters) {
  int splitPos = parameters.indexOf(';');
  int lightId = parameters.substring(0, splitPos).toInt();
  float fraction = parameters.substring(splitPos + 1).toFloat();
  int pwmValue = fraction * 255;

  if (lightId == 1) {
    analogWrite(LIGHT1, pwmValue);
  } else if (lightId == 2) {
    analogWrite(LIGHT2, pwmValue);
  }
}

void executeSequence(String parameters) {
  int splitPos = parameters.indexOf(';');
  String sequenceType = parameters.substring(0, splitPos);
  int sequenceDuration = parameters.substring(splitPos + 1).toInt();

  if (sequenceType == "alternating") {
    runAlternating(sequenceDuration);
  } else if (sequenceType == "simultaneous") {
    runSimultaneous(sequenceDuration);
  }
}

void runAlternating(int duration) {
  int cycles = duration / 500;
  for (int i = 0; i < cycles; i++) {
    analogWrite(LIGHT1, 255);
    analogWrite(LIGHT2, 0);
    delay(250);
    analogWrite(LIGHT1, 0);
    analogWrite(LIGHT2, 255);
    delay(250);
  }
  analogWrite(LIGHT1, 0);
  analogWrite(LIGHT2, 0);
}

void runSimultaneous(int duration) {
  int cycles = duration / 500;
  for (int i = 0; i < cycles; i++) {
    analogWrite(LIGHT1, 255);
    analogWrite(LIGHT2, 255);
    delay(250);
    analogWrite(LIGHT1, 0);
    analogWrite(LIGHT2, 0);
    delay(250);
  }
}
