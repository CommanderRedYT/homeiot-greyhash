#include <Arduino.h>
#include "settings.h"
#include "include.h"
int channel[] = {
    14,
    2,
    27,
    4,
    26,
    5,
    25,
    18,
    33,
    19,
    32,
    21,
    15,
    22,
    12,
    23};
void irfunction(const String &function);
bool state[16];
int counter = 0;
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
WiFiMulti wifiMulti;
WiFiClient client;
IRsend irsend(SEND_PIN);
WiFiUDP UDP;
WakeOnLan WOL(UDP);

void setup()
{
  Serial.begin(BAUD_RATE);
  //Init Channels
  for (int i = 0; i < 16; i++)
  {
    pinMode(channel[i], OUTPUT);
    if (ACTIVE_HIGH == true)
      digitalWrite(channel[i], LOW);
    if (ACTIVE_HIGH == false)
      digitalWrite(channel[i], HIGH);
  }
  pinMode(SEND_PIN, OUTPUT);
  thing.add_wifi(ssid, password);
  thing["relais"] << [](pson &in) {
    state[0] = in["1"];
    state[1] = in["2"];
    state[2] = in["3"];
    state[3] = in["4"];
    state[4] = in["5"];
    state[5] = in["6"];
    state[6] = in["7"];
    state[7] = in["8"];
    state[8] = in["9"];
    state[9] = in["10"];
    state[10] = in["11"];
    state[11] = in["12"];
    state[12] = in["13"];
    state[13] = in["14"];
    state[14] = in["15"];
    state[15] = in["16"];
  };
  thing["enable_ir"] << [](pson &in) {
    enableIR = in;
  };
  thing["wol"] << [](pson &in) {
    WOL.sendMagicPacket(MACAddress);
  };
  thing["sendIR"] << [](pson &in) {
    irfunction(in);
  };
  thing["state"] >> [](pson &out) {
    out["1"] = state[0];
    out["2"] = state[1];
    out["3"] = state[2];
    out["4"] = state[3];
    out["5"] = state[4];
    out["6"] = state[5];
    out["7"] = state[6];
    out["8"] = state[7];
    out["9"] = state[8];   
    out["10"] = state[9];
    out["11"] = state[10];
    out["12"] = state[11];
    out["13"] = state[12];
    out["14"] = state[13];
    out["15"] = state[14];
    out["16"] = state[15];
  };
}

void loop()
{
  thing.handle();
  if (thing.is_connected() == true && enableIR == false)
  {
    counter++;
  }
  else
  {
    counter = 0;
  }
  for (int i = 0; i < 16; i++)
  {
    if (ACTIVE_HIGH == true)
      digitalWrite(channel[i], state[i]);
    if (ACTIVE_HIGH == false)
      digitalWrite(channel[i], !state[i]);
  }
  counter++;
  if (counter == 50)
    digitalWrite(SEND_PIN, HIGH);
  if (counter == 100)
    digitalWrite(SEND_PIN, LOW);
  if (counter == 1500)
    counter = 0;
  delay(3);
}

void irfunction(const String &function)
{
  if (enableIR == true)
  {
    //You can define your own IR-Functions in here
    if (function == "FUNC-NAME")
      irsend.sendNEC(0x00000000);
  }
}