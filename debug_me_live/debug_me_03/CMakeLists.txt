set(target dbm_03)

add_executable(${target} debug_me_03.cpp)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)
