/**
 * @brief Minimal firmware to test building STM32CubeMX projects using CMake.
 *
 * This code remains mostly unchanged from the output of STM32CubeMX targeting
 * the NUCLEO-F042K6 development board featuring the STM32F042K6.
 *
 * - Code to initialize and toggle the green user LED has been added.
 * - Other generated files are left unmodified.
 *
 * @author  Windsor Schmidt. | https://github.com/windsorschmidt
 * @license MIT License. Contributions welcome.
 */

#include "stm32f0xx_hal.h"

void clock_config(void);
static void gpio_config(void);

int main(void) {
    HAL_Init(); /* Mixing snake-case and camel-case? Ninja please. */
    clock_config();
    gpio_config();
    while (1) {
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	HAL_Delay(200);
    }
}

void clock_config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /* The NUCLEO-F042K6 has no crystal on board; use the internal oscillator. */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
	while (1) {
	}
    }
    /* Configure the system peripheral clock tree. */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
	while (1) {
	}
    }
    /* Configure the SysTick hardware timer, used by the HAL for HAL_Delay(). */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void gpio_config(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    /* The peripheral bus clocks are not running at power-on. Enable them now. */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /* Set up GPIO for USART2 (connects to the USB virtual serial port). */
    GPIO_InitStruct.Pin = VCP_TX_Pin | VCP_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Set up GPIO for the green user LED at PB3 (GPIO port B, pin number 3) */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
