#define TRIG_PIN1 2
#define ECHO_PIN1 3
#define IR_PIN1 6
#define LED_PIN1 9

#define TRIG_PIN2 4
#define ECHO_PIN2 5
#define IR_PIN2 7
#define LED_PIN2 10

void setup() {
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(IR_PIN1, INPUT);
  pinMode(LED_PIN1, OUTPUT);

  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(IR_PIN2, INPUT);
  pinMode(LED_PIN2, OUTPUT);

  analogWrite(LED_PIN1, 0);
  analogWrite(LED_PIN2, 0);

  Serial.begin(9600);
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return 999; // No object detected
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  // -------- LED 1 Logic --------
  int irState1 = digitalRead(IR_PIN1);  // LOW = object detected
  long distance1 = getDistance(TRIG_PIN1, ECHO_PIN1);
  int brightness1 = 0;

  if (distance1 >= 5 && distance1 <= 100) {
    int linear = map(distance1, 100, 5, 0, 255);
    brightness1 = (linear * linear) / 255;
  }

  if (irState1 == LOW) {
    brightness1 = 80;  // Dim if IR detects
  }

  if (distance1 > 100 && irState1 == HIGH) {
    brightness1 = 0;  // Turn OFF
  }

  analogWrite(LED_PIN1, brightness1);

  // -------- LED 2 Logic --------
  int irState2 = digitalRead(IR_PIN2);
  long distance2 = getDistance(TRIG_PIN2, ECHO_PIN2);
  int brightness2 = 0;

  if (distance2 >= 5 && distance2 <= 100) {
    int linear = map(distance2, 100, 5, 0, 255);
    brightness2 = (linear * linear) / 255;
  }

  if (irState2 == LOW) {
    brightness2 = 80;
  }

  if (distance2 > 100 && irState2 == HIGH) {
    brightness2 = 0;
  }

  analogWrite(LED_PIN2, brightness2);

  // Debugging
  Serial.print("D1: ");
  Serial.print(distance1);
  Serial.print(" cm | IR1: ");
  Serial.print(irState1);
  Serial.print(" | B1: ");
  Serial.print(brightness1);

  Serial.print("  ||  D2: ");
  Serial.print(distance2);
  Serial.print(" cm | IR2: ");
  Serial.print(irState2);
  Serial.print(" | B2: ");
  Serial.println(brightness2);

  delay(100);
}
