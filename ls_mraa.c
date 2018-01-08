
/*
 * A draft of a simple `ls` of a board (tested on Raspberry Pi 3).
 *
 * Based on hellomraa.c by Brendan Le Foll <brendan.le.foll@intel.com>
 * (the present program is not endorsed by that author)
 */

#include <stdio.h>

#include "mraa/common.h"


int describe_board(void);   // defined at the end


int
main(int argc, char** argv)
{

    mraa_result_t ret = MRAA_SUCCESS;

    mraa_set_log_level(7);    // set debug-level to ultra-verbose

    mraa_platform_t platform_type = mraa_get_platform_type();

    if (platform_type != MRAA_RASPBERRY_PI) {
        fprintf(stderr, "Error: This program is only for Raspberry Pi\n");
        ret = MRAA_ERROR_INVALID_PLATFORM;
        goto end;
    }

    ret = describe_board();

end:
    if (ret != MRAA_SUCCESS)
       mraa_result_print(ret);

    mraa_deinit();

    return ret;
}


int
describe_board(void)
{
    const char* board_name = mraa_get_platform_name();

    board_name = ( board_name ) ? board_name : "UNKNOWN";

    const char* main_platform_version = mraa_get_platform_version(0);

    main_platform_version = ( main_platform_version ) ? main_platform_version :
                                                       "UNKNOWN";

    const char* sub_platform_version = mraa_has_sub_platform() ?
                                           mraa_get_platform_version(1) :
                                           "NO SUBPLATFORM";

    int pin_count = mraa_get_pin_count();
    int uart_count = mraa_get_uart_count();
    int pwm_count = mraa_get_pwm_count();
    int gpio_count = mraa_get_gpio_count();
    int i2c_bus_count = mraa_get_i2c_bus_count();

    printf((
               "MRAA\n Version: %s\n"
               " Running on %s\n"
               " MainPlatformVersion: %s\n"
               " SubPlatformVersion: %s\n"
               " Pins: %d\n"
               " UARTs: %d\n"
               " PWM pins: %d\n"
               " GPIO pins: %d\n"
               " I2C buses: %d\n"
           ),
           mraa_get_version(),
           board_name,
           main_platform_version,
           sub_platform_version,
           pin_count,
           uart_count,
           pwm_count,
           gpio_count,
           i2c_bus_count);

    printf(" Pin names:\n");
    for (int pin_idx=1; pin_idx <= pin_count; pin_idx++) {
        const char* pin_name = mraa_get_pin_name(pin_idx);
        pin_name = (pin_name) ? pin_name : "UNKNOWN";

        const char * pin_platform = mraa_is_sub_platform_id(pin_idx) ?
                                           "SUB" : "MAIN" ;

        char pin_platform_description[64];

        snprintf(pin_platform_description,
                 sizeof(pin_platform_description),
                 "pin index relative to %s platform = %3d",
                 pin_platform,
                 mraa_get_sub_platform_index(pin_idx)
                );


        printf("  Pin %3d: %-10s (%s)\n",
               pin_idx, pin_name, pin_platform_description);
    }

    return MRAA_SUCCESS;
}


