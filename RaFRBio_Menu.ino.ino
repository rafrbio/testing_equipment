
#include <UTFT.h>
#include "Arduino.h"
#include <digitalWriteFast.h>  

// Declare which fonts we will be using
extern uint8_t SmallFont[];
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT myGLCD(ITDB32S,38,39,40,41);

#define encoder_A 2
#define encoder_B 3
#define encoder_button 8
#define button1 11
#define button2 10
#define button3 13
#define button4 12
#define buzz 9

int buttonState = 0;
int counter = 0;
int aState;
int aLastState;

int timer = 0;

volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte reading =0;
volatile byte oldEncPos = 0;

volatile bool _EncoderBSet;
volatile long _EncoderTicks = 0;
long copy_EncoderTicks = 0; //new variable for protected copy


void setup()
{
  randomSeed(analogRead(0));
  
// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 319, 13);
  myGLCD.setColor(255, 0, 255);
  myGLCD.fillRect(0, 226, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("* RaRFBio *", CENTER, 1);
  myGLCD.setBackColor(255, 0, 255);
  myGLCD.setColor(255,255,0);
  myGLCD.print("<https://github.com/rafrbio/>", CENTER, 227);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 319, 225);

  
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(80, 70, 239, 169);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("Project RaFRBio", CENTER, 93);
  myGLCD.print("Welcome :)", CENTER, 139);


  pinMode(encoder_A, INPUT);
  pinMode(encoder_B, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  //aLastState = digitalRead(encoder_A);

  attachInterrupt(digitalPinToInterrupt(encoder_A), UpdateA, RISING);// encoder pin on interrupt 0 - pin 2
  //attachInterrupt(digitalPinToInterrupt(encoder_B), UpdateB, CHANGE);// encoder pin on interrupt 1 - pin 3
  Serial.begin (115200);
  Serial.println("start");

}

int is_knob_pressed(){
  if (digitalRead(encoder_button) == 0) {
    return 0;
  } else {
    return 1;
  }
}

int is_knob_turned(){}

void UpdateA()
{
  cli();
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  //_EncoderBSet = (PIND & 0b00001000)>>3;
  _EncoderBSet = digitalReadFast(encoder_B); // read the input pin

  // and adjust counter + if A leads B
  _EncoderTicks = _EncoderBSet ? (_EncoderTicks -1)%5 : (_EncoderTicks+1)%5;
  _EncoderTicks = _EncoderTicks<0 ? _EncoderTicks+5 : _EncoderTicks;
  //_EncoderTicks += _EncoderBSet ? -1 : +1;
  sei();
}




void loop(){

  //encoderPos=is_knob_pressed()*abs(encoderPos%5);
  noInterrupts();
  encoderPos = _EncoderTicks;
  interrupts();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(80, 150, 239, 169); 
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(String(encoderPos), CENTER, 155);

}





















//void UpdateA()
//{
//  cli();
//  if ((PIND & 0b00001000)==0b00001000 || (bFlag==1))   {  
//    Serial.println((PIND & 0b00001000));                  
//    encoderPos--;
//    bFlag=0;
//    aFlag=0;
//  } else aFlag=1 ;
//  sei();
//}

//void UpdateB()
//{
//  cli();
//  if ((PIND & 0b00000100)==0b00000100 || (aFlag==1))   {  
//    Serial.println((PIND & 0b00000100));                  
//    encoderPos++;
//    bFlag=0;
//    aFlag=0;
//  } else bFlag=1 ;
//  sei();
//}

//    
//  aState = digitalRead(encoder_A);
//  if (aState != aLastState){
//    if ((digitalRead(encoder_A) ^ digitalRead(encoder_B)) || (digitalRead(encoder_B) != aState)) {
//      counter ++;
//      //return 1;
//    }  else {
//      counter --;
//        //return -1;
//       }
//    Serial.print("Position: ");
//    Serial.println(counter);
//  }
//
//  aLastState = aState;
//
//    counter = (counter + is_knob_turned())*(is_knob_pressed());
//    Serial.print("Position: ");
//    Serial.println(counter);
//



//  tone(buzz, 1047, 50);
//  delay(200);
//  tone(buzz, 1319, 50);
//  delay(200);
//  tone(buzz, 1568, 50);
//  delay(200);
//  tone(buzz, 2093, 50);



// Read a optical rotary encoder from a PS/2 mouse with interrupts
// Encoder Sensor hooked up with common to 5V,
// myPinA to pin 2, myPinB to pin 3 

// uses Arduino pullups on A & B channel outputs
// turning on the pullups saves having to hook up resistors
// to the A & B channel outputs
// each channel has a 0.1nF to the ground

//Maximum servo speed is 375deg/s
//Encoder wheel has 34 slots (cuts) in it

