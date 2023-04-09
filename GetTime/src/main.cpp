#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "leisure";
const char *password = "shadow27";

void get_time()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;                                    // 重点1 创建 HTTPClient 对象
    http.begin("http://quan.suning.com/getSysTime.do"); // 重点2 通过begin函数配置请求地址。
    int httpCode = http.GET();                          // 重点3 通过GET函数启动连接并发送HTTP请求
    if (httpCode == HTTP_CODE_OK)
    {
      // 重点4. 如果服务器响应HTTP_CODE_OK(200)则从服务器获取响应体信息并通过串口输出
      // 如果服务器不响应HTTP_CODE_OK(200)则将服务器响应状态码通过串口输出
      String payload = http.getString(); // 获取响应信息
      Serial.println(payload);
      http.end(); // 重点5. 关闭ESP8266与服务器连接
    }
  }
}

void connectwifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));
  Serial.println(F("WiFi Connected!"));
  Serial.println(F(""));
  get_time();
}

void setup()
{
  Serial.begin(9600);
  connectwifi(); // 连接WIFI
}

void loop()
{
  // put your main code here, to run repeatedly:
}