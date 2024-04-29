#include <SimpleWebSerial.h>
#include <Arduino_MKRIoTCarrier.h>
SimpleWebSerial WebSerial;
MKRIoTCarrier carrier;

float temperature = 0;
float humidity = 0;
float pressure = 0;

JSONVar sensorData;
static unsigned long lastPrint = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 57600 bits per second:
  Serial.begin(57600);
  // while (!Serial);

  carrier.noCase();
  carrier.begin();
  carrier.display.setRotation(0);




  readSensorData();

}


// the loop routine runs over and over again forever:
void loop() {
  readSensorData();


  carrier.leds.setPixelColor(0, 20, 20, 20);
  carrier.leds.setPixelColor(1, 20, 20, 20);
  carrier.leds.show();

  carrier.Buttons.update();
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    carrier.leds.setPixelColor(0, 0, 0, 0);
    Serial.println("Down Touch Button 0");
    WebSerial.send("touch", "TOUCH0");
  }
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    carrier.leds.setPixelColor(1, 0, 0, 0);
    Serial.println("Down Touch Button 1");
    WebSerial.send("touch", "TOUCH1");
  }

  if (carrier.Buttons.onTouchUp(TOUCH0)) {
    carrier.leds.setPixelColor(0, 20, 20, 20);
    Serial.println("Release Touch Button 0");
  }
  if (carrier.Buttons.onTouchUp(TOUCH1)) {
    carrier.leds.setPixelColor(1, 20, 20, 20);
    Serial.println("Release Touch Button 1");
  }
  carrier.leds.show();


  if ((lastPrint + 1000) < millis()) {

      printTemperature();
  printHumidity();
  printPressure();

  
    sensorData["temp"] = String(temperature);
    sensorData["humi"] = String(humidity);
    sensorData["pres"] = String(pressure);

    WebSerial.send("sensors", sensorData);
    lastPrint = millis();  // Update lastPrint time
  }


  // WebSerial needs to check if there is serial data
  WebSerial.check();

  // char str[80];
  // sprintf(str, "It has been %lu ms since the last reset!", millis() - reset);
  // WebSerial.send("log", str);
  delay(100);  // delay in between reads for stability
}











void readSensorData() {
  // read the sensor values
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
}

void printTemperature() {
  //cursor coordinates
  int16_t x1 = 60, y1 = 50;

  String tempString = "";
  tempString += "T: ";
  tempString += String(temperature);
  tempString += " C";

  printText(x1, y1, tempString);
}

void printHumidity() {
  //cursor coordinates
  int16_t x1 = 60, y1 = 80;

  String humiString = "";
  humiString += "H: ";
  humiString += String(humidity);
  humiString += " %";

  printText(x1, y1, humiString);
}

void printPressure() {
  //cursor coordinates
  int16_t x1 = 60, y1 = 110;

  String str = "";
  str += "P: ";
  str += String(pressure);
  str += " kPa";

  printText(x1, y1, str);
}


void printText(int x, int y, String textStr) {
  //calculated cursor coordinates
  int16_t x2, y2;
  //calculated w, h
  uint16_t w, h;

  carrier.display.getTextBounds(textStr, x, y, &x2, &y2, &w, &h);

  refreshBackground(x2, y2, w, h);
  carrier.display.setTextColor(ST77XX_WHITE);  //white text
  carrier.display.setTextSize(2);              //medium sized text

  carrier.display.setCursor(x, y);  //sets position for printing (x and y)
  carrier.display.println(textStr);
}

void refreshBackground(int x, int y, int w, int h) {
  carrier.display.fillRect(x, y, w, h, ST77XX_BLACK);
}