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
    Periodo(){};
    Periodo(const Periodo &disc)
    {
        disciplinas.resize(disc.disciplinas.size());
        for (int i=0; i < disc.disciplinas.size(); i++) {
            disciplinas[i] = new Disciplina(*disc.disciplinas[i]);
        }
    };

    virtual ~Periodo() {
        for (auto d: disciplinas) {
            delete d;
        }
        disciplinas.clear();
        disciplinas.shrink_to_fit();
    }

    void addDisciplinas(Disciplina * disciplina) {
        disciplinas.push_back(disciplina);
    }
    std::vector<Disciplina *> getDisciplinas(){return disciplinas;}
};


#endif //METAG_PERIODO_H
