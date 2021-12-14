#include <Servo.h>
#include <ArduinoJson.h>

//long previousMillis = 0; 
//long interval = 1000;  

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void sendMessage();
void moveServo();
void startPosition();
void getJson();
void switchEffector();
bool effector = true; //true = garra fechada 

const char * servo[20];

void setup() {
  
  Serial.begin(9600);
  delay(250);
  

  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  servo5.attach(8);

  startPosition();

}

void loop() {
  
  getJson();
  //moveServo(messageFromPC, integerFromPC);

}

void startPosition(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(70);
  
};

void moveServo(const char* servo, int angle){
  
  if (strcmp(servo, "value0") == 0){
    servo1.write(angle);
  }
  
  if (strcmp(servo, "value1") == 0){
    servo2.write(angle);
  }
  
  if (strcmp(servo, "value2") == 0){
    servo3.write(angle);
  }
  
  if (strcmp(servo, "value3") == 0){
    servo4.write(angle);
  }
  
  if (strcmp(servo, "effector") == 0){
    switchEffector();
  }
};

void switchEffector() {
  if (effector == true) servo5.write(70);
  else if (effector == false) servo5.write(20);
  effector = !effector;
};


//void sendMessage(char message[numChars], int num1, int num2){
//
//  unsigned long currentMillis = millis();
//  
//  if(currentMillis - previousMillis > interval) {
//    previousMillis = currentMillis;
//    Serial.print("<");
//    Serial.print(message);Serial.print(", ");
//    Serial.print(num1);Serial.print(", ");
//    Serial.print(num2);Serial.println(">");
//  }
//}

void getJson(){
  
  if(Serial.available()>2){
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, Serial);
        
    if (err == DeserializationError::Ok) 
    {
      const char* servo = doc["slider"].as<const char*>();
      int angle = doc["angle"].as<int>();
      Serial.print("Servo: ");
      Serial.println(servo);
      Serial.print("Angulo: ");
      Serial.println(angle);
      moveServo(servo, angle);
    } 
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (Serial.available() > 0)
        Serial.read();
    }
  }
}
