#include <Adafruit_AHTX0.h>
#include <Wire.h>
#include <TFT_eSPI.h>

#define SDA_PIN 27  // Your desired SDA pin (e.g., GPIO 27)
#define SCL_PIN 22

Adafruit_AHTX0 aht;
TFT_eSPI tft;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);


  if (!aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  tft.init();
  tft.setRotation(3);  // Adjust screen rotation if needed(3 is landscape usb on left)(X=320 W=240)
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
}

void loop() {
  tft.fillRect(80, 130, 280, 90, TFT_BLACK);  // cover over large temp display

  tft.drawRect(0, 0, 319, 239, TFT_WHITE);  // draw window box

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // populate temp and humidity objects with fresh data
  delay(1000);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.fillRect(2, 2, 300, 120, TFT_BLACK);  // cover over white txt
  tft.setCursor(10, 30);
  tft.print("Temp: ");
  tft.print(temp.temperature);
  tft.println(" C");

  tft.setCursor(10, 60);
  tft.print("Humidity: ");
  tft.print(humidity.relative_humidity);
  tft.println(" %");

  tft.setCursor(80, 130);  // display large temp display 3 colours for low comfort or hot
  if ((temp.temperature) < 18.0) {
    tft.setTextColor(TFT_BLUE);
  } else if ((temp.temperature) > 25.0) {
    tft.setTextColor(TFT_RED);
  } else {
    tft.setTextColor(TFT_GREEN);
  }
  tft.setTextSize(10);
  tft.print(int((temp.temperature)));
  tft.println(" C");


  delay(5000);
}