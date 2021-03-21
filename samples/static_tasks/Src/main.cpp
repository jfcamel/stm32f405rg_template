#include <stdio.h>
#include <stdint.h>

#include <stm32f4xx.h>

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "static_tasks.h"

#define STACK_SIZE_IDLE 200
StackType_t idleTaskStack[ STACK_SIZE_IDLE ];
StaticTask_t idleTaskBuffer;

void vApplicationInit(void)
{
  printf("configTICK_RATE_HZ=%d\n", (uint16_t)configTICK_RATE_HZ);
  printf("configCPU_CLOCK_HZ=%ld\n", (uint32_t)configCPU_CLOCK_HZ);
  printf("configUSE_PREEMPTION=%d\n", (uint16_t)configUSE_PREEMPTION);
}

void vApplicationTickHook( void )
{
  // printf(".");
}

void vApplicationMallocFailedHook( void )
{
  taskDISABLE_INTERRUPTS();
  for( ;; );
}

void vApplicationIdleHook( void )
{
  // printf(".");
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
  taskDISABLE_INTERRUPTS();
  for( ;; );
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = (StaticTask_t*)&idleTaskBuffer;
  *ppxIdleTaskStackBuffer = (StackType_t*)idleTaskStack;
  *pulIdleTaskStackSize = STACK_SIZE_IDLE;
}

void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_16, 200, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }
  LL_Init1msTick(100000000);
  LL_SetSystemCoreClock(100000000);
}

int main(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  vApplicationInit();

  task_init_tasks();

  vTaskStartScheduler();
  while (1)
  {
    printf("hello world\n");
  }
}
