#include <PS2X_lib.h>  //for v1.6
int error = 0; 
byte type = 0;
byte vibrate = 0;
PS2X ps2x; // create PS2 Controller Class
#include <SoftwareSerial.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin

#define SSerialTxControl 3   //RS485 Direction control

#define RS485Transmit    HIGH
#define RS485Receive     LOW
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

/*-----( Declare Variables )-----*/
int byteReceived;
int byteSend;

void setup()
{
  pinMode(SSerialTxControl, OUTPUT);    
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver   
  
  // Start the software serial port, to another device
  RS485Serial.begin(4800);   // set the data rate 

   error = ps2x.config_gamepad(4,2,8,7, true, true);  
   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");}
     else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
   Serial.begin(9600);
      type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
 
}
void loop()
{
    
 if(error == 1) //skip loop if no controller found
  return; 
   
 if(type == 2){ //Guitar Hero Controller
   
//   ps2x.read_gamepad();          //read controller 
//   
//   if(ps2x.ButtonPressed(GREEN_FRET))
//     Serial.println("Green Fret Pressed");
//   if(ps2x.ButtonPressed(RED_FRET))
//     Serial.println("Red Fret Pressed");
//   if(ps2x.ButtonPressed(YELLOW_FRET))
//     Serial.println("Yellow Fret Pressed");
//   if(ps2x.ButtonPressed(BLUE_FRET))
//     Serial.println("Blue Fret Pressed");
//   if(ps2x.ButtonPressed(ORANGE_FRET))
//     Serial.println("Orange Fret Pressed");
//     
//
//    if(ps2x.ButtonPressed(STAR_POWER))
//     Serial.println("Star Power Command");
//    
//    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
//     Serial.println("Up Strum");
//    if(ps2x.Button(DOWN_STRUM))
//     Serial.println("DOWN Strum");
//  
// 
//    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
//         Serial.println("Start is being held");
//    if(ps2x.Button(PSB_SELECT))
//         Serial.println("Select is being held");
//
//    
//    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
//    {
//        Serial.print("Wammy Bar Position:");
//        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
//    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
       digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(1); 
       delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
        digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(4); 
       delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
         digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(5); 
       delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
       digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(2); 
       delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit   
      }   
  
    
     // vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
//    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
//    {
//     
//       
//         
//        if(ps2x.Button(PSB_L3))
//         Serial.println("L3 pressed");
//        if(ps2x.Button(PSB_R3))
//         Serial.println("R3 pressed");
//        if(ps2x.Button(PSB_L2))
//         Serial.println("L2 pressed");
//        if(ps2x.Button(PSB_R2))
//         Serial.println("R2 pressed");
//        if(ps2x.Button(PSB_GREEN))
//         Serial.println("Triangle pressed");
//         
//    }   
         
    
    if(ps2x.Button(PSB_RED))             //will be TRUE if button was JUST pressed
  {
       Serial.println("Circle just pressed");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
       digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(3); 
       delay(1000);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit              
  }   
if(ps2x.Button(PSB_GREEN)) //move up
{
  
   digitalWrite(SSerialTxControl, RS485Transmit); 
       RS485Serial.write(6); 
       delay(1000);
    digitalWrite(SSerialTxControl, RS485Receive); 
}
  
//    if(ps2x.Button(PSB_PINK))//move up
//{ 
//}
    //will be TRUE if button was JUST released
//         Serial.println("Square just released");     
//    
    if(ps2x.NewButtonState(PSB_BLUE))            
    {
       digitalWrite(SSerialTxControl, RS485Transmit); 
  RS485Serial.write(7); 
  delay(1000);
  digitalWrite(SSerialTxControl, RS485Receive); 
    }

// if(ps2x.NewButtonState(PSB_BLUE))     //move down
//{
//  
//}
 //will be TRUE if button was JUST pressed OR released
//         Serial.println("X just changed");    
//    
//    
//    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
//    {
//        Serial.print("Stick Values:");
//        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_LX), DEC); 
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_RY), DEC); 
//        Serial.print(",");
//        Serial.println(ps2x.Analog(PSS_RX), DEC); 
//    } 
//    
    
 }
 
 
 delay(50);
     
}
