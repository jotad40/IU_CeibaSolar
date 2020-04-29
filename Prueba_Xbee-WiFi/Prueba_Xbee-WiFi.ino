

/*****************************************************************
Phant_XBee_WiFi.ino
Post data to SparkFun's data stream server system (phant) using
an XBee WiFi and XBee Shield.
Jim Lindblom @ SparkFun Electronics
Original Creation Date: May 20, 2014
https://learn.sparkfun.com/tutorials/online-datalogging-with-an-xbee-wifi

This sketch uses an XBee WiFi and an XBee Shield to get on
the internet and POST analogRead values to SparkFun's data
logging streams (http://data.sparkfun.com).

Hardware Hookup:
  The Arduino shield makes all of the connections you'll need
  between Arduino and XBee WiFi. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION.

  I've also got four separate analog sensors (methane, co,
  temperature, and photocell) connected to pins A0-A3. Feel
  free to switch that up. You can post analog data, digital 
  data, strings, whatever you wish to the Phant server.

Requires the lovely Phant library:
  https://github.com/sparkfun/phant-arduino

Development environment specifics:
    IDE: Arduino 1.0.5
    Hardware Platform: SparkFun RedBoard
    XBee Shield & XBee WiFi (w/ trace antenna)

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please 
buy us a round!

Distributed as-is; no warranty is given.
*****************************************************************/
// SoftwareSerial is used to communicate with the XBee
#include <SoftwareSerial.h>
// The Phant library makes creating POSTs super-easy
#include <Phant.h>

// Time in ms, where we stop waiting for serial data to come in
// 2s is usually pretty good. Don't go under 1000ms (entering
// command mode takes about 1s).
#define COMMAND_TIMEOUT 2000 // ms

////////////////////////
// WiFi Network Stuff //
////////////////////////
// Your WiFi network's SSID (name):
String WIFI_SSID = "BETANCUR_YOL";
// Your WiFi network's encryption setting
// Set the "encrypt" variable to one of these four characters:
// OPEN = 0, WPA_TKIP = 1, WPA2_AES = 2, WEP = 3
enum encryption{NO_SECURITY, WPA_TKIP, WPA2_AES, WEP};
encryption WIFI_EE = WPA2_AES;
// Your WiFi network's passphrase (if necessary). If your network
// is open, make this a blank string (passphrase = "";)
String WIFI_PSK = "24091955";

/////////////////
// Phant Stuff //
/////////////////
// destIP will go into the XBee's configuration setting, so
// it'll automatically connect to the correct server.
String destIP = "54.86.132.254"; // data.sparkfun.com's IP address
// Initialize the phant object:
// Phant phant(server, publicKey, privateKey);
Phant phant("data.sparkfun.com", "1nr20QwDW0FD0YlXWbzO", "0mv4kVYJpkIxae4Y5Kkb");  //Actualizado
// Phant field string defintions. Make sure these match the
// fields you've defined in your data stream:
//              const String methaneField = "methane";
//              const String coField = "co";
const String tempField = "temp";
//              const String lightField = "light";

////////////////
// XBee Stuff //
////////////////
const byte XB_RX = 2; // XBee's RX (Din) pin
const byte XB_TX = 3; // XBee's TX (Dout) pin
// We'll use "xB" from here-on to send and receive data to it:
SoftwareSerial xB(XB_RX, XB_TX); 
const int XBEE_BAUD = 9600; // Your XBee's baud (9600 is default)

/////////////////////////////
// Sensors/Input Pin Stuff //
/////////////////////////////
//          const int lightPin = A0; // Photocell input
const int tempPin = A1;  // TMP36 temp sensor input
//          const int coPin = A2;    // Carbon-monoxide sensor input
//          const int methanePin = A3; // Methane sensor input
// opVoltage - Useful for converting ADC reading to voltage:
const float opVoltage = 4.7;
float tempVal;
//        int lightVal, coVal, methaneVal;

/////////////////////////
// Update Rate Control //
/////////////////////////
// Phant limits you to 10 seconds between posts. Use this variable
// to limit the update rate (in milliseconds):
const unsigned long UPDATE_RATE = 300000; // 300000ms = 5 minutes
unsigned long lastUpdate = 0; // Keep track of last update time

///////////
// Setup //
///////////
// In setup() we configure our INPUT PINS, start the XBee and
// SERIAL ports, and CONNECT TO THE WIFI NETWORK.
void setup()
{
  // Set up sensor pins:
//       pinMode(lightPin, INPUT);
//       pinMode(coPin, INPUT);
//       pinMode(methanePin, INPUT);
  pinMode(tempPin, INPUT);

  // Set up serial ports:
  Serial.begin(9600);
  // Make sure the XBEE BAUD RATE matches its pre-set value
  // (defaults to 9600).
  xB.begin(XBEE_BAUD);

  // Set up WiFi network
  Serial.println("Testing network");
  // connectWiFi will attempt to connect to the given SSID, using
  // encryption mode "encrypt", and the passphrase string given.
  connectWiFi(WIFI_SSID, WIFI_EE, WIFI_PSK);
  // Once connected, print out our IP address for a sanity check:
  Serial.println("Connected!");
  Serial.print("IP Address: "); printIP(); Serial.println(); 

  // setupHTTP() will set up the destination address, port, and
  // make sure we're in TCP mode:
  setupHTTP(destIP);

  // Once everything's set up, send a data stream to make sure
  // everything check's out:
  Serial.print("Sending update...");
  if (sendData())
    Serial.println("SUCCESS!");
  else
    Serial.println("Failed :(");
}

