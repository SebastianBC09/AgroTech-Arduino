#include<DHT.h>;
#include<LiquidCrystal_I2C.h>;

DHT dhtSensor(3 , DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  //Pin for irrigation system
  pinMode(13,OUTPUT);

  //Sensor & LCD
  dhtSensor.begin();  
  lcd.init();
  lcd.backlight();
}

void loop() {
  //Code logic-program for humidity sensor
  int humiditySensorReadings = analogRead(A0);

  Serial.println("La lectura del sensor de humedad es: ");
  Serial.println(humiditySensorReadings);

  if(humiditySensorReadings >= 1000){
    Serial.println("El sensor esta desconectado o fuera del suelo");
  } else if(humiditySensorReadings < 1000 && humiditySensorReadings >= 600) {
    Serial.println("El suelo esta seco");
  } else if(humiditySensorReadings < 600 && humiditySensorReadings >= 370) {
    Serial.println("El suelo esta humedo");
  } else if (humiditySensorReadings < 370) {
    Serial.println("El sensor esta en agua");
  }

  if(humiditySensorReadings >= 1000) {
    digitalWrite(13,LOW);
    Serial.println("Bomba se enciende");
  } else if (humiditySensorReadings <= 900) {
    digitalWrite(13,HIGH);
    Serial.println("Bomba se apaga");
  }

  //Code logic-program for DHT sensor & LCD Screen
  float TempC = dhtSensor.readTemperature();
  float TempF = dhtSensor.readTemperature(true);
  float Humd = dhtSensor.readHumidity();

  if(isnan(TempC) || isnan(TempF) || isnan(Humd)) {
    Serial.println("Revisar conexion");
  } else {
    Serial.println("Temp:" + String(TempC,1) + "C " + String(TempF, 1)+"F");

    lcd.home();
    lcd.print("Temp: ");
    lcd.print(TempC);
    lcd.print(" C");
    Serial.println("Humd:" + String(Humd, 1)+ "%"); 
    lcd.setCursor(0, 1);
    lcd.print("Humd: ");
    lcd.print(Humd);
    lcd.print(" %");
  }

  delay(1000);
}
