set(target dbm_01)

add_executable(${target} debug_me_01.cpp)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)
