//
// Created by Alex on 11/04/2017.
//

#ifndef METAG_QUADROHORARIO_H
#define METAG_QUADROHORARIO_H


#include "Disciplina.h"

class QuadroHorario {
private:
    bool ocupado;
    Disciplina * disciplina;
public:
    QuadroHorario(const QuadroHorario &qh){
        ocupado = qh.ocupado;
        disciplina = qh.disciplina;
    }
    QuadroHorario(){
        ocupado = false;
        disciplina = nullptr;
    }
    bool isOcupado() {return ocupado;}
    void setOcupado(bool o){ ocupado = o;}
    Disciplina *getDisciplina() {return disciplina;}
    void setDisciplina(Disciplina *d){disciplina = d;}
    void reset(){
        ocupado = false;
        disciplina = nullptr;
    }
};


#endif //METAG_QUADROHORARIO_H
