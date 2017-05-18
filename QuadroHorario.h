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
    }
    QuadroHorario(){
        ocupado = false;
        disciplina = 0;
    }
    bool isOcupado() {return ocupado;}
    void setOcupado(bool o){ ocupado = o;}
    Disciplina *getDisciplina() {return disciplina;}
    void setDisciplina(Disciplina *d){disciplina = d;}
};


#endif //METAG_QUADROHORARIO_H
