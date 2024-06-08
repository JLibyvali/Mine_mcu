#include "GPIO.h"


/**
 * @brief Just set different RCC clock source, and drive the LED
 * 
 */

// different rcc source
void clockHSI(void);
void clockHSE(void);

void DelayN(__IO uint32_t n)
{
    for (; n != 0; n--);

    return;
}


/**
 * @brief set HSI or HSE as RCC source
 *
 */
void Prac_clockSource(void)
{
    HAL_Init();

    while (1) {
        HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        DelayN(0x80000);
    }

}


void clockHSI(void)
{

    RCC_OscInitTypeDef RCC_OscInit = {0};
    RCC_ClkInitTypeDef RCC_ClkInit = {0};

    // Initialize rcc_oscinit
    RCC_OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInit.HSIState       = RCC_HSI_ON;

    RCC_OscInit.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInit.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInit.PLL.PLLSource       = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInit.PLL.PLLMUL          = RCC_PLLMUL_16; // 16 multiply

    if (HAL_RCC_OscConfig(&RCC_OscInit) != HAL_OK)
        while (1);

    // Initialize rcc-clkinit
    RCC_ClkInit.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInit.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInit.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInit.APB1CLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInit.APB2CLKDivider = RCC_SYSCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInit, FLASH_LATENCY_2) != HAL_OK)
        while (1);  // Error handling
}

void clockHSE(void)
{

    RCC_OscInitTypeDef RCC_OscInit = {0};
    RCC_ClkInitTypeDef RCC_ClkInit = {0};

    // Initialize rcc_oscinit
    RCC_OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInit.HSEState       = RCC_HSE_ON;

    RCC_OscInit.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInit.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInit.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInit.PLL.PLLMUL     = RCC_PLL_MUL9; // 9 multiply

    if (HAL_RCC_OscConfig(&RCC_OscInit) != HAL_OK)
        while (1);

    // Initialize rcc-clkinit
    RCC_ClkInit.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInit.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInit.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInit.APB1CLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInit.APB2CLKDivider = RCC_SYSCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInit, FLASH_LATENCY_2) != HAL_OK)
        while (1);  // Error handling
}