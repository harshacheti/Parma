#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Countimer.h"
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <DS3232RTC.h>     
#include <Streaming.h>


LiquidCrystal_I2C lcd(0x3F, 20, 4);
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//I2CScanner scanner;

Countimer tDown;
Countimer uvtDown;
String readString;
String uvtreadString;

int winsen=13;
int winval = 0;  

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

boolean nextPageSet = false;

boolean fmclean = false;

byte currentMenu = 0;
const byte NUMBER_OF_SCREENS = 5;
byte buttonState = LOW;
byte lastButtonState = LOW;
boolean didMyOneTimeAction = false;
boolean systemStatus = false;

boolean uvt = false;
boolean flv = false;
boolean fan = false;
boolean exh = false;


int Tsec=20;
int Tmint=00;
int Thour=900;

int UVTsec=20;
int UVTmint=1;
int UVThour=000;

int pbuttonPin = 8;
int buzzer = 12;
//int next = A0;
int menu = A3; 

int up = A1;
int down = A2;
int next = A0;

int valu = 1;  
int vald = 1;
int valn = 1;

int stepNo = 0;
byte nextButtonState = LOW;

int yearme = 20;
int monthme = 6;
int dateme = 18;

int val = 0;  
int lightON = 0;
int pushed = 1; 
 

const char custom[][8] PROGMEM = {                        // Custom character definitions
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 }, // char 1 
      { 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }, // char 2 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x03 }, // char 3 
      { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 4 
      { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C, 0x18 }, // char 5 
      { 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F }, // char 6 
      { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F }, // char 7 
      { 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F }  // char 8 
};

// BIG FONT Character Set
// - Each character coded as 1-4 byte sets {top_row(0), top_row(1)... bot_row(0), bot_row(0)..."}
// - number of bytes terminated with 0x00; Character is made from [number_of_bytes/2] wide, 2 high
// - codes are: 0x01-0x08 => custom characters, 0x20 => space, 0xFF => black square

