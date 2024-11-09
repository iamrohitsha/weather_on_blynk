#include <LiquidCrystal.h>

#include <DHT.h>
#include <DHT_U.h>


const int RS = 8, EN = 9, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
const int red = 13;
const int green = 12;

const int buzzer = 10;
//float threshold_temperature =  30; 
DHT dth11(6,DHT11);
void setup() {
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2); // set up number of columns and rows
 
  lcd.setCursor(0, 0); 
  lcd.print("Smart weather mon");
  lcd.setCursor(0, 1);
  lcd.print("itoring system");
  delay(1000);
 
  dth11.begin();
  Serial.begin(9600);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
}

void loop() {
  float temperature = dth11.readTemperature();
  float humidity = dth11.readHumidity();
  if(temperature >= 32 || humidity >=80){
    lcd.clear();
    lcd.setCursor(0,0);
    digitalWrite(red,HIGH);
    digitalWrite(green, LOW);
    lcd.print("TEMP('C) : ");
    lcd.setCursor(11,0);
    lcd.print(temperature);
    lcd.setCursor(0,1);
    lcd.print("HUMIDITY : ");
    lcd.setCursor(11,1);
    lcd.print(humidity);
    digitalWrite(buzzer, HIGH);
    Serial.print("Temperature");
    Serial.println(temperature);
      
    }
    
  
  else{
    digitalWrite(green , HIGH);
    digitalWrite(red, LOW);
    digitalWrite(buzzer , LOW);
    lcd.print("TEMP('C) : ");
    lcd.setCursor(11,0);
    lcd.print(temperature);
    lcd.print("HUMIDITY : ");
    lcd.setCursor(11,1);
    lcd.print(humidity);
        Serial.print("Temperature");
    Serial.println(temperature);
  }
  
  

}
