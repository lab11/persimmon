// Pin definitions for nRF52 development kit (PCA10040)

#pragma once

#include "nrf_gpio.h"

// LED
#define LEDS_NUMBER 3
#define LEDS_ACTIVE_STATE 0
#define LED_1 NRF_GPIO_PIN_MAP(0,4)
#define LED_2 NRF_GPIO_PIN_MAP(0,5)
#define LED_3 NRF_GPIO_PIN_MAP(0,6)
#define LEDS_INV_MASK LEDS_MASK
#define LEDS_LIST { LED_1, LED_2, LED_3 }
#define BSP_LED_0 LED_1
#define BSP_LED_1 LED_2
#define BSP_LED_2 LED_3

// BUTTONS
#define BUTTONS_NUMBER 0
#define BUTTON_PULL 0

// UART
#define UART_TXD NRF_GPIO_PIN_MAP(1,15)
#define UART_RXD NRF_GPIO_PIN_MAP(1,13)

// GPS
#define GPS_RXD NRF_GPIO_PIN_MAP(0,7)
#define GPS_TXD NRF_GPIO_PIN_MAP(0,8)
#define GPS_PWR_EN NRF_GPIO_PIN_MAP(0,19)

// SPI
#define SPI_MISO NRF_GPIO_PIN_MAP(0,15)
#define SPI_MOSI NRF_GPIO_PIN_MAP(0,13)
#define SPI_SCLK NRF_GPIO_PIN_MAP(0,27)


#define CS_SD NRF_GPIO_PIN_MAP(0,20)
#define SD_DETECT NRF_GPIO_PIN_MAP(1,0)
#define SD_ENABLE NRF_GPIO_PIN_MAP(0,14)

// Hardware Watchdog
#define HW_WDI NRF_GPIO_PIN_MAP(0,11)
#define EXT_RST NRF_GPIO_PIN_MAP(0,24)

// Multiplexers
#define MUX_EN NRF_GPIO_PIN_MAP(0,17)
#define MUX_SEL1 NRF_GPIO_PIN_MAP(1,9)
#define MUX_SEL2 NRF_GPIO_PIN_MAP(0,25)

// Radio
#define GSM_CTS NRF_GPIO_PIN_MAP(0,2)
#define GSM_POWER NRF_GPIO_PIN_MAP(0,3)
#define GSM_RTS NRF_GPIO_PIN_MAP(0,28)
#define GSM_RST NRF_GPIO_PIN_MAP(0,29)
#define GSM_RX NRF_GPIO_PIN_MAP(0,30)
#define GSM_TX NRF_GPIO_PIN_MAP(0,31)

#define BATIN NRF_GPIO_PIN_MAP(1,6)

#define NRF_RST NRF_GPIO_PIN_MAP(0,18)

//compatbility with softdevice

#define SD_CARD_ENABLE      SD_ENABLE
#define SD_CARD_SPI_CS      CS_SD
#define SD_CARD_SPI_MISO    SPI_MISO
#define SD_CARD_SPI_MOSI    SPI_MOSI
#define SD_CARD_SPI_SCLK    SPI_SCLK

#define SD_CARD_SPI_INSTANCE    NRF_SPI1

//RTC
#define RTC_CS      NRF_GPIO_PIN_MAP(0,12)
#define RTC_IRQ1    NRF_GPIO_PIN_MAP(0,16)
#define RTC_IRQ2    NRF_GPIO_PIN_MAP(0,0)
#define RTC_IRQ3    NRF_GPIO_PIN_MAP(0,0)
#define RTC_WDI     NRF_GPIO_PIN_MAP(0,0)
