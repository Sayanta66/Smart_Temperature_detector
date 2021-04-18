
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN        6
#define NUMPIXELS 16 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 10 



SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
pinMode(3,OUTPUT);
pixels.begin();
  mlx.begin();
  apds.init();
  apds.enableProximitySensor(false);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Serial.begin(9600);

}


void loop() {
  pixels.clear();
  String temperature = "";
  /*
    Serial.print("Ambient ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print(" C");
    Serial.println();

    Serial.print("Target  ");
    Serial.print(mlx.readObjectTempC());
    Serial.print(" C");
    Serial.println();
  */
  apds.readProximity(proximity_data);
  if (proximity_data == 255 && mlx.readObjectTempF() < 100) {


    temperature = String(mlx.readObjectTempC(), 1);
    Serial.println(mlx.readObjectTempC());
    display.clearDisplay();
    display.invertDisplay(false);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 0);
    display.clearDisplay();
    display.println("Body Temp:");
    display.setCursor(25, 18);
    display.print(mlx.readObjectTempC());

    display.setCursor(85, 8);
    display.print(".");


    display.setTextColor(WHITE);
    display.setCursor(85, 18);
    display.print(" C");
    display.display();

for(int i=0; i<NUMPIXELS; i++)
  { 
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show(); 
    delay(50);
  }
  delay (10);
  for(int i=0; i<NUMPIXELS; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();   
    delay(50); 
  }


   delay(1000);

  }
  if (proximity_data == 255) {
    if (mlx.readObjectTempF() > 102) {
      digitalWrite(3, HIGH);
      noTone(5);
      // play a note on pin 8 for 500 ms:
      tone(8, 523, 500);
      Serial.println(mlx.readObjectTempC());
      display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");


      display.invertDisplay(true);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");


      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");


      display.invertDisplay(true);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");


      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");




      display.setCursor(23, 18);
      display.print(mlx.readObjectTempC());
      display.setCursor(93, 8);
      display.print(".");
      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" C");
      display.display();
      
for(int i=0; i<NUMPIXELS; i++)
  { 
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    pixels.show(); 
    delay(10);
  }
  delay (10);
  for(int i=0; i<NUMPIXELS; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();   
    delay(10); 
  }


      delay(1000);
   digitalWrite(3, LOW);
    }

  }

  if (proximity_data == 255) {
    if (mlx.readObjectTempF() > 100) {

      display.setCursor(93, 8);
      display.print(".");


      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" C");
      display.display();



    }
  }


  else if (proximity_data <= 255) {
    delay(1000);

    display.clearDisplay();
    display.invertDisplay(true);
    display.setTextSize(2.8);
    display.setTextColor(WHITE);
    display.setCursor(45, 1);
    display.clearDisplay();
    display.println("NOT");
    display.setCursor(17, 17);
    display.print("DETECTED");
    display.display();
    digitalWrite(5, LOW);
 

  }



}
