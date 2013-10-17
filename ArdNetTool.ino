#include <FlexiTimer2.h>


//#include <EthernetDHCP.h>

#include <RGBTools.h>

#include <ICMPPing.h>

#include <SPI.h>
#include <Ethernet.h>
#include <ICMPing.h>
#include <EthernetUdp.h>
//#include <EthernetClient.h>
//#include <EthernetServer.h>

#include <util.h>

////NETWORK VARIABLES:
//UDP Comm Device:
EthernetUDP Udp;
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
//This code will check a preset computer by ping, ping google, or query an NTP server to see if the network is working. Here are the 
//IP addresses for the servers:
IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov NTP server

// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov NTP server
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov NTP server
byte outsideServer[] = {74,125,140,101}; // outside server IP.

const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 
//ping buffers
SOCKET pingSocket = 0;
char buffer [256];
//UDP INFORMATION FOR TIME SERVER PING:
unsigned int localPort =  8888;


boolean hasDHCP = false;
boolean hasPing = false;
boolean hasNTP = false;
float pingLatency = 0.00;
//color arrays
RGBTools rgb(9,6,5);
//pins:
int redLEDPin = A3;
int grnLEDPin = A4;
int ipIndPin = A0;
int ntpIndPin = A1;
int btnLED = A2;
int btnOut = 2;
int ledState = HIGH;
 byte r = 0;
 byte g = 0;
 byte b = 255;

//Input Keys:
// define some values used by the panel and buttons


void setColor(char color, float qty)
{
  int qtyVal = (int)(qty * 255);
  switch(color)
  {
    case 'R':
    rgb.setColor(255,0,0);
    break;
    case 'B':
    rgb.setColor(0,0,255);
    break;
    case 'G':
    rgb.setColor(0,255,0);
    break;
    case 'P':
    rgb.setColor(224,27,198);
    break;
    case 'Y':
    rgb.setColor(245,255,0);
    break;
    case 'O':
    rgb.setColor(255,106,0);
    break;
    case 'T':
    rgb.setColor(1,251,255);
    break;
    case 'K':
    rgb.setColor(0,0,0);
    break;
  }
}
void setColor(char color)
{
  setColor(color, 1);
}

void waitIndicator()
{
   //EMPTY LOOP - WAITING FOR A NETWORK ADDRESS.
   r = (r + 1) % 255;
   g = (g + 1) % 255;
   b = (b - 1) % 255;
   
   rgb.setColor(r,g,b);
   
 
}

void setup() {
    // put your setup code here, to run once:
  pinMode(redLEDPin, OUTPUT);
  pinMode(grnLEDPin, OUTPUT);
  pinMode(ipIndPin, OUTPUT);
  pinMode(ntpIndPin, OUTPUT);
  pinMode(btnLED, OUTPUT);
  pinMode(btnOut, INPUT); // button wire.
  digitalWrite(btnOut, HIGH); // set pull up resistor to high.
  
  Serial.begin(9600);
  //let the debugger know that it is working:
  Serial.print("Hi there - we are setting up!");
  setColor('B');
  digitalWrite(redLEDPin, HIGH);
  //Begin ethernet connection:
  int r = 0;
  int g = 0;
  int b = 255;
  //set up wait!!
  FlexiTimer2::set(100,waitIndicator);
  FlexiTimer2::start();
  while(Ethernet.begin(mac) == 0)
   {
     //wait around!!
   }
  
  digitalWrite(grnLEDPin, HIGH);
  digitalWrite(redLEDPin, LOW);
  Udp.begin(localPort);
   FlexiTimer2::stop();
   //if we are outside of the loop, then we have an IP address.
   //indicate that the thing is working.
    setColor('P');
     //lcd.setCursor(0,0);
     //lcd.print("CT:OK. IP:");
     Serial.print("IP GOT!");
     //lcd.setCursor(0,1);  
     rgb.setColor(0,0,0);
     delay(100);
}


 
String okMsg = "Pinging IP..";
int numReply;
float latency;
boolean isPinging = true;
boolean isNTP = false;

//debounce codE:
int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;


boolean getButton()
{
  int reading = digitalRead(btnOut);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
     if (buttonState == HIGH) {
      return false;
     }
     else
     {
       return true;
     }
    }
  }
}
void loop() {
  // put your main code here, to run repe: 
 
   if(true)//isPinging)
   {
     
    ICMPPing ping(pingSocket);
    if (ping(4, outsideServer, buffer))
    {
      //we have a ping!!
      digitalWrite(ntpIndPin, HIGH);
      rgb.setColor(0,0,0);
      digitalWrite(9,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
  
      Serial.println("Got Ping.");
    }
    else
    {
      Serial.println("No Ping.");
      
      rgb.setColor(255,0,0);
      digitalWrite(9,HIGH);
    }
    Serial.print(buffer);
  }  
  else if (isNTP)
  {
    
  }

  
}
