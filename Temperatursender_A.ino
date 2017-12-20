#include <RCSwitch.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);
RCSwitch mySwitch = RCSwitch();

int Data = 7;


void setup()
{
  Serial.begin(9600);
  pinMode(Data, INPUT);
  
  dht.begin();
}

void loop()
{
  float Luftfeuchtigkeit = dht.readHumidity();
  float Temperatur = dht.readTemperature();

  
  
  Serial.println(Luftfeuchtigkeit, 2);
  Serial.println(Temperatur, 2);


    
  mySwitch.send(Temperatur, 2);
  mySwitch.send(Luftfeuchtigkeit, 2);
  delay(10000);
}
