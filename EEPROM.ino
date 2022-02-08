//карта ячеек еепром
// 1-6 MAC
// 7-8 PORT
// 9 boud rate

void readEEPROM(){
  getMacEEPROM(); 
  getPortEEPROM(); 
  getBaudRateEEPROM();
}

void getMacEEPROM(){
  randomSeed(analogRead(0));
  byte firstByteMac = eeprom_read_byte(1);
  delay(5);
  if(firstByteMac > 2 && firstByteMac < 255){
    for(int i = 0; i < 6; i++){
      mac[i] = eeprom_read_byte(i+1);  
      delay(5);
    }
  }else{
    for(int i = 0; i < 6; i++){
      byte num = random(1,254);
      mac[i] = num;
      eeprom_write_byte(i + 1,num);
      delay(50);
    }
  }
}

void getPortEEPROM(){
  byte firstBytePort = eeprom_read_byte(7);
  delay(5);
  if(firstBytePort < 9){
    port = firstBytePort;
  }else{
    eeprom_write_byte(7, 0);
  }
}

void getBaudRateEEPROM(){
  byte firstByteBaudRate = eeprom_read_byte(9);
  delay(5);
  if(firstByteBaudRate < 9){
    baudRate = firstByteBaudRate;
  }else{
    eeprom_write_byte(9, 3); 
  }
}

void deleteMac(){
  for(int i = 0; i < 6; i++){
    eeprom_write_byte(i + 1,255);
    delay(50);
  }
}

void writeBaudRateEEPROM(int e){
  eeprom_write_byte(9,e);
  delay(50);
}

void writePortEEPROM(int e){
  eeprom_write_byte(7,e);
  delay(50);
}
