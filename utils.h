#ifndef ESP_UTILS
#define ESP_UTILS

#include "settings.h"

uint led_on_time = 0;
uint led_off_time = 0;
uint retry_time = 0;
uint retry_cnt = 0;

void GetElapsedTime(int &delta);
void GetElapsedTime(int &delta)
{
  static unsigned long timestamp = millis();
  unsigned long dt;

  dt = millis() - timestamp;
  timestamp = millis();
  delta = (int)(dt);
}

void ledTask(const int delta_time);
void ledTask(const int delta_time)
{
  static uint led_timer = 0;
  led_timer += delta_time;
  if (LED_IS_ON && led_timer >= led_on_time)
  {
    led_timer = 0;
    LED_OFF;
  }
  else if (!LED_IS_ON && led_timer >= led_off_time)
  {
    led_timer = 0;
    LED_ON;
  }
}

void ledTime(uint on, uint off);
void ledTime(uint on, uint off)
{
  led_on_time = on;
  led_off_time = off;
}

int HTTPRequest(String Server, String Port, String URL);
int HTTPRequest(String Server, String Port, String URL)
{
  WiFiClient client;
  HTTPClient http;

  String auth = "KEY=" + DEVICE_TOKEN;
  auth += "&MAC=" + WiFi.macAddress();
  auth += "&IP=" + WiFi.localIP().toString();

  if (Server.indexOf(":" + Port) < 0)
  {
    Server += ":" + Port;
  }

  String request = Server + "/" + URL + "/";
  request.replace("//", "/");

  if (!request.startsWith("http://"))
  {
    request = "http://" + request;
  }

  LOG();
  LOG("HTTP Request: " + request);

  http.begin(client, request);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int responseCode = http.POST(auth);
  http.end();

  LOG("Response code: " + (String)responseCode);

  return responseCode;
}

int WiFiConnectionTask();
int WiFiConnectionTask()
{
  static bool wifi_is_connected = false;

  if (WIFI_IS_CONNECTED && !wifi_is_connected)
  {
    wifi_is_connected = true;
    LOG();
    LOG("Connection to WiFi successful");
    LOG("Obtained IP: " + WiFi.localIP().toString());
    return 1;
  }
  if (!WIFI_IS_CONNECTED && wifi_is_connected)
  {
    wifi_is_connected = false;
    LOG();
    LOG("Connection to " + STA_SSID + " failed!");
    return -1;
  }
  return 0;
}

int ApiConnectionTask(int delta_time);
int ApiConnectionTask(int delta_time)
{
  retry_time += delta_time;

  if (retry_cnt == 0 || retry_time >= 60000)
  {
    retry_time = 0;
    int response = HTTPRequest(STA_HOST, STA_PORT, "device/connect/");
    if (response == 202)
    {
      retry_time = 0;
      retry_cnt = 0;
      return 1;
    }
    retry_cnt++;
  }
  return 0;
}

String processor(const String& var);
String processor(const String& var)
{
  if (var == "STA_SSID")
  {
    return STA_SSID;
  }
  if (var == "STA_PASS")
  {
    return STA_PASS;
  }
  if (var == "STA_HOST")
  {
    return STA_HOST;
  }
  if (var == "STA_PORT")
  {
    return STA_PORT;
  }
  if (var == "STA_WIFI_CONN")
  {
    if (wifi_is_connected) return "Connected to WiFi";
    return "Not connected to WiFi";
  }
  if (var == "STA_API_CONN")
  {
    if (api_is_connected) return "Connected to API";
    return "Not connected to API";
  }
  if (var == "STA_WIFI_CONN_CLASS")
  {
    if (wifi_is_connected) return "correct";
    return "incorrect";
  }
  if (var == "STA_API_CONN_CLASS")
  {
    if (api_is_connected) return "correct";
    return "incorrect";
  }
  return String();
}

void SocketSendSaveConfirmation(AsyncWebSocket &socket);
void SocketSendSaveConfirmation(AsyncWebSocket &socket)
{
  String json = "";
  json += "{";
  json += "\"type\":\"save\",";
  json += "\"info\":\"ok\",";
  json += "\"SSID\":\""+STA_SSID+"\",";
  json += "\"PASS\":\""+STA_PASS+"\",";
  json += "\"HOST\":\""+STA_HOST+"\",";
  json += "\"PORT\":\""+STA_PORT+"\"";
  json += "}";
  socket.textAll(json);
}

void SocketSendConnectionInfo(AsyncWebSocket &socket, const String type);
void SocketSendConnectionInfo(AsyncWebSocket &socket, const String type)
{
  String json = "{\"type\":\"" + type + "\"}";
  socket.textAll(json);
}

bool LogRequest(String level, String text);
bool LogRequest(String level, String text)
{
  if (api_is_connected)
  {
    if (level == "WAR" || level == "INF" || level == "ERR")
    {
      String URL = "/device/log/" + level + "/" + text + "/";
      int resp = HTTPRequest(STA_HOST, STA_PORT, URL);
      if (resp == 202)
      {
        return true;
      }
    }
  }
  return false;
}

void CommandsTask(int &delta);
void CommandsTask(int &delta)
{
  static int  error_cmd_time = 0;
  static bool rec_cmd_start = false;

  error_cmd_time += delta;

  if (error_cmd_time > 1000 && rec_cmd_start)
  {
    CMD = "";
    rec_cmd_start = false;
    LogRequest("ERR", "no end of command character");
  }

  while (Serial.available() > 0)
  {
    rec_cmd_start = true;
    error_cmd_time = 0;
    char received = (char)Serial.read();
    if (received == '\n')
    {
      error_cmd_time = 0;
      rec_cmd_start = false;
      LOG("Command: " + CMD);
      switch (CMD.charAt(0))
      {
        case 'M':
        {
          String temperature = CMD.substring(2);
          HTTPRequest(STA_HOST, STA_PORT, "/device/measurement/" + temperature + "/");
          LOG();
          LOG("Sending meas temperature: " + temperature);
        }
        break;

        case 'L':
        {
          String Level = CMD.substring(2, 5);
          String Message = CMD.substring(6, -1);
          LOG();
          LOG("Sending Log: " + Level + " | " + Message);
          if (Level == "INF" || Level == "WAR" || Level == "ERR")
            LogRequest(Level, Message);
        }
        break;

        default:
        break;
      }
      CMD = "";
      return;
    }
    CMD += received;
  }
}

#endif