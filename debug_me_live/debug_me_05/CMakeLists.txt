set(target dbm_05)

add_executable(${target} debug_me_05.cpp src/pot.cpp src/deposit.cpp src/pot_manager.cpp)

target_include_directories(${target} PRIVATE inc)

set_target_properties(${target} PROPERTIES SANITIZE_TARGET OFF)

configure_file(data/gwfr.txt gwfr.txt COPYONLY)
configure_file(data/ctdorw.txt ctdorw.txt COPYONLY)
