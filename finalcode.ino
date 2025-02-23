#include <TEA5767Radio.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // RS, Enable, D4, D5, D6, D7

TEA5767Radio radio; 

int analogPin = 0;
int val = 0; 
int frequencyInt = 0;
float frequency = 0;
float previousFrequency = 0;

void setup(){
  lcd.begin(16, 2); // Start the LCD in 4-bit mode for a 16x2 display
  analogWrite(11,100);
  showSplashScreen();
  //lcd.print("Testing LCD...");
  delay(2000);
  lcd.clear();
  showSplashScreen();
  Serial.begin(9600);
  
}
 
void loop() {
  for(int i = 0; i < 30; i++)
  {
     val += analogRead(analogPin); 
     delay(1);
  }
  
  val = val / 30;
  frequencyInt = map(val, 2, 1014, 8700, 10700); 
  float frequency = frequencyInt / 100.0f;
  

  if(fabs(frequency - previousFrequency) >= 0.1f)
  {
    lcd.clear();
    radio.setFrequency(frequency);  
    printFrequency(frequency);
    previousFrequency = frequency;   
     
  }

  delay(50); 
  val = 0;  
}

void printFrequency(float frequency)
{   
  lcd.setCursor(0, 0); 
  lcd.print("Freq: ");
  lcd.print(frequency, 1); 
  lcd.print(" MHz");
}

void showSplashScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FM Radio Init");
  delay(2000);
  lcd.clear();
}
