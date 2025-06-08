# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LED_CONTROLLER_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LED_CONTROLLER_autogen.dir\\ParseCache.txt"
  "LED_CONTROLLER_autogen"
  )
endif()
