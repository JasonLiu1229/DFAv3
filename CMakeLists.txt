cmake_minimum_required(VERSION 3.20)
project(DFAv3)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-fexceptions)

set(json
        json.hpp)

set(DFA
        DFA.cpp DFA.h
        State.cpp State.h
        TransitionDFA.cpp TransitionDFA.h DFA.cpp DFA.h TFA_test.cpp)


add_executable(DFAP_test DFA_product_test.cpp ${DFA} ${json})

add_executable(TFA_test TFA_test.cpp ${DFA} ${json})