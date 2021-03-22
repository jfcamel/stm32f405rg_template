#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "static_tasks.h"

#define STACK_SIZE1 200
#define STACK_SIZE2 200

TaskHandle_t task1;
StackType_t stack1[ STACK_SIZE1 ];
StaticTask_t taskBuffer1;

TaskHandle_t task2;
StackType_t stack2[ STACK_SIZE2 ];
StaticTask_t taskBuffer2;

void task_init_tasks(void)
{
  task1 = xTaskCreateStatic((TaskFunction_t)task_function1,
                            "task1",
                            (const uint32_t)STACK_SIZE1,
                            NULL,
                            0,
                            stack1,
                            &taskBuffer1);

  task2 = xTaskCreateStatic((TaskFunction_t)task_function2,
                            "task1",
                            (const uint32_t)STACK_SIZE2,
                            NULL,
                            5,
                            stack2,
                            &taskBuffer2);
}

void task_function1(void* args)
{
  while (1) {
    printf(" ,low priority...\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void task_function2(void* args)
{
  while (1) {
    printf("high priority task\n");
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}
