// DC Voltmeter Test

int analogInput = 0;
float vout = 0.0;
float vin = 0.0;

float R1 = 100000.0;
float R2 = 10000.0;
int value = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(analogInput, INPUT);  

}

void loop()
{
  //read tje value at analog input
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; 
  vin = vout / (R2/(R1+R2));
  
  if (vin<0.09)
  {
     vin=0.0;
  }

  Serial.print("Spannung: ");
  Serial.println(vin, 3);
  delay(5000);
}
