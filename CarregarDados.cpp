//
// Created by Alex on 13/02/2017.
//

#include "CarregarDados.h"


bool CarregarDados::CarregarSalas(){
    std::ifstream fileSteam("input/salas.txt");
    std::string linha;

    if(!fileSteam.is_open()){
        std::cout<< "Erro ao abrir salas.txt"<<std::endl;
        return false;
    }

    while(std::getline(fileSteam, linha)){
        std::vector<std::string> salaVector {Util::explode(linha, '\t')};
        if(salaVector.size() == 4){

            Sala *sala = new Sala();
            sala->setTipoBloco(std::stoi(salaVector[0]));
            sala->setSala(std::stoi(salaVector[1]));
            sala->setQuantidade(std::stoi(salaVector[2]));
            sala->setTipoSala(std::stoi(salaVector[3]));
            salas->push_back(sala);

        }else{
            std::cout<< "Quantidade incorreta de itens carregados em salas.txt"<<std::endl;
            return false;
        }
    }
    std::cout<< "Arquivo carregado salas.txt"<<std::endl;
    fileSteam.close();
    return true;
}



bool CarregarDados::CarregarDiciplinas(){
    if(CarregarDadosExtras()){
        std::ifstream fileSteam("input/disciplinas.txt");
        std::string linha;

        if(!fileSteam.is_open()){
            std::cout<< "Erro ao abrir disciplinas.txt"<<std::endl;
            return false;
        }

        while(std::getline(fileSteam, linha)){
            std::vector<std::string> dspVector {Util::explode(linha, '\t')};
            if(dspVector.size() == 5){
                Disciplina* disciplina = new Disciplina();

                disciplina->setCodDisciplina(dspVector[0]);
                disciplina->setQntAlunos(std::stoi(dspVector[2]));
                disciplina->setNomeDisciplina(mapNomeDisciplina[dspVector[0]]);
                disciplina->setNomeProfessor(mapNomeProfessor[dspVector[0]]);
                disciplina->setReqTipoSala(TipoSala(std::stoi(dspVector[1])));

                std::vector<std::string> codCursoVector {Util::explode(dspVector[3], ',')};
                disciplina->setTipoCurso(TipoCurso(stoi(codCursoVector[0])));

                Horario* horario = new Horario(std::stoi(dspVector[4]));
                for(auto curso:mapHorarios[dspVector[0]]){
                    if(!horario->addHorario(std::stoi(curso[1])))
                        std::cout<< "Erro quantidade de horarios incompativeis na linha 65"<<std::endl;
                }
                disciplina->setQuadroHorario(horario);
                periodo->addDisciplinas(disciplina);

            }else{
                std::cout<< "Quantidade incorreta de itens carregados em disciplinas.txt"<<std::endl;
                return false;
            }
        }
        std::cout<< "Arquivo carregado disciplinas.txt"<<std::endl;
        fileSteam.close();
        return true;
    }
    return false;
}

bool CarregarDados::CarregarDadosExtras(){
    return (CarregarMapHorarios() && CarregarMapNomeDisciplina() && CarregarMapNomeProfessor());
}

bool CarregarDados::CarregarMapHorarios(){
    std::ifstream fileSteam("input/horarios.txt");
    std::string linha, codDisciplina, curso, horario;

    if(!fileSteam.is_open()){
        std::cout<< "Erro ao abrir horarios.txt"<<std::endl;
        return false;
    }

    while(std::getline(fileSteam, linha)){
        std::vector<std::string> sala {Util::explode(linha, '\t')};
        if(sala.size() == 3){
            codDisciplina = sala[0];
            curso = sala[1];
            horario = sala[2];

            std::map<std::string, std::vector<std::array<std::string, 2>>>::iterator iter = mapHorarios.find(codDisciplina);
            if(iter == mapHorarios.end()){
                mapHorarios[codDisciplina];
            }
            mapHorarios[codDisciplina].push_back({curso, horario});
        }else{
            std::cout<< "Quantidade incorreta de itens carregados em salas.txt"<<std::endl;
            return false;
        }
    }
    std::cout<< "Arquivo carregado horarios.txt"<<std::endl;
    fileSteam.close();
    return true;
}

bool CarregarDados::CarregarMapNomeDisciplina(){
    std::ifstream fileSteam("input/nomeDisciplinas.txt");
    std::string linha, codDisciplina, nomeDisciplina;

    if(!fileSteam.is_open()){
        std::cout<< "Erro ao abrir disciplinas.txt"<<std::endl;
        return false;
    }

    while(std::getline(fileSteam, linha)){
        codDisciplina = linha.substr(0,9);
        nomeDisciplina = linha.substr(10, linha.size() - 10);
        mapNomeDisciplina[codDisciplina] = nomeDisciplina;
    }
    std::cout<< "Arquivo carregado nomeDisciplinas.txt"<<std::endl;
    fileSteam.close();
    return true;
}

bool CarregarDados::CarregarMapNomeProfessor(){
    std::ifstream fileSteam("input/nomeProfessores.txt");
    std::string linha, codDisciplina, nomeProfessor;

    if(!fileSteam.is_open()){
        std::cout<< "Erro ao abrir disciplinas.txt"<<std::endl;
        return false;
    }

    while(std::getline(fileSteam, linha)){
        codDisciplina = linha.substr(0, 9);
        nomeProfessor = linha.substr(10, linha.size() - 10);
        mapNomeProfessor[codDisciplina] = nomeProfessor;
    }
    std::cout<< "Arquivo carregado nomeProfessores.txt"<<std::endl;
    fileSteam.close();
    return true;
}