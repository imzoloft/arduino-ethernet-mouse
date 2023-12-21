#include <Mouse.h>
#include <Ethernet.h>
#include <SPI.h>

#include "config.h"

byte mac[] = {0xa8, 0xa1, 0x59, 0x6e, 0x78, 0x92};
EthernetServer server(20983);

void setup()
{
  delay(2000);

#ifdef DEBUG_ENABLED
  Serial.begin(9600);
  Serial.println("Starting");
#endif
  Ethernet.begin(mac);
  server.begin();
  Mouse.begin();

  delay(1000);

#ifdef DEBUG_ENABLED
  Serial.println("Obtaining IP address via DHCP...");
#endif

  if (Ethernet.localIP() == IPAddress(0, 0, 0, 0))
  {
#ifdef DEBUG_ENABLED
    Serial.println("Failed to get IP via DHCP. Check the connection and restart.");
#endif
    while (true)
      ;
  }
  else
  {
#ifdef DEBUG_ENABLED
    Serial.print("DHCP assigned IP: ");
    Serial.println(Ethernet.localIP());
#endif
  }
}

void loop()
{
  EthernetClient client = server.available();

  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        String data = client.readStringUntil('\n');
        Serial.print(data);

        int commaIndex = data.indexOf(',');

        if (commaIndex != -1)
        {
          String xStr = data.substring(0, commaIndex);
          String yStr = data.substring(commaIndex + 1);

          int x = xStr.toInt();
          int y = yStr.toInt();
#ifdef DEBUG_ENABLED
          Serial.print(x);
          Serial.print(y);
#endif
          Mouse.move(x, y);
        }
      }
    }
    client.stop();

    Ethernet.maintain();
  }
}
