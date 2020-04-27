#include "MAX31856.h"
// The power requirement for the board is less than 2mA.  Most microcontrollers can source or sink a lot more
// than that one each I/O pin.  For example, the ATmega328 supports up to 20mA.  So it is possible to power the
// board using I/O pins for power - so you can turn the board on and off (if you want to).
// FAULT and DRDY are not used by the library (see above)
#define SCK    13
#define CS     10
#define SDI    11
#define SDO    12

// MAX31856 Initial settings (see MAX31856.h and the MAX31856 datasheet)
// The default noise filter is 60Hz, suitable for the USA
#define CR0_INIT  (CR0_AUTOMATIC_CONVERSION + CR0_OPEN_CIRCUIT_FAULT_TYPE_K /* + CR0_NOISE_FILTER_50HZ */)
#define CR1_INIT  (CR1_AVERAGE_2_SAMPLES + CR1_THERMOCOUPLE_TYPE_T)
#define MASK_INIT (~(MASK_VOLTAGE_UNDER_OVER_FAULT + MASK_THERMOCOUPLE_OPEN_FAULT))

MAX31856 *temperature;

void setup() {
  // Display temperatures using the serial port
  Serial.begin(115200);
  delay(3000);
  Serial.println("MAX31856 Sample application");
  
  // Define the pins used to communicate with the MAX31856
  temperature = new MAX31856(SDI, SDO, CS, SCK);
  
  // Initializing the MAX31855's registers
  temperature->writeRegister(REGISTER_CR0, CR0_INIT);
  temperature->writeRegister(REGISTER_CR1, CR1_INIT);
  temperature->writeRegister(REGISTER_MASK, MASK_INIT);
  
  // Wait for the first sample to be taken
  delay(200);
}

void loop () {
  float t1,t2;
  
  // Display the junction (IC) temperature
  // Sometimes the junction temperature is not provided until a thermocouple is attached
  t1 = temperature->readJunction(CELSIUS);
  Serial.print("Junction (IC) temperature =");
  printTemperature(t1);


  // Display the thermocouple temperature
  t2 = temperature->readThermocouple(CELSIUS);
  Serial.print("  Thermocouple temperature = ");
  printTemperature(t2);

  if(t1<0 || t2<0)
  {
    Serial.print("I = 1");
    
    }
    else
    {
      Serial.print("I = 0");
      }
  
  Serial.println();
  delay(1000);
}


// Print the temperature, or the type of fault
void printTemperature(double temperature) {
  switch ((int) temperature) {
    case FAULT_OPEN:
      Serial.print("FAULT_OPEN");
      break;
    case FAULT_VOLTAGE:
      Serial.print("FAULT_VOLTAGE");
      break;
    case NO_MAX31856:
      Serial.print("NO_MAX31856");
      break;
    default:
      Serial.print(temperature);
      break;
  }
  Serial.print(" ");
}
