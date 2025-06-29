#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object (16 cols, 2 rows)
// 0x27 is the common I2C address — change to 0x3F if your LCD does not show text
LiquidCrystal_I2C lcd(0x27, 16, 2);

int gasPin = 34;         // Potentiometer signal (gas sensor)
int valveMotorPin = 26;  // LED simulating motorized valve
int buzzerPin = 25;      // Buzzer
int threshold = 500;     // Gas leak threshold

void setup() {
  pinMode(valveMotorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);

  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("Gas Shutoff Sys");
  delay(2000);         // Show welcome message
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(gasPin);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);
  lcd.print("   "); // Clear trailing chars

  if (gasValue > threshold) {
    digitalWrite(valveMotorPin, HIGH);  // Valve ON
    digitalWrite(buzzerPin, HIGH);      // Buzzer ON

    lcd.setCursor(0, 1);
    lcd.print("Status: LEAK!   ");
  } else {
    digitalWrite(valveMotorPin, LOW);   // Valve OFF
    digitalWrite(buzzerPin, LOW);       // Buzzer OFF

    lcd.setCursor(0, 1);
    lcd.print("Status: SAFE    ");
  }

  delay(500);
}
