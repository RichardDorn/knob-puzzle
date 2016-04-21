#include <LiquidCrystal.h>
#include <Servo.h>
Servo myServo;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	//(rs, enable, d4, d5, d6, d7)
const int potPin1 = A0;					//Input pins for potentiometers
const int potPin2 = A1;
const int potPin3 = A2;
const int potPin4 = A3;
const int skipPin = 11;					//Skip button pin
const int modePin = 8;					//Mode button pin
const int greenLedPin = 13;
const int redLedPin = 12;
int potVal1;			//Value of potentiometers 0-1023. Used to map(angle, ... 0, 179) and debounce pots.
int potVal2;
int potVal3;
int potVal4;
int skipState = 0;
int lastSkipState = 0;
int randState = 0;
int lastRandState = 0;
int randMode = 0;
int highestLevel = 10;	//****************************************************SET TO HIGHEST LEVEL**************************************************************
int randLevel = random(1, highestLevel+1);	//random() doesn't include the last value
int knobAssign = random(1, 5);	//Create switch(knobAssign) with 4 cases in each random level. Randomizes knob assignment in Random Mode
int angle;
int level = 1;		//Or whatever level you want to start on
int skips = 1;		//*******************************************************SET # OF SKIPS*********************************************************************
int begSkips = skips;		//Only need to adjust your starting skips once. (See lines 96, 117, 128) To change the amount of bonus skips in easter egg see last line of credits() function.
int passLevel = 0;			//Determines whether to continue playing a level or call nextLevel();
unsigned long startTime = 0;	//Time campaign mode started
long millis_held;				//Millis button has been pressed
long prevMillis_held;			//Used as comparison to check if button was released
unsigned long btnPressed;		//Time button was pressed
unsigned long currentTime;		//Time since campaign mode started


void setup() {
	pinMode(skipPin, INPUT);
	pinMode(modePin, INPUT);
	pinMode(greenLedPin, OUTPUT);
	pinMode(redLedPin, OUTPUT);
	myServo.attach(9);
	lcd.begin(16, 2);
	Serial.begin(9600);
	}


