
// Example for the MCP49x1 *single* DACs
// For the dual MCP49x2 series, see the other bundled example sketch.
//

#include <SPI.h>         // Remember this line!
#include <DAC_MCP49xx.h>

// The Arduino pin used for the slave select / chip select
#define SS_PIN1 7
#define SS_PIN2 6
#define SS_PIN3 5
#define SS_PIN4 4
#define SS_PIN5 3

#define D1 8
#define D2 9
#define D3 2

#define LOWSIG_1 75 //0.82 V
#define LOWSIG_2 75
#define LOWSIG_3 75
#define LOWSIG_4 75
#define LOWSIG_5 75

#define HIGHSIG_1 144
#define HIGHSIG_2 132 //1.79V
#define HIGHSIG_3 140 
#define HIGHSIG_4 136
#define HIGHSIG_5 170

// Set up the DAC. 
// First argument: DAC model (MCP4901, MCP4911, MCP4921)
// Second argument: SS pin (10 is preferred)
// (The third argument, the LDAC pin, can be left out if not used)
DAC_MCP49xx dac1(DAC_MCP49xx::MCP4901, SS_PIN1);
DAC_MCP49xx dac2(DAC_MCP49xx::MCP4901, SS_PIN2);
DAC_MCP49xx dac3(DAC_MCP49xx::MCP4901, SS_PIN3);
DAC_MCP49xx dac4(DAC_MCP49xx::MCP4901, SS_PIN4);
DAC_MCP49xx dac5(DAC_MCP49xx::MCP4901, SS_PIN5);



void setup() {
  // Set the SPI frequency to 1 MHz (on 16 MHz Arduinos), to be safe.
  // DIV2 = 8 MHz works for me, though, even on a breadboard.
  // This is not strictly required, as there is a default setting.
 
  dac1.setSPIDivider(SPI_CLOCK_DIV16);
  dac2.setSPIDivider(SPI_CLOCK_DIV16);
  dac3.setSPIDivider(SPI_CLOCK_DIV16);
  dac4.setSPIDivider(SPI_CLOCK_DIV16);
  dac5.setSPIDivider(SPI_CLOCK_DIV16);

  dac1.setPortWrite(false);
  dac2.setPortWrite(false);
  dac3.setPortWrite(false);
  dac4.setPortWrite(false);
  dac5.setPortWrite(false);

 
  pinMode(D1, INPUT); 
  pinMode(D2, INPUT); 
  pinMode(D3, INPUT); 

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
 // SPI.setClockDivider(spi_divider);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}


void loop() {

  bool b1 = digitalRead(D1);
  bool b2 = digitalRead(D2);
  bool b3 = digitalRead(D3);

  
//  Serial.println(b1);
//  Serial.println(b2);
//  Serial.println(b3);
//  Serial.println("--s--"); 

 if        ( b1 == 1 && b2 == 0 && b3 == 0) { 
    // PARK
    Serial.println("PARK"); // For Serial Debugging only
    dac1.output(HIGHSIG_1);
    dac2.output(LOWSIG_2);
    dac3.output(HIGHSIG_3);
    dac4.output(LOWSIG_4);
    dac5.output(LOWSIG_5);
   
  } else if (b1 == 0 && b2 == 1 && b3 == 0) {
  
    // REVERSE
    Serial.println("REVERSE"); // For Serial Debugging only
    dac1.output(LOWSIG_1);
    dac2.output(HIGHSIG_2);
    dac3.output(HIGHSIG_3);
    dac4.output(LOWSIG_4);
    dac5.output(HIGHSIG_5); 
  } else if (b1 == 1 && b2 == 1 && b3 == 0) {
    // NEUTRAL
    Serial.println("NEUTRAL"); // For Serial Debugging only
    dac1.output(LOWSIG_1);
    dac2.output(HIGHSIG_2);
    dac3.output(LOWSIG_3);
    dac4.output(HIGHSIG_4);
    dac5.output(LOWSIG_5);
  } else if (b1 == 0 && b2 == 0 && b3 == 1) {
    // DRIVE
    Serial.println("DRIVE"); // For Serial Debugging only
    dac1.output(HIGHSIG_1);
    dac2.output(LOWSIG_2);
    dac3.output(LOWSIG_3);
    dac4.output(HIGHSIG_4);
    dac5.output(HIGHSIG_5);
  } else if (b1 == 1 && b2 == 0 && b3 == 1) {
    // MANUAL
    Serial.println("MANUAL"); // For Serial Debugging only
    dac1.output(HIGHSIG_1);
    dac2.output(LOWSIG_2);
    dac3.output(LOWSIG_3);
    dac4.output(HIGHSIG_4);
    dac5.output(LOWSIG_5);
    } else { 
    //if (b1 == 0 && b2 == 0 && b3 == 0) {
    // INBETWEEN
    Serial.println("BETWEEN"); // For Serial Debugging only
    dac1.output(LOWSIG_1);
    dac2.output(LOWSIG_2);
    dac3.output(LOWSIG_3);
    dac4.output(LOWSIG_4);
    dac5.output(LOWSIG_5);
  }
  delay(200); // For Serial Debugging only
  Serial.println("END!"); // For Serial Debugging only


}
