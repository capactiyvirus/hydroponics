#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 52

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celcius=0;
float Fahrenheit=0;
float calibration = 22.00; //change this value to calibrate
const int analogInPin = A0; 
const int analogInPin5 = A5;
int sensorValue = 0; 
unsigned long int avgValue, avgTemp; 
float b;
int buf[10],temp, buff[10], tempe;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
 sensors.requestTemperatures(); 
 Celcius=sensors.getTempCByIndex(0);
 Fahrenheit=sensors.toFahrenheit(Celcius);
 for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(30);
  buff[i]=analogRead(analogInPin5);
  delay(30);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
    if(buf[i]>buf[j])
    {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
    }
    if(buff[i]>buff[j])
    {
    tempe=buff[i];
    buff[i]=buff[j];
    buff[j]=tempe;
    }
  }
 }
 avgValue=0;
 avgTemp=0;
 for(int i=2;i<8;i++){
 avgValue+=buf[i];
 avgTemp+=buff[i];
 }
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + calibration;
 float temperature = (float)avgTemp*5.0/1024/6;
 Serial.print("sensor = ");
 Serial.println(phValue);
 //Serial.println(buff[1]);
 Serial.print(" C  ");
 Serial.print(Celcius);
 Serial.print(" F  ");
 Serial.println(Fahrenheit);
 //Serial.println(A5);
 
 delay(500);
}
