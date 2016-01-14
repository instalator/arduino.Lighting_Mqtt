#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 

byte mac[]    = { 0x0C, 0x8E, 0x40, 0x41, 0x19, 0x12 };
byte server[] = { 192, 168, 1, 190 }; //IP Брокера
byte ip[]     = { 192, 168, 1, 199 }; //IP Клиента (Arduino)
////////////////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
   // Serial.print(topic);
   // Serial.print("=");
    String strTopic = String(topic);
    String strPayload = String((char*)payload);
   // Serial.println(strPayload);
    callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);
#define id_connect "myhome-Lighting"
#define Prefix_subscribe "myhome/Lighting/"

///////////////Объявляем порты ввода-вывода

const int start_DI_pin []= {22,24,26,28,30,32,34,36,38,40,42,44,46,48,51,52,2,3,4,5}; // Порты Ввода
int n_DI_pin = sizeof(start_DI_pin) / sizeof(start_DI_pin[0])-1; //Вычисляем длинну массива

const int start_DO_pin []= {23,25,27,29,31,33,35,37,39,41,43,45,47,49,6}; //Порты Вывода
int n_DO_pin = sizeof(start_DO_pin) / sizeof(start_DO_pin[0])-1; //Вычисляем длинну массива

///////////////////////////Переменные для работы с освещением//////////////////////////////////////
  int pre1 = digitalRead(22);
  int pre2 = digitalRead(24);
  int pre3 = digitalRead(26);
  int pre4 = digitalRead(28);
  int pre5 = digitalRead(30);
  int pre6 = digitalRead(32);
  int pre7 = digitalRead(34);
  int pre8 = digitalRead(36);
  int pre9 = digitalRead(38);
  int pre10 = digitalRead(40);
  int pre11 = digitalRead(42);
  int pre12 = digitalRead(44);
  int pre13 = digitalRead(46);
  int pre14 = digitalRead(48);
int flag = 1;
int pause = 150;
long previousMillis = 0;
//long previous2Millis = 0;
int bathswitch = 0;
int posetitel = 0;
int flag_Cupboard = 0;
//int flag2_Cupboard = 3;

////////////////////////////////////////////////////////////////////////////
void setup() {
  //Serial.begin(57600);
 // Serial.println("start");
  
    //Объявляем порты Digital inputs/outputs
  for(int i=0 ;i<=n_DI_pin; i++) { pinMode (start_DI_pin [i], INPUT); }
  for(int i=0 ;i<=n_DO_pin; i++) { pinMode (start_DO_pin [i], OUTPUT); }

  Ethernet.begin(mac, ip);
  if (client.connect(id_connect)) {
    client.publish("myhome/Lighting/All_OFF", "0");
    client.publish("myhome/Bathroom/Ventilator", "0");
    client.publish("myhome/Lighting/BedRoom_Main", "0");
    client.publish("myhome/Lighting/BedRoom_Additional", "0");
    client.publish("myhome/Lighting/GuestRoom_Main", "0");
    client.publish("myhome/Lighting/GuestRoom_Additional", "0");
    client.publish("myhome/Lighting/Kitchen_Main", "0");
    client.publish("myhome/Lighting/Kitchen_Additional", "0");
    client.publish("myhome/Lighting/BathRoom_Main", "0");
    client.publish("myhome/Lighting/BathRoom_Additional", "0");
    client.publish("myhome/Lighting/Hall_Main", "0");
    client.publish("myhome/Lighting/Cupboard", "0");
    
    client.subscribe("myhome/Lighting/#");
    client.subscribe("myhome/Bathroom/Ventilator");
  }
  if (client.connect("myhome-Bathroom")) {
    client.publish("myhome/Bathroom/Ventilator", "0");
    client.subscribe("myhome/Bathroom/Ventilator");
  }
}
/////////////////////////////////////////////////////////////////////////
void loop() {
  client.loop();
  Button(); //Опрос выключателей
        
  if (!client.connected()) {
    if (client.connect(id_connect)) {
          client.publish("myhome/Lighting/All_OFF", "0");
          client.publish("myhome/Lighting/BedRoom_Main", "0");
          client.publish("myhome/Lighting/BedRoom_Additional", "0");
          client.publish("myhome/Lighting/GuestRoom_Main", "0");
          client.publish("myhome/Lighting/GuestRoom_Additional", "0");
          client.publish("myhome/Lighting/Kitchen_Main", "0");
          client.publish("myhome/Lighting/Kitchen_Additional", "0");
          client.publish("myhome/Lighting/BathRoom_Main", "0");
          client.publish("myhome/Lighting/BathRoom_Additional", "0");
          client.publish("myhome/Lighting/Hall_Main", "0");
          client.publish("myhome/Lighting/Cupboard", "0");
    Button(); //Опрос выключателей
    client.subscribe("myhome/Lighting/#");
    client.subscribe("myhome/Bathroom/Ventilator");
        }
    }
}
