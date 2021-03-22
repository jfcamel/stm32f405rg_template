# FindFreeRTOS.cmake
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

``FREERTOS_VERSION``

VERSION for FreeRTOS

#]=======================================================================]

function(FindFreeRTOS)
  set(optional)
  set(oneValue COMPILER PROCESSOR HEAP)
  set(multiValues)
  cmake_parse_arguments(FREERTOS "${optional}" "${oneValue}" "${multiValues}" ${ARGN})
  message(TRACE "compiler=${FREERTOS_COMPILER}, processor=${FREERTOS_PROCESSOR}, heap=${FREERTOS_HEAP}" )

  # set(CMAKE_MESSAGE_LOG_LEVEL TRACE)
  set(FREERTOS_FOUND FALSE)
  set(FREERTOS_INCLUDE_DIRS "")

  find_file( FreeRTOS_HEADER NAMES FreeRTOS.h
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    Source/include
    FreeRTOS/Source/include
    )

  if (FreeRTOS_HEADER STREQUAL FreeRTOS_HEADER-NOTFOUND)
    message(WARNING "FreeRTOS DID NOT FOUND")
  endif()

  find_path( FreeRTOS_INCLUDE_PATH NAMES FreeRTOS.h
    PATHS
    ${CMAKE_SOURCE_DIR}
    $ENV{FREERTOS_ROOT}
    PATH_SUFFIXES
    Source/include
    FreeRTOS/Source/include
    )

  file(GLOB _FreeRTOS_TASK_HEADER "${FreeRTOS_INCLUDE_PATH}/task.h")
  if (NOT EXISTS ${_FreeRTOS_TASK_HEADER})
    message(WARNING "task.h DID NOT FOUND")
  endif()

  file(STRINGS "${_FreeRTOS_TASK_HEADER}"
    _FreeRTOS_VER_MAJOR REGEX "^#define[\t ]+tskKERNEL_VERSION_MAJOR[\t ]+.*")
  string(REGEX REPLACE "^#define[\t ]+tskKERNEL_VERSION_MAJOR[\t ]+([0-9].*)"
    "\\1" FREERTOS_VER_MAJOR "${_FreeRTOS_VER_MAJOR}")
  file(STRINGS "${_FreeRTOS_TASK_HEADER}"
    _FreeRTOS_VER_MINOR REGEX "^#define[\t ]+tskKERNEL_VERSION_MINOR[\t ]+.*")
  string(REGEX REPLACE "^#define[\t ]+tskKERNEL_VERSION_MINOR[\t ]+([0-9].*)"
    "\\1" FREERTOS_VER_MINOR "${_FreeRTOS_VER_MINOR}")
  file(STRINGS "${_FreeRTOS_TASK_HEADER}"
    _FreeRTOS_VER_BUILD REGEX "^#define[\t ]+tskKERNEL_VERSION_BUILD[\t ]+.*")
  string(REGEX REPLACE "^#define[\t ]+tskKERNEL_VERSION_BUILD[\t ]+([0-9].*)"
    "\\1" FREERTOS_VER_BUILD "${_FreeRTOS_VER_BUILD}")
  message(TRACE "version = ${FREERTOS_VER_MAJOR}.${FREERTOS_VER_MINOR}.${FREERTOS_VER_BUILD}")
  set(FREERTOS_VERSION
    ${FREERTOS_VER_MAJOR}.${FREERTOS_VER_MINOR}.${FREERTOS_VER_BUILD}
    PARENT_SCOPE)

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
    message(WARNING "FreeRTOS portable headers DID NOT FOUND")
  endif()

  message(TRACE "FreeRTOS_HEADER is ${FreeRTOS_HEADER}")
  message(TRACE "FreeRTOS_INCLUDE_PATH is ${FreeRTOS_INCLUDE_PATH}")
  message(TRACE "FreeRTOS_CONFIG_PATH is ${FreeRTOS_CONFIG_PATH}")
  message(TRACE "FreeRTOS_PORTABLE_INCLUDE_PATH is ${FreeRTOS_PORTABLE_INCLUDE_PATH}")
  message(TRACE "FreeRTOS_SOURCE_PATH is ${FreeRTOS_SOURCE_PATH}")
  message(TRACE "FREERTOS_HEAP is ${FREERTOS_HEAP}")
  message(TRACE "FREERTOS_ROOT is $ENV{FREERTOS_ROOT}")

  set(FREERTOS_SOURCES_INTERNAL
    ${FreeRTOS_SOURCE_PATH}/list.c
    ${FreeRTOS_SOURCE_PATH}/tasks.c
    ${FreeRTOS_SOURCE_PATH}/portable/${FREERTOS_COMPILER}/${FREERTOS_PROCESSOR}/port.c
    ${FreeRTOS_SOURCE_PATH}/queue.c
    ${FreeRTOS_SOURCE_PATH}/stream_buffer.c
    ${FreeRTOS_SOURCE_PATH}/timers.c
    ${FreeRTOS_SOURCE_PATH}/event_groups.c
    ${FreeRTOS_SOURCE_PATH}/croutine.c)

  if (FREERTOS_HEAP)
    set(FREERTOS_SOURCES_INTERNAL
      ${FREERTOS_SOURCES_INTERNAL}
      ${FreeRTOS_SOURCE_PATH}/portable/MemMang/${FREERTOS_HEAP}.c)
  endif()

  set(FREERTOS_SOURCES
    ${FREERTOS_SOURCES_INTERNAL}
    PARENT_SCOPE)

  set(FREERTOS_INCLUDE_DIRS
    ${FreeRTOS_INCLUDE_PATH}
    ${FreeRTOS_PORTABLE_INCLUDE_PATH}
    PARENT_SCOPE)

  set(FREERTOS_FOUND TRUE
    PARENT_SCOPE)

endfunction()
