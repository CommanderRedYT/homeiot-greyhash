/*
Start User Settings
Circuit: https://oshwlab.com/ccommanderred/homeiot-v2
*/

#define _DEBUG_ //Uncomment if you want to enable debug mode

    //WiFi
    const char *ssid = ""; //WiFi SSID
    const char *password = ""; //WiFi Password

    //thinger.io
    #define USERNAME "" //Get it from https://console.thinger.io/
    #define DEVICE_ID ""
    #define DEVICE_CREDENTIAL ""

    //WakeOnLan
    const char *MACAddress = ""; //MAC-Address for Computer to WakeOnLan

    //IR-pin (connected to transistor to control ir led)
    const uint16_t SEND_PIN = 13;

    //Serial Monitor Baud Rate
    #define BAUD_RATE 115200

    //Logic
        #define ACTIVE_HIGH true  //Relais are closed on high (true/false)
        
    //Using
        bool enableIR = false; //Change to true when using IR-LED