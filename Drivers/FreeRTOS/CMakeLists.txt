# CMakeLists.txt for FreeRTOS


set(FREERTOS_COMPILER "GCC")
set(FREERTOS_ARCH  "ARM_CM4F")

option(freertos_use_static_allocation "Use Static Allocation" OFF)
option(freertos_use_dynamic_allocation "Use Dynamic AllocatioN" ON)
option(freertos_use_queue "Use Queue" OFF)
option(freertos_use_stream_buffer "Use Stream buffer" OFF)
option(freertos_use_software_timer "Use software timer" OFF)
option(freertos_use_event_groups "Use event groups" OFF)
option(freertos_use_croutine "Use c routine" OFF)

set(FREERTOS_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Source/list.c
  ${CMAKE_CURRENT_LIST_DIR}/Source/tasks.c
  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/port.c
  )

add_library(FreeRTOS ${FREERTOS_SOURCES})

if (${freertos_use_dynamic_allocation})
  set(FREERTOS_HEAP_SOURCE  "heap_1")
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/portable/MemMang/${FREERTOS_HEAP_SOURCE}.c)
endif()
if (${freertos_use_queue})
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/queue.c)
endif()
if (${freertos_use_stream_buffer})
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/stream_buffer.c)
endif()
if (${freertos_use_software_timer})
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/timers.c)
endif()
if (${freertos_use_event_groups})
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/event_groups.c)
endif()
if (${freertos_use_croutine})
  target_sources(FreeRTOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source/croutine.c)
endif()

set(FREERTOS_INCLUDE_DIRS
  ${CMAKE_CURRENT_LIST_DIR}/Source/include/
  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/
  PARENT_SCOPE)

target_include_directories(FreeRTOS PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Source/include/
  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/
  )

target_compile_definitions(FreeRTOS PRIVATE
  configUSE_PORT_OPTIMIZED_TASK_SELECTION=0
  configUSE_PREEMPTION=1
  configUSE_IDLE_HOOK=1
  configUSE_TICK_HOOK=1
  configUSE_TICK_RATE_HZ=1000
  configIDLE_SHOULD_YIELD=1
  )