const char bigChars[][8] PROGMEM = {
      { 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Space
      { 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // !
      { 0x05, 0x05, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00 }, // "
      { 0x04, 0xFF, 0x04, 0xFF, 0x04, 0x01, 0xFF, 0x01 }, // #
      { 0x08, 0xFF, 0x06, 0x07, 0xFF, 0x05, 0x00, 0x00 }, // $
      { 0x01, 0x20, 0x04, 0x01, 0x04, 0x01, 0x20, 0x04 }, // %
      { 0x08, 0x06, 0x02, 0x20, 0x03, 0x07, 0x02, 0x04 }, // &
      { 0x05, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '
      { 0x08, 0x01, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00 }, // (
      { 0x01, 0x02, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00 }, // )
      { 0x01, 0x04, 0x04, 0x01, 0x04, 0x01, 0x01, 0x04 }, // *
      { 0x04, 0xFF, 0x04, 0x01, 0xFF, 0x01, 0x00, 0x00 }, // +
      { 0x20, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // 
      { 0x04, 0x04, 0x04, 0x20, 0x20, 0x20, 0x00, 0x00 }, // - 
      { 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // .
      { 0x20, 0x20, 0x04, 0x01, 0x04, 0x01, 0x20, 0x20 }, // /
      { 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00 }, // 0
      { 0x01, 0x02, 0x20, 0x04, 0xFF, 0x04, 0x00, 0x00 }, // 1
      { 0x06, 0x06, 0x02, 0xFF, 0x07, 0x07, 0x00, 0x00 }, // 2
      { 0x01, 0x06, 0x02, 0x04, 0x07, 0x05, 0x00, 0x00 }, // 3
      { 0x03, 0x04, 0xFF, 0x20, 0x20, 0xFF, 0x00, 0x00 }, // 4
      { 0xFF, 0x06, 0x06, 0x07, 0x07, 0x05, 0x00, 0x00 }, // 5
      { 0x08, 0x06, 0x06, 0x03, 0x07, 0x05, 0x00, 0x00 }, // 6
      { 0x01, 0x01, 0x02, 0x20, 0x08, 0x20, 0x00, 0x00 }, // 7
      { 0x08, 0x06, 0x02, 0x03, 0x07, 0x05, 0x00, 0x00 }, // 8
      { 0x08, 0x06, 0x02, 0x07, 0x07, 0x05, 0x00, 0x00 }, // 9
      { 0xA5, 0xA5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // :
      { 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ;
      { 0x20, 0x04, 0x01, 0x01, 0x01, 0x04, 0x00, 0x00 }, // <
      { 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x00, 0x00 }, // =
      { 0x01, 0x04, 0x20, 0x04, 0x01, 0x01, 0x00, 0x00 }, // >
      { 0x01, 0x06, 0x02, 0x20, 0x07, 0x20, 0x00, 0x00 }, // ?
      { 0x08, 0x06, 0x02, 0x03, 0x04, 0x04, 0x00, 0x00 }, // @
      { 0x08, 0x06, 0x02, 0xFF, 0x20, 0xFF, 0x00, 0x00 }, // A
      { 0xFF, 0x06, 0x05, 0xFF, 0x07, 0x02, 0x00, 0x00 }, // B
      { 0x08, 0x01, 0x01, 0x03, 0x04, 0x04, 0x00, 0x00 }, // C
      { 0xFF, 0x01, 0x02, 0xFF, 0x04, 0x05, 0x00, 0x00 }, // D
      { 0xFF, 0x06, 0x06, 0xFF, 0x07, 0x07, 0x00, 0x00 }, // E
      { 0xFF, 0x06, 0x06, 0xFF, 0x20, 0x20, 0x00, 0x00 }, // F
      { 0x08, 0x01, 0x01, 0x03, 0x04, 0x02, 0x00, 0x00 }, // G
      { 0xFF, 0x04, 0xFF, 0xFF, 0x20, 0xFF, 0x00, 0x00 }, // H
      { 0x01, 0xFF, 0x01, 0x04, 0xFF, 0x04, 0x00, 0x00 }, // I
      { 0x20, 0x20, 0xFF, 0x04, 0x04, 0x05, 0x00, 0x00 }, // J
      { 0xFF, 0x04, 0x05, 0xFF, 0x20, 0x02, 0x00, 0x00 }, // K
      { 0xFF, 0x20, 0x20, 0xFF, 0x04, 0x04, 0x00, 0x00 }, // L
      { 0x08, 0x03, 0x05, 0x02, 0xFF, 0x20, 0x20, 0xFF }, // M
      { 0xFF, 0x02, 0x20, 0xFF, 0xFF, 0x20, 0x03, 0xFF }, // N
      { 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00 }, // 0
      { 0x08, 0x06, 0x02, 0xFF, 0x20, 0x20, 0x00, 0x00 }, // P
      { 0x08, 0x01, 0x02, 0x20, 0x03, 0x04, 0xFF, 0x04 }, // Q
      { 0xFF, 0x06, 0x02, 0xFF, 0x20, 0x02, 0x00, 0x00 }, // R
      { 0x08, 0x06, 0x06, 0x07, 0x07, 0x05, 0x00, 0x00 }, // S
      { 0x01, 0xFF, 0x01, 0x20, 0xFF, 0x20, 0x00, 0x00 }, // T
      { 0xFF, 0x20, 0xFF, 0x03, 0x04, 0x05, 0x00, 0x00 }, // U
      { 0x03, 0x20, 0x20, 0x05, 0x20, 0x02, 0x08, 0x20 }, // V
      { 0xFF, 0x20, 0x20, 0xFF, 0x03, 0x08, 0x02, 0x05 }, // W
      { 0x03, 0x04, 0x05, 0x08, 0x20, 0x02, 0x00, 0x00 }, // X
      { 0x03, 0x04, 0x05, 0x20, 0xFF, 0x20, 0x00, 0x00 }, // Y
      { 0x01, 0x06, 0x05, 0x08, 0x07, 0x04, 0x00, 0x00 }, // Z
      { 0xFF, 0x01, 0xFF, 0x04, 0x00, 0x00, 0x00, 0x00 }, // [
      { 0x01, 0x04, 0x20, 0x20, 0x20, 0x20, 0x01, 0x04 }, // Backslash
      { 0x01, 0xFF, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00 }, // ]
      { 0x08, 0x02, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00 }, // ^
      { 0x20, 0x20, 0x20, 0x04, 0x04, 0x04, 0x00, 0x00 }  // _
};
byte col,row,nb=0,bc=0;                                   // general
byte bb[8];           
            


void setup() {
Serial.begin (115200);

pinMode(winsen, INPUT_PULLUP); 

setSyncProvider(RTC.get);
    Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;
    
tDown.setCounter(Thour, Tmint, Tsec, tDown.COUNT_DOWN, tDownComplete);
    // Call print_time2() method every 1s.
  tDown.setInterval(print_time2, 1000);

uvtDown.setCounter(UVThour, UVTmint, UVTsec, uvtDown.COUNT_DOWN, uvtDownComplete);
    // Call print_time2() method every 1s.
  uvtDown.setInterval(uvtprint_time2, 1000);
  
pinMode(pbuttonPin, INPUT_PULLUP);
pinMode(menu, INPUT_PULLUP);

pinMode(up, INPUT_PULLUP);
pinMode(down, INPUT_PULLUP);
pinMode(next, INPUT_PULLUP);
digitalWrite(2, HIGH);

pinMode(buzzer, OUTPUT);
lcd.init();
lcd.backlight();
//lcd.clear();
// lcd.print("Hello, World!");
writeBigString("R J I L S", 0, 1);  
delay(2000); 
lcd.clear();

//lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
//lcd.setBacklight(HIGH);

Serial.println(F("BMP280 Sensor event test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();

for (nb=0; nb<8; nb++ ) {                     // create 8 custom characters
    for (bc=0; bc<8; bc++) bb[bc]= pgm_read_byte( &custom[nb][bc] );
    lcd.createChar ( nb+1, bb );
  }
 
}

void loop() {
   char msg[16] = "";
  
  winval = digitalRead(winsen);

 static time_t tLast;
    time_t t;
    tmElements_t tm;

    // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (Serial.available() >= 12) {
        // note that the tmElements_t Year member is an offset from 1970,
        // but the RTC wants the last two digits of the calendar year.
        // use the convenience macros from the Time Library to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    // (y < 100)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
            RTC.set(t);        // use the time_t value to ensure correct weekday is set
            setTime(t);
            Serial << F("RTC set to: ");
            printDateTime(t);
            Serial << endl;
            // dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }
  
  tDown.run();
  uvtDown.run();


sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
buttonState = digitalRead(menu);
 
if (buttonState == LOW)  // check that button has transition to HIGH. i.e.: just been pressed
    {
      Serial.print(currentMenu); 
        currentMenu++;
        tDown.setCounter(Thour, Tmint, Tsec, tDown.COUNT_DOWN, tDownComplete);
        tDown.setCounter(UVThour, UVTmint, UVTsec, uvtDown.COUNT_DOWN, uvtDownComplete);
        if(currentMenu>1){
          currentMenu=0; 
          }  
          delay(200);
      //  currentMenu = currentMenu % NUMBER_OF_SCREENS; // loop back to Menu 0 after last menu
    }
  if(currentMenu==0){
    if(didMyOneTimeAction == true){
      didMyOneTimeAction = false;
    lcd.clear();
      }
//lcd.setCursor(0, 0); 
 // lcd.print(dateme);
//  lcd.setCursor(2, 0); 
//  lcd.print(F ("-"));
//  lcd.setCursor(3, 0); 
//  lcd.print(monthme);
//  lcd.setCursor(5, 0); 
 // lcd.print(F ("-"));
//  lcd.setCursor(6, 0); 
//  lcd.print(yearme);
 t = now();
    if (t != tLast) {
        tLast = t;
        printDateTime(t);
      
        if (second(t) == 0) {
            float c = RTC.temperature() / 4.;
            float f = c * 9. / 5. + 32.;
            Serial << F("  ") << c << F(" C  ") << f << F(" F");
        }
        Serial << endl;
    }
//lcd.setCursor(15, 0); 
//  lcd.print(F ("02:00"));
//lcd.setCursor(10, 0); 
  //lcd.print(F (" ON "));
lcd.setCursor(0, 1); 
  lcd.print(F ("M/S:"));
  lcd.setCursor(17, 0); 
  lcd.print(F (":"));
lcd.setCursor(0, 2); 
  lcd.print(F ("F/M:"));  
  if(isnan(4005*sqrt((pressure_event.pressure*0.4015)-378.54))){  
    if(fmclean == true){
      lcd.clear();
      fmclean=false;
      }     
  lcd.print("0");
  }
  else{
    fmclean=true;
    lcd.print((4005*sqrt((pressure_event.pressure*0.4015)-378.54)));
    }
  
  lcd.setCursor(0, 3); 
  lcd.print(F ("Cab_T:")); 
  lcd.setCursor(6, 3); 
  lcd.print(temp_event.temperature); 
  lcd.setCursor(10, 1); 
  lcd.print(F ("UVT:"));
  
   lcd.setCursor(14, 1); 
  uvtreadString = uvtDown.getCurrentTime();
  lcd.print(uvtreadString.substring(0,6));
  
  lcd.setCursor(12, 2); 
  lcd.print(F ("T:"));
  lcd.setCursor(14, 2); 
  readString = tDown.getCurrentTime();
  lcd.print(readString.substring(0,6));
  lcd.setCursor(13, 3); 
  if(winval==HIGH){
  lcd.print(F ("UnSafe")); 
  }
  else{
    lcd.print(F ("  Safe")); 
    }
Serial.println(pressure_event.pressure);
Serial.println((4005*sqrt((pressure_event.pressure*0.4015)-378.54)));
   val = digitalRead(pbuttonPin);

    if (val == LOW) {
 //   Serial.println("The button is being pressed");
    digitalWrite(buzzer, HIGH); // turn on
    
  }
  else
  if (val == HIGH) {
  //  Serial.println("The button is unpressed");
    digitalWrite(buzzer, LOW);  // turn off
    
  }

if(val == HIGH && lightON == LOW){
  
  
  //  digitalWrite(buzzer, HIGH);  
    pushed = 1-pushed;
    delay(100);
  }    
  lightON = val;

      if(pushed == HIGH){
      // Serial.println("Light ON");
        lcd.setCursor(10, 0); 
        lcd.print(" ON");
        tDown.start();
        uvtDown.start();
      //   digitalWrite(buzzer, HIGH); 
      // digitalWrite(relayPin, LOW); 
       
      }else{
      //  Serial.println("Light OFF");
        lcd.setCursor(10, 0);
        lcd.print("OFF");
        tDown.stop(); 
        uvtDown.stop();
       // digitalWrite(buzzer, HIGH); 
       // digitalWrite(relayPin, HIGH);
   
      }
   
    }
    if(currentMenu==1 && pushed == 0){
if (didMyOneTimeAction == false){
    didMyOneTimeAction = true;
    lcd.clear(); 
  }
  
  nextButtonState = digitalRead(next); 
 if (nextButtonState == LOW) 
    {
      Serial.print(stepNo);
      lcd.noBlink();
        stepNo++;
        if(stepNo==17){
          lcd.clear();
          stepNo=0;
          }
    }
    
    dmy();
    
  // Turn off the cursor:
  if(stepNo<11){
    nextPageSet = false;

  // Turn off the cursor:
  lcd.setCursor(0, 0);
  lcd.print(dateme); 
  //datefn();
  lcd.setCursor(2, 0);
  lcd.print(F ("-"));
  lcd.setCursor(3, 0);
  lcd.print(monthme);
  lcd.setCursor(5, 0);
  lcd.print(F ("-"));
  lcd.setCursor(6, 0);
  lcd.print(yearme);
  lcd.setCursor(15, 0);
  lcd.print(F ("12"));
  lcd.setCursor(17, 0);
  lcd.print(F (":"));
  lcd.setCursor(18, 0);
  lcd.print(F ("03")); 

  lcd.setCursor(0, 1);
  lcd.print(F ("M/S:H"));
  
  lcd.setCursor(0, 2);
  lcd.print(F ("UVT:"));
  
  if(uvt==false){
  lcd.setCursor(4, 2);
  lcd.print("OFF");
  }
  if(uvt==true){
  lcd.setCursor(4, 2);
  lcd.print(" ON");
  }
  
  lcd.setCursor(0, 3);   
  lcd.print("FAN:");
  
  if(fan==false){
  lcd.setCursor(4, 3);
  lcd.print("OFF");
  }
  if(fan==true){
  lcd.setCursor(4, 3);
  lcd.print(" ON");
  }
  
  lcd.setCursor(12, 1);
  lcd.print(F ("M/S:L"));
  
  lcd.setCursor(12, 2);
  lcd.print(F ("FLV:"));

  if(flv==false){
  lcd.setCursor(16, 2);
  lcd.print("OFF");
  }
  if(flv==true){
  lcd.setCursor(16, 2);
  lcd.print(" ON");
  }
  
  lcd.setCursor(12, 3);
  lcd.print(F ("EXH:"));

  if(exh==false){
  lcd.setCursor(16, 3);
  lcd.print("OFF");
  }
  if(exh==true){
  lcd.setCursor(16, 3);
  lcd.print(" ON");
  }
  }
  
 else{
if(nextPageSet==false){
  lcd.clear();
  nextPageSet=true;
  }
  lcd.setCursor(0, 0);
  lcd.print("UV Timer  :");
  lcd.setCursor(0, 1);
  lcd.print("TotalTimer:");
  lcd.setCursor(11, 1);
  lcd.print(Thour);
  lcd.setCursor(15, 1);
  lcd.print(":");
  sprintf(msg, "%02d", Tmint);
  lcd.setCursor(16, 1);
  lcd.print(msg);
//  lcd.setCursor(16, 1);
//  lcd.print(":");
 // lcd.setCursor(17, 1);
//  lcd.print(Tsec);
  
  lcd.setCursor(0, 2);
  lcd.print("EXH Timer :");
  lcd.setCursor(0, 3);
  lcd.print("TotalUVT  :");
  }
 }
}

  void print_time2()
{
  Serial.print("tDown: ");
  Serial.println(tDown.getCurrentTime());
}

 void uvtprint_time2()
{
  Serial.print("uvtDown: ");
  Serial.println(uvtDown.getCurrentTime());
}

void tDownComplete()
{
  digitalWrite(2, LOW);
}

void uvtDownComplete()
{
  digitalWrite(2, LOW);
}

//////////////////////////////////////////////
void printDateTime(time_t t)
{
    printDate(t);
    Serial << ' ';
    printTime(t);
}

// print time to Serial
void printTime(time_t t)
{
  printI00lcdtimH(hour(t), 0);
  printI00lcdtimM(minute(t), 0);
 // printI00lcdtimS(second(t), 0);
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    printI00lcd(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
    lcd.setCursor(2, 0); 
    lcd << monthShortStr(month(t)) << _DEC(year(t));
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0';
    Serial << _DEC(val);  
    if (delim > 0) Serial << delim;
    return;
}

void printI00lcd(int val, char delim)
{
    lcd.setCursor(0, 0);
    if (val < 10) lcd << '0';
    lcd << _DEC(val); 
    if (delim > 0) lcd << delim;
    return;
}

void printI00lcdtimH(int val, char delim)
{
    lcd.setCursor(15, 0);
    if (val < 10) lcd << '0';
    lcd << _DEC(val); 
    if (delim > 0) lcd << delim;
    return;
}
void printI00lcdtimM(int val, char delim)
{
    lcd.setCursor(18, 0);
    if (val < 10) lcd << '0';
    lcd << _DEC(val); 
    if (delim > 0) lcd << delim;
    return;
}
void printI00lcdtimS(int val, char delim)
{
    lcd.setCursor(18, 0);
    if (val < 10) lcd << '0';
    lcd << _DEC(val); 
    if (delim > 0) lcd << delim;
    return;
}
//////////////////////////////////////////////////
