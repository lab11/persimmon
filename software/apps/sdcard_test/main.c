#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrfx_power.h"
#include "nrf_gpiote.h"
#include "nrfx_gpiote.h"

// SPI
#include "nrf_spi_mngr.h"
#include "nrf_drv_spi.h"

// SoftDevice
#include "nrf_sdh.h"
#include "nrf_soc.h"

// TWI
#include "nrfx_twi.h"
#include "nrfx_twim.h"

// Clocks
#include "nrfx_rtc.h"
#include "nrf_drv_clock.h"

// Debug output
#include "SEGGER_RTT.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "persimmon.h"



/*-----------------------------------------------------------------------*/
/* SD card functions                                                     */
/*-----------------------------------------------------------------------*/

// RTC0 is used by SoftDevice, RTC1 is used by app_timer
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(2);

// Function starting the internal LFCLK XTAL oscillator
/*static void lfclk_config(void) {
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);
}*/

// Interrupt handler; currently not used
static void rtc_handler(nrfx_rtc_int_type_t int_type) {}

static void rtc_init(void) {

    // Initialize LFCLK if no SoftDevice available
    //lfclk_config();

    // Initialize RTC instance
    nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
    rtc_config.prescaler = 32; // Approximately 1000 Hz
    ret_code_t err_code = nrfx_rtc_init( &rtc_instance, &rtc_config, rtc_handler);
    APP_ERROR_CHECK(err_code);

    // Power on RTC instance
    nrfx_rtc_enable(&rtc_instance);
}


static bool sd_card_inserted() {

    // SD card inserted:    Pin connected to GND
    // SD card not present: Pin connected to VCC
    return !nrf_gpio_pin_read(SD_DETECT);
}

static void sd_card_init(void) {

    // Setup hardware
    nrf_gpio_cfg_input(SD_DETECT, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(SPI_MISO,  NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_output(SPI_MOSI);
    nrf_gpio_cfg_output(SPI_SCLK);
    nrf_gpio_cfg_output(SD_ENABLE);
    nrf_gpio_cfg_output(CS_SD);

    nrf_gpio_pin_set(SD_ENABLE);
    nrf_gpio_pin_set(CS_SD);

    // Initialize Real-time counter
    rtc_init();

    // Configs
    const char filename[] = "testfile.log";
    const char permissions[] = "a"; // w = write, a = append

    //printf("Waiting for SD card to be inserted...\n");

    // Wait for SC card
    while (!sd_card_inserted()) {};

    //printf("Detected SD card; trying to connect...\n");

    // Start file
    simple_logger_init(filename, permissions);

    // If no header, add it
    simple_logger_log_header("HEADER for file \'%s\', written on %s \n", filename, "08/23/18");
}

// Test SD card ----------------------------------------------------------------------------------------------------
//#define TEST_SD_CARD
#ifdef TEST_SD_CARD
printf("Testing SD card: ");

// Initialize
sd_card_init();

// Write sample lines
uint64_t nr_lines = 0;
uint64_t nr_bytes = 0;

uint8_t log_buf[1000] = { 0 };

while(true) {

    uint32_t current_time_stamp = nrfx_rtc_counter_get(&rtc_instance);
    sprintf(log_buf, "%li: Line %llu - Additional line added\n", current_time_stamp, nr_lines + 1);

    // Add bytes
    for (int16_t i = 0; i < 1000; i++) {

        if (log_buf[i] == '\0') {
            nr_bytes += i;
            break;
        }
    }

    // Write
    simple_logger_log("%s", log_buf);
    printf("Bytes written: %llu; line: %llu\n", nr_bytes, nr_lines);


    nr_lines++;
}

printf("OK\r\n");
#endif
