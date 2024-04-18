set(target dbm_04)

add_executable(${target} debug_me_04.cpp debug_me_04.cpp src/pot.cpp src/deposit.cpp)
target_include_directories(${target} PRIVATE inc)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)
