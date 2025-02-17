#define analogPin A0 
//Analog read pin

void setup() {
  byte pinTable[] = {15,22,23,9,10,13,11,12,28,27,29,30};
  for(int i = dacStart; i < dacLen; i++){
    pinMode(pinTable[i],OUTPUT);
  }
}

void loop() {
  //bitshift is to convert the 10-bit reading to a 12-bit number to output to DAC
  int aIn = analogRead(analogPin) << 2;
  
  GPIOC_PDOR = aIn;
}
