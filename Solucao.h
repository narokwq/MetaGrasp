//
// Created by Alex on 14/05/2017.
//

#ifndef METAG_SOLUCAO_H
#define METAG_SOLUCAO_H


#include "Sala.h"

class Solucao {
private:
    std::vector<Sala *> salas;
    unsigned long long avaliacao;
public:
    Solucao(const Solucao &sl){
        avaliacao = sl.avaliacao;
        salas.resize(sl.salas.size());
        for (int i = 0; i < sl.salas.size(); ++i) {
            salas[i] = new Sala(*sl.salas[i]);
        }
    }
    Solucao(){
        avaliacao = 0;
    };

    virtual ~Solucao() {
        for (auto s: salas) {
            delete s;
        }
        salas.clear();
        salas.shrink_to_fit();
    }

    void addSalas(Sala * sala) { salas.push_back(sala); }

    unsigned long long int getAvaliacao() const { return avaliacao; }
    void setAvaliacao(unsigned long long int avaliacao) { Solucao::avaliacao = avaliacao; }

    std::vector<Sala *> getSalas(){return salas;}
    std::vector<Sala *> setSalas(std::vector<Sala *> sls){salas = sls;}
};


#endif //METAG_SOLUCAO_H
