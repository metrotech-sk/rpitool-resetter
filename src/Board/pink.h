#ifndef __PINK_H
#define __PINK_H


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// For board detection
#define PINK_BOARD

// --- UART ---
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#endif
// no PICO_DEFAULT_WS2812_PIN

// --- I2C ---
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 4 
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif

// --- SPI ---
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif
#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 6
#endif
#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 7
#endif
#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 8
#endif
#ifndef PICO_DEFAULT_SPI_CSN_PIN
#define PICO_DEFAULT_SPI_CSN_PIN 9
#endif

// --- FLASH ---
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SPI_CLKDIV
/**
 * @brief 
 * 
 * This is critical for some flash chips, and can be set to 4 for some, but needs to be at least 32 for others.
 * @note Increasing this value will help with BOOTLOOPs, but will slow down the flash chip.
 */
#define PICO_FLASH_SPI_CLKDIV 128  // this will be rock solid
#endif // !PICO_FLASH_SPI_CLKDIV

#ifndef PICO_XOSC_STARTUP_DELAY_MULTIPLIER
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 32
#endif // !PICO_XOSC_STARTUP_DELAY_MULTIPLIER

#ifndef PICO_FLASH_SIZE_BYTES
/**
 * @brief 16MiB, Flash size in bytes
 * 
 * This is the size of the flash chip on the board, not the size of the flash chip that is used for the bootloader.
 */
#define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)
#endif // !PICO_FLASH_SIZE_BYTES

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED 
#define PICO_RP2040_B0_SUPPORTED  0
#endif // !PICO_RP2040_B0_SUPPORTED


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __PINK_H