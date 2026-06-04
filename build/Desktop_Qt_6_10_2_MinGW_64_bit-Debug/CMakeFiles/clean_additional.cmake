# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DiamondSquare_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DiamondSquare_autogen.dir\\ParseCache.txt"
  "DiamondSquare_autogen"
  )
endif()
