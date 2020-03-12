
#include <ESP8266WiFi.h>
#include <PubSubClient.h>



const char* ssid = "";
const char* password = "";



int puerta=16;

const char* mqtt_server = "192.168.43.145";
int v0,res;
int outputpin= A0; 

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
//      client.publish("ejercicio/raspberry/chat1", "sopa de murcielago");
//       client.publish("ejercicio/raspberry/chat2", "sopa de murcielago");
     
    // ... and resubscribe
   //   client.subscribe("laboratorio/iluminacion");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(puerta, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  int analogValue = analogRead(outputpin);
   v0 = analogValue*3.3/1024;  
        res = (10000*v0)/(3.3-v0);
  
     Serial.print("resistance: ");
       Serial.println(res);
       Serial.print(v0);
       Serial.print("%\n");


    int acceso=digitalRead(puerta);
    Serial.print(acceso);

    if(acceso==0){
      client.publish("laboratorio/iluminacion","abierto");
      }

    if(acceso==1){
      client.publish("laboratorio/iluminacion","cerrado");
      }
    acceso=0;


       
    //   client.subscribe("ejercicio/chat1");

    if(res<=4400){
      client.publish("laboratorio/iluminacion","noche");
      }
    else
      client.publish("laboratorio/iluminacion","dia");
       
      delay(1000); 
  client.loop();
}
