#include <SoftwareSerial.h>
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
int byteReceived;
int byteSent;

#define motor_hr_f 4
#define motor_hr_r 5
#define motor_hl_f 6
#define motor_hl_r 9
#define motor_vr_f 2
#define motor_vr_r 7
#define motor_vl_f 12
#define motor_vl_r 13

class MOTOR {
  public:
  void attach(byte, byte);
  void write(boolean);
  void stop();
  
  private:
   byte in1;
   byte in2;
   boolean state;
   boolean pstate;
   }motor1,motor2,motor3,motor4;
   
   void setup()
   {
     motor1.attach(motor_hr_f,motor_hr_r);
     motor2.attach(motor_hl_f,motor_hl_r);
     motor3.attach(motor_vr_f,motor_vr_r);
     motor4.attach(motor_vl_f,motor_vl_r);
     pinMode(SSerialTxControl, OUTPUT);  
     digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver
     RS485Serial.begin(4800);
     Serial.begin(9600);
     
   }
   
   void loop()
   {
   
//   if (RS485Serial.available()) 
//     {
//        byteSent = RS485Serial.read(); 
//       
//      motor1.write(1);
//      motor2.write(1);
//      motor3.write(1);
//      motor4.write(1);
//      Serial.println("up is held");
//        
//     }
 if (RS485Serial.available()) 
  {
    byteSent = RS485Serial.read();   // Read the byte
   if (byteSent==1) 
   {
     
     motor1.write(1);
     motor2.write(1);
     motor3.stop();
     motor4.stop();
    delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
   }  
  else if (byteSent==2) 
   {
     
     motor1.write(0);
     motor2.write(0);
     motor3.stop();
     motor4.stop();
    delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
   }  
  else if(byteSent==4)//move right
{
 motor1.write(1);
 motor2.write(0);
 motor3.stop();
 motor4.stop();
    delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
} 
    else if(byteSent==5)
{
 motor1.write(0);
 motor2.write(1);
 motor3.stop();
 motor4.stop();
    delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
} 

else if(byteSent==6)//move up
{
  motor3.write(1);
  motor4.write(1);
  motor1.stop();
  motor2.stop();    
  delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
}
else if(byteSent==7)//move up
{
  motor3.write(0);
  motor4.write(0);
  motor1.stop();
  motor2.stop();    
  delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
}
 
else if(byteSent==3)
{
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();

    delay(10);              
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
    Serial.println("up is held !!!");
}}}

void MOTOR::attach(byte MO1, byte MO2 )
{
  
 MOTOR::in1=MO1;
 MOTOR::in2=MO2;
   
 pinMode(MO1,OUTPUT);
 pinMode(MO2,OUTPUT);
}



void MOTOR::write(boolean MOdir)
{ 
      MOTOR::state=MOdir ;
      
      if(state!=pstate)
      {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,HIGH); 
  delay(50);
  //Serial.println("here");
      }
 
  digitalWrite(in1,MOdir);
  MOdir=!MOdir ;
  digitalWrite(in2,MOdir);
  pstate=state ;
}

void MOTOR::stop()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,HIGH);  
}
