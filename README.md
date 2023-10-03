# ESP32 Motor Control and Web Interface

This project demonstrates controlling a DC motor using an ESP32 microcontroller and a web interface. It is built using the PlatformIO development environment, providing a simple way to manage libraries and dependencies for your project.

## Prerequisites

- [PlatformIO](https://platformio.org/) installed in your preferred code editor or IDE.
- ESP32 board added to your PlatformIO environment.
- Required libraries added to your `platformio.ini` file: WiFi, WiFiClient, WebServer, DNSServer, Update.

## Hardware Configuration

- **Rudder Motor Control Pins:**
  - `motorPin1 (25)`: Input pin for motor channel A.
  - `motorPin2 (26)`: Input pin for motor channel B.

## WiFi Configuration

Set your WiFi SSID and Password in the following lines of the code:

```cpp
const char *ssid = "your_SSID_here";
const char *password = "your_PASSWORD_here";
```

## Web Pages

- `root.html`: Root page.
- `manualControl.html`: Page for manual motor control.
- `settings.html`: Settings page.

## Usage

1. Open the project in your preferred PlatformIO-compatible code editor.
2. Build and upload the code to the ESP32 board.
3. Access the web interface using the ESP32's IP address.

## Endpoints

- `/`: Root endpoint.
- `/manual`: Manual control endpoint.
- `/settings`: Settings endpoint.
- `/update`: Firmware update endpoint.

## Manual Motor Control

The motor can be controlled manually through the `/manualControl` endpoint using POST requests with the `motor` parameter:

- `motor=forwards`: Move the motor forwards.
- `motor=stop`: Stop the motor.

## Firmware Update

Firmware updates can be performed by sending a POST request to the `/update` endpoint with the firmware binary file. The ESP32 will automatically restart after the update.

## Dependencies

- [WiFi.h](https://docs.platformio.org/en/latest/platforms/espressif32.html#framework-arduinoespressif32) - WiFi library for ESP32.
- [WebServer.h](https://docs.platformio.org/en/latest/platforms/espressif32.html#framework-arduinoespressif32) - Web server library for ESP32.
- [DNSServer.h](https://docs.platformio.org/en/latest/platforms/espressif32.html#framework-arduinoespressif32) - DNS server library for ESP32.
- [Update.h](https://docs.platformio.org/en/latest/platforms/espressif32.html#framework-arduinoespressif32) - Firmware update library for ESP32.

## Notes

- Ensure proper hardware connections.
- Use appropriate safety measures while handling the motor.
