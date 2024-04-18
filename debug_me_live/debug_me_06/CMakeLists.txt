set(target dbm_06)

add_executable(${target} debug_me_06.cpp src/pot.cpp src/deposit.cpp src/pot_manager.cpp experimental/compactor.cpp)

target_include_directories(${target} PRIVATE inc)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)

