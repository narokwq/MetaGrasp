//
// Created by Alex on 26/02/2017.
//

#ifndef METAG_HORARIO_H
#define METAG_HORARIO_H


class Horario {
private:
    int qntHorarios;
    int qntDiasHorario;
    int * horarios;
    int counter;
public:
    Horario() {
        qntHorarios = 0;
        qntDiasHorario = 0;
        counter = 0;
    }
    Horario(int numeroHorarios){
        qntHorarios = numeroHorarios;
        qntDiasHorario = 0;
        counter = 0;
        horarios = new int[numeroHorarios];
    }
    int getQntHorarios() {return qntHorarios;}
    void setQntHorarios(int q) {qntHorarios = q;}
    int getQntDiasHorario() {return qntDiasHorario;}
    void setQntDiasHorario(int q){qntDiasHorario = q;}
    int *getHorarios() {return horarios;}
    void setHorarios(int *h){ horarios = h;}
    bool addHorario(int horario){
        if(qntHorarios == counter) return false;
        horarios[counter++] = horario;
        return true;
    }
};

#endif //METAG_HORARIO_H
