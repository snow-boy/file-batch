file(GLOB_RECURSE SOURCES_LIST
    src/*.h
    src/*.cpp
)

add_executable(file_batch ${SOURCES_LIST})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(everything_sdk REQUIRED)

target_link_libraries(file_batch 
    Qt5::Widgets
    everything_sdk  
)