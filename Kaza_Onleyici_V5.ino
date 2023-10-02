const int trigPin1 = 2;   // HC-SR04 1. trig pini
const int echoPin1 = 3;   // HC-SR04 1. echo pini
const int trigPin2 = 4;   // HC-SR04 2. trig pini
const int echoPin2 = 5;   // HC-SR04 2. echo pini
const int trigPin3 = 6;   // HC-SR04 3. trig pini
const int echoPin3 = 7;   // HC-SR04 3. echo pini
const int trigPin4 = 8;   // HC-SR04 4. trig pini
const int echoPin4 = 9;   // HC-SR04 4. echo pini

const int motorPin1A = 10;  // Sol motor A pin
const int motorPin1B = 11;  // Sol motor B pin
const int motorPin2A = 12;  // Sağ motor A pin
const int motorPin2B = 13;  // Sağ motor B pin

const int buzzerPin = A0;  // Buzzer pin

int distanceThreshold = 5; // Yakın mesafe eşiği (5 cm olarak varsayıyoruz)

void setup() {
  pinMode(motorPin1A, OUTPUT);
  pinMode(motorPin1B, OUTPUT);
  pinMode(motorPin2A, OUTPUT);
  pinMode(motorPin2B, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  Serial.begin(9600);
}

void loop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  int distance3 = getDistance(trigPin3, echoPin3);
  int distance4 = getDistance(trigPin4, echoPin4);

  Serial.print("Distance 1: ");
  Serial.println(distance1);
  Serial.print("Distance 2: ");
  Serial.println(distance2);
  Serial.print("Distance 3: ");
  Serial.println(distance3);
  Serial.print("Distance 4: ");
  Serial.println(distance4);
  Serial.println("-----------------");

  // Sol taraftan engel yaklaşırsa
  if (distance1 < distanceThreshold) {
    Serial.print("SOLDA ENGEL TESPIT EDILDI..");
    buzzerAlert();
      turnRight();
    Serial.print("saga donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnLeft();
    Serial.print("sola donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnLeft();
    Serial.print("sola donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnRight();
    Serial.print("saga donuluyor..");
      delay(1000);
    
  }
  // Sağ taraftan engel yaklaşırsa
  else if (distance2 < distanceThreshold) {
    Serial.print("SAGDA ENGEL TTESPIT EDILDI..");
    buzzerAlert();
      turnLeft();
    Serial.print("sola donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnRight();
    Serial.print("saga donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnRight();
    Serial.print("saga donuluyor..");
      delay(1000);
      forward();
    Serial.print("Duz gidiliyor..");
      delay(1000);
      turnLeft();
    Serial.print("sola donuluyor..");
      delay(1000);
    
  }
  // Ön taraftan engel yaklaşırsa
  else if (distance3 < distanceThreshold) {
    Serial.print("ONDE ENGEL TESPIT EDILDI..");
    buzzerAlert();
    if (distance4 > distanceThreshold) {
      reverse();
    } else {
      stopMotors();
    }
    
  }
  // Arka taraftan engel yaklaşırsa
  else if (distance4 < distanceThreshold) {
    Serial.print("ARKADA ENGEL TESPIT EDILDI..");
    buzzerAlert();
    if (distance1 > distanceThreshold) {
      forward();
    } else {
      stopMotors();
    }
    
  }
  // Tüm yönlere engel yaklaşırsa
  else if (distance1 < distanceThreshold && distance2 < distanceThreshold && distance3 < distanceThreshold && distance4 < distanceThreshold) {
    Serial.print("HER YONDE ENGEL TESPIT EDILDI..");
    buzzerAlert();
    stopMotors();
    
  }
  // Engel yoksa ileri git
  else {
    Serial.print("ENGEL YOK..");
    forward();
  }

  delay(100);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void forward() {
  digitalWrite(motorPin1A, HIGH);
  digitalWrite(motorPin1B, LOW);
  digitalWrite(motorPin2A, HIGH);
  digitalWrite(motorPin2B, LOW);
}

void reverse() {
  digitalWrite(motorPin1A, LOW);
  digitalWrite(motorPin1B, HIGH);
  digitalWrite(motorPin2A, LOW);
  digitalWrite(motorPin2B, HIGH);
}

void turnLeft() {
  digitalWrite(motorPin1A, LOW);
  digitalWrite(motorPin1B, HIGH);
  digitalWrite(motorPin2A, HIGH);
  digitalWrite(motorPin2B, LOW);
}

void turnRight() {
  digitalWrite(motorPin1A, HIGH);
  digitalWrite(motorPin1B, LOW);
  digitalWrite(motorPin2A, LOW);
  digitalWrite(motorPin2B, HIGH);
}

void stopMotors() {
  digitalWrite(motorPin1A, LOW);
  digitalWrite(motorPin1B, LOW);
  digitalWrite(motorPin2A, LOW);
  digitalWrite(motorPin2B, LOW);
}

void buzzerAlert() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
  }
