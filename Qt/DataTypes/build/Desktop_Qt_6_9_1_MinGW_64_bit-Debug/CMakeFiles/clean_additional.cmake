# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appDataTypes_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appDataTypes_autogen.dir\\ParseCache.txt"
  "appDataTypes_autogen"
  )
endif()
