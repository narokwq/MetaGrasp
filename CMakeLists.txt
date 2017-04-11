cmake_minimum_required(VERSION 3.6)
project(MetaG)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        CarregarDados.cpp
        CarregarDados.h
        Util.cpp
        Util.h
        Sala.h
        TipoStruct.h
        Disciplina.h
        Horario.h QuadroHorario.cpp QuadroHorario.h Periodo.h)
add_executable(MetaG ${SOURCE_FILES})