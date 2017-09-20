// Driving DC motors at variable speed
//
//  Uses DRV8833 dual DC motor driver module
// ===============================================================================

// Define the pin numbers
#define MOT1_A1_PIN 5
#define MOT1_A2_PIN 6
#define MOT2_B1_PIN 9
#define MOT2_B2_PIN 10

// ===============================================================================
void setup()
{
  
  // Initialize motor pins to output
  pinMode(MOT1_A1_PIN, OUTPUT);
  pinMode(MOT1_A2_PIN, OUTPUT);
  pinMode(MOT2_B1_PIN, OUTPUT);
  pinMode(MOT2_B2_PIN, OUTPUT);

  // Start with drivers off
  digitalWrite(MOT1_A1_PIN, LOW);
  digitalWrite(MOT1_A2_PIN, LOW);
  digitalWrite(MOT2_B1_PIN, LOW);
  digitalWrite(MOT2_B2_PIN, LOW);

  // Initialize the serial UART at 9600 bits per second. // Julien had it set to 115200
   Serial.begin(9600);
}

// ===============================================================================
// Set the current on a motor channel using PWM and directional logic.

void set_motor_pwm(int pwm, int IN1, int IN2)
{

  if (pwm < 0) {  // reverse
    analogWrite(IN1, -pwm);
    digitalWrite(IN2, LOW);

  } else { // stop or forward
    digitalWrite(IN1, LOW);
    analogWrite(IN2, pwm);
  }
}

// ===============================================================================

void loop()
{
  if(Serial.available() > 0){
    
    String data = "";

    // Serial read while there is data
    for(;Serial.available() > 0;) {
      char j = Serial.read();
      data = data + j;  // Form string
      Serial.flush();
    }
   
    int motor_pwm = data.toInt(); // Convert string to int
    set_motor_pwm(motor_pwm, MOT2_B1_PIN, MOT2_B2_PIN); 

    Serial.flush();    
  }
    Serial.print("Set motor A PWM = ");
}
/****************************************************************/
