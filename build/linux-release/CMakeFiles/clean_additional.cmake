# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles/TicketManageSystem_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TicketManageSystem_autogen.dir/ParseCache.txt"
  "TicketManageSystem_autogen"
  )
endif()
