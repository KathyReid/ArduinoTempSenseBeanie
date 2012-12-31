void initialiseRGB(void);  
void writeColour(int RGB[]);
void slide (int RGB1[], int RGB2[], int slideSteps, int slideTime);

void initialiseRGB()
{
  int Rpin = 9;                
  int Gpin = 10;                
  int Bpin = 11; 

  pinMode(Rpin, OUTPUT);      
  pinMode(Gpin, OUTPUT);      
  pinMode(Bpin, OUTPUT);      

  writeColour(off);
  delay (2000);

}

void writeColour(int RGB[])
{
  analogWrite(Rpin, RGB[0]);
  analogWrite(Gpin, RGB[1]);
  analogWrite(Bpin, RGB[2]);
}

/*

 This function is intended to take two sets of three RGB integers (0-255)
 and an integer value in milliseconds, and will calculate a 'slide'
 transition between the two colours.
 
 */
void slide (int RGB1[], int RGB2[], int slideSteps, int slideTime)

{
  float diff[] = {
    0,0,0                    };

  int newRGB[] = {
    0,0,0                  };

  float
    stepVal[] = {
    0.00,0.00,0.00                };

  int origRGB1[] = {
    RGB1[0], RGB1[1], RGB1[2]  };
  int origRGB2[] = {
    RGB2[0], RGB2[1], RGB2[2]  };

  float flRGB1[] = {
    origRGB1[0], origRGB1[1], origRGB1[2]  };

  // calculate difference between the two sets
  for (int i=0; i < 3; i++){

    diff[i] = origRGB1[i] - origRGB2[i];

    // if the difference is negative, make it positive
    if (diff[i] < 0)
    {
      diff[i] = (diff[i] * -1);
    }

    Serial.print ("\n------------------\nRGB1 i is ");
    Serial.print (RGB1[i]);
    Serial.print ("  RGB2 i is ");
    Serial.print (RGB2[i]);
    Serial.print ("\norigRGB1 i is ");
    Serial.print (origRGB1[i]);
    Serial.print (" - origRGB2 i is ");
    Serial.print (origRGB2[i]);
    Serial.print  ("diff i is:");
    Serial.print ( diff[i]);


    // determine how much the colour should change on each iteration
    stepVal[i] = (diff[i]/slideSteps);

    Serial.print ("   slide time is: ");
    Serial.print   (slideSteps, DEC);
    Serial.print  ("  stepval is:");
    Serial.println ( stepVal[i]);
  }

  // now we calculate the different values that the LED has to be set to in between RGB1 and RGB2 values

  for (int j=0; j < slideSteps; j++)
  {

    for (int l=0; l < 3; l++)
    {
      // determine whether RGB1 has to increment up to RGB2 or decrement down
      if (origRGB1[l] < origRGB2[l])
      {
        newRGB[l] = int(flRGB1[l] + stepVal[l]);
        flRGB1[l]   = (flRGB1[l] + stepVal[l]);
      } 
      else
      {
        newRGB[l] = int(flRGB1[l] - stepVal[l]);
        flRGB1[l]   = (flRGB1[l] - stepVal[l]);
      }

    }

    Serial.print  ("origRGB1 is: ");
    Serial.print  (" ");
    Serial.print (origRGB1[0]);
    Serial.print  (" ");
    Serial.print (origRGB1[1]);
    Serial.print  (" ");
    Serial.print (origRGB1[2]);
    Serial.println  (" ");

    Serial.print  ("origRGB2 is: ");
    Serial.print  (" ");
    Serial.print (origRGB2[0]);
    Serial.print  (" ");
    Serial.print (origRGB2[1]);
    Serial.print  (" ");
    Serial.print (origRGB2[2]);
    Serial.println  (" ");

    Serial.println  (" ");
    Serial.print  ("newRGB is: ");
    Serial.print  (" ");
    Serial.print (newRGB[0]);
    Serial.print  (" ");
    Serial.print (newRGB[1]);
    Serial.print  (" ");
    Serial.print (newRGB[2]);
    Serial.println  (" ");

    writeColour(newRGB);
    delay (slideTime);

  }

}


