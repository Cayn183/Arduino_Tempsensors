//Temperatur-Empfänger version 		//


//Benötigte Libarys
#include <VirtualWire.h>

struct Daten
{
	float Spannung;
	float Temperatur;
	float Luftfeuchtigkeit;
};
Daten daten;


void setup()
{
	Serial.begin(9600);
	pinMode(0, INPUT);
	
	vw_set_rx_pin(11);
	vw_setup(2000);
	vw_rx_start();
	
	Serial.println("Device Ready!");
}

void loop()
{
	byte len = sizeof(daten);	

	if(vw_get_message((byte*)&daten, &len))
	{
	
	float WertSpannung = daten.Spannung;
	float WertTemperatur = daten.Temperatur;
	float WertLuftfeuchtigkeit = daten.Luftfeuchtigkeit;
	
	Serial.println(WertTemperatur, 2);
	
	}

}