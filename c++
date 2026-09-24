// ===== Ультразвуковой датчик =====
#define TRIG 3
#define ECHO 2

// ===== Правые моторы =====
#define RIGHT_A1 4
#define RIGHT_A2 5
#define RIGHT_B1 6
#define RIGHT_B2 7

// ===== Левые моторы =====
#define LEFT_A1 10
#define LEFT_A2 11
#define LEFT_B1 8
#define LEFT_B2 9

// Расстояние до препятствия
#define LIMIT 10

// Время поворота
#define TURN_TIME 550


void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RIGHT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(RIGHT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);

  pinMode(LEFT_A1, OUTPUT);
  pinMode(LEFT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(LEFT_B2, OUTPUT);

  stopMotors();

  Serial.begin(9600);
}


void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Если препятствие на расстоянии 10 см или меньше
  if (distance <= LIMIT) {

    stopMotors();
    delay(200);

    // Поворачиваем направо
    turnRight();
    delay(TURN_TIME);

    stopMotors();
    delay(100);

  } 
  else {

    // Едем вперёд
    forward();
  }

  delay(50);
}


// =================================================
// Измерение расстояния HC-SR04
// =================================================

long getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long time = pulseIn(ECHO, HIGH, 30000);

  if (time == 0) {
    return 400;
  }

  long distance = time * 0.0343 / 2;

  return distance;
}


// =================================================
// Движение вперёд
// =================================================

void forward() {

  // Правые моторы
  digitalWrite(RIGHT_A1, HIGH);
  digitalWrite(RIGHT_A2, LOW);

  digitalWrite(RIGHT_B1, HIGH);
  digitalWrite(RIGHT_B2, LOW);

  // Левые моторы
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_A2, LOW);

  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(LEFT_B2, LOW);
}


// =================================================
// Поворот направо
// =================================================

void turnRight() {

  // Правые моторы назад
  digitalWrite(RIGHT_A1, LOW);
  digitalWrite(RIGHT_A2, HIGH);

  digitalWrite(RIGHT_B1, LOW);
  digitalWrite(RIGHT_B2, HIGH);

  // Левые моторы вперёд
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_A2, LOW);

  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(LEFT_B2, LOW);
}


// =================================================
// Стоп
// =================================================

void stopMotors() {

  digitalWrite(RIGHT_A1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B1, LOW);
  digitalWrite(RIGHT_B2, LOW);

  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_A2, LOW);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(LEFT_B2, LOW);
}
