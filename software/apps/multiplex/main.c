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


int main(void) {

  ret_code_t error_code = NRF_SUCCESS;
  printf("start multiplexing test\n");
  // Enable SoftDevice (used to get RTC running)
  nrf_sdh_enable_request();
  printf("enabled");

  // Initialize GPIO driver
  if (!nrfx_gpiote_is_init()) {
  error_code = nrfx_gpiote_init();
}
  APP_ERROR_CHECK(error_code);

  // Configure GPIOs
  nrf_gpio_cfg_output(MUX_EN);
  nrf_gpio_cfg_output(MUX_SEL1);
  nrf_gpio_cfg_output(MUX_SEL2);

  nrf_gpio_pin_set(MUX_EN);
  //sim 3
  nrf_gpio_pin_set(MUX_SEL2);
  nrf_gpio_pin_clear(MUX_SEL1);
  //sim 2
  // nrf_gpio_pin_set(MUX_SEL1);
  //sim 1
  // nrf_gpio_pin_clear(MUX_SEL1);
  // nrf_gpio_pin_clear(MUX_SEL2);

  printf("mux gpios set");
}
