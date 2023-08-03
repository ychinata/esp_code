#include <Arduino.h>
/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *  Project:         Webspector - WebServer based Spectrum Analyzer                                                                                      *
 *  Target Platform: ESP32                                                                                                                               *
 *                                                                                                                                                       *
 *  Version: 1.0                                                                                                                                         *
 *  Hardware setup: See github                                                                                                                           *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *  Mark Donners                                                                                                                                         *
 *  The Electronic Engineer                                                                                                                              *
 *  Website:   www.theelectronicengineer.nl                                                                                                              *                                                                          *
 *  github:    https://github.com/donnersm                                                                                                               *
 *                                                                                                                                                       *
 ********************************************************************************************************************************************************/

#define VERSION "V1.0"
//#include <TFT_eSPI.h>
// general libaries
#include <arduinoFFT.h> //libary for FFT analysis
//#include <EasyButton.h> //libary for handling buttons

// included files
#include "I2SPLUGIN.h" //Setting up the ADC for I2S interface ( very fast readout)
#include "FFT.h"       //some things for selecting the correct arrays for each number of bands
#include "Settings.h"  // your general settings
//#include "Webstuf.h"   //This is the actual webpage housed in a variable

// libaries for webinterface
//#include <WiFi.h>
//#include <WebServer.h>
//#include <WebSocketsServer.h>
//#include <Ticker.h>
//#include <WiFiManager.h> //The magic setup for wifi! If you need to setup your WIFI, hold the mode button during boot up.

//TFT_eSPI tft = TFT_eSPI();
//TFT_eSprite clk = TFT_eSprite(&tft);

int numBands = 64; // Default number of bands. change it by pressing the mode button

//************* web server setup *************************************************************************************************************************
/*
TaskHandle_t tftTask;
TaskHandle_t WebserverTask;                        // setting up the task handler for webserver                                                  //**
bool webtoken = false;                             // this is a flag so that the webserver noise when the other core has new data                //**
WebServer server(80);                              // more webserver stuff                                                                       //**
WiFiManager wm;                                    // Wifi Manager init                                                                          //**
WebSocketsServer webSocket = WebSocketsServer(81); // Adding a websocket to the server                                                           //**
//************* web server setup end**********************************************************************************************************************
*/
//*************Button setup ******************************************************************************************************************************
//EasyButton ModeBut(0); // defining the button                                                                         //**
// Mode button 1 short press                                                                                                                          //**
// will result in changing the number of bands                                                                                                        //**

void onPressed()
{                                                  //**
  Serial.println("Mode Button has been pressed!"); //**
  if (numBands == 8)
    numBands = 16; //**
  else if (numBands == 16)
    numBands = 24; //**
  else if (numBands == 24)
    numBands = 32; //**
  else if (numBands == 32)
    numBands = 64; //**
  else if (numBands == 64)
    numBands = 8;                                      //**
  SetNumberofBands(numBands);                          //**
  Serial.printf("New number of bands=%d\n", numBands); //**
} //**

//*************Button setup end***************************************************************************************************************************

// Return the frequency corresponding to the Nth sample bucket.  Skips the first two
// buckets which are overall amplitude and something else.
int BucketFrequency(int iBucket)
{
  if (iBucket <= 1)
    return 0;
  int iOffset = iBucket - 2;
  return iOffset * (samplingFrequency / 2) / (SAMPLEBLOCK / 2);
}

//void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
//{
//  // Do something with the data from the client
//  if (type == WStype_TEXT)
//  {
//    Serial.println("websocket event Triggered");
//  }
//}

//void SendData()
//{
//  String json = "[";
//  for (int i = 0; i < numBands; i++)
//  {
//    if (i > 0)
//    {
//      json += ", ";
//    }
//    json += "{\"bin\":";
//    json += "\"" + labels[i] + "\"";
//    json += ", \"value\":";
//    json += String(FreqBins[i]);
//    json += "}";
//  }
//  json += "]";
//  webSocket.broadcastTXT(json.c_str(), json.length());
//}

//void SendData_tft()
//{
//  String json = "[";
//  for (int i = 0; i < numBands; i++)
//  {
//    if (i > 0)
//    {
//      json += ", ";
//    }
//    json += "{\"bin\":";
//    json += "\"" + labels[i] + "\"";
//    json += ", \"value\":";
//    json += String(FreqBins[i]);
//    json += "}";
//  }
//  json += "]";
//  Serial.println(json);
//}

// Task1code: webserver runs on separate core so that WIFI low signal doesn't freeze up program on other core
//void Task1code(void *pvParameters)
//{
//  delay(3000);
//  Serial.print("Webserver task is  running on core ");
//  Serial.println(xPortGetCoreID());
//  int gHue = 0;
//  for (;;)
//  {
//    wm.process();
//    webSocket.loop();
//    server.handleClient();
//    if (webtoken == true)
//    {
//      SendData(); // webbrowser
//      webtoken = false;
//    }
//  }
//}
//
//void task2code(void *pvParameters)
//{
//  delay(3000);
//  Serial.print("Webserver task is  running on core ");
//  Serial.println(xPortGetCoreID());
//  int gHue = 0;
//  for (;;)
//  {
//
//    if (webtoken == true)
//    {
//      SendData_tft(); // webbrowser
//      Serial.printf("\nLoop() - Free Stack Space: %d", uxTaskGetStackHighWaterMark(NULL));
//      webtoken = false;
//    }
//  }
//}

