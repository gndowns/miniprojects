// ================================================================================
// Define constant values and global variables.

// Define the pin numbers on which the outputs are generated.
#define MOT_A1_PIN 5
#define MOT_A2_PIN 6
#define MOT_B1_PIN 9
#define MOT_B2_PIN 10
#include <SoftwareSerial.h>
#include <Servo.h>
#define servoPin 3
Servo servo;
SoftwareSerial btSerial(11, 12); //RX, TX
//SoftwareSerial btSerial(5,6); //RX, TX

bool flag = true;

// ================================================================================
void setup()
{
  
  
  // Initialize the stepper driver control pins to output drive mode.
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);
  servo.attach(servoPin);

  // Start with drivers off, motors coasting.
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);

  // Initialize the serial
   Serial.begin(115200);
   while (!Serial);
   //bluetooth serial
   btSerial.begin(115200);
   btSerial.print("hello");
}

// ================================================================================
/// Set the current on a motor controller
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}
// ================================================================================

void set_motor_currents(int pwm_A, int pwm_B)
{
  set_motor_pwm(pwm_A, MOT_A1_PIN, MOT_A2_PIN);
  set_motor_pwm(pwm_B, MOT_B1_PIN, MOT_B2_PIN);
}

// ================================================================================
void loop()
{
 //set_motor_pwm(100, MOT_B1_PIN, MOT_B2_PIN);
 //digitalWrite(11, LOW);
 
  if(btSerial.available() > 0){
    
    String data = "";
    for(;btSerial.available() > 0;) {
      char j = btSerial.read();
      //String s = String(j);
      data = data + j;
      //Serial.flush();
      //Serial.write(j);
      //delay(500);
      //String inString = (char)data + "";;
      //inString = inString.substring(0,2);
      //inString = inString.substring(inString.length()-2, inString.length()-1);
      //int dataInt = inString.toInt();
      //int data2 = (int)data;
  
       
     // spin_and_wait(data2, data2, 0);
      
      
    }

    
    String subDataFront = data.substring(0,1);
    String subDataBack = data.substring(1);
    int data2 = subDataBack.toInt();
    if((data2 < 256)&& (data2 > -256 )){

//       analogWrite(5, data2);
       //analogWrite(9, data2);
      if(subDataFront == "R"){
        set_motor_pwm(data2, MOT_B1_PIN, MOT_B2_PIN);
      }
      if(subDataFront == "L"){
        set_motor_pwm(data2, MOT_A1_PIN, MOT_A2_PIN);
      }
      if(subDataFront == "B"){
        if(flag == true){
          servo.write(180);
        //  analogWrite(servoPin, 255);
          flag = false;
        }else if(flag == false){
         // analogWrite(servoPin, 0);
          servo.write(0);
          flag = true;
        }
        
      }
     
      
     // set_motor_pwm(data2, MOT_A1_PIN, MOT_A2_PIN);
      //set_motor_currents(data2, data2);
      Serial.print(subDataFront + " ON ");
      Serial.print(data2);
      btSerial.print(subDataFront + " ON ");
      btSerial.print(data2);
      
      btSerial.flush();
    }
    
    btSerial.flush();
  }
}
/****************************************************************/
