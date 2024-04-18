set(target dbm_02)

add_executable(${target} debug_me_02.cpp)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)
