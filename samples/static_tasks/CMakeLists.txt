get_filename_component(EXECNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" EXECNAME ${EXECNAME})

FindFreeRTOS(COMPILER GCC PROCESSOR ARM_CM4F)

set(SOURCES_${EXECNAME}
  ${C_SOURCES_COMMON}
  ${ASM_SOURCES_Core}
  ${FREERTOS_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/Src/static_tasks.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_it.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/system_stm32f4xx.c
  ${CMAKE_CURRENT_LIST_DIR}/Src/main.c
  )

foreach(SOURCE_${EXECNAME} ${SOURCES_${EXECNAME}})
  set_property(SOURCE ${SOURCE_${EXECNAME}} PROPERTY LANGUAGE C)
endforeach()

add_executable(${EXECNAME}
  ${SOURCES_${EXECNAME}}
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
  )

target_link_libraries(${EXECNAME}
  -lm -lnosys
  )

add_custom_target(${EXECNAME}.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME} ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME}.bin
  )

add_dependencies(${EXECNAME}.bin ${EXECNAME})
