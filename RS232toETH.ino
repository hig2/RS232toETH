#include <SPI.h>
#include <Ethernet.h>
#include <avr/eeprom.h>
#define W5500_ETHERNET_SHIELD
#define BUFFER_LENGTH 128
byte dataBuffer[BUFFER_LENGTH];
#include <SoftwareSerial.h>
SoftwareSerial serial2(8,9);

byte ipBox[] = { 192, 168, 2, 100};
byte mac[] = { 31, 33, 73, 13, 37, 11};
int port = 0; 
String programVer = "1.0.0";

long  baudRateList[] = {
 9600,    //0
 19200,   //1
 38400,   //2   
 57600,   //3
 74880,   //4 
 115200   //5 
};

long  portsList[] = {
 1801,  //0
 1802,  //1
 1803,  //2   
 1804   //3
};

int baudRate = 0; // ид из бод листа
bool settingsModFlag = false; // флаг для перехода в режим настройки
void(* resetMCU) (void) = 0; // resetMCU(); програмный ресет 


void setup() {
  readEEPROM();
  pinMode(5,OUTPUT); // перезагрузка сетевой карты 
  digitalWrite(5, HIGH);
  pinMode(6,INPUT); // джампер для прехода в режим отладки 

  Serial.begin(baudRateList[0]); // тестовый порт 
  if(settingsModFlag){
    Serial1.begin(baudRateList[0]);
  }else{
    Serial1.begin(baudRateList[baudRate]);
    Serial1.setTimeout(1);
    //serial2.begin(38400);
  }
}

void loop() {
  if(settingsModFlag){
    settingsMod();
  }else{
    genaralMod();
  }
}

void genaralMod(){
  IPAddress ip(ipBox[0], ipBox[1], ipBox[2], ipBox[3]);
  EthernetServer server(portsList[port]);
  Ethernet.begin(mac, ip);
  server.begin();
  IPAddress lip = Ethernet.localIP();  

  while(true){
    EthernetClient client = server.available(); // ожидаем подключения  
    if (client) { // принимаем запрос на подключение TCP клиента
      while (client.connected()){ // пока клиент подключён 
        while (Serial1.available()){ // ЕСЛИ ПРИШЛИ ДАННЫЕ ПО COM
          int dataLength = Serial1.readBytes(dataBuffer, BUFFER_LENGTH);
          client.write(dataBuffer, dataLength);
        }        
        while (client.available()){// ЕСЛИ ПРИШЛИ ДАННЫЕ ПО TCP:
          byte c = client.read();
          Serial1.write(c);
        }   
      }    
      client.stop(); // закрываем соединение
    }else{
      timerReset(5000);
    }
  }
}

void ethRestart(){
 digitalWrite(5, LOW);
 delay(500);
} 

void timerReset(long timer){
  static unsigned long t;
  bool flagReset = true;
  if(flagReset){
    t = millis();
    flagReset = false;
  }
  if(millis() - t > timer){
    flagReset = true;
    ethRestart();
  }
}
