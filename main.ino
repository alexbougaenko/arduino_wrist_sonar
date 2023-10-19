const int trigPin = A0;   // Trigger pin for the ultrasonic sensor
const int echoPin = A1;   // Echo pin for the ultrasonic sensor
const int buzzPin = A2;   // Pin for the buzzer

const float minBpm = 60;  // Minimum beats per minute
const float maxBpm = 180; // Maximum beats per minute

const float palmLength = 10; // Length from sensor to palm bottom

float distance, buzzRatio, buzzBpm, buzzPeriod, buzzTime, silenceTime;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);   // Ensure trigger is low
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Send a 10 microsecond pulse to trigger
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH) * 0.034 / 2 - palmLength; // Calculate distance

  buzzRatio = 1 - floor(log(distance / 10 + 1) / log(2)) / 6; // Calculate buzz ratio
  buzzBpm = minBpm + (maxBpm - minBpm) * buzzRatio;           // Calculate beats per minute
  buzzPeriod = 60000 / buzzBpm;                               // Calculate buzzer period

  if (buzzRatio <= 0)
  {
    digitalWrite(buzzPin, LOW);
    delay(buzzPeriod);
  }
  else if (buzzRatio >= 1)
  {
    digitalWrite(buzzPin, HIGH);
    delay(buzzPeriod);
  }
  else
  {
    buzzTime = buzzPeriod * buzzRatio;          // Calculate time to turn on the buzzer
    silenceTime = buzzPeriod * (1 - buzzRatio); // Calculate time to keep the buzzer off

    digitalWrite(buzzPin, HIGH);  // Turn on the buzzer
    delay(buzzTime);              // Wait for the buzzer on time
    digitalWrite(buzzPin, LOW);   // Turn off the buzzer
    delay(silenceTime);           // Wait for the silence time
  }
}