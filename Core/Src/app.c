#include "app.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

TaskHandle_t task1;
StackType_t stack1;
StaticTask_t buf;

void app_init(void) {
  printf("app initialization started\n");
  xTaskCreate((TaskFunction_t)app_process,
              "app task",
              1024,
              NULL,
              0,
              NULL
    );

  printf("app initialized\n");
}

void app_process(void) {
  for ( ;; )
  {
    printf("Hello world\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void vApplicationTickHook( void )
{
}

void vApplicationMallocFailedHook( void )
{
  taskDISABLE_INTERRUPTS();
  for( ;; );
}

void vApplicationIdleHook( void )
{
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
  taskDISABLE_INTERRUPTS();
  for( ;; );
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
}
  
