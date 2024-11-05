#ifndef _keyboard_conf_h_
#define _keyboard_conf_h_

#include <stdint.h>
#include "nrf_adc.h"
#include "config.h"

#ifdef KEYBOARD_60


#ifdef KEYBOARD_REVB  //BLE60 REVC

#define KEYBOARD_ADC NRF_ADC_CONFIG_INPUT_2
static const uint8_t column_pin_array[MATRIX_COLS] = {19,17,15,13,11,9,7,6,5,4,3,2,0,30};
static const uint8_t row_pin_array[MATRIX_ROWS] = {24,20,29,25,28};

#define LED_CAPS  18
#define LED_RGB   23
#define PIN_EXT1  16
#define PIN_EXT2  14
#define PIN_EXT3  12
#define PIN_EXT4  10

#define UART_TXD 22
#define UART_RXD 21

#define BOOTLOADER_BUTTON           8

#define LED_CHARGING                PIN_EXT1
#define LED_FULL                    PIN_EXT4
#define LED_BLE                     PIN_EXT2
#define LED_USR1                    PIN_EXT4

#define UPDATE_IN_PROGRESS_LED      PIN_EXT4
#define ADVERTISING_LED_PIN_NO      PIN_EXT4
#define CONNECTED_LED_PIN_NO        PIN_EXT4

#define LED_POSITIVE

#endif 
 
#ifdef KEYBOARD_REVC  //BLE60 REVC

#define KEYBOARD_ADC NRF_ADC_CONFIG_INPUT_3
static const uint8_t column_pin_array[MATRIX_COLS] = {30,28,24,22,21,13,14,15,16,17,18,19,20,0};
static const uint8_t row_pin_array[MATRIX_ROWS] = {29,25,23,4,3};

#define LED_CAPS  5
#define LED_RGB   8
#define PIN_EXT1  10
#define PIN_EXT2  11
#define PIN_EXT3  12
#define PIN_EXT4  1


#define UART_TXD 7
#define UART_RXD 6

#define BOOTLOADER_BUTTON           9

#define LED_CHARGING                PIN_EXT1
#define LED_FULL                    PIN_EXT4
#define LED_BLE                     PIN_EXT2
#define LED_USR1                    PIN_EXT4

#define UPDATE_IN_PROGRESS_LED      PIN_EXT4
#define ADVERTISING_LED_PIN_NO      PIN_EXT4
#define CONNECTED_LED_PIN_NO        PIN_EXT4

#define LED_POSITIVE

#endif

#ifdef KEYBOARD_REVD  //BLE60 REVD

#define KEYBOARD_ADC NRF_ADC_CONFIG_INPUT_3
static const uint8_t column_pin_array[MATRIX_COLS] = {30,28,24,22,21,10,11,12,13,14,15,16,17,18};
static const uint8_t row_pin_array[MATRIX_ROWS] = {29,25,23,4,3};


#define LED_RGB   8
#define PIN_EXT1  19
#define PIN_EXT2  20
#define PIN_EXT3  1
#define PIN_EXT4  0
#define PIN_EXT5  5

#define UART_TXD 7
#define UART_RXD 6

#define BOOTLOADER_BUTTON           9

#define LED_CAPS                    PIN_EXT1
#define LED_CHARGING                PIN_EXT4 
#define LED_FULL                    PIN_EXT3
#define LED_BLE                     PIN_EXT2
#define LED_USR1                    PIN_EXT5

#define UPDATE_IN_PROGRESS_LED      PIN_EXT5
#define ADVERTISING_LED_PIN_NO      PIN_EXT5
#define CONNECTED_LED_PIN_NO        PIN_EXT5

#define LED_POSITIVE

#endif

#ifdef LED_POSITIVE
    #define LED_SET(x) nrf_gpio_pin_set(x)
    #define LED_CLEAR(x) nrf_gpio_pin_clear(x)
    #define LED_WRITE(x,b) nrf_gpio_pin_write(x,b)
#else
    #define LED_SET(x) nrf_gpio_pin_clear(x)
    #define LED_CLEAR(x) nrf_gpio_pin_set(x)
    #define LED_WRITE(x,b) nrf_gpio_pin_write(x,!(b))
#endif

#endif  // KEYBOARD_60

#ifdef KEYBOARD_MODELM

#ifdef KEYBOARD_REV0  // MODEL M PCB REV 0
#define KEYBOARD_ADC NRF_ADC_CONFIG_INPUT_3
static const uint8_t column_pin_array[MATRIX_COLS] = {21,22,23,24,25,28,28,30,0,1,2,3,4,5,6,7};
static const uint8_t row_pin_array[MATRIX_ROWS] = {15,14,13,12,11,10,9,8};


#define LED_NUML  16
//#define PIN_EXT1  19
//#define PIN_EXT2  20
//#define PIN_EXT3  1
//#define PIN_EXT4  0
//#define PIN_EXT5  5

#define UART_TXD 18     // shared with LED_SL
#define UART_RXD 17     // shared with LED_CL

#define BOOTLOADER_BUTTON           20  // button to GND

#define LED_CAPS                    LED_NUML
//#define LED_CHARGING                PIN_EXT4 
//#define LED_FULL                    PIN_EXT3
//#define LED_BLE                     PIN_EXT2
//#define LED_USR1                    PIN_EXT5

/* used on bootloader */
#define UPDATE_IN_PROGRESS_LED      LED_NUML
#define ADVERTISING_LED_PIN_NO      LED_NUML
#define CONNECTED_LED_PIN_NO        LED_NUML

#define LED_POSITIVE
#endif  // KEYBOARD_REV0

#ifdef LED_POSITIVE
    #define LED_SET(x) nrf_gpio_pin_set(x)
    #define LED_CLEAR(x) nrf_gpio_pin_clear(x)
    #define LED_WRITE(x,b) nrf_gpio_pin_write(x,b)
#else
    #define LED_SET(x) nrf_gpio_pin_clear(x)
    #define LED_CLEAR(x) nrf_gpio_pin_set(x)
    #define LED_WRITE(x,b) nrf_gpio_pin_write(x,!(b))
#endif

#endif  // KEYBOARD_MODELM

#endif
