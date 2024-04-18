cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(debug_me VERSION 1.0)

add_subdirectory(debug_me_01)
add_subdirectory(debug_me_02)
add_subdirectory(debug_me_03)
add_subdirectory(debug_me_04)
add_subdirectory(debug_me_05)
add_subdirectory(debug_me_06)

# Get all targets and store them in the all_targets variable
get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
get_property(subdirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY SUBDIRECTORIES)

foreach(subdir ${subdirs})
    get_property(subdir_target DIRECTORY ${subdir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND all_targets ${subdir_target})
endforeach()

# Sanitizers related options
set(ENABLE_SANITIZERS ON CACHE BOOL "Enable sanitizers")

if (ENABLE_SANITIZERS)
    # check if sanitizers are available and enable them
    include(CheckCXXCompilerFlag)

    # need to set linker flags for the address sanitizer check, otherwise it fails
    set(SAVED_CRLO ${CMAKE_REQUIRED_LINK_OPTIONS})
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
    check_cxx_compiler_flag("-fsanitize=address" COMPILER_SUPPORTS_ASAN)
    set (CMAKE_REQUIRED_LINK_OPTIONS ${SAVED_CRLO})

    CHECK_CXX_COMPILER_FLAG(-fsanitize=undefined COMPILER_SUPPORTS_USAN)

    if (ENABLE_SANITIZERS AND NOT COMPILER_SUPPORTS_ASAN)
        message("Address sanitizer is not supported by the compiler")
    elseif(ENABLE_SANITIZERS AND COMPILER_SUPPORTS_ASAN)
        message("Address sanitizer is supported by the compiler")
    endif(ENABLE_SANITIZERS AND NOT COMPILER_SUPPORTS_ASAN)

    if (ENABLE_SANITIZERS AND NOT COMPILER_SUPPORTS_USAN)
        message("Undefined behavior sanitizer is not supported by the compiler")
    elseif(ENABLE_SANITIZERS AND COMPILER_SUPPORTS_USAN)
        message("Undefined behavior sanitizer is supported by the compiler")
    endif(ENABLE_SANITIZERS AND NOT COMPILER_SUPPORTS_USAN)

endif(ENABLE_SANITIZERS)

# Enforce build type... bit ugly

set(CMAKE_BUILD_TYPE Debug)


foreach(target ${all_targets})

    message("Configuring target ${target}")

    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_options(${target} PRIVATE -ggdb3 -O0 -fno-omit-frame-pointer)

    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

    get_target_property(SANITIZE_TARGET ${target} SANITIZE_TARGET)

    if (ENABLE_SANITIZERS AND COMPILER_SUPPORTS_ASAN AND SANITIZE_TARGET)
        message("Enabling ASAN for target ${target}")
        target_compile_options(${target} PRIVATE -fsanitize=address -fsanitize-address-use-after-scope)
        target_link_options(${target} PRIVATE -fsanitize=address)
    endif(ENABLE_SANITIZERS AND COMPILER_SUPPORTS_ASAN AND SANITIZE_TARGET)

    if (ENABLE_SANITIZERS AND COMPILER_SUPPORTS_USAN AND SANITIZE_TARGET)
        message("Enabling USAN for target ${target}")
        target_compile_options(${target} PRIVATE -fsanitize=undefined)
        target_link_options(${target} PRIVATE -fsanitize=undefined)
    endif(ENABLE_SANITIZERS AND COMPILER_SUPPORTS_USAN AND SANITIZE_TARGET)

endforeach(target ${all_targets})



# configure_file(gdb/.gdbinit .gdbinit COPYONLY)