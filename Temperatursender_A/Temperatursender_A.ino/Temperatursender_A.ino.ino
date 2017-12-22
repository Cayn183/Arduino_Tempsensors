#include <RCSwitch.h> //RCSwitch-Libary einfügen
#include <DHT.h>  //DHT-Sensor Libary einfügen


#define DHTPIN 7  //Definiere Sensor an PIN7
#define DHTTYPE DHT22 //Definiere DHT22 als Sensor
DHT dht(DHTPIN,DHTTYPE);  
RCSwitch mySwitch = RCSwitch();


int voltinput = 0; //Definiere Variable Voltinput als 0
float vout = 0.0; //Definiere Variable Vout als 0
float vin = 0.0;  //Definiere Variable Vin als 0

float R1 = 100200.0;  //Definiere Wiederstand R1
float R2 = 9960.0;  //Definiere Wiederstand R2
int value = 0;  //Definiere Value Pin als A0
int Data = 7;   //Definiere Data Pin als D7


void setup()
{
  Serial.begin(9600); //Sarte Serielle Verbindung
  pinMode(voltinput, INPUT);  //Definiere voltinput als Eingang

  pinMode(Data, INPUT); //Definiere Data-Pin als Input
  dht.begin();  //Starte Sensor-Messungen

}

void loop()
{
  Spannungsmessung();
}



void Spannungsmessung()
{
  //read tje value at analog input
  value = analogRead(voltinput);
  vout = (value * 4.65) / 1024.0; 
  vin = vout / (R2/(R1+R2));
  
  if (vin<0.09)
  {
     vin=0.0;
  }

  Serial.print("Spannung: ");
  Serial.print(vin, 1);
  Serial.println("V");

  Temperaturmessung();
}


void Temperaturmessung()
{
  float Luftfeuchtigkeit = dht.readHumidity();
  float Temperatur = dht.readTemperature();

  
  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(Luftfeuchtigkeit, 2);
  Serial.println("%");
  Serial.print("Tempertatur: ");
  Serial.print(Temperatur, 2);
  Serial.println("°C");
  Serial.println("");

    
  mySwitch.send(Temperatur, 2);
  mySwitch.send(Luftfeuchtigkeit, 2);
  delay(10000);
}

