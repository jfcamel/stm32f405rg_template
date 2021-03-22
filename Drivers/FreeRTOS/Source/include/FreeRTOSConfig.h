#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;

#ifndef configUSE_PORT_OPTIMISED
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#endif
#ifndef configUSE_PREEMPTION
#define configUSE_PREEMPTION			1
#endif
#ifndef configUSE_IDLE_HOOK
#define configUSE_IDLE_HOOK				1
#endif
#ifndef configUSE_TICK_HOOK
#define configUSE_TICK_HOOK				1
#endif
#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ				( SystemCoreClock )
#endif
#ifndef configTICK_RATE_HZ
#define configTICK_RATE_HZ				( ( TickType_t ) 400 )
#endif
#ifndef configMAX_PRIORITIES	
#define configMAX_PRIORITIES			( 5 )
#endif
#ifndef configMINIMAL_STACK_SIZE
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 130 )
#endif
#ifndef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 75 * 1024 ) )
#endif
#ifndef configMAX_TASK_NAME
#define configMAX_TASK_NAME_LEN			( 10 )
#endif
#ifndef configUSE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY		1
#endif
#ifndef configUSE_16_BIT
#define configUSE_16_BIT_TICKS			0
#endif
#ifndef configIDLE_SHOULD_YIELD
#define configIDLE_SHOULD_YIELD			1
#endif
#ifndef configUSE_MUTEXES	
#define configUSE_MUTEXES				1
#endif
#ifndef configQUEUE_REGISTRY_SIZE
#define configQUEUE_REGISTRY_SIZE		8
#endif
#ifndef configCHECK_FOR_STACK
#define configCHECK_FOR_STACK_OVERFLOW	2
#endif
#ifndef configUSE_RECURSIVE_MUTEXES
#define configUSE_RECURSIVE_MUTEXES		1
#endif
#ifndef configUSE_MALLOC_FAILED
#define configUSE_MALLOC_FAILED_HOOK	1
#endif
#ifndef configUSE_APPLICATION_TASK
#define configUSE_APPLICATION_TASK_TAG	0
#endif
#ifndef configUSE_COUNTING_SEMAPHORES
#define configUSE_COUNTING_SEMAPHORES	1
#endif
#ifndef configGENERATE_RUN_TIME
#define configGENERATE_RUN_TIME_STATS	0
#endif
#ifndef configSUPPORT_STATIC_ALLOCATION
#define configSUPPORT_STATIC_ALLOCATION  0
#endif
#ifndef configSUPPORT_DYNAMIC_ALLOCATION
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#endif

/* Co-routine definitions. */
#ifndef configUSE_CO_ROUTINES
#define configUSE_CO_ROUTINES 		0
#endif
#ifndef configMAX_CO_ROUTINE
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )
#endif

/* Software timer definitions. */
#define configUSE_TIMERS				0
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
