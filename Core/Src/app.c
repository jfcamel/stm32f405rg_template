#include "app.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>


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
  printf(".");
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
