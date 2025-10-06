# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\gsxg_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\gsxg_autogen.dir\\ParseCache.txt"
  "gsxg_autogen"
  )
endif()
