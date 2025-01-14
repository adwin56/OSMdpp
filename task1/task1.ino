int LED_PIN[2]={5,6};

String cmd = "";

void setup() {
  pinMode(LED_PIN[0], OUTPUT);
  pinMode(LED_PIN[1], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char chr = Serial.read();
    if (chr == '#') {
      processCommand(cmd);
      cmd = "";
    } else {
      cmd += chr;
    }
  }
}

void processCommand(String command) {
  int Del = command.indexOf(';');
  String commandType = command.substring(0, Del);
  String args = command.substring(Del + 1);

  if (commandType == "setBrightINT") {
    int Del = args.indexOf(';');
    int Num = args.substring(0, Del).toInt();
    int brightness = args.substring(Del + 1).toInt();
    analogWrite(LED_PIN[Num-1], brightness);
  } else if (commandType == "setBrightFLOAT") {
    int Del = args.indexOf(';');
    int Num = args.substring(0, Del).toInt();
    float brightness = args.substring(Del + 1).toFloat();
    int Value = brightness * 255;
    analogWrite(LED_PIN[Num-1], Value);
  } else if (commandType == "launchAnimation") {
    int Del = args.indexOf(';');
    String animType = args.substring(0, Del);
    int duration = args.substring(Del + 1).toInt();

    if (animType == "separately") {
      SeparateAnim(duration);
    } else if (animType == "together") {
      TogetherAnim(duration);
    }
  }
}

void SeparateAnim(int duration) {
  int halfDuration = duration / 2;
  for (int i = 0; i < halfDuration / 250; i++) {
    analogWrite(LED_PIN[0], 255);
    analogWrite(LED_PIN[1], 0);
    delay(250);
    analogWrite(LED_PIN[0], 0);
    analogWrite(LED_PIN[1], 255);
    delay(250);
  }
  analogWrite(LED_PIN[0], 0);
  analogWrite(LED_PIN[1], 0);
}

void TogetherAnim(int duration) {
  for (int i = 0; i < duration / 500; i++) {
    analogWrite(LED_PIN[0], 255);
    analogWrite(LED_PIN[1], 255);
    delay(250);
    analogWrite(LED_PIN[0], 0);
    analogWrite(LED_PIN[1], 0);
    delay(250);
  }
}
