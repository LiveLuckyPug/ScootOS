#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the analog pin for the resistance sensor
const int analogPin = A0;

void setup() {
    // Initialize the LCD
    lcd.begin(16, 2);
    lcd.backlight();  // Turn on the backlight
    lcd.setCursor(0, 0);
    lcd.print("Tank Level: ");
    
    Serial.begin(9600); // Initialize Serial Monitor for debugging
}

void loop() {
    // Read the analog value from the specified pin
    int sensorValue = analogRead(analogPin);

    // Convert the analog value (0-1023) to a percentage (0-100)
    float percentage = (sensorValue / 10.23); // 1023 / 100 = 10.23

    // Clear the first line and print the tank level
    lcd.setCursor(0, 0); // Move to the first line
    lcd.print("Tank Level: ");
    lcd.print(percentage, 1); // Print percentage with one decimal place
    lcd.print("%"); // Add percent sign

    // Create a bar graph on the second line
    lcd.setCursor(0, 1); // Move to the second line
    int barLength = map(sensorValue, 0, 1023, 0, 16); // Map sensor value to bar length (0-16)
    
    for (int i = 0; i < 16; i++) {
        if (i < barLength) {
            lcd.write(255); // Print filled block (custom character)
        } else {
            lcd.print(" "); // Print empty space
        }
    }

    // Optional: Print to Serial Monitor for debugging
    Serial.print("Analog Value: ");
    Serial.print(sensorValue);
    Serial.print(" - Tank Level: ");
    Serial.print(percentage);
    Serial.println("%");

    delay(1000); // Update every second
}
