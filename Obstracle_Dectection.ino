#define TRIG_PIN 5
#define ECHO_PIN 18
#define VIBRATION_PIN 19

long duration;
float distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(VIBRATION_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(VIBRATION_PIN, LOW);

  Serial.println("Smart Obstacle Detection Glasses Started");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    Serial.println("No valid distance measurement");
    digitalWrite(VIBRATION_PIN, LOW);
  } else {
    // Calculate distance in centimeters
    distance = duration * 0.0343 / 2.0;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Vibrate when an obstacle is within 100 cm
    if (distance <= 100 && distance > 0) {
      digitalWrite(VIBRATION_PIN, HIGH);
      Serial.println("Obstacle detected - Vibration ON");
    } else {
      digitalWrite(VIBRATION_PIN, LOW);
      Serial.println("Path clear - Vibration OFF");
    }
  }

  delay(200);
}