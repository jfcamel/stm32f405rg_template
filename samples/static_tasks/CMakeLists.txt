get_filename_component(EXECNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" EXECNAME ${EXECNAME})

set(CXX_SOURCES_static_tasks
  ${C_SOURCES_COMMON}
  ${CMAKE_CURRENT_LIST_DIR}/Src/static_tasks.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_it.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/system_stm32f4xx.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/main.cpp
  ${ASM_SOURCES_Core}
  )

foreach(CXX_SOURCES_static_task ${CXX_SOURCES_static_tasks})
  set_property(SOURCE ${CXX_SOURCES_static_task} PROPERTY LANGUAGE CXX)
endforeach()

FindFreeRTOS(COMPILER GCC PROCESSOR ARM_CM4F)

add_executable(${EXECNAME}
  ${C_SOURCES_COMMON}
  ${FREERTOS_SOURCES}
  ${CXX_SOURCES_static_tasks}
  )

target_compile_options(${EXECNAME}
  ${C_FLAGS_OPTIONS}
  )

target_link_options(${EXECNAME}
  ${C_FLAGS_OPTIONS}
  PRIVATE -T${CMAKE_CURRENT_LIST_DIR}/STM32F405RGTx_FLASH.ld
  PRIVATE --specs=rdimon.specs
  PRIVATE -Wl,--gc-sections
  )

target_include_directories(${EXECNAME} PRIVATE
  ${INCLUDES_COMMON}
  ${FREERTOS_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/Inc/
  )

target_compile_definitions(${EXECNAME} PRIVATE
  ${DEFINITIONS_COMMON}
  configSUPPORT_STATIC_ALLOCATION=1
  configSUPPORT_DYNAMIC_ALLOCATION=0
  configUSE_PREEMPTION=1
  configUSE_IDLE_HOOK=1
  configUSE_TICK_HOOK=1
  configIDLE_SHOULD_YIELD=1
  )

target_link_libraries(${EXECNAME}
  -lm -lnosys
  )

add_custom_target(${EXECNAME}.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME} ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME}.bin
  )

add_dependencies(${EXECNAME}.bin ${EXECNAME})
