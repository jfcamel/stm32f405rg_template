# CMakeLists.txt for FreeRTOS

set(FREERTOS_COMPILER "GCC")
set(FREERTOS_ARCH  "ARM_CM4F")

set(FREERTOS_HEAP_SOURCE  "heap_1")

set(FREERTOS_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Source/list.c
  ${CMAKE_CURRENT_LIST_DIR}/Source/tasks.c

  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/port.c
  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/MemMang/${FREERTOS_HEAP_SOURCE}.c

  # ${CMAKE_CURRENT_LIST_DIR}/Source/queue.c
  # ${CMAKE_CURRENT_LIST_DIR}/Source/stream_buffer.c
  # ${CMAKE_CURRENT_LIST_DIR}/Source/timers.c
  # ${CMAKE_CURRENT_LIST_DIR}/Source/event_groups.c
  # ${CMAKE_CURRENT_LIST_DIR}/Source/croutine.c
  PARENT_SCOPE)

set(FREERTOS_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/Source/include/
  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/
  PARENT_SCOPE)
