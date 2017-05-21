//
// Created by Alex on 15/05/2017.
//

#ifndef METAG_AULA_H
#define METAG_AULA_H


#include <vector>


struct TPoint {
    int semana;
    int periodo;
};

class Aula {
private:
    int qntHorario;
    bool alocado;
    int idDisciplinaAula;
    int idSala;
    unsigned long long razao;
    std::vector<TPoint> horario;
public:
    Aula(){
        alocado = false;
    }
    Aula(const Aula &al){
        qntHorario = al.qntHorario;
        alocado = al.alocado;
        idDisciplinaAula = al.idDisciplinaAula;
        idSala = al.idSala;
        razao = al.razao;
        horario.resize(al.horario.size());
        for (int i = 0; i < al.horario.size(); ++i) {
            horario[i].semana = al.horario[i].semana;
            horario[i].periodo = al.horario[i].periodo;
        }
    }

    virtual ~Aula() {
        horario.clear();
        horario.shrink_to_fit();
    }

    int getIdDisciplinaAula() const { return idDisciplinaAula; }
    void setIdDisciplinaAula(int idDisciplinaAula) { Aula::idDisciplinaAula = idDisciplinaAula; }

    int getIdSala() const { return idSala; }
    void setIdSala(int idSala) { Aula::idSala = idSala; }

    int getQntHorario() const { return qntHorario; }
    void setQntHorario(int qntHorario) { Aula::qntHorario = qntHorario; }

    bool isAlocado() const { return alocado; }
    void setAlocado(bool alocado) { Aula::alocado = alocado; }

    const std::vector<TPoint> &getHorario() const { return horario; }
    void setHorario(const std::vector<TPoint> &horario) { Aula::horario = horario; }

    unsigned long long int getRazao() const { return razao; }
    void setRazao(unsigned long long int razao) { Aula::razao = razao; }

    void addHorario(int hr) {
        TPoint point;
        point.semana = hr/100;
        point.periodo = hr%100;
        horario.push_back(point);
    }

    unsigned int getSemana(int i) const { return (unsigned int) (horario.at(i).semana == 0 ? 0: horario.at(i).semana - 1); }
    unsigned int getPeriodo(int i) const { return (unsigned int) (horario.at(i).periodo == 0 ? 0: horario.at(i).periodo - 1); }

};


#endif //METAG_AULA_H
