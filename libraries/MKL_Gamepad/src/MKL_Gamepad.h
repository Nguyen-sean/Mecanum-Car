#ifndef MKL_Gamepad_SEAN__
#define MKL_Gamepad_SEAN__

#include "kxnTask.h"


#include <Wire.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Default_Pin_CE 9
#define Default_Pin_CSN 10

// #endif

#include "MKL_Gamepad_NRF24.h"


// uint8_t I2C_ADDRESS = 0x6C; // I2C address
uint8_t I2C_ADDRESS = 0x08;

#include "MKL_Gamepad_TX.h"
#include "MKL_Gamepad_RX.h"
#include "MKL_Gamepad_I2C_device.h"



#endif