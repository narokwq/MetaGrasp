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
        Horario.h QuadroHorario.cpp QuadroHorario.h Periodo.h Grasp.cpp Grasp.h Candidato.cpp Candidato.h Solucao.cpp Solucao.h Candidatos.cpp Candidatos.h Elemento.cpp Elemento.h Avaliacao.cpp Avaliacao.h Aula.cpp Aula.h)
add_executable(MetaG ${SOURCE_FILES})