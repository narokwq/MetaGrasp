//
// Created by Alex on 11/04/2017.
//

#ifndef METAG_PERIODO_H
#define METAG_PERIODO_H


#include <vector>
#include "Disciplina.h"

class Periodo {
private:
    std::vector<Disciplina *> disciplinas;
public:
    void addDisciplinas(Disciplina * disciplina) {
        disciplinas.push_back(disciplina);
    }
    std::vector<Disciplina *> getDisciplinas(){return disciplinas;}
};


#endif //METAG_PERIODO_H