void setup()
{
  disableCore0WDT();
  // create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  //  this will run the webinterface datatransfer.
  // xTaskCreatePinnedToCore(
  //     Task1code,       /* Task function. */
  //     "WebserverTask", /* name of task. */
  //     10000,           /* Stack size of task */
  //     NULL,            /* parameter of the task */
  //     4,               /* priority of the task */
  //     &WebserverTask,  /* Task handle to keep track of created task */
  //     0);              /* pin task to core 0 */
  // xTaskCreatePinnedToCore(
  //     task2code, /* Task function. */
  //     "tftTask", /* name of task. */
  //     100000,     /* Stack size of task */
  //     NULL,      /* parameter of the task */
  //     4,         /* priority of the task */
  //     &tftTask,  /* Task handle to keep track of created task */
  //     0);        /* pin task to core 0 */
  delay(500);
  Serial.begin(115200);
  Serial.println("Setting up Audio Input I2S");
  pinMode(12, OUTPUT);
  
  //ftf初始化
//  tft.init();
//  tft.setRotation(3);
//  tft.fillScreen(TFT_BLACK);
//  digitalWrite(12, HIGH);
//  tft.setTextColor(TFT_BLUE);
//  tft.setTextFont(2);
//  tft.drawString(" ESP-NOW", 0, 0);

  // I2S初始化
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  Serial.println("Audio input setup completed");
  // Button初始化
//  ModeBut.begin();
//  ModeBut.onPressed(onPressed);

//  if (digitalRead(MODE_BUTTON_PIN) == 0)
//  { // reset saved settings is mode button is pressed and hold during startup
//    Serial.println("button pressed on startup, WIFI settings will be reset");
//    // wm.resetSettings();
//  }

  // wm.setConfigPortalBlocking(false); // Try to connect WiFi, then create AP but if no success then don't block the program
  //   If needed, it will be handled in core 0 later
  // wm.autoConnect("ESP32_AP", "");

  // Serial.println(Projectinfo); // print some info about the project
  // server.on("/", []() {        // this will load the actual html webpage to be displayed
  //   server.send_P(200, "text/html", webpage);
  // });

  // server.begin(); // now start the server
  // Serial.println("HTTP server started");
  // webSocket.begin();
  // webSocket.onEvent(webSocketEvent);
  SetNumberofBands(numBands);
}

void loop()
{
    size_t bytesRead = 0;
    int TempADC = 0;
    //ModeBut.read();

  //############ Step 1: read samples from the I2S Buffer ##################
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
  if (result == ESP_OK)
  {
    // int samples_read = bytesIn / 8;
    // if (samples_read > 0)
    // {
    //   float mean = 0;
    //   for (int i = 0; i < samples_read; ++i)
    //   {
    //     mean += (sBuffer[i]);
    //   }
    //   mean /= samples_read;
    //   Serial.println(mean);
    //}
  }
  //############ Step 2: compensate for Channel number and offset, safe all to vReal Array   ############
  for (uint16_t i = 0; i < ARRAYSIZE(sBuffer); i++)
  {
    vReal[i] = offset - sBuffer[i];
    vImag[i] = 0.0; // Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows
  }

  //############ Step 3: Do FFT on the VReal array  ############
  // compute FFT
  FFT.DCRemoval();
  FFT.Windowing(vReal, SAMPLEBLOCK, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLEBLOCK, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLEBLOCK);
  FFT.MajorPeak(vReal, SAMPLEBLOCK, samplingFrequency);//寻峰
  for (int i = 0; i < numBands; i++)
  {
    FreqBins[i] = 0;
  }
  //############ Step 4: Fill the frequency bins with the FFT Samples ############
  for (int i = 2; i < SAMPLEBLOCK / 2; i++)
  {
    if (vReal[i] > NoiseTresshold)
    {
      int freq = BucketFrequency(i);
      int iBand = 0;
      while (iBand < numBands)
      {
        if (freq < BandCutoffTable[iBand])
          break;
        iBand++;
      }
      if (iBand > numBands)
        iBand = numBands;
      FreqBins[iBand] += vReal[i];
    }
  }

  //############ Step 5: Averaging and making it all fit on screen
  static float lastAllBandsPeak = 0.0f;
  float allBandsPeak = 0;
  for (int i = 0; i < numBands; i++)
  {
    if (FreqBins[i] > allBandsPeak)
    {
      allBandsPeak = FreqBins[i];
    }
  }
  if (allBandsPeak < 1)
    allBandsPeak = 1;
  allBandsPeak = max(allBandsPeak, ((lastAllBandsPeak * (GAIN_DAMPEN - 1)) + allBandsPeak) / GAIN_DAMPEN); // Dampen rate of change a little bit on way down
  lastAllBandsPeak = allBandsPeak;
  if (allBandsPeak < 80000)
    allBandsPeak = 80000;
  for (int i = 0; i < numBands; i++)
    FreqBins[i] /= (allBandsPeak * 1.0f);
    
//  webtoken = true; // set marker so that other core can process data
//  clk.setColorDepth(8);
//  clk.createSprite(240, 135);
//  clk.fillSprite(TFT_BLACK);
  // clk.setCursor(0, 0, 2);
  // clk.setTextColor(TFT_YELLOW, TFT_BLACK);
  // clk.print(FreqBins[0]);
  uint8_t hw;
  hw = (240 - 2 * (numBands-1))/numBands;
    // 显示
//  for (int i = 0; i < numBands; i++) {
//    clk.drawRect(hw *i + 2 * i, 135 - FreqBins[i] * 135, hw, FreqBins[i] * 135, TFT_BLUE);
//
//  }
//  clk.pushSprite(0, 0);
//  clk.deleteSprite();
  
  // SendData_tft();
} // loop end
