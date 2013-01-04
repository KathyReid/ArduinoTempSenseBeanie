/*
  
 ArduinoTempSenseBeanie
 
 The purpose of this sketch is to;
 1. Read input from Lilypad temperature sensors
 2. Analyse temperature
 3. Take action if the temperature is above or below a certain threshold
 
 Arrays are deliberately used in this sketch in case future iterations use more sensors / pins. 
 
 
 Components used;
 * Lilypad simple board - http://littlebirdelectronics.com/products/lilypad-arduino-328-main-board - $21.95
 * Lilypad temperature sensors x 3 - http://littlebirdelectronics.com/products/lilypad-temperature-sensor - $5.69 each
 * Lilypad coin cell battery holder (and batteries) - http://littlebirdelectronics.com/products/lilypad-coin-cell-battery-holder-1 - $5.50
 * Lilypad slide switch - http://littlebirdelectronics.com/products/lilypad-slide-switch - $4.89
 * Lilypad tri-colour LED  
 
 
 VERSIONS
 Refer git log
 
 
 Created by Kathy Reid - @KathyReid on GitHub, Twitter etc
 kathyreid.id.au
 
 */

/* Initialise variables */

int ledPin =  13;                  // LED connected to digital pin 13

int Rpin   =  11;                  // tri-colour LED output to pin 11
int Gpin   =  9;                  // tri-colour LED output to pin 10
int Bpin   =  10;                  // tri-colour LED output to pin 09

float tempSensorVal[] = {
  0,0,0};   // an array of temperature sensor values

int   tempSensorPin[] = {
  0,1,2};   // the temp sensors will be connected to analogue pins 0, 1, 2 

int   tempSensorFreq  = 30000;       // number of milliseconds between sensor readings
int   numSensors      = 3;          // the number of temperature sensors in use
int   numSamples      = 5;          // the number of samples to take in each reading for better precision

int   tempSensorUpper[] = {
  70,70,70}; // upper threshold for temp warning
int   tempSensorLower[] = {
  30,30,30}; // lower threshold for temp warning

float reading[] = {
};
float sum = 0;


/*
  Define RGB colours 
 */
int off[]    =  {
  255,255,255};
int white[] = {
  0, 0, 0};
int red[]    =  {
  0, 255, 255};
int blue[]   =  {
  255, 255, 0};
int green[]  =  {
  255, 0, 255};
int cyan[]   =  {
  255, 0, 0};
int magenta[] = {
  0, 255, 0};
int yellow[] =  {
  0, 0, 255};

/*
  Define RGB slide transition speeds
 */
#define vfast   10
#define fast    20
#define med     40
#define slow    80
#define vslow   160

#define vfastTime 10
#define fastTime  20
#define medTime   40
#define slowTime  80
#define vslowTime 160

void setup() 	 
{ 	 
  Serial.begin(9600); 	//initialize the serial port       
  pinMode(ledPin, OUTPUT); 	// sets the ledPin to be an output

  initialiseRGB();

  //  slide(green, yellow, med, medTime);
  // slide(yellow, green, med, medTime);
  // slide(green, yellow, med, medTime);
  // slide(yellow, green, med, medTime);
  // slide(green, yellow, med, medTime);
  // slide(yellow, green, med, medTime);
  // slide(green, yellow, med, medTime);
  // slide(yellow, green, med, medTime);


} 	 

void loop() 	// run over and over again
{ 	 


  Serial.write("-----------------------START------------------------");



  for (int i=0; i < numSensors; i++)
  {

    sum = 0;

    Serial.println(analogRead(tempSensorPin[i]));

    for (int j=0; j < numSamples; j++)
    {
      Serial.println(analogRead(tempSensorPin[i]));
      reading[j] = analogRead(tempSensorPin[i]);
      Serial.write(" reading j is: ");
      delay(100);
      Serial.print(reading[j], DEC);
      Serial.write("\n");
      Serial.write("i is: ");
      Serial.print(i, DEC);
      Serial.write(" j is: ");
      Serial.print(j, DEC);
      Serial.write("\n");
    }

    for (int k=0; k < (numSamples-1); k++)
    {
      sum = sum + reading[k];
      Serial.write(" k is: ");
      Serial.print(k);
      Serial.write("\n");
      Serial.write(" sum is: ");
      Serial.print(sum);
    }


    tempSensorVal[i] = sum/numSamples;
    Serial.write(" tempSensorVal[i] is: ");
    Serial.print(tempSensorVal[i]);

    /*
    Now to convert the temperature reading in to Celcius
     */

    Serial.println('\n');
    Serial.println(i);
    Serial.println(tempSensorVal[i]); 	// send that value to the computer
  } 


  /* Delay for defined delay period */
  delay(tempSensorFreq); 


} 






