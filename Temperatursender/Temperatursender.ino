//Temperatursender Version     //


//Benötigte Libarys
#include <RCSwitch.h> //RCSwitch-Libary einfügen
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
RCSwitch mySwitch = RCSwitch();

void setup()
{
  Serial.begin(9600); //Sarte Serielle Verbindung
  pinMode(voltinput, INPUT);  //Definiere voltinput als Eingang

  pinMode(Data, INPUT); //Definiere Data-Pin als Input
  dht.begin();  //Starte Sensor-Messungen

}

void loop()
{
  Spannungsmessung(); //Führe void Spannungsmessung durch
  Temperaturmessung();	//Führe void Temperaturmessung durch
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
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int Temperatur = (t * 100);
  int Luftfeuchtigkeit = (h * 100);
  int Spannung = (vin * 100);
  
  String Auswertung = String('a' + Spannung + 'b' + Temperatur + 'c' + Luftfeuchtigkeit);
 
  Serial.println(Auswertung);

    
  //mySwitch.send(Auswertung, 2);
}

