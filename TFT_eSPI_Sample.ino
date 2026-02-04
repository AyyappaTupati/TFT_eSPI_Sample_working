/*
NOTE :: use the below setup for esp32 wroom 32 module for my convinence 
************************************************************************
************************************************************************
Below settings are done at user_setup.h header file and this file is located in 
file path :: C:\Users\ayyappa\OneDrive\Documents\Arduino\libraries\TFT_eSPI\User_Steup.h

#define ILI9341_2_DRIVER     // Alternative ILI9341 driver, see https://github.com/Bodmer/TFT_eSPI/issues/1172

#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_SCLK 18
#define TFT_CS   25
#define TFT_DC   32
#define TFT_RST  33

#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH

#define SPI_FREQUENCY  27000000

************************************************

these are the spi and pin setting done based ont the requirments
Dont modify them use them as it is........
*/

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320
#define LINE_HEIGHT   18    // Safe for font size 1
#define START_Y       40


#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  Serial.begin(115200);
  delay(200);

  Serial.println("ESP32 TFT_eSPI FINAL TEST");

  // Backlight ON
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Set WiFi to Station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();   // Avoid auto connect
  delay(100);

  // Initialize display
  tft.init();
  tft.setRotation(0);   // 0 = Portrait (240x320)

  // Clear screen
  tft.fillScreen(TFT_BLACK);

  // Print detected resolution
  Serial.print("Width: ");
  Serial.println(tft.width());
  Serial.print("Height: ");
  Serial.println(tft.height());


  // Text test
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  PrintText("ESP32 + TFT", 20, 20, 2);
  PrintText("FULL SCREEN OK", 20, 50, 2);
  delay(1000);
  tft.fillScreen(TFT_BLACK);

  PrintText("Wi-Fi", 50, 70, 3);
  PrintText("Scanning....", 20, 100, 2);
  delay(500);


  int n = WiFi.scanNetworks();

  tft.fillScreen(TFT_BLACK);
  PrintText("Wi-Fi Networks:", 10, 10, 2);

  if (n == 0) 
  {
    PrintText("No networks found", 10, START_Y, 1);
  } 
  else
  {
      int y = START_Y;

      for (int i = 0; i < n; i++)
      {
        // Stop if screen is full
        if (y > SCREEN_HEIGHT - LINE_HEIGHT)
        {
          PrintText("More networks...", 10, y, 1);
          break;
        }
        // Format text
        String line = String(i + 1) + ". " + WiFi.SSID(i);

        // Truncate long SSIDs
        if (line.length() > 26)
        {
          line = line.substring(0, 26) + "...";
        }
        PrintText(line, 10, y, 1);
        y += LINE_HEIGHT;
      }
    }
  }

void loop() {
}


void PrintText(const String& string, int32_t x, int32_t y, int8_t font){
  tft.setTextSize(font);
  tft.setCursor(x, y);
  tft.println(string);  
}




