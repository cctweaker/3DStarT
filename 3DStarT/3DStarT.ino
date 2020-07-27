#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>
#include <DNSServer.h>

//////////

#include "variables.h"
#include "webpages.h"

//////////

WiFiClient net;
ESP8266WebServer server(80);
DNSServer dnsServer;

//////////

void initVariant()
{
  WiFi.persistent(false);
}

//////////

void setup()
{
  load_config();    // load config data
  init_wifi();      // initialize wifi
  init_softap();    // initialize softap for configuration
  init_dns();       // initialize dns for softap
  init_webserver(); // initialize webserver
}

void loop()
{
  if (use_dns) // if dns server is started
    dnsServer.processNextRequest();

  if (use_webserver) // if webserver is used
    server.handleClient();

  delay(10);
}
