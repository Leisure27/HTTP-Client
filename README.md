### 通过网络获取时间
* 设计参考：http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
* 使用`ESP8266HTTPClient.h>`获取时间
* 使用ESP8266通过互联网向网络服务器(API接口)发送请求并且将API响应信息输出在屏幕上
* 使用`ESP8266HTTPClient库`和`WiFiClient库`均可以实现相同的功能，前者简单一些
```c
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
```
**同理，使用这种方法可以获取天气信息。**