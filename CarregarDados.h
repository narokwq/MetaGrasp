//
// Created by Alex on 13/02/2017.
//

#ifndef METAG_CARREGARDADOS_H
#define METAG_CARREGARDADOS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>


#include "Util.h"
#include "TipoStruct.h"
#include "Sala.h"
#include "Periodo.h"

class CarregarDados {
    public:
        bool CarregarSalas();

        bool CarregarDiciplinas();
        bool CarregarMapNomeDisciplina();
        bool CarregarMapNomeProfessor();
        bool CarregarMapHorarios();

        void setSalas(std::vector<Sala*>* argSala){salas = argSala;}
        void setDisciplina(Periodo * p){periodo = p;}
    private:
        bool CarregarDadosExtras();
        std::map <std::string, std::vector<std::array<std::string, 2>> >  mapHorarios;
        std::map <std::string, std::string>  mapNomeDisciplina;
        std::map <std::string, std::string>  mapNomeProfessor;
        std::vector<Sala*>* salas;
        Periodo * periodo;
};


#endif //METAG_CARREGARDADOS_H
