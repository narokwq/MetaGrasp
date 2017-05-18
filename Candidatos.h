//
// Created by Alex on 15/05/2017.
//

#ifndef METAG_CANDIDATOS_H
#define METAG_CANDIDATOS_H


#include <vector>
#include <climits>
#include "Elemento.h"
#include "Candidato.h"

class Candidatos {
private:
    std::vector<Candidato> candidatos;
    unsigned __int64 min;
    unsigned __int64 max;
public:

    Candidatos() {
        candidatos.clear();
        candidatos.shrink_to_fit();
        min = ULLONG_MAX;
        max = 0;
    }

    virtual ~Candidatos() {
        candidatos.clear();
    }

    const std::vector<Candidato> &getCandidatos() const { return candidatos; }
    void setCandidatos(const std::vector<Candidato> &candidato) { Candidatos::candidatos = candidato; }

    void addCandidato(Candidato candidato) {
        candidatos.push_back(Candidato(candidato));
        if(candidato.getRazao() > max)
            max = candidato.getRazao();
        if(candidato.getRazao() < min)
            min = candidato.getRazao();
    }

    unsigned __int64 getMax() const { return max; }
    void setMax(unsigned __int64 max) { Candidatos::max = max; }

    unsigned __int64 getMin() const { return min; }
    void setMin(unsigned __int64 min) { Candidatos::min = min; }
};


#endif //METAG_CANDIDATOS_H
