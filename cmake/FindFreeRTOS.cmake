# @file
# FindFreeRTOS.cmaks

if (UNIX)
  set(FreeRTOS_FOUND FALSE)
  set(FreeRTOS_INCLUDE_DIRS "")
  set(FreeRTOS_LIBRARIES "")
  set(FreeRTOS_LIBRARY_DIR "")

  find_file( FreeRTOS_HEADER NAMES FreeRTOS.h
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    Source/include
    FreeRTOS/Source/include
    )

  if (FreeRTOS_HEADER STREQUAL FreeRTOS_HEADER-NOTFOUND)
    message(FATAL_ERROR "FreeRTOS DID NOT FOUND")
  endif()

  find_path( FreeRTOS_INCLUDE_PATH NAMES FreeRTOS.h
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    Source/include
    FreeRTOS/Source/include
    )

  find_path( FreeRTOS_SOURCE_PATH
    NAMES
    tasks.c list.c queue.c stream_buffer.c timers.c c
    croutine.c event_group.c
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    Source
    FreeRTOS/Source
    )

  set(FreeRTOS_LIB FreeRTOS_${FREERTOS_VERSION})

  function(FindFreeRTOS)
    add_library(${FreeRTOS_LIB} INTERFACE IMPORTED)
    target_include_directories(${FreeRTOS_LIB} INTERFACE
      ${FreeRTOS_INCLUDE_PATH}
      )
  endfunction()

endif()

message(STATUS "FreeRTOS_HEADER is ${FreeRTOS_HEADER}")
message(STATUS "FreeRTOS_CONFIG_HEADER is ${FreeRTOS_CONFIG_HEADER}")
message(STATUS "FreeRTOS_INCLUDE_PATH is ${FreeRTOS_INCLUDE_PATH}")
message(STATUS "FreeRTOS_SOURCE_PATH is ${FreeRTOS_SOURCE_PATH}")
message(STATUS "FREERTOS_ROOT is $ENV{FREERTOS_ROOT}")


function(add_freertos_dependency)
  set(optional EXTRA)
  set(oneValue COMPILER PROCESSOR)
  set(multiValues DEFINITIONS)
  cmake_parse_arguments(FREERTOS "${optional}" "${oneValue}" "${multiValues}" ${ARGN})

  set(FREERTOS_COMPILER ${FREERTOS_COMPILER}) # "GCC")
  set(FREERTOS_PROCESSOR ${FREERTOS_PROCESSOR}) # "ARM_CM4F")
  set(FREERTOS_HEAP_SOURCE  ${FREERTOS_HEAP}) #"heap_1")

  set(FREERTOS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_PROCESSOR}/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/croutine.c
    PARENT_SCOPE)

  if (${FREERTOS_HEAP})
    set(FREERTOS_SOURCES
      ${FREERTOS_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/MemMang/${FREERTOS_HEAP_SOURCE}.c
      PARENT_SCOPE)
  endif()

  set(FREERTOS_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_ARCH}/
    PARENT_SCOPE)

  # set(FREERTOS_DEFINITIONS
  #   configUSE_PORT_OPTIMIZED_TASK_SELECTION=$<BOOL:freertos_use_port_optimized_task_selection>
  #   configUSE_PREEMPTION=$<BOOL:freertos_use_preemption>
  #   configUSE_IDLE_HOOK=$<BOOL:freertos_use_idle_hook>
  #   configUSE_IDLE_HOOK=$<BOOL:freertos_use_idle_hook>
  #   configUSE_TICK_HOOK=$<BOOL:freertos_use_tick_hook>
  #   configUSE_TICK_RATE_HZ=1000
  #   configIDLE_SHOULD_YIELD=1
  #   configSUPPORT_STATIC_ALLCATION=$<BOOL:freertos_support_static_allocation>
  #   configSUPPORT_DYNAMIC_ALLOCATION=$<BOOL:freertos_support_dynamic_allocation>
  #   PARENT_SCOPE)

endfunction()
