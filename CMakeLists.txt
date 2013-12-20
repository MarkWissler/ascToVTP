cmake_minimum_required(VERSION 2.8)
 
PROJECT(DelimitedTextReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DelimitedTextReader MACOSX_BUNDLE DelimitedTextReader)
 
if(VTK_LIBRARIES)
  target_link_libraries(DelimitedTextReader ${VTK_LIBRARIES})
else()
  target_link_libraries(DelimitedTextReader vtkHybrid)
endif()