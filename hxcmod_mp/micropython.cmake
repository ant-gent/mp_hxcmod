# Create an INTERFACE library for our C module.
add_library(usermod_hxcmod INTERFACE)

# Add our source files to the lib
target_sources(usermod_hxcmod INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/hxcmod_mp.c
)

target_sources(usermod_hxcmod INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/hxcmod.c
)

# Add the current directory as an include directory.
target_include_directories(usermod_hxcmod INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_hxcmod)
