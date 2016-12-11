#include <Arduino.h>

#include <Homie.h>
#include <Button.h>

const int PIN_RELAY = 15;
const int PIN_LED = 2;
const int PIN_BUTTON = 13;


HomieNode switchNode("plug", "switch");
Button button1(PIN_BUTTON, true, false, 100); // Connect your button between pin 2 and GND

bool lightOnHandler(HomieRange range, String value) {
  if (value == "true") {
    digitalWrite(PIN_RELAY, HIGH);
     switchNode.setProperty("on").send("true");
    Serial.println("Light is on");
  //  switchState = true;
  } else if (value == "false") {
    digitalWrite(PIN_RELAY, LOW);
     switchNode.setProperty("on").send("false");
    Serial.println("Light is off");
//    switchState = false;
  } else {
    Serial.print("Error Got: ");
    Serial.println(value);
    return false;
  }

  return true;
}



void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  //pinMode(PIN_BUTTON,INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  Serial.print("Setup - PIN_RELAY: ");
  Serial.println(digitalRead(PIN_RELAY));

  Homie.setLedPin(PIN_LED, LOW);
  delay(200);
  Homie.setLedPin(PIN_LED, HIGH);
  delay(200);
  Homie.setLedPin(PIN_LED, LOW);
  //Homie.setResetTrigger(PIN_BUTTON, LOW, 5000);
  Homie_setFirmware("ecoplug", "1.0.0");
  switchNode.advertise("on").settable(lightOnHandler);
  //button1.begin();
  Homie.setup();
}

void loop() {
  Homie.loop();
  if (button1.isPressed())
  {
    Serial.println("Button pressed");
    digitalWrite(PIN_RELAY, !digitalRead(PIN_RELAY));
  }


}
