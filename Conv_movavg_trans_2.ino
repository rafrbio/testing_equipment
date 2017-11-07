#define length_array 100 // number of elements stored in the array
#define length_avg 10// number of averaged elements
int analogPin=4; // pin from which a voltage value is read and then converted by the ADC
int read_value=0; // value read after the conversion
int i=0; // counter used in for loops;
float var1[length_array]; // floating point array which will be sent to pc
float var2[length_array]; // floating point array which will be sent to pc
float var3[length_array]; // floating point array which will be sent to pc
float var4[length_array]; // floating point array which will be sent to pc

void setup() {
 Serial.begin(9600); // start the serial data transmission at baudrate 9600 bps
}

void loop() {
  // ------------- This part tests the 2 functions for data conversion ----------
  for (i=0; i<length_array; i++) {
    read_value = analogRead(analogPin); // read an analog value from the selected pin
    var1[i]=inputToFrequency(read_value); // store the float value obtained by the function
    var1[i]=frequencyToConcentration(var1[i]); // conversion from frequency to concentration (coefficients to be defined after sensor testing)
    arduino2pcSingleValue(var1,i);
    var2[i]=movingAverage(var1,length_avg,i);
    arduino2pcSingleValue(var2,i);
    var3[i]=inputToFrequency(read_value); 
    var3[i]=frequencyToConcentration(var3[i]);
    var3[i]=var3[i]*3;
    arduino2pcSingleValue(var3,i);
    var4[i]=movingAverage(var3, length_avg, i);
    arduino2pcSingleValue(var4,i);
    delay(5);
    
  }
  // -------------- This part tests the data transfer function --------
 // arduino2pc4ch(var1,var2,var3,var4);
}
//
// ------------------ Moving average function
float movingAverage(float input[], int num_elem, int index)
{
  float avg=0;
  int counter=0;
  float sum=0;
  if (index < num_elem)
  {
    avg=input[index]; // if we have not enough elements we don't compute the average
  }
  else
  {
    for (counter=0; counter<num_elem; counter++) 
    {
      sum+=input[index-counter];
    }
    avg=sum/num_elem;
  }
  return avg;
}
//
// ------------------ Function for data transmission ---------------
void arduino2pc4ch(float data1[],float data2[],float data3[],float data4[])
{
   int counter=0;
   for (counter=0; counter<length_array; counter++) {
      Serial.println(data1[counter]); // send data through serial (data is of float type, thus it has 4 digit precision)
      delay(10); // delay introduced because when running the Matlab script it may happen that the first 2 or 3 value are all read at once, causing an error when running the script,
               // by introducing this delay the problem is avoided
      Serial.println(data2[counter]); // I'd like to have used a function like println(string) to send data 4 by 4 ,but I get error messages beacuse apparently it's not supported :-(
      delay(10);
      Serial.println(data3[counter]);
      delay(10);
      Serial.println(data4[counter]);
      delay(10);
   }
}
//
//INPUT TO FREQUENCY
float inputToFrequency (int input) {
  // define a proportionality factor, here set to 1
  float Factor=1;
  float out = float(input) ;
  out= Factor * out;
  return out;
}
//
//FREQUENCY TO CONCENTRATION
float frequencyToConcentration (float in_freq) {
  // define a calibration curve
  float a=2.06;
  float b=3.2;
  float out=in_freq*b+a;
  return out;
}

// a non linear calibration curve can be realised with an ‘if’ instruction linearising in small steps
// from experimental data.
//the conversion factors are here defined inside the functions


// ------------------ Function for single value of data transmission ---------------
void arduino2pcSingleValue(float data1[],int index)
{
    Serial.println(data1[index]); // send data through serial (data is of float type, thus it has 4 digit precision)
 //   delay(10); // delay introduced because when running the Matlab script it may happen that the first 2 or 3 value are all read at once, causing an error when running the script,
               // by introducing this delay the problem is avoided
}
//
