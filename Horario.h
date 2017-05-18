//
// Created by Alex on 26/02/2017.
//

#ifndef METAG_HORARIO_H
#define METAG_HORARIO_H


#include "Aula.h"

class Horario {
private:
    int qntHorarios;
    int qntDiasHorario;
    int counter;
    std::vector<Aula *> aulas;

public:
    Horario(const Horario &hr) {
        qntHorarios = hr.qntHorarios;
        qntDiasHorario = hr.qntDiasHorario;
        counter = hr.counter;
        aulas.resize(hr.aulas.size());
        for (int i = 0; i < aulas.size(); ++i) {
            aulas[i] = new Aula(*hr.aulas[i]);
        }
    }
    Horario() {
        qntHorarios = 0;
        qntDiasHorario = 0;
        counter = 0;
    }
    Horario(int numeroHorarios){
        qntHorarios = numeroHorarios;
        qntDiasHorario = 0;
        counter = 0;
    }

    virtual ~Horario() {
        for (auto a: aulas) {
            delete a;
        }
        aulas.clear();
        aulas.shrink_to_fit();
    }

    int getQntHorarios() {return qntHorarios;}
    void setQntHorarios(int q) {qntHorarios = q;}
    int getQntDiasHorario() {return qntDiasHorario;}
    void setQntDiasHorario(int q){qntDiasHorario = q;}

    const std::vector<Aula *> &getAulas() const {
        return aulas;
    }

    void setAulas(const std::vector<Aula *> &aulas) {
        Horario::aulas = aulas;
    }

    bool addHorario(Aula * aula){
        aulas.push_back(aula);
    }
};

#endif //METAG_HORARIO_H