//////////
// Loop //
//////////
// loop() constantly checks to see if enough time has lapsed
// (controlled by UPDATE_RATE) to allow a new stream of data
// to be posted.
// Otherwise, to kill time, it'll print out the sensor values
// over the serial port.
void loop()
{
  // If current time is UPDATE_RATE milliseconds greater than
  // the last update rate, send new data.
  if (millis() > (lastUpdate + UPDATE_RATE))
  {
    Serial.print("Sending update...");
    if (sendData())
      Serial.println("SUCCESS!");
    else
      Serial.println("Failed :(");
    lastUpdate = millis();
  }
  // In the meanwhile, we'll print data to the serial monitor,
  // just to let the world know our Arduino is still operational:
  readSensors(); // Get updated values from sensors
  Serial.print(millis()); // Timestamp
  Serial.print(": ");
//        Serial.print(lightVal);
//        Serial.print('\t');
  Serial.print(tempVal);
  Serial.print('\t');
//        Serial.print(coVal);
//        Serial.print('\t');
//        Serial.println(methaneVal);
  delay(1000);
}

////////////////
// sendData() //
////////////////
// sendData() makes use of the PHANT LIBRARY to send data to the
// data.sparkfun.com server. We'll use phant.add() to add specific
// parameter and their values to the param list. Then use
// phant.post() to send that data up to the server.
int sendData()
{
  xB.flush(); // Flush data so we get fresh stuff in
  // IMPORTANT PHANT STUFF!!!
  // First we need to add fields and values to send as parameters
  // Since we just need to read values from the analog pins, this
  // can be automized with a for loop:
  readSensors(); // Get updated values from sensors.
  phant.add(tempField, tempVal);
//     phant.add(lightField, lightVal);
//     phant.add(methaneField, methaneVal);
//     phant.add(coField, coVal);
  // After our PHANT.ADD's we need to PHANT.POST(). The post needs
  // to be sent out the XBee. A simple "print" of that post will
  // take care of it.
  xB.print(phant.post());

  // Check the response to make sure we receive a "200 OK". If 
  // we were good little programmers we'd check the content of
  // the OK response. If we were good little programmers...
  char response[12];
  if (waitForAvailable(12) > 0)
  {
    for (int i=0; i<12; i++)
    {
      response[i] = xB.read();
    }
    if (memcmp(response, "HTTP/1.1 200", 12) == 0)
      return 1;
    else
    {
      Serial.println(response);
      return 0; // Non-200 response
    }
  }
  else // Otherwise timeout, no response from server
    return -1;
}

// readSensors() will simply update a handful of global variables
// It updates tempVal, lightVal, coVal, and methaneVal
void readSensors()
{
  //tempVal = ((analogRead(tempPin)*opVoltage/1024.0)-0.5)*100;
  Serial.print("Ingrese temperatura");
  if (Serial.available()>0){
    
  tempVal=Serial.read();
  tempVal = (tempVal * 9.0/5.0) + 32.0; // Convert to farenheit
  }
//     lightVal = analogRead(lightPin);
//     methaneVal = analogRead(methanePin);
//     coVal = analogRead(coPin);  
}

///////////////////////////
// XBee WiFi Setup Stuff //
///////////////////////////
// setupHTTP() sets three important parameters on the XBee:
// 1. Destination IP -- This is the IP address of the server
//    we want to send data to.
// 2. Destination Port -- We'll be sending data over port 80.
//    The standard HTTP port a server listens to.
// 3. IP protocol -- We'll be using TCP (instead of default UDP).
void setupHTTP(String address)
{
  // Enter command mode, wait till we get there.
  while (!commandMode(1))
    ;

  // Set IP (1 - TCP)
  command("ATIP1", 2); // RESP: OK
  // Set DL (destination IP address)
  command("ATDL" + address, 2); // RESP: OK
  // Set DE (0x50 - port 80)
  command("ATDE50", 2); // RESP: OK

  commandMode(0); // Exit command mode when done
}

