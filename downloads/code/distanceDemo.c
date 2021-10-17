#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
int LED = 13;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("DistanceSensor:");
  pinMode(LED,OUTPUT);
}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 8);
  // convert to inches by dividing by 2.54
  Serial.print(cm);
  Serial.println("cm");
  lcd.clear();
  lcd.print("DistanceSensor:");
  lcd.setCursor(0, 1);
  lcd.print(cm);
  lcd.print("cm");
    if (cm < 90) {
      digitalWrite(LED, HIGH);
      delay(1000);
  } else {
      digitalWrite(LED, LOW);
      delay(500); // Wait for 100 millisecond(s)
  }
}