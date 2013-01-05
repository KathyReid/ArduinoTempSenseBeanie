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

int   tempSensorFreq  = 200;       // number of milliseconds between sensor readings
int   numSensors      = 3;          // the number of temperature sensors in use
int   numSamples      = 10;          // the number of samples to take in each reading for better precision
int   sampleDelay     = 10;          // time in milliseconds to delay between each precision sample

int   tempSensorUpper[] = {
  70,70,70}; // upper threshold for temp warning
int   tempSensorLower[] = {
  30,30,30}; // lower threshold for temp warning

float reading[] = {
};
float sum = 0;

#define BANDGAPREF 14   // special indicator that we want to measure the bandgap

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

  for (int i=0; i < numSensors; i++)
  {

    sum = 0;

    /* Multiple temperature samples are taken and averaged
     to yield a higher degree of precision
     You may wish to adjust the timing and number of samples 
     */

    for (int j=0; j < numSamples; j++)
    {
      reading[j] = analogRead(tempSensorPin[i]);
      delay(sampleDelay);
    }

    for (int k=0; k < (numSamples-1); k++)
    {
      sum = sum + reading[k];
    }

    tempSensorVal[i] = sum/numSamples;

    /*
    Now to convert the temperature reading in to Celcius
     */

    Serial.println("--------Doing Celcius conversion---------");
    Serial.println(i);
    Serial.println("Value is: ");
    Serial.println(tempSensorVal[i]); 	// send that value to the computer
    
    // get voltage reading from the secret internal 1.05V reference
    float refReading = analogRead(BANDGAPREF);  
    Serial.println(refReading);
    
    // now calculate our power supply voltage from the known 1.05 volt reading
  float supplyvoltage = (1.05 * 1024) / refReading;
  Serial.print(supplyvoltage); 
  Serial.println("V power supply");
  
  // converting that reading to voltage
  float voltage = (tempSensorVal[i] * supplyvoltage) / 1024;
 
  // print out the voltage
  Serial.print(voltage); 
  Serial.println(" volts");
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;   //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((volatge - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degress C");
 
  // now convert to Fahrenheight
  float temperatureF = (temperatureC * 9 / 5) + 32;
  Serial.print(temperatureF); Serial.println(" degress F");
  }

  /* Delay for defined delay period */
  delay(tempSensorFreq); 


} 