void loop() {
	currentTime = millis();
	potVal1 = analogRead(potPin1);
	potVal2 = analogRead(potPin2);
	potVal3 = analogRead(potPin3);
	potVal4 = analogRead(potPin4);
	skipState = digitalRead(skipPin);
	randState = digitalRead(modePin);
//////////////////////////////////////////////////////////////// SKIP Button /////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////Easter Egg To Access Credits///////////////////////////////////////////////////////////////
	if(skipState == HIGH && lastSkipState == LOW){
		btnPressed = millis();				//If skip btn has just been pressed record the time
	}
	millis_held = millis() - btnPressed;	//Record how much time has passed since the button was pressed
	if(skipState == HIGH && millis_held > prevMillis_held && millis_held >= 5000 && level == highestLevel+1 && randMode == 0){
		level++;		//If the skip button has been held for 5 seconds and you've passed the final level... increase the level so campaign wont restart on button
		credits();		//release, then begin credits easter egg.
	}
	if(skipState == LOW && lastSkipState == HIGH){
		millis_held = 0;		//If the button has just been released reset millis_held
	}
	prevMillis_held = millis_held;
///////////////////////////////////////////////////////////////End Easter Egg///////////////////////////////////////////////////////////////////////////
	if(skipState != lastSkipState){
		if(skipState == HIGH && level < highestLevel && skips > 0){	//Skip Level
		lastSkipState = skipState;
		skips--;
		digitalWrite(redLedPin, HIGH);
		delay(30);
		digitalWrite(redLedPin, LOW);
		delay(30);
		digitalWrite(redLedPin, HIGH);
		delay(30);
		digitalWrite(redLedPin, LOW);
		delay(30);
		digitalWrite(redLedPin, HIGH);
		delay(30);
		digitalWrite(redLedPin, LOW);
		delay(30);
		passLevel = 1;
		}else if(randMode == 0 && skipState == HIGH && level == highestLevel){	//Block skip on final level
			lcd.clear();
			lcd.print("You May Not Skip");
			lcd.setCursor(0, 1);
			lcd.print("The Final Level!");
			delay(1500);
			lcd.clear();
		}else if(skipState == LOW && lastSkipState == HIGH && level == highestLevel+1){	//Restart campaign on button release after passing final level
			skips = begSkips;
			level = 1;
			startTime = currentTime;
			lcd.clear();
		}else if(skipState == HIGH && skips < 1 && level < highestLevel+1){	//Block skip if no skips remaining
			lcd.clear();
			lcd.print("No  Skips  Left.");
			lcd.setCursor(0, 1);
			lcd.print("   Good Luck.   ");
			digitalWrite(redLedPin, HIGH);
			delay(1500);
			lcd.clear();
			digitalWrite(redLedPin, LOW);
		}
	lastSkipState = skipState;
	}
///////////////////////////////////////////////////////////////////////////////MODE Button /////////////////////////////////////////////////////////	
	if(randState != lastRandState){
		if(randState == HIGH && randMode == 0){	//Enter Random Mode
			lastRandState = randState;
			level = 1;
			skips = begSkips;
			lcd.setCursor(0, 0);
			lcd.write("    Entering    ");
			lcd.setCursor(0, 1);
			lcd.write("  Random  Mode  ");
			delay(2000);
			randMode = !randMode;
			
		}else if(randState == HIGH && randMode == 1){	//Enter Campaign Mode
			startTime = currentTime;
			level = 1;
			skips = begSkips;
			lcd.setCursor(0, 0);
			lcd.write("    Entering    ");
			lcd.setCursor(0, 1);
			lcd.write(" Campaign  Mode ");
			delay(2000);
			randMode = !randMode;
		}
		lastRandState = randState;
	}
//////////////////////////////////////////////////////////////////// Random Mode //////////////////////////////////////////////////////////////////////
	if(randMode == 1 && passLevel == 0){
		randStats();	//Display random mode and remaining skips
		switch(randLevel){
		
			case 1:{												//Level 1
					switch(knobAssign){
				
						case 1:{
							angle = map(potVal1, 0, 1023, 0, 179);
							myServo.write(angle);
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							angle = map(potVal2, 0, 1023, 0, 179);
							myServo.write(angle);
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							angle = map(potVal3, 0, 1023, 0, 179);
							myServo.write(angle);
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							angle = map(potVal4, 0, 1023, 0, 179);
							myServo.write(angle);
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 2:{													//Level 2
					switch(knobAssign){
					
						case 1:{
							if(potVal1 >= 1020){
								angle = map(potVal4, 0, 1023, 0, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal2 >= 1020){
								angle = map(potVal3, 0, 1023, 0, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////	
						case 3:{
							if(potVal3 >= 1020){
								angle = map(potVal2, 0, 1023, 0, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////	
						case 4:{
							if(potVal4 >= 1020){
								angle = map(potVal1, 0, 1023, 0, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////		
					}
			break;
			}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 3:{														//Level 3
						//pots all go to 45 and add together in no particular order. No need for switch(knobAssign)
					int pot1 = map(potVal1, 0, 1023, 0, 179);
					int pot2 = map(potVal2, 0, 1023, 0, 179);
					int pot3 = map(potVal3, 0, 1023, 0, 179);
					int pot4 = map(potVal4, 0, 1023, 0, 179);
					angle = pot1 + pot2 + pot3 + pot4;
					myServo.write(angle);
					if(pot1 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot2 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot3 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot4 > 45){
						angle = 0;
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 4:{													//Level 4
					switch(knobAssign){
						
						case 1:{
							if(potVal1 <=3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 0, 90);
								myServo.write(angle);
							}
							if(potVal2 >= 1020 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal1 <=3 && potVal2 <= 3 && potVal3 <= 3){
								angle = map(potVal4, 0, 1023, 0, 90);
								myServo.write(angle);
							}
							if(potVal4 >= 1020 && potVal3 <= 3 && potVal1 <= 3){
								angle = map(potVal2, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							if(potVal1 <=3 && potVal2 <= 3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 0, 90);
								myServo.write(angle);
							}
							if(potVal3 >= 1020 && potVal1 <= 3 && potVal2 <= 3){
								angle = map(potVal4, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							if(potVal2 <=3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 0, 90);
								myServo.write(angle);
							}
							if(potVal1 >= 1020 && potVal2 <= 3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			case 5:{														//Level 5
					int firstHalf;
					switch(knobAssign){
						
						case 1:{
							if(potVal2 <=3 && potVal3 <= 3 && potVal4 <= 3){
								firstHalf = map(potVal1, 0, 1023, 0, 90);
								if(firstHalf == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								angle = map(potVal4, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal1 <=3 && potVal2 <= 3 && potVal4 <= 3){
								firstHalf = map(potVal3, 0, 1023, 0, 90);
								if(firstHalf == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							if(potVal1 <=3 && potVal3 <= 3 && potVal4 <= 3){
								firstHalf = map(potVal2, 0, 1023, 0, 90);
								if(firstHalf == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							if(potVal1 <=3 && potVal2 <= 3 && potVal3 <= 3){
								firstHalf = map(potVal4, 0, 1023, 0, 90);
								if(firstHalf == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 90, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 6:{												//Level 6
					int firstQuarter;
					int secondQuarter;
					int thirdQuarter;
					int fourthQuarter;
					switch(knobAssign){
						
						case 1:{
							if(potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								firstQuarter = map(potVal1, 0, 1023, 0, 45);
								if(firstQuarter == 45){
									angle = 45;
									myServo.write(angle);
								}
							}
							if(angle >= 43 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								secondQuarter = map(potVal2, 0, 1023, 45, 90);
								if(secondQuarter == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								thirdQuarter = map(potVal3, 0, 1023, 90, 135);
								if(thirdQuarter == 135){
									angle = 135;
									myServo.write(angle);
								}
							}
							if(angle >= 133 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								fourthQuarter = map(potVal4, 0, 1023, 135, 179);
								if(fourthQuarter == 179){
									angle = 179;
									myServo.write(angle);
								}
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								firstQuarter = map(potVal2, 0, 1023, 0, 45);
								if(firstQuarter == 45){
									angle = 45;
									myServo.write(angle);
								}
							}
							if(angle >= 43 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								secondQuarter = map(potVal3, 0, 1023, 45, 90);
								if(secondQuarter == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								thirdQuarter = map(potVal4, 0, 1023, 90, 135);
								if(thirdQuarter == 135){
									angle = 135;
									myServo.write(angle);
								}
							}
							if(angle >= 133 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								fourthQuarter = map(potVal1, 0, 1023, 135, 179);
								if(fourthQuarter == 179){
									angle = 179;
									myServo.write(angle);
								}
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							if(potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								firstQuarter = map(potVal3, 0, 1023, 0, 45);
								if(firstQuarter == 45){
									angle = 45;
									myServo.write(angle);
								}
							}
							if(angle >= 43 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								secondQuarter = map(potVal4, 0, 1023, 45, 90);
								if(secondQuarter == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								thirdQuarter = map(potVal1, 0, 1023, 90, 135);
								if(thirdQuarter == 135){
									angle = 135;
									myServo.write(angle);
								}
							}
							if(angle >= 133 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								fourthQuarter = map(potVal2, 0, 1023, 135, 179);
								if(fourthQuarter == 179){
									angle = 179;
									myServo.write(angle);
								}
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							if(potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								firstQuarter = map(potVal4, 0, 1023, 0, 45);
								if(firstQuarter == 45){
									angle = 45;
									myServo.write(angle);
								}
							}
							if(angle >= 43 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								secondQuarter = map(potVal2, 0, 1023, 45, 90);
								if(secondQuarter == 90){
									angle = 90;
									myServo.write(angle);
								}
							}
							if(angle >= 88 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								thirdQuarter = map(potVal1, 0, 1023, 90, 135);
								if(thirdQuarter == 135){
									angle = 135;
									myServo.write(angle);
								}
							}
							if(angle >= 133 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								fourthQuarter = map(potVal3, 0, 1023, 135, 179);
								if(fourthQuarter == 179){
									angle = 179;
									myServo.write(angle);
								}
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
				break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 7:{													//Level 7	Contains extraSkip()
					switch(knobAssign){
						
						case 1:{
							if(potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 0, 178);
								myServo.write(angle);
							}
							if(potVal2 >= 1020 && potVal1 <= 3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 178, 0);
								myServo.write(angle);
							}
							if(potVal2 >= 1020 && potVal3 >= 1020 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 0, 179);
								myServo.write(angle);
							}
							if(angle == 179){
								extraSkip();
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 0, 178);
								myServo.write(angle);
							}
							if(potVal1 >= 1020 && potVal2 <= 3 && potVal3 <= 3){
								angle = map(potVal4, 0, 1023, 178, 0);
								myServo.write(angle);
							}
							if(potVal1 >= 1020 && potVal4 >= 1020 && potVal3 <= 3){
								angle = map(potVal2, 0, 1023, 0, 179);
								myServo.write(angle);
							}
							if(angle == 179){
								extraSkip();
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							if(potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 0, 178);
								myServo.write(angle);
							}
							if(potVal3 >= 1020 && potVal2 <= 3 && potVal4 <= 3){
								angle = map(potVal1, 0, 1023, 178, 0);
								myServo.write(angle);
							}
							if(potVal1 >= 1020 && potVal3 >= 1020 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 0, 179);
								myServo.write(angle);
							}
							if(angle == 179){
								extraSkip();
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							if(potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								angle = map(potVal4, 0, 1023, 0, 178);
								myServo.write(angle);
							}
							if(potVal4 >= 1020 && potVal2 <= 3 && potVal3 <= 3){
								angle = map(potVal1, 0, 1023, 178, 0);
								myServo.write(angle);
							}
							if(potVal1 >= 1020 && potVal4 >= 1020 && potVal2 <= 3){
								angle = map(potVal3, 0, 1023, 0, 179);
								myServo.write(angle);
							}
							if(angle == 179){
								extraSkip();
							}
						break;
					}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 8:{												//Level 8
					switch(knobAssign){
				
						case 1:{
							int key = map(potVal4, 0, 1023, 0, 135);
							int add3 = map(potVal3, 0, 1023, 0, 40);
							int add2 = map(potVal2, 0, 1023, 0, 60);
							int add1 = map(potVal1, 0, 1023, 0, 35);
							if(key >= 39 && key <= 44){
								angle = add1 + add2 + add3 + key;
								myServo.write(angle);
							}
							if(potVal3 <= 3 && potVal2 <= 3 && potVal1 <= 3 && key < 39 || key > 44){
								angle = key;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal2 <= 3){
								angle = add1;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal1 <= 3){
								angle = add2;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add3;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							int key = map(potVal3, 0, 1023, 0, 135);
							int add3 = map(potVal4, 0, 1023, 0, 40);
							int add2 = map(potVal2, 0, 1023, 0, 60);
							int add1 = map(potVal1, 0, 1023, 0, 35);
							if(key >= 39 && key <= 44){
								angle = add1 + add2 + add3 + key;
								myServo.write(angle);
							}
							if(potVal4 <= 3 && potVal2 <= 3 && potVal1 <= 3 && key < 39 || key > 44){
								angle = key;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal2 <= 3){
								angle = add1;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal1 <= 3){
								angle = add2;
								myServo.write(angle);
							}
							if(potVal3 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add3;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							int key = map(potVal2, 0, 1023, 0, 135);
							int add3 = map(potVal3, 0, 1023, 0, 40);
							int add2 = map(potVal4, 0, 1023, 0, 60);
							int add1 = map(potVal1, 0, 1023, 0, 35);
							if(key >= 39 && key <= 44){
								angle = add1 + add2 + add3 + key;
								myServo.write(angle);
							}
							if(potVal4 <= 3 && potVal3 <= 3 && potVal1 <= 3 && key < 39 || key > 44){
								angle = key;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal2 <= 3){
								angle = add1;
								myServo.write(angle);
							}
							if(potVal3 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add2;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add3;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							int key = map(potVal1, 0, 1023, 0, 135);
							int add3 = map(potVal3, 0, 1023, 0, 40);
							int add2 = map(potVal2, 0, 1023, 0, 60);
							int add1 = map(potVal4, 0, 1023, 0, 35);
							if(key >= 39 && key <= 44){
								angle = add1 + add2 + add3 + key;
								myServo.write(angle);
							}
							if(potVal4 <= 3 && potVal3 <= 3 && potVal2 <= 3 && key < 39 || key > 44){
								angle = key;
								myServo.write(angle);
							}
							if(potVal3 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add1;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal3 <=3 && potVal1 <= 3){
								angle = add2;
								myServo.write(angle);
							}
							if(potVal4 <=3 && potVal2 <=3 && potVal1 <= 3){
								angle = add3;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 9:{												//Level 9
					if(potVal1 <= 3 && potVal2 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = 178;
						myServo.write(angle);
					}else if(potVal1 > 3 && potVal2 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = map(potVal1, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal2 > 3 && potVal1 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = map(potVal2, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal3 > 3 && potVal1 <= 3 && potVal2 <=3 && potVal4 <= 3){
						angle = map(potVal3, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal4 > 3 && potVal1 <= 3 && potVal2 <=3 && potVal3 <= 3){
						angle = map(potVal4, 0, 1023, 178, 0);
						myServo.write(angle);
					}
					
					switch(knobAssign){
			
						case 1:{
							if(potVal2 >= 1020 && potVal1 <=3 && potVal3 <= 3){
								angle = map(potVal4, 0, 1023, 0, 80);
								myServo.write(angle);
							}else if(potVal2 >= 1020 && potVal4 >= 1020 && potVal3 <= 3){
								angle = map(potVal1, 0, 1023, 80, 160);
								myServo.write(angle);
							}else if(potVal2 >= 1020 && potVal4 >= 1020 && potVal1 >= 1020){
								angle = map(potVal3, 0, 1023, 160, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							if(potVal3 >= 1020 && potVal1 <=3 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 0, 80);
								myServo.write(angle);
							}else if(potVal2 >= 1020 && potVal3 >= 1020 && potVal1 <= 3){
								angle = map(potVal4, 0, 1023, 80, 160);
								myServo.write(angle);
							}else if(potVal2 >= 1020 && potVal3 >= 1020 && potVal4 >= 1020){
								angle = map(potVal1, 0, 1023, 160, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							if(potVal4 >= 1020 && potVal2 <=3 && potVal3 <= 3){
								angle = map(potVal1, 0, 1023, 0, 80);
								myServo.write(angle);
							}else if(potVal1 >= 1020 && potVal4 >= 1020 && potVal2 <= 3){
								angle = map(potVal3, 0, 1023, 80, 160);
								myServo.write(angle);
							}else if(potVal1 >= 1020 && potVal3 >= 1020 && potVal4 >= 1020){
								angle = map(potVal2, 0, 1023, 160, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							if(potVal1 >= 1020 && potVal2 <=3 && potVal4 <= 3){
								angle = map(potVal3, 0, 1023, 0, 80);
								myServo.write(angle);
							}else if(potVal1 >= 1020 && potVal3 >= 1020 && potVal4 <= 3){
								angle = map(potVal2, 0, 1023, 80, 160);
								myServo.write(angle);
							}else if(potVal1 >= 1020 && potVal2 >= 1020 && potVal3 >= 1020){
								angle = map(potVal4, 0, 1023, 160, 179);
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 10:{												//Level 10
					switch(knobAssign){
				
						case 1:{
							int add = map(potVal1, 0, 1023, 0, 135);
							int sub1 = map(potVal2, 0, 1023, 0, 179);
							int sub2 = map(potVal3, 0, 1023, 0, 179);
							int sub3 = map(potVal4, 0, 1023, 0, 179);
							if(potVal1 > 3 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = add;
								myServo.write(angle);
							}else if(potVal1 <= 3 && sub1 <= 43 && sub2 <= 45 && sub3 <= 45){
								angle = 178 - sub1 - sub2 - sub3;
								myServo.write(angle);
							}else if(sub1 > 43){
								angle = 178;
								myServo.write(angle);
							}else if(sub2 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub3 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub1 >= 40 && sub1 <= 50 && sub2 >= 40 && sub2 <= 50 && sub3 >= 40 && sub3 <= 50){
								angle = 178 - sub1 - sub2 - sub3 + add;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 2:{
							int add = map(potVal2, 0, 1023, 0, 135);
							int sub1 = map(potVal1, 0, 1023, 0, 179);
							int sub2 = map(potVal3, 0, 1023, 0, 179);
							int sub3 = map(potVal4, 0, 1023, 0, 179);
							if(potVal2 > 3 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
								angle = add;
								myServo.write(angle);
							}else if(potVal2 <= 3 && sub1 <= 43 && sub2 <= 45 && sub3 <= 45){
								angle = 178 - sub1 - sub2 - sub3;
								myServo.write(angle);
							}else if(sub1 > 43){
								angle = 178;
								myServo.write(angle);
							}else if(sub2 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub3 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub1 >= 40 && sub1 <= 50 && sub2 >= 40 && sub2 <= 50 && sub3 >= 40 && sub3 <= 50){
								angle = 178 - sub1 - sub2 - sub3 + add;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 3:{
							int add = map(potVal3, 0, 1023, 0, 135);
							int sub1 = map(potVal2, 0, 1023, 0, 179);
							int sub2 = map(potVal1, 0, 1023, 0, 179);
							int sub3 = map(potVal4, 0, 1023, 0, 179);
							if(potVal3 > 3 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
								angle = add;
								myServo.write(angle);
							}else if(potVal3 <= 3 && sub1 <= 43 && sub2 <= 45 && sub3 <= 45){
								angle = 178 - sub1 - sub2 - sub3;
								myServo.write(angle);
							}else if(sub1 > 43){
								angle = 178;
								myServo.write(angle);
							}else if(sub2 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub3 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub1 >= 40 && sub1 <= 50 && sub2 >= 40 && sub2 <= 50 && sub3 >= 40 && sub3 <= 50){
								angle = 178 - sub1 - sub2 - sub3 + add;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
						case 4:{
							int add = map(potVal4, 0, 1023, 0, 135);
							int sub1 = map(potVal2, 0, 1023, 0, 179);
							int sub2 = map(potVal3, 0, 1023, 0, 179);
							int sub3 = map(potVal1, 0, 1023, 0, 179);
							if(potVal4 > 3 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
								angle = add;
								myServo.write(angle);
							}else if(potVal4 <= 3 && sub1 <= 43 && sub2 <= 45 && sub3 <= 45){
								angle = 178 - sub1 - sub2 - sub3;
								myServo.write(angle);
							}else if(sub1 > 43){
								angle = 178;
								myServo.write(angle);
							}else if(sub2 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub3 > 45){
								angle = 178;
								myServo.write(angle);
							}else if(sub1 >= 40 && sub1 <= 50 && sub2 >= 40 && sub2 <= 50 && sub3 >= 40 && sub3 <= 50){
								angle = 178 - sub1 - sub2 - sub3 + add;
								myServo.write(angle);
							}
						break;
						}
				///////////////////////////////////////////////////////////////////
					}
			break;
			}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} //close switch(randLevel)
	} //close if(randMode == 1)
///////////////////////////////////////////////////////////////////////////// Normal Mode ////////////////////////////////////////////////////////////////
	else if(randMode == 0 && passLevel == 0){
		stats();	//Display current level and remaining skips
		switch(level){
			
			case 1:{												//Level 1
					angle = map(potVal3, 0, 1023, 0, 179);
					myServo.write(angle);
				}
			break;
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 2:{												//Level 2
					if(potVal1 >= 1020){
						angle = map(potVal4, 0, 1023, 0, 179);
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 3:{												//Level 3
					int pot1 = map(potVal1, 0, 1023, 0, 179);
					int pot2 = map(potVal2, 0, 1023, 0, 179);
					int pot3 = map(potVal3, 0, 1023, 0, 179);
					int pot4 = map(potVal4, 0, 1023, 0, 179);
					angle = pot1 + pot2 + pot3 + pot4;
					myServo.write(angle);
					if(pot1 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot2 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot3 > 45){
						angle = 0;
						myServo.write(angle);
					}
					if(pot4 > 45){
						angle = 0;
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 4:{												//Level 4
					if(potVal1 <=3 && potVal3 <= 3 && potVal4 <= 3){
						angle = map(potVal2, 0, 1023, 0, 90);
						myServo.write(angle);
					}
					if(potVal2 >= 1020 && potVal3 <= 3 && potVal4 <= 3){
						angle = map(potVal1, 0, 1023, 90, 179);
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 5:{												//Level 5
					int firstHalf;
					if(potVal2 <=3 && potVal3 <= 3 && potVal4 <= 3){
						firstHalf = map(potVal1, 0, 1023, 0, 90);
					if(firstHalf == 90){
						angle = 90;
						myServo.write(angle);
					}
					}
					if(angle >= 88 && potVal1 <= 3 && potVal3 <= 3 && potVal2 <= 3){
						angle = map(potVal4, 0, 1023, 90, 179);
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 6:{												//Level 6
					int firstQuarter;
					int secondQuarter;
					int thirdQuarter;
					int fourthQuarter;
					if(potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
						firstQuarter = map(potVal1, 0, 1023, 0, 45);
						if(firstQuarter == 45){
							angle = 45;
							myServo.write(angle);
						}
					}
					if(angle >= 43 && potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
						secondQuarter = map(potVal2, 0, 1023, 45, 90);
						if(secondQuarter == 90){
							angle = 90;
							myServo.write(angle);
						}
					}
					if(angle >= 88 && potVal1 <= 3 && potVal2 <= 3 && potVal4 <= 3){
						thirdQuarter = map(potVal3, 0, 1023, 90, 135);
						if(thirdQuarter == 135){
							angle = 135;
							myServo.write(angle);
						}
					}
					if(angle >= 133 && potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3){
						fourthQuarter = map(potVal4, 0, 1023, 135, 179);
						if(fourthQuarter == 179){
							angle = 179;
							myServo.write(angle);
						}
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 7:{												//Level 7
					if(potVal1 <= 3 && potVal3 <= 3 && potVal4 <= 3){
						angle = map(potVal2, 0, 1023, 0, 178);
						myServo.write(angle);
					}
					if(potVal2 >= 1020 && potVal1 <= 3 && potVal4 <= 3){
						angle = map(potVal3, 0, 1023, 178, 0);
						myServo.write(angle);
					}
					if(potVal2 >= 1020 && potVal3 >= 1020 && potVal4 <= 3){
						angle = map(potVal1, 0, 1023, 0, 179);
						myServo.write(angle);
					}
					if(angle == 179){
						extraSkip();
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 8:{												//Level 8
					int key = map(potVal4, 0, 1023, 0, 135);
					int add3 = map(potVal3, 0, 1023, 0, 40);
					int add2 = map(potVal2, 0, 1023, 0, 60);
					int add1 = map(potVal1, 0, 1023, 0, 35);
					if(key >= 39 && key <= 44){
						angle = add1 + add2 + add3 + key;
						myServo.write(angle);
					}
					if(potVal3 <= 3 && potVal2 <= 3 && potVal1 <= 3 && key < 39 || key > 44){
						angle = key;
						myServo.write(angle);
					}
					if(potVal4 <=3 && potVal3 <=3 && potVal2 <= 3){
						angle = add1;
						myServo.write(angle);
					}
					if(potVal4 <=3 && potVal3 <=3 && potVal1 <= 3){
						angle = add2;
						myServo.write(angle);
					}
					if(potVal4 <=3 && potVal2 <=3 && potVal1 <= 3){
						angle = add3;
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 9:{												//Level 9
					if(potVal1 <= 3 && potVal2 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = 178;
						myServo.write(angle);
					}else if(potVal1 > 3 && potVal2 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = map(potVal1, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal2 > 3 && potVal1 <= 3 && potVal3 <=3 && potVal4 <= 3){
						angle = map(potVal2, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal3 > 3 && potVal1 <= 3 && potVal2 <=3 && potVal4 <= 3){
						angle = map(potVal3, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal4 > 3 && potVal1 <= 3 && potVal2 <=3 && potVal3 <= 3){
						angle = map(potVal4, 0, 1023, 178, 0);
						myServo.write(angle);
					}else if(potVal2 >= 1020 && potVal1 <=3 && potVal3 <= 3){
						angle = map(potVal4, 0, 1023, 0, 80);
						myServo.write(angle);
					}else if(potVal2 >= 1020 && potVal4 >= 1020 && potVal3 <= 3){
						angle = map(potVal1, 0, 1023, 80, 160);
						myServo.write(angle);
					}else if(potVal2 >= 1020 && potVal4 >= 1020 && potVal1 >= 1020){
						angle = map(potVal3, 0, 1023, 160, 179);
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 10:{											//Level 10
					int add = map(potVal1, 0, 1023, 0, 135);
					int sub1 = map(potVal2, 0, 1023, 0, 179);
					int sub2 = map(potVal3, 0, 1023, 0, 179);
					int sub3 = map(potVal4, 0, 1023, 0, 179);
					if(potVal1 > 3 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
						angle = add;
						myServo.write(angle);
					}else if(potVal1 <= 3 && sub1 <= 43 && sub2 <= 45 && sub3 <= 45){
						angle = 178 - sub1 - sub2 - sub3;
						myServo.write(angle);
					}else if(sub1 > 43){
						angle = 178;
						myServo.write(angle);
					}else if(sub2 > 45){
						angle = 178;
						myServo.write(angle);
					}else if(sub3 > 45){
						angle = 178;
						myServo.write(angle);
					}else if(sub1 >= 40 && sub1 <= 50 && sub2 >= 40 && sub2 <= 50 && sub3 >= 40 && sub3 <= 50){
						angle = 178 - sub1 - sub2 - sub3 + add;
						myServo.write(angle);
					}
			break;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} //Close switch(level)
	} //close else if(randMode == 0 && passLevel == 0)
	
	
	if(angle >= 179){
		passLevel = 1;
		}
		
		
	if(passLevel == 1){	//Make sure all knobs start at zero before beginning level
		angle = 0;
		myServo.write(angle);
		digitalWrite(greenLedPin, HIGH);
		lcd.setCursor(0, 0);
		lcd.print("Reset All Knobs ");
		lcd.setCursor(0, 1);
		lcd.print("To Continue Play");
		if(potVal1 <= 3 && potVal2 <= 3 && potVal3 <= 3 && potVal4 <= 3){
			digitalWrite(greenLedPin, LOW);
			nextLevel();
		}
	}else if(passLevel == 0 && level <= highestLevel){
		levelStats();	//Display current angle
	}
	
	
	if(level > highestLevel){
		win();
	}
} //close loop()
//////////////////////////////////////////////////////////////////////////// Functions ///////////////////////////////////////////////////////////
void nextLevel(){
	randLevel = random(1, highestLevel+1);
	knobAssign = random(1, 5);
	if(level < highestLevel){
	if(randMode == 0){
	level++;
	lcd.clear();
	lcd.print("Level ");
	lcd.print(level);
	lcd.print("         ");
	lcd.setCursor(0, 1);
	lcd.print("Will Begin Soon ");
	delay(2000);
	}
	lcd.clear();
	passLevel = 0;
	}else{
		randLevel = random(1, highestLevel+1);
		level++;
		passLevel = 0;
	}
}
void extraSkip(){
	skips++;
	lcd.clear();
	lcd.print("You  Earned  An ");
	lcd.setCursor(0, 1);
	lcd.print("  Extra  Skip!  ");
	delay(1500);
	lcd.clear();
}
void win(){
	unsigned long currentTime = millis();
	lcd.setCursor(0, 0);
	lcd.print("Congratulations!");
	lcd.setCursor(0, 1);
	lcd.print("Time: ");
	lcd.print((currentTime - startTime)/1000);
	lcd.print(" S      ");
	digitalWrite(greenLedPin, HIGH);
	digitalWrite(redLedPin, HIGH);
	delay(30);
	digitalWrite(greenLedPin, LOW);
	digitalWrite(redLedPin, LOW);
	delay(30);
	digitalWrite(greenLedPin, HIGH);
	digitalWrite(redLedPin, HIGH);
	delay(30);
	digitalWrite(greenLedPin, LOW);
	digitalWrite(redLedPin, LOW);
	delay(30);
}
void stats(){
	lcd.setCursor(0, 0);
	lcd.print("Lvl: ");
	lcd.print(level);
	lcd.print("   ");
	lcd.setCursor(9, 0);
	lcd.print(skips);
	lcd.print(" Skips");
}
void randStats(){
	lcd.setCursor(0, 0);
	lcd.print("Random   ");
	lcd.setCursor(9, 0);
	lcd.print(skips);
	lcd.print(" Skips");
}
void levelStats(){
		lcd.setCursor(0, 1);
		lcd.print("Angle: ");
		lcd.print(angle);
		delay(100);
		lcd.setCursor(8, 1);
		lcd.print("        ");
}
///////////////////////////////////////////////////////////////////////////Easter Eggs///////////////////////////////////////////////////////////////////////
void credits(){
	digitalWrite(greenLedPin, HIGH);
	digitalWrite(redLedPin, HIGH);
	lcd.clear();
	lcd.setCursor(16, 0);
	lcd.print("Designed & Built");
	lcd.setCursor(16, 1);
	lcd.print("By: Richard Dorn");
	for(int positionCounter = 0; positionCounter < 16; positionCounter++){
		lcd.scrollDisplayLeft();
		delay(300);
	}
	delay(1500);
	lcd.clear();
	lcd.setCursor(16, 0);
	lcd.print("To My Wonderful Mother");
	for(int positionCounter = 0; positionCounter < 37; positionCounter++){
		lcd.scrollDisplayLeft();
		delay(350);
	}
	lcd.clear();
	lcd.setCursor(16, 0);
	lcd.print("    Vicki Jo    ");
	lcd.setCursor(16, 1);
	lcd.print("     Barker     ");
	for(int positionCounter = 0; positionCounter < 16; positionCounter++){
		lcd.scrollDisplayLeft();
		delay(300);
	}
	delay(1500);
	digitalWrite(greenLedPin, LOW);
	digitalWrite(redLedPin, LOW);
	lcd.clear();
	level = 1;
	skips = 9;
}
