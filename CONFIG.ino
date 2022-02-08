long menuId = 1;

bool flagOneRun = true;
int data = 0;

void settingsMod(){
  while(!Serial){
  }
  readSerialData();
  switch (menuId) {
    case 1:
      rendStartMenu();
    break;
    case 11:
      rendSetupPorts();
    break;
    case 12:
      deleteMac();
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 13:
      rendSetupSerial();
    break;
    case 111:
      writePortEEPROM(0);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 112:
      writePortEEPROM(1);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 113:
      writePortEEPROM(2);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 114:
      writePortEEPROM(3);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 131:
      writeBaudRateEEPROM(0);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 132:
      writeBaudRateEEPROM(1);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 133:
      writeBaudRateEEPROM(2);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 134:
      writeBaudRateEEPROM(3);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 135:
      writeBaudRateEEPROM(4);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    case 136:
      writeBaudRateEEPROM(5);
      readEEPROM();
      menuId = 1;
      flagOneRun = true;
      Serial.println("                 Success!                 ");
    break;
    default:
    Serial.println("           Error! Invalid value.          ");
    menuId = 1;
  }
}



void rendStartMenu(){
  if(flagOneRun){
    Serial.println("----------------Start menu----------------");
    Serial.print("Your IP: ");
    Serial.println(getIp());
    Serial.print("Your port: ");
    Serial.println(portsList[port]);
    Serial.print("Your MAC: ");
    Serial.println(getMac());
    Serial.print("Your serial port baud rate: ");
    Serial.println(baudRateList[baudRate]);
    Serial.print("Your program version: ");
    Serial.println(programVer);
    Serial.println("");
    Serial.println("  Available Settings:");
    Serial.println("    1 - Setup ports");
    Serial.println("    2 - Rewriting MAC");
    Serial.println("    3 - Setup serial port baud rate");
    Serial.println("------------------------------------------");
    flagOneRun = false; 
  }
}


void rendSetupPorts(){
   if(flagOneRun){
    Serial.println("----------------Setup ports---------------");
    Serial.print("Your port: ");
    Serial.println(portsList[port]);
    Serial.println("");
    Serial.println("  Available ports:");
    Serial.println("    1 - 1801");
    Serial.println("    2 - 1802");
    Serial.println("    3 - 1803");
    Serial.println("    4 - 1804");
    Serial.println("------------------------------------------");
    flagOneRun = false; 
  }
}

void rendSetupSerial(){
   if(flagOneRun){
    Serial.println("--------Setup serial port baud rate-------");
    Serial.print("Serial port baud rate: ");
    Serial.println(baudRateList[baudRate]);
    Serial.println("");
    Serial.println("  Available baud rate:");
    Serial.println("    1 - 9600");
    Serial.println("    2 - 19200");
    Serial.println("    3 - 38400");
    Serial.println("    4 - 57600");
    Serial.println("    5 - 74880");
    Serial.println("    6 - 115200");
    Serial.println("------------------------------------------");
    flagOneRun = false; 
  }
}

String getIp(){
  String str= "";
  for(int i = 0; i < 4; i++){
     str += ipBox[i];
    if(i != 3) str += "."; 
    delay(5);
  }
  return str;
}

String getMac(){
  String str= "";
  for(int i = 0; i < 6; i++){
    str += mac[i];
    if(i != 5) str += "."; 
    delay(5);
  }
  return str;
}

void readSerialData(){
static int aciiList[] = {
48, //0
49, //1
50, //2
51, //3
52, //4
53, //5
54, //6
55, //7
56, //8
57  //9
};
  
while (Serial.available()){
 int d = Serial.read();
  for(int i = 0; i < 10; i++){
    if(d == aciiList[i]){
      menuId = (menuId*10) + i;
      flagOneRun = true;
      break;
     }
    }
  }
}
