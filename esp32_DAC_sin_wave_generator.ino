int i = 0;
int f;
int N, Fs;
double T, Ts;
double y = 0;
float Max_vdc;
float V_peak;
int Resolution;
float V_peak_bits;
float DC_offset, Amplitude;

void setup() {

  
  Serial.begin(115200);
  //Signal frequency and period
  f = 60;
  
  //Sampling frequency and sample period
  Fs = 32400;
  Ts = 1.0 / Fs;
  
  //Number of samples
  N = Fs / f;


  
  //Esp32 DAC resolution
  Resolution = 255;

  //Max voltage output wanted
  V_peak = 1.1;  //1.1 to read on ESP32 ADC with 0dB attenuation
  Max_vdc = 3.3; //System Vdc

  //Convert Voutput to Bits  
  V_peak_bits = Resolution * V_peak / Max_vdc;
  //Offset the wave to oscillate between 0 ~ 1.1V
  DC_offset = V_peak_bits / 2;

  //Signal amplitude
  Amplitude = DC_offset;


   // Vp |            *  *                                    
   //    |         *        *                               
   //    |      *              *                             
   //    |    *                  *                          
   //    |   *                     *                      
   //    |  *                       *                    
   // DC | *-----------------------------------------------------------
   //    |                            *                        *
   //    | |   |                       *                      *
   //    | +---+                        *                    *  
   //    |  Ts                            *                *  
   //    |                                  *            *
   //    |                                    *        *
   //    | |                                     *  *          |
   //    | +---------------------------------------------------+
   //                                       1/f
}

void loop() {

  y = 35 * sin(2 * PI * f * Ts * i) + DC_offset; 
  dacWrite(25, y);
  // Functions delay is about 16 us
  delayMicroseconds((Ts * 1000000) - 16);
  i++;
  if (i >= N) i = 0;

}
