// SD card app
//
// Writes sample lines to the SD card on Buckler

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "nrf.h"
#include "nrf_sdh.h"
#include "nrf_soc.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "persimmon.h"
#include "simple_logger.h"

static bool sd_card_inserted() {

    // SD card inserted:    Pin connected to GND
    // SD card not present: Pin connected to VCC
    return !nrf_gpio_pin_read(SD_DETECT);
}

int main(void) {

  ret_code_t error_code = NRF_SUCCESS;
  printf("Started SD card demo app...\n");
  // Enable SoftDevice (used to get RTC running)
  nrf_sdh_enable_request();
  printf("enabled");

  // Initialize GPIO driver
  if (!nrfx_gpiote_is_init()) {
  error_code = nrfx_gpiote_init();
}
  APP_ERROR_CHECK(error_code);

  // Configure GPIOs
  nrf_gpio_cfg_output(SD_ENABLE);
  nrf_gpio_cfg_output(CS_SD);
  nrf_gpio_cfg_output(SPI_MOSI);
  nrf_gpio_cfg_output(SPI_SCLK);
  nrf_gpio_cfg_input(SPI_MISO, NRF_GPIO_PIN_NOPULL);

  nrf_gpio_pin_set(SD_ENABLE);
  nrf_gpio_pin_set(CS_SD);

  // Initialize SD card

  if (sd_card_inserted() == 1) {
    printf("sd card not inserted%d\n");
  }

  const char filename[] = "testfile.log";
  // printf(filename);
  const char permissions[] = "a"; // w = write, a = append

  printf("initialized sd card");
  // Start file

  simple_logger_init(filename, permissions);
  printf("started file");

  // If no header, add it
  simple_logger_log_header("HEADER for file \'%s\', written on %s \n", filename, "DATE");
  printf("Wrote header to SD card\n");

  // Write sample lines
  int nr_lines = 5;

  for (int i = 0; i < nr_lines; i++) {
    simple_logger_log("%s: Line %i - Additional line added\n", "TIMESTAMP", i+1);
    printf("Wrote line to SD card\n");
  }

  // Signal that lines were written
  nrf_gpio_cfg_output(LED_1);
  nrf_gpio_pin_clear(LED_1);
}
