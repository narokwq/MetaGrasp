//
// Created by Alex on 23/02/2017.
//

#ifndef METAG_SALA_H
#define METAG_SALA_H

#include <vector>
#include <array>
#include "TipoStruct.h"
#include "QuadroHorario.h"

class Sala {
public:
    Sala(const Sala &sl){
        id = sl.id;
        codSala = sl.codSala;
        quantidade = sl.quantidade;
        tipoSala = sl.tipoSala;
        tipoBloco = sl.tipoBloco;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 15; j++) {
                this->quadroHorario[i][j] = new QuadroHorario(*sl.quadroHorario[i][j]);

            }
        }
    }
    Sala(){
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 15; j++) {
                this->quadroHorario[i][j] = new QuadroHorario();

            }
        }
    }

    virtual ~Sala() {
        for (auto q: quadroHorario) {
            for (auto e: q) {
                delete e;
            }
        }
    }

    void setSala(int cod){ codSala = cod;}
    int getSala(){return codSala;}

    void setQuantidade(int qnt){ quantidade = qnt;}
    int getQuantidade(){ return quantidade;}

    void setTipoSala(int tipo){ tipoSala = TipoSala(tipo);}
    TipoSala getTipoSala(){ return tipoSala;}

    void setTipoBloco(int tipo){tipoBloco = TipoBloco(tipo);}
    TipoBloco getTipoBloco(){ return tipoBloco;}

    int getId() const { return id; }
    void setId(int id) { Sala::id = id; }

    std::array<std::array<QuadroHorario *, 15>, 5> getQuadroHorario(){return quadroHorario;}
private:
    int id;
    int codSala;
    int quantidade;
    TipoSala tipoSala;
    TipoBloco tipoBloco;
    std::array<std::array<QuadroHorario *, 15>, 5> quadroHorario;
};


#endif //METAG_SALA_H
