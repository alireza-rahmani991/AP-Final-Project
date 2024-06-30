# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AP_Final_Project_autogen"
  "CMakeFiles\\AP_Final_Project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AP_Final_Project_autogen.dir\\ParseCache.txt"
  )
endif()
