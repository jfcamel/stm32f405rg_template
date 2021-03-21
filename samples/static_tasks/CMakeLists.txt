get_filename_component(EXECNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" EXECNAME ${EXECNAME})

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -fpermissive -fexceptions -fnon-call-exceptions -fno-rtti -fno-use-cxa-atexit -fno-common")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_CURRENT_LIST_DIR}/STM32F405RGTx_FLASH.ld  --specs=rdimon.specs -Wl,--gc-sections")

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

set(DEFINITIONS_static_tasks
  ${DEFINITIONS_COMMON}
  )

add_executable(${EXECNAME}
  ${C_SOURCES_COMMON}

  ${CXX_SOURCES_static_tasks}
  )

target_include_directories(${EXECNAME} PRIVATE
  ${INCLUDES_COMMON}
  ${FREERTOS_INCLUDES}
  ${CMAKE_CURRENT_LIST_DIR}/Inc/
  )

target_compile_definitions(${EXECNAME} PRIVATE
  ${DEFINITIONS_COMMON}
  ${DEFINITIONS_static_tasks}
  -DconfigTICK_RATE_HZ=1000
  -DconfigIDLE_SHOULD_YIELD=0
  )

target_link_libraries(${EXECNAME}
  -lm -lnosys
  )

add_custom_target(${EXECNAME}.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME} ${CMAKE_CURRENT_BINARY_DIR}/${EXECNAME}.bin
  )

add_dependencies(${EXECNAME}.bin ${EXECNAME})

message(STATUS "CMAKE_CXX_LINK_FLAGS = ${CMAKE_CXX_LINK_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
