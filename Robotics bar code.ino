#include <Servo.h>            //This will include the library Servo.h in to the coding.
#define RightLDR A2            //The #define will change the first word with the second word in all of the code.
#define MidLDR   A1
#define LeftLDR  A0
#define Yellow 12
#define Green   7
#define Red    13
#define on HIGH
#define off LOW
#define S01 4
#define S02 2
#define IR 3
Servo RightServo;
Servo LeftServo;
/*
  Sets the defult stopp value for my robot.
*/
int RightStopVal = 94;
int LeftStopVal =   89;
int ForwardRight = RightStopVal  - 20;
int ForwardLeft = LeftStopVal     + 20;
int BackRight = RightStopVal      + 20;
int BackLeft = LeftStopVal           - 20;
float Onedegree = 22.4;
/*
  Sets a couple of global value.
*/
int Average;
bool Run = true;

void setup() {
  /*
     This is the beginning of the main code and where all the pins are set.
  */
  Serial.begin(9600);
  /*
    The pins are set to inputs or outputs.
  */
  pinMode(RightLDR, INPUT);
  pinMode(LeftLDR,   INPUT);
  pinMode(MidLDR,    INPUT);
  pinMode(Yellow,  OUTPUT);
  pinMode(Green,  OUTPUT);
  pinMode(Red,     OUTPUT);
  pinMode(IR,       OUTPUT);
  pinMode(S02, INPUT);
  pinMode(S01, INPUT);
  RightServo.attach(5);                                                 //Saying where the servos are connected.
  LeftServo.attach (6);
  LeftServo.write (LeftStopVal);                                      //Stopping the servos.
  RightServo.write(RightStopVal);
  Serial.println("Push the left button to begin calibration.");
  while (digitalRead(S01));                                              //Waiting for the left button to be prest.
  StopVal();                                                                 //Starts the StopVal function to finde the stop values.
  delay(500);
  BlackWhite();                                                             //Starts the BlackWhite function to find the average value between black and white.
  while (true) {
    delay(1000);
    Serial.println("Push the left button to begin Scanning of code.");
    while (digitalRead(S01));                                            //Waiting for the left button to be prest.
    delay(800);                                                              //Waiting 0,8 seconds so we don't triger any of the next code with one push on the button.
    FindBar();                                                                //Starts the FindBar to find the beginning of the barcode.
    Read();                                                                   //Starts the Read function to try to read the barcode
    delay(150);
  }
}
void loop() {}
//Task 2.1
/*==============================Functions==============================*/
void Forward(bool i) {                                                     //This function will take in a bool and if the bool equals to 1 it will not turn on the preset LED values.
  if (i == 1) {
  }
  else {
    //This wil set the value of the different LEDs
    digitalWrite(Green, off);
    digitalWrite(Yellow, off);
    digitalWrite(Red, off);
  }
  RightServo.write(ForwardRight);                           //This will give servo the forward values.
  LeftServo.write(ForwardLeft);
}
void Backward() {                                                          //
  RightServo.write(BackRight);
  LeftServo.write(BackLeft);
}
void Left(bool i) {                                                          //This function will take in a bool and if the bool equals to 1 it will not turn on the preset LED values.
  if (i == 1) {
  }
  else {
    //This wil set the value of the different LEDs
    digitalWrite(Green, on);
    digitalWrite(Yellow, off);
    digitalWrite(Red, off);
  }
  RightServo.write(ForwardRight);                           //This will give one of the servos the forward value and the and the other one the backwards valu so that the robot will turn on the spot.
  LeftServo.write(BackLeft);
  delay(Onedegree * 90);                                      //This will tell the robot to set det delay to the value of the one degree multplyed by 90 degrees
  RightServo.write(RightStopVal);
  LeftServo.write(LeftStopVal);
}
void Right(bool i) {                                                        //This function will take in a bool and if the bool equals to 1 it will not turn on the preset LED values.
  if (i == 1) {
  }
  else {
    //This wil set the value of the different LEDs
    digitalWrite(Green, off);
    digitalWrite(Yellow, on);
    digitalWrite(Red, off);
  }
  RightServo.write(BackRight);                              //This will give one of the servos the forward value and the and the other one the backwards valu so that the robot will turn on the spot.
  LeftServo.write(ForwardLeft); 
  delay(Onedegree * 90);                                    //This will tell the robot to set det delay to the value of the one degree multplyed by 90 degrees
  RightServo.write(RightStopVal);
  LeftServo.write(LeftStopVal);
}
void Uturn(bool i) {                                                       //This function will take in a bool and if the bool equals to 1 it will not turn on the preset LED values.
  if (i == 1) {
  }
  else {
    //This wil set the value of the different LEDs
    digitalWrite(Green, on);
    digitalWrite(Yellow, on);
    digitalWrite(Red, off);
  }
  RightServo.write(ForwardRight);                         //This will give one of the servos the forward value and the and the other one the backwards valu so that the robot will turn on the spot.
  LeftServo.write(BackLeft);
  delay(Onedegree * 180);                                  //This will tell the robot to set det delay to the value of the one degree multplyed by 180 degrees
  RightServo.write(RightStopVal);
  LeftServo.write(LeftStopVal);
}
void Stop(bool i) {                                                        //This function will take in a bool and if the bool equals to 1 it will not turn on the preset LED values.
  if (i == 1) {
  }
  else {
    //This wil set the value of the different LEDs
    digitalWrite(Green, off);
    digitalWrite(Yellow, off);
    digitalWrite(Red, on);
  }
  LeftServo.write(LeftStopVal);                            //This will give the servos it's stops values.
  RightServo.write(RightStopVal);
}
int StopVal() {                                                              //T
  /*
     This is a function to calibrate the stop values of the servos starting whit the right servo.
  */
  bool RightVal = 1;
  bool LeftVal = 1;
  RightStopVal = 80;                                      //The servos starts at 80 because my stop value varies from 88 to 100.
  LeftStopVal = 80;
  while (LeftVal == 1) {
    if (RightVal == 1) {
      /*
         Her the servo is testing the value that's in RightVal,
         and for every time it tests one value it will give you 1,2 seconds to push
         the button that's on the same side as the servo. and it will test every value above 80.
      */
      RightStopVal++;                                   //Will add one to the stop value.
      RightServo.write(RightStopVal);              //Sets the value of the right servo to the new stop values.
      Serial.println(RightStopVal);                  //Printing the value of stop.
      delay(1200);                                      //Waits 1,2 second for you to see the changes in value.
      RightVal = digitalRead(S02);                 //Stops this sequence.
    }
    else {
      /*
         And her it's turnig off the testing off the right servo, and doing the same as it did on the previous servo.
      */
      RightVal = 0;
      LeftStopVal++;                                   //Will add one to the stop value.
      LeftServo.write(LeftStopVal);               //Sets the value of the right servo to the new stop values.
      Serial.println(LeftStopVal);                  //Printing the value of stop.
      delay(1200);                                     //Waits 1,2 second for you to see the changes in value.
      LeftVal = digitalRead(S01);                  //Stops this sequence.
    }
  }
  delay(1200);
  /*
     In the end of the function, and print the values.
  */
  Serial.println("============================================================");
  Serial.println( "Right value is " + String(RightStopVal) + " " + "Left value is " + String(LeftStopVal));
  Serial.println("============================================================");
  delay(1200);
  return (LeftStopVal + RightStopVal);          //I'm also sending both values back to global variables.
}
int BlackWhite() {                                                         //T
  /*
     In this function, we will find the difference between the colours.
  */
  Serial.println("Place the robot above the first black line, and push left button");
  while (digitalRead(S01));                                                                                     //Waits for the left button to be pushed.
  int MidBlack = analogRead(MidLDR);                                                                       //Reads the value of the Light Dependent Resistors (LDR) in the middle 
  Serial.println("The value of black is " + String(MidBlack));                                         //Prints the value of the LDR in the middle.
  delay(1000);
  Backward();                                                                                                      //Waits a second then goes backwards for 0,8 seconds and then stops.
  delay(800);
  Stop(0);
  int MidWhite = analogRead(MidLDR);                                                                      //Then reads the vlue of the LDR in the middle and prints it.
  Serial.print("The value of white is " + String(MidWhite) + "\n");
  Average = (MidBlack + MidWhite) / 2;                                                                    //Finds the average of the black and white value.
  Serial.println("The average of black and white is " + String(Average));
  return (Average);                                                                                              //Returns the average value to a global variable.
}
void FindBar() {                                                            //T
  int a = true;
  CheckIR();
  while (a) {
    Forward(0);
    if (analogRead(MidLDR) < Average) {
      Stop(0);
      delay(200);
      a = false;
    }
  }
}
void Read() {                                                               //T
  int val1;
  //Defines the different barcodes we have.
  String LeftBar =          "1101011010";
  String StopBar =        "1101011011";
  String PartyBar =       "1010110100";
  String RightBar =       "1101010110";
  String UturnBar =      "1101101010";
  String BoogieBar =    "1011011010";
  String BarCode =  "";
  for (int a; a < 10; a++) {                                //Thils will make the code under go in a loop 10 times
    Forward(0);
    delay(220);
    val1 = analogRead(MidLDR);
    delay(10);
    if (val1 < Average) {                                    //Here the val1 will be compared to Average and if val1 is less then Average it will register as a black.
      BarCode = BarCode + "1";                           //Here we add 1 to the barcode  string.
      Serial.println("This is a black line " + String(val1));
    }
    else if (val1 > Average) {                             //Here the val1 will be compared to Average and if val1 is more then Average it will register as a white.
      BarCode = BarCode + "0";                           //Here we add 1 to the barcode  string.
      Serial.println("This is a white line " + String(val1));
    }
  }
  Stop(0);
  Serial.println("===========================================================");
  Serial.println(BarCode);
  Serial.println("===========================================================");
  //The next part of the code will compare the barcode the robot read to all of the known barcodes.
  if (BarCode == LeftBar) {
    Left(0);
  }
  else if (BarCode == RightBar) {
    Right(0);
  }
  else if (BarCode == UturnBar) {
    Uturn(0);
  }
  else if (BarCode == StopBar) {
    Stop(0);
  }
  else if (BarCode == BoogieBar) {
    Boogie();
  }
  else if (BarCode == PartyBar) {
    PartyTime();
  }
  //But if the robot can't recognise the barcode it will go back.
  else {
    Backward();
    delay(2300);
    Stop(0);
  }
}
//Task 2.2
void Wall() {                                                                //This function will be activated when the robot meet a obstical and it will try to go around it.
  //Turning on all the LEDs
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Right(1);                                                                    //When the functions are called I call them with the value 1 to don't use the preset LED setings.
  Stop(1);
  Forward(1);
  delay(2600);
  Stop(1);
  Left(1);
  Stop(1);
  digitalWrite(Green, off);                                                //Then turning off all the LEDs.
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  CheckIR();
}
void CheckIR() {                                                          //This function will check if there is an obstacle infront of the robot.
  tone(IR, 38000);                                                          //This will send a tone on the IR diode on 38KHZ
  if  (digitalRead(S02) == 0) {                                           //If the tone come back the value will go to 0 and activate the wall function and turn of the tone.
    Serial.println("Obstacle detected. Going around :D");
    Wall();
    noTone(IR);
    return;
  }
  else {
    Serial.println("Moving on");
    return;
  }
}
//Task 2.3.1
void Boogie() {                                                           //This function will make the robot "dance".
  //The robot will turn the LEDs of and on after every move and do certain moves longer time then orginale.
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Uturn(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  Stop(1);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  delay(200);
  Forward(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  delay(800);
  Right(1);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Stop(1);
  delay(200);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  Forward(1);
  delay(800);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Left(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Uturn(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  Stop(1);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  delay(200);
  Forward(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  delay(800);
  Right(1);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Stop(1);
  delay(200);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  Forward(1);
  delay(800);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Left(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  Uturn(1);
  digitalWrite(Green, off);
  digitalWrite(Yellow, off);
  digitalWrite(Red, off);
  Stop(1);
  digitalWrite(Green, on);
  digitalWrite(Yellow, on);
  digitalWrite(Red, on);
  delay(200);
}
//Task 2.3.2
void PartyTime() {                                                      //This function will make the robot spin and send out tons of 80 ms every 10 degree.
  for (int i; i < 36; i++) {
    LeftServo.write(BackLeft);
    RightServo.write(ForwardRight);
    delay(Onedegree * 10);
    Serial.println(i);
    tone(IR, 38000, 80);                                                  //This will send a tone on 38kHZ in bursts on 80ms.
  }
  noTone(IR);                                                               //This wil turn of the tone.
  Stop(0);
}
//Task 2.3.3
void CheckParty() {                                                    //This will check if someone sending a party invite.
  int Start = millis();                                                       //This will check the time the system has been on.
  while (digitalRead(S02));                                               //This will check the time of length of the burst. 
  int Stop = millis();                                                        //This will check the time the system has been on.
  if (Start - Stop > 70 && Start - Stop < 90) {                    //This will check if the burst is between 70 and 90 and if it's between it will start the booie function..
    Boogie();
    return;
  }
  else {
    return;
  }
}
