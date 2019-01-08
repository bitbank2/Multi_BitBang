#include <Multi_BitBang.h>

#define NUM_BUSES 4
// I2C bus info
uint8_t scl_list[NUM_BUSES] = {0xb5,0xb5,0xb5,0xb5}; //{9,9,9,9};
uint8_t sda_list[NUM_BUSES] = {0xc6, 0xd7, 0xe6, 0xb4}; //{5,6,7,8};
int32_t speed_list[NUM_BUSES] = {400000L, 400000L, 400000L, 400000L};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
} // setup

void loop() {
  // put your main code here, to run repeatedly:
uint8_t i, j, bit, map[16];
uint8_t addr;
char szTemp[16];

  Multi_I2CInit(sda_list, scl_list, speed_list, NUM_BUSES);

  for (i=0; i<NUM_BUSES; i++)
  {
    Serial.print("Scanning I2C bus ");
    Serial.println(i);
    Multi_I2CScan(i, map);
    for (j=0; j<16; j++)
    {
      if (map[j] != 0) // device(s) found
      {
        for (bit=0; bit < 8; bit++)
        {
          if (map[j] & (1<<bit)) // device here
          {
            addr = (j*8) + bit;
            Serial.print("Device found at address 0x");
            Serial.println(addr, HEX);
          }
        }
      }
    }
  } // for each bus

  delay(5000);  
} // loop
