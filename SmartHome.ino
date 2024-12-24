#include <ESP8266WiFi.h>


const char* ssid     = "JioFi4_0E8FC7";
const char* password = "9502555333";


/*const char* host = "api.thingspeak.com";
const String talkBackAPIKey = "XIZQXJV5ZFQBTSJX";
const String talkBackID = "20183";*/

const char* host = "api.thingspeak.com";
const char* privateKey = "XIXTM5YLUHJ95CRC";
const String talkBackAPIKey = "2VV5URTNYRIM7XNH";
const String talkBackID = "20621";

String talkBackCommand,tbRequest;

WiFiClient client;

void setup() {
 Serial.begin(115200);
 pinMode(D0,OUTPUT);
 /*pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D3,OUTPUT);*/

 startWiFi();
}

void loop() {
  int ldr=analogRead(A0);
  Serial.println(ldr);
  delay(1000);
  analogWrite(D0,ldr);
  /*analogWrite(D1,ldr);
  analogWrite(D2,ldr);
  analogWrite(D3,ldr);*/
  if(ldr<600){
    Serial.println("light on");
    digitalWrite(D0,LOW);
    /*digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,HIGH);*/
    delay(1000);
    }
    else{
      Serial.println("light off");
      digitalWrite(D0,HIGH);
      
      /*digitalWrite(D1,LOW);
      digitalWrite(D2,LOW);
      digitalWrite(D3,LOW);*/
    }
    Serial.print("connecting to ");
Serial.println(host);

getTalkBack(); // Get the command issued from mobile app/web app

if(talkBackCommand == "LIGHTON") digitalWrite(D0, LOW);
if(talkBackCommand == "LIGHTOFF") digitalWrite(D0, HIGH);
if(talkBackCommand == "LIGHTON") digitalWrite(D1, LOW);
if(talkBackCommand == "LIGHTOFF") digitalWrite(D1, HIGH);
if(talkBackCommand == "LIGHTON") digitalWrite(D2, LOW);
if(talkBackCommand == "LIGHTOFF") digitalWrite(D2, HIGH);
if(talkBackCommand == "LIGHTON") digitalWrite(D3, LOW);
if(talkBackCommand == "LIGHTOFF") digitalWrite(D3, HIGH);
delay(1000);

}
void getTalkBack()
{
tbRequest="GET /talkbacks/"+ talkBackID + "/commands/execute?api_key=" + talkBackAPIKey;
Serial.println(tbRequest);

if(!client.connected())
{
  if (client.connect("api.thingspeak.com", 80))
  {
    client.println(tbRequest);
    if (client.connected())
      {
        talkBackCommand="";
        while(client.connected() && !client.available()) delay(10); //waits for data
        while (client.connected() || client.available())
            {
              talkBackCommand = client.readString();
            }
        Serial.print("Command -> ");
        Serial.println(talkBackCommand);
        Serial.println();
      }
  client.stop();
  Serial.flush();
 }
}
}
  
void startWiFi()
{
client.stop();
Serial.println();
Serial.println("Connecting to");
Serial.println(ssid);
WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
delay(1000);
}

