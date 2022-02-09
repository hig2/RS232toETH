//улучшить стабильность!
//



#include <SPI.h>
#include <Ethernet.h>
#include <avr/eeprom.h>
#include <GyverWDT.h>
#define W5500_ETHERNET_SHIELD


byte ipBox[] = { 192, 168, 2, 111};
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

void(* resetFunc) (void) = 0;

void setup() {
  readEEPROM();
  pinMode(5,OUTPUT); // перезагрузка сетевой карты 
  pinMode(4,OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  pinMode(6,INPUT); // джампер для прехода в режим отладки 
  uart.begin(baudRateList[5]); // тестовый порт 
 // Watchdog.enable(RESET_MODE, WDT_PRESCALER_512);
}

void loop() {
  if(settingsModFlag){
   // settingsMod();
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
   // Watchdog.reset(); 
    if (client) { // принимаем запрос на подключение TCP клиента
      while (client.connected()){ // пока клиент подключён
        pointOne:
        //Watchdog.reset();  
        while (int numBytes = uart.available()){ // ЕСЛИ ПРИШЛИ ДАННЫЕ ПО COM 
          byte buferBytes[numBytes]; 
          for(int i = 0; i < numBytes; i ++){
              buferBytes[i] = (byte)uart.read();
          }
          client.write(buferBytes, numBytes);
        }  
             
        while (int numBytes = client.available()){// ЕСЛИ ПРИШЛИ ДАННЫЕ ПО TCP:
          byte buferBytes[numBytes]; 
          for(int i = 0; i < numBytes; i ++){
            uart.write((byte)client.read());
            if(uart.available() > 60){
              goto pointOne; // защита от переполнения буфера последовательного порта
            }
          }
        }
      }
    }else{
      if(ethWatcherStatus(15000)){
        client.stop();
        digitalWrite(4, LOW);
      }
    }
  }
}

bool ethWatcherStatus(int timer){
  static unsigned long t = 0;
  static bool flag = false;
  if(!flag){
    flag = true;
    t = millis();
  }else if((millis() - t) > timer){
    return true;
    flag = false;
  }
  return false;
}


void ethRestart(){
 digitalWrite(5, LOW);
 delay(1000);
 digitalWrite(5, HIGH);
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