///////////////
// printIP() //
///////////////
// Simple function that enters command mode, reads the IP and
// prints it to a serial terminal. Then exits command mode.
void printIP()
{
  // Wait till we get into command Mode.
  while (!commandMode(1))
    ;
  // Get rid of any data that may have already been in the
  // serial receive buffer:
  xB.flush();
  // Send the ATMY command. Should at least respond with
  // "0.0.0.0\r" (7 characters):
  command("ATMY", 7);
  // While there are characters to be read, read them and throw
  // them out to the serial monitor.
  while (xB.available() > 0)
  {
    Serial.write(xB.read());
  }
  // Exit command mode:
  commandMode(0);
}

//////////////////////////////
// connectWiFi(id, ee, psk) //
//////////////////////////////
// For all of your connecting-to-WiFi-networks needs, we present
// the connectWiFi() function. Supply it an SSID, encryption
// setting, and passphrase, and it'll try its darndest to connect
// to your network.
int connectWiFi(String id, byte auth, String psk)
{
  const String CMD_SSID = "ATID";
  const String CMD_ENC = "ATEE";
  const String CMD_PSK = "ATPK";
  // Check if we're connected. If so, sweet! We're done.
  // Otherwise, time to configure some settings, and print
  // some status messages:
  int status;
  while ((status = checkConnect(id)) != 0)
  {
    // Print a status message. If `status` isn't 0 (indicating
    // "connected"), then it'll be one of these 
    //  (from XBee WiFI user's manual):
    // 0x01 - WiFi transceiver initialization in progress. 
    // 0x02 - WiFi transceiver initialized, but not yet scanning 
    //        for access point. 
    // 0x13 - Disconnecting from access point. 
    // 0x23 – SSID not configured. 
    // 0x24 - Encryption key invalid (either NULL or invalid 
    //        length for WEP) 
    // 0x27 – SSID was found, but join failed. 0x40- Waiting for 
    //        WPA or WPA2 Authentication 
    // 0x41 – Module joined a network and is waiting for IP 
    //        configuration to complete, which usually means it is
    //        waiting for a DHCP provided address. 
    // 0x42 – Module is joined, IP is configured, and listening 
    //        sockets are being set up. 
    // 0xFF– Module is currently scanning for the configured SSID.
    //
    // We added 0xFE to indicate connected but SSID doesn't match
    // the provided id.
    Serial.print("Waiting to connect: ");
    Serial.println(status, HEX);

    commandMode(1); // Enter command mode

    // Write AH (2 - Infrastructure) -- Locked in
    command("ATAH2", 2);
    // Write CE (2 - STA) -- Locked in
    command("ATCE2", 2);  
    // Write ID (SparkFun) -- Defined as parameter
    command(CMD_SSID + id, 2);
    // Write EE (Encryption Enable) -- Defined as parameter
    command(CMD_ENC + auth, 2);
    // Write PK ("sparkfun6175") -- Defined as parameter
    command(CMD_PSK + psk, 2);
    // Write MA (0 - DHCP) -- Locked in
    command("ATMA0", 2);
    // Write IP (1 - TCP) -- Loced in
    command("ATIP1", 2);

    commandMode(0); // Exit Command Mode CN

    delay(2000);
  }
}

// Check if the XBee is connected to a WiFi network.
// This function will send the ATAI command to the XBee.
// That command will return with either a 0 (meaning connected)
// or various values indicating different levels of no-connect.
byte checkConnect(String id)
{
  char temp[2];
  commandMode(0);
  while (!commandMode(1))
    ;
  command("ATAI", 2);
  temp[0] = hexToInt(xB.read());
  temp[1] = hexToInt(xB.read());
  xB.flush();

  if (temp[0] == 0)
  {
    command("ATID", 1);
    int i=0;
    char c=0;
    String atid;
    while ((c != 0x0D) && xB.available())
    {
      c = xB.read();
      if (c != 0x0D)
        atid += c;
    }
    if (atid == id)
      return 0;
    else
      return 0xFE;
  }
  else
  {
    if (temp[1] == 0x13)
      return temp[0];
    else
      return (temp[0]<<4) | temp[1];
  }
}

/////////////////////////////////////
// Low-level, ugly, XBee Functions //
/////////////////////////////////////
void command(String atcmd, int rsplen)
{
  xB.flush();
  xB.print(atcmd);
  xB.print("\r");
  waitForAvailable(rsplen);
}

int commandMode(boolean enter)
{
  xB.flush();

  if (enter)
  {
    char c;
    xB.print("+++");   // Send CMD mode string
    waitForAvailable(1);
    if (xB.available() > 0)
    {
      c = xB.read();
      if (c == 'O') // That's the letter 'O', assume 'K' is next
        return 1; // IF we see "OK" return success
    }
    return 0; // If no (or incorrect) receive, return fail
  }
  else
  {
    command("ATCN", 2);
    return 1;
  }
}

int waitForAvailable(int qty)
{
  int timeout = COMMAND_TIMEOUT;

  while ((timeout-- > 0) && (xB.available() < qty))
    delay(1);

  return timeout;
}

byte hexToInt(char c)
{
  if (c >= 0x41) // If it's A-F
    return c - 0x37;
  else
    return c - 0x30;
}

