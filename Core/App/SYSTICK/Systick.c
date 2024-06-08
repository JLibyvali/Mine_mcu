#include "GPIO.h"

static __IO uint32_t TimingDelay;

/*************************************************************
 * @brief System timer, System timer is a counter.
 * when it equals 0, occurred interrupt, the MAX_VALUE = 2^24
 * Tdec = 1 / SYSCLK. INterrupt time: "ticks"/SYSCLK
 * 
 ************************************************************/


/**
  * @brief  Initializes the System Timer and its interrupt, and starts the System Tick Timer.
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb: Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
void SystickInit(void){

    // So the ticks: 72Mhz/10^5 = 720, 720/72Mhz = 10us.
    if(HAL_SYSTICK_Config(SystemCoreClock / 100000)){
        while (1) {
            // Error handler
        }
    }
}

/**
 * @brief Delay function, n * 10us
 * 
 * @param n 
 */
 void Delay_us(__IO uint32_t n){

    TimingDelay = n;    
    while (TimingDelay != 0);

 }

 /**
  * @brief Get the tick?
  * @ref  invoked in SysTick_Handler();
  * 
  */
 void TimingDelay_Dec(void){

    if(TimingDelay != 0x00){
        TimingDelay --;
    }

 }