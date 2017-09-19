int pin3 = 3;
void setup() {
  Serial.begin(115200);
 
  pinMode(pin3, OUTPUT);
  
}
void loop() {
  if(Serial.available() > 0) {
    char data = Serial.read();
    String inString = (char)data + "";;
    int dataInt = inString.toInt();
   
    //Serial.write(data);
    
   

   analogWrite(pin3, dataInt);
    
  }
  
  
}
