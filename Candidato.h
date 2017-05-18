//
// Created by Alex on 14/05/2017.
//

#ifndef METAG_CANDIDATO_H
#define METAG_CANDIDATO_H


#include <utility>
#include "Sala.h"

class Candidato {
private:
    int idVectorDisciplina;
    std::vector<std::pair<int, Aula *>> salasAula;
    unsigned __int64 razao;
public:
    Candidato(int idVectorDisciplina) : idVectorDisciplina(idVectorDisciplina) { razao = 0; }


    int getIdVectorDisciplina() const { return idVectorDisciplina; }
    void setIdVectorDisciplina(int idVectorDisciplina) { Candidato::idVectorDisciplina = idVectorDisciplina; }

    const std::vector<std::pair<int, Aula *>> &getSalasAula() const { return salasAula; }
    void setSalasAula(const std::vector<std::pair<int, Aula *>> &salas) { Candidato::salasAula = salas; }

    unsigned long long int getRazao() const { return razao; }
    void setRazao(unsigned long long int razao) { Candidato::razao = razao; }

    void addSalas(int sala, Aula * aula, unsigned __int64 custo){
        salasAula.push_back(std::make_pair(sala, aula));
        razao += custo;
    }


};


#endif //METAG_CANDIDATO_H
