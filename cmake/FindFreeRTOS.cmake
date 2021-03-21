# @file
#
#[=======================================================================[.rst:
FindFreeRTOS
------------

Find FreeRTOS header files and source files.

Result VARIABLES
^^^^^^^^^^^^^^^^

This module will set the following variables in your project

``FREERTOS_FOUND``
FreeRTOS is found and ready to build.
``FREERTOS_INCLUDE_DIRS``
PATH for FreeRTOS Header
``FREERTOS_SOURCES``
PATH for FreeRTOS Sources
``FREERTOS_VERSION
VERSION for FreeRTOS

#]=======================================================================]

# FindFreeRTOS.cmaks
# COMPILER PROCESSOR

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

function(FindFreeRTOS)
  set(optional)
  set(oneValue COMPILER PROCESSOR HEAP)
  set(multiValues)
  message(STATUS "ARGN = ${ARGN}")
  cmake_parse_arguments(FREERTOS "${optional}" "${oneValue}" "${multiValues}" ${ARGN})

  message(STATUS "compiler=${FREERTOS_COMPILER}, processor=${FREERTOS_PROCESSOR}, heap=${FREERTOS_HEAP}" )

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

  find_path( FreeRTOS_PORTABLE_INCLUDE_PATH
    NAMES
    portmacro.h
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    FreeRTOS/Source/portable/${FREERTOS_COMPILER}/${FREERTOS_PROCESSOR}
    )

  if (FreeRTOS_PORTABLE_INCLUDE_PATH STREQUAL FreeRTOS_PORTABLE_INCLUDE_PATH-NOTFOUND)
    message(FATAL_ERROR "FreeRTOS portable headers DID NOT FOUND")
  endif()

  message(STATUS "FreeRTOS_HEADER is ${FreeRTOS_HEADER}")
  message(STATUS "FreeRTOS_CONFIG_HEADER is ${FreeRTOS_CONFIG_HEADER}")
  message(STATUS "FreeRTOS_INCLUDE_PATH is ${FreeRTOS_INCLUDE_PATH}")
  message(STATUS "FreeRTOS_PORTABLE_INCLUDE_PATH is ${FreeRTOS_PORTABLE_INCLUDE_PATH}")
  message(STATUS "FreeRTOS_SOURCE_PATH is ${FreeRTOS_SOURCE_PATH}")
  message(STATUS "FREERTOS_HEAP is ${FREERTOS_HEAP}")
  message(STATUS "FREERTOS_ROOT is $ENV{FREERTOS_ROOT}")

  set(FREERTOS_SOURCES_INTERNAL
    ${FreeRTOS_SOURCE_PATH}/list.c
    ${FreeRTOS_SOURCE_PATH}/tasks.c
    ${FreeRTOS_SOURCE_PATH}/portable/${FREERTOS_COMPILER}/${FREERTOS_PROCESSOR}/port.c
    ${FreeRTOS_SOURCE_PATH}/queue.c
    ${FreeRTOS_SOURCE_PATH}/stream_buffer.c
    ${FreeRTOS_SOURCE_PATH}/timers.c
    ${FreeRTOS_SOURCE_PATH}/event_groups.c
    ${FreeRTOS_SOURCE_PATH}/croutine.c
  )
  if (FREERTOS_HEAP)
    set(FREERTOS_SOURCES_INTERNAL
      ${FREERTOS_SOURCES_INTERNAL}
      ${FreeRTOS_SOURCE_PATH}/portable/MemMang/${FREERTOS_HEAP}.c
    )
  endif()

  function(FREERTOS_CREATE_LIB TARGET DEFINITIONS)
    add_library(${TARGET}_LIB INTERFACE)
    target_include_directories(${TARGET}_LIB PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
      ${FreeRTOS_INCLUDE_PATH}
      ${FreeRTOS_PORTABLE_INCLUDE_PATH}
      )
    target_sources(${TARGET}_LIB PUBLIC
      ${FREERTOS_SOURCES_INTERNAL}
      )
  endfunction()

  set(FREERTOS_SOURCES
    ${FREERTOS_SOURCES_INTERNAL}
    PARENT_SCOPE)

  set(FREERTOS_INCLUDE_DIRS
    ${FreeRTOS_INCLUDE_PATH}
    ${FreeRTOS_PORTABLE_INCLUDE_PATH}
    PARENT_SCOPE)

endfunction()
