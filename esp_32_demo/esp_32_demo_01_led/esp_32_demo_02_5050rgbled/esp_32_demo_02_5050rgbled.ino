/*
  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

// 2023.1.6

int ledPinG1 = 18;
int ledPinR1 = 23;
int ledPinB1 = 26;
int ledPinG2 = 25;
int ledPinR2 = 27;
int ledPinB2 = 27;

void setup() {
    //pinMode(ledPin, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(ledPinG1, OUTPUT);
    pinMode(ledPinR1, OUTPUT);
    pinMode(ledPinB1, OUTPUT);
    pinMode(ledPinG2, OUTPUT);
    pinMode(ledPinR2, OUTPUT);
    pinMode(ledPinB2, OUTPUT);                    
}

// the loop function runs over and over again forever
/*
void loop1() {
    digitalWrite(ledPin, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    delay(1000);                      // Wait for a second
    digitalWrite(ledPin, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
*/

//
void loop() {
    // 白光
    LED_LightOnWhite();
    delay(1000);
    LED_LightOffWhite();
    // 暖黄光
    LED_LightOnWarm();
    delay(1000);
    // 暖白光
    LED_LightOnWhite();
    delay(1000);
    LED_LightOffWarm();
}

void LED_LightOnWhite(void) {
    digitalWrite(ledPinG1, HIGH);
    digitalWrite(ledPinR1, HIGH);
    digitalWrite(ledPinB1, HIGH);
}

void LED_LightOffWhite(void) {
    digitalWrite(ledPinG1, LOW);
    digitalWrite(ledPinR1, LOW);
    digitalWrite(ledPinB1, LOW);
}

void LED_LightOnWarm(void) {
    digitalWrite(ledPinG2, HIGH);
    digitalWrite(ledPinR2, HIGH);
    //digitalWrite(ledPinB1, HIGH);
}

void LED_LightOffWarm(void) {
    digitalWrite(ledPinG2, LOW);
    digitalWrite(ledPinR2, LOW);
    //digitalWrite(ledPinB1, HIGH);
}