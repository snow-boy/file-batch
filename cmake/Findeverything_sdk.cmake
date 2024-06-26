set(SDK_PATH ${CMAKE_SOURCE_DIR}/3rdparty/everything_sdk)

add_library(everything_sdk INTERFACE)

target_link_libraries(everything_sdk 
    INTERFACE 
        ${SDK_PATH}/lib/Everything64.lib
) 

target_include_directories(everything_sdk 
    INTERFACE
        ${SDK_PATH}/include
)

install(FILES 
    ${SDK_PATH}/bin/Everything64.dll 
    CONFIGURATIONS Debug
    DESTINATION ${CMAKE_BINARY_DIR}/Debug/bin)

install(FILES 
    ${SDK_PATH}/bin/Everything64.dll 
    CONFIGURATIONS Release
    DESTINATION ${CMAKE_SOURCE_DIR}/bin)