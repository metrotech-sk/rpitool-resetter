#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "pico/stdlib.h"


constexpr uint64_t MINUTES = 60;
constexpr uint64_t HOURS = 60 * MINUTES;
constexpr uint64_t DAYS = 24 * HOURS;
constexpr uint64_t WEEKS = 7 * DAYS;
constexpr uint64_t MONTHS = 30 * DAYS;
constexpr uint64_t YEARS = 365 * DAYS;

// Normally opened GPIO
#define GPIO_NO 26
// Normally closed GPIO
#define GPIO_NC 29


/**
 * @brief Disable clocks to save power
 * 
 * @param adc ADC clock
 * @param usb USB clock
 * @param peri Peripheral clock Peripheral clock for UART and SPI.
 * @param rtc Real time clock
 */
void disable_clocks(bool adc = true, bool usb = true, bool peri = true, bool rtc = true)
{
    // Disable ADC
    if (adc)
    {
        clock_stop(clk_adc);
    }

    // Disable USB
    if (usb)
    {
        clock_stop(clk_usb);
        // stop USB PLL to save even more power
    }

    // Disable peripheral clock
    if (peri)
    {
        clock_stop(clk_peri);
    }

    // Disable RTC
    if (rtc)
    {
        clock_stop(clk_rtc);
    }
}


/**
 * @brief Lower clock speed to save power
 * 
 * Lower clock speed to 12 MHz and disable system and USB PLL to save most of the power.
 * 
 */
void lower_clock_speed()
{
    // Set clock speed to 12 MHz, switch to external oscillator
    clock_configure(
        clk_sys, // system clock
        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF, // main source
        0, // aux source - not used
        12 * MHZ, // source clock
        12 * MHZ // target clock
    );

    // Disable system and USB PLL to save even more power
    pll_deinit(pll_sys);
    pll_deinit(pll_usb);
}


int main()
{
    stdio_init_all();

    // Set the LED and other pins to output
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_init(GPIO_NO);
    gpio_init(GPIO_NC);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_set_dir(GPIO_NO, GPIO_OUT);
    gpio_set_dir(GPIO_NC, GPIO_OUT);

    // Set normally opened GPIO to 0 and normally closed GPIO to 1
    gpio_put(GPIO_NO, 0);
    gpio_put(GPIO_NC, 1);

    // Disable clocks and lower clock speed
    disable_clocks();
    lower_clock_speed();

    // Seconds counter
    uint64_t seconds = 0;

    // Blink the LED
    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(10);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(990);

        seconds++;

        // if seconds counter reached 15 minutes
        if (seconds == 15 * MINUTES)
        {
            // reset seconds counter
            seconds = 0;

            // turn on normally opened GPIO and turn off normally closed GPIO
            gpio_put(GPIO_NO, 1);
            gpio_put(GPIO_NC, 0);
            sleep_ms(1000);
            // turn off normally opened GPIO and turn on normally closed GPIO
            gpio_put(GPIO_NO, 0);
            gpio_put(GPIO_NC, 1);
        }
    }
}