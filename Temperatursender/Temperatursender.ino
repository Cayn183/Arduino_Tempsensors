//Temperatursender Version     //


//Benötigte Libarys
#include <VirtualWire.h>
#include <DHT.h>  //DHT-Sensor Libary einfügen

//Variablen für DHT-Sensor
#define DHTPIN 7  //Definiere Sensor an PIN7
#define DHTTYPE DHT22 //Definiere DHT22 als Sensor
DHT dht(DHTPIN,DHTTYPE);  


//Variablen für Spannungsmessung
int voltinput = 0; //Definiere Variable Voltinput als 0
float vout = 0.0; //Definiere Variable Vout als 0
float vin = 0.0;  //Definiere Variable Vin als 0
float R1 = 100200.0;  //Definiere Wiederstand R1
float R2 = 9960.0;  //Definiere Wiederstand R2

//Variablen für Temperaturmessung
int value = 0;  //Definiere Value Pin als A0

//Variablen für Datenübertragung
int Data = 7;   //Definiere Data Pin als D7


struct Daten
{
	float Spannung;
	float Temperatur;
	float Luftfeuchtigkeit;
};

Daten daten;


void setup()
{
  Serial.begin(9600); //Sarte Serielle Verbindung
  pinMode(voltinput, INPUT);  //Definiere voltinput als Eingang

  pinMode(Data, INPUT); //Definiere Data-Pin als Input
  dht.begin();  //Starte Sensor-Messungen
  
  pinMode(12, OUTPUT);
  vw_setup(2000); // Bits per sec
  vw_set_tx_pin(12);// Set the Tx pin. Default is 12

}

void loop()
{
  Spannungsmessung(); //Führe Spannungsmessung durch
  Temperaturmessung();	//Führe Temperaturmessung durch
  delay(10000);	//Pause von 10Sekunden
}



void Spannungsmessung()
{
  //Read the value at analog input
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
}


void Temperaturmessung()
{
  daten.Spannung = vin;
  daten.Luftfeuchtigkeit = dht.readHumidity();
  daten.Temperatur = dht.readTemperature();
  
  vw_send((byte*)&daten, sizeof(daten));
  vw_wait_tx();
}

