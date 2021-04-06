cmake_minimum_required(VERSION 3.13)
project(LFA)


add_executable(team1 "sources/execute.cpp" "sources/main.cpp")
add_executable(proiect1 "sources/execute.cpp" "sources/proiect1.cpp")


set_property(TARGET team1 PROPERTY CXX_STANDARD 17)
set_property(TARGET proiect1  PROPERTY CXX_STANDARD 17)

target_compile_definitions(team1 PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions(team1 PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game

target_compile_definitions(proiect1 PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions(proiect1 PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game


target_sources(team1 PRIVATE ${MY_SOURCES})
target_sources(proiect1 PRIVATE ${MY_SOURCES})

target_include_directories(team1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(proiect1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC) # If using the VS compiler...

	set_target_properties(team1 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	set_target_properties(team1 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

	set_target_properties(proiect1 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	set_target_properties(proiect1 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

endif()

if(WIN32)
	target_compile_definitions(team1 PUBLIC PLATFORM_WIN32="1") 
	target_compile_definitions(proiect1 PUBLIC PLATFORM_WIN32="1") 
  
endif()

