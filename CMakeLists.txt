cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJ ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJ} LANGUAGES C CXX)

SET(PREFIX arm-none-eabi)
SET(CMAKE_C_COMPILER ${PREFIX}-gcc)
SET(CMAKE_CXX_COMPILER ${PREFIX}-g++)
SET(CMAKE_ASM_COMPILER ${PREFIX}-as)
SET(CMAKE_OBJCPY ${PREFIX}-objcopy)

set(CPU "-mcpu=cortex-m4")
set(THUMB "-mthumb")
set(FPU "-mfpu=fpv4-sp-d16")
set(FLOAT-ABI "-mfloat-abi=hard")
set(MCU "${CPU} ${THUMB} ${FPU} ${FLOAT-ABI}")

set(DEBUG "-g3")
set(OPTIMIZATION_LEVEL "-Os")

set(CMAKE_C_FLAGS "${MCU} ${OPTIMIZATION_LEVEL} ${DEBUG} -ffunction-sections -fdata-sections -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -fpermissive -fexceptions -fnon-call-exceptions -fno-rtti -fno-use-cxa-atexit -fno-common")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_CURRENT_LIST_DIR}/STM32F405RGTx_FLASH.ld  --specs=nano.specs -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_FLAGS} -T${PROJECT_SOURCE_DIR}/STM32F405RGTx_FLASH.ld  --specs=rdimon.specs -Wl,--gc-sections")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFreeRTOS.cmake)
FindFreeRTOS(COMPILER GCC PROCESSOR ARM_CM4F HEAP heap_1)

set(C_SOURCES_COMMON
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c
  )

set(DEFINITIONS_COMMON
  -DUSE_FULL_LL_DRIVER
  -DHSE_VALUE=16000000
  -DHSE_STARTUP_TIMEOUT=100
  -DLSE_STARTUP_TIMEOUT=5000
  -DLSE_VALUE=32768
  -DEXTERNAL_CLOCK_VALUE=12288000
  -DHSI_VALUE=16000000
  -DLSI_VALUE=32000
  -DVDD_VALUE=3300
  -DPREFETCH_ENABLE=1
  -DINSTRUCTION_CACHE_ENABLE=1
  -DDATA_CACHE_ENABLE=1
  -DSTM32F405xx
  )

set(INCLUDES_COMMON
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/
  )

set(C_SOURCES_Core
  ${C_SOURCES_COMMON}
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/app.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
  )

set(ASM_SOURCES_Core
  ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f405xx.s
  )

set_property(SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f405xx.s PROPERTY LANGUAGE C)

add_executable(${PROJ}
  ${C_SOURCES_Core}
  ${ASM_SOURCES_Core}
  ${FREERTOS_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/main.c
  )

target_compile_options(${PROJ} PRIVATE
  ${CPU}
  ${THUMB}
  ${FPU}
  ${FLOAT-ABI}
  ${OPTIMIZE}
  ${DEBUG}
  -ffunction-sections
  -fdata-sections
  -Wall
  -T${PROJECT_CURRENT_LIST_DIR}/STM32F405RGTx_FLASH.ld
  --specs=rdimon.specs
  -Wl,--gc-sections
  )

target_include_directories(${PROJ} PRIVATE
  ${INCLUDES_COMMON}
  ${FREERTOS_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/Core/Inc/
  )

target_compile_definitions(${PROJ} PRIVATE
  ${DEFINITIONS_COMMON}
  )

target_link_libraries(${PROJ}
  -lm -lnosys ${FreeRTOS_LIB}
  )

add_custom_target(${PROJ}.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJ} ${CMAKE_CURRENT_BINARY_DIR}/${PROJ}.bin
  )

add_dependencies(${PROJ}.bin ${PROJ})

add_subdirectory(test)
add_subdirectory(samples)
