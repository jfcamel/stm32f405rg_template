#ifndef __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"

#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007)
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006)
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005)
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004)
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003)
#endif


  void SystemClock_Config(void);
  void vApplicationInit(void);
  void vApplicationTickHook( void );
  void vApplicationIdleHook( void );
  void vApplicationMallocFailedHook( void );
  void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
  void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
