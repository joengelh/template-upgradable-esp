#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Update.h>

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char *ssid = "r3d3";
const char *password = "12345678";

// Rudder motor control pins
const int motorPin1 = 25;       // Input pin 25 for motor channel A
const int motorPin2 = 26;       // Input pin 26 for motor channel A
const int maxRudderTime = 9000; // Milliseconds it takes the rudder to travel the entire way

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 0, 1);
DNSServer dnsServer;
WebServer webServer(80);

const char *root =
#include "html/root.h"
    ;

const char *manualControl =
#include "html/manualControl.h"
    ;

const char *settings =
#include "html/settings.h"
    ;

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";
  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}
void setMotorDirection(bool rudderDirection)
{
  digitalWrite(motorPin1, rudderDirection ? HIGH : LOW);
  digitalWrite(motorPin2, rudderDirection ? LOW : HIGH);
}

void stopMotor()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void setup(void)
{
  Serial.begin(115200);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Initialize Wifi Ad-Hoc Network
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "www.r3d3.com", apIP);

  webServer.on("/", []()
               { webServer.send(200, "text/html", root); });

  webServer.on("/manual", []()
               { webServer.send(200, "text/html", manualControl); });

  webServer.on("/settings", []()
               { webServer.send(200, "text/html", settings); });

  webServer.on(
      "/update", HTTP_POST, []()
      {
    webServer.sendHeader("Connection", "close");
    webServer.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart(); },
      []()
      {
        HTTPUpload &upload = webServer.upload();
        if (upload.status == UPLOAD_FILE_START)
        {
          Serial.printf("Update: %s\n", upload.filename.c_str());
          if (!Update.begin(UPDATE_SIZE_UNKNOWN))
          { // start with max available size
            Update.printError(Serial);
          }
        }
        else if (upload.status == UPLOAD_FILE_WRITE)
        {
          /* flashing firmware to ESP*/
          if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
          {
            Update.printError(Serial);
          }
        }
        else if (upload.status == UPLOAD_FILE_END)
        {
          if (Update.end(true))
          { // true to set the size to the current progress
            Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
          }
          else
          {
            Update.printError(Serial);
          }
        }
      });

  webServer.on("/manualControl", HTTP_POST, []()
               {
    if (webServer.hasArg("direction"))
    {
      String direction = webServer.arg("motor");
      if (direction == "forwards")
      {
        setMotorDirection(true);
      }
      else if (direction == "stop")
      {
        stopMotor();
      }
      webServer.send(200, "text/plain", "True");
    }
    else
    {
      webServer.send(400, "text/plain", "Bad Request");
    } });

  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  dnsServer.processNextRequest();
  webServer.handleClient();
}
