#include <iostream>
#include "CarregarDados.h"

int main() {
    CarregarDados *CD = new CarregarDados();
    Periodo * periodo  = new Periodo();
    CD->setDisciplina(periodo);
    CD->CarregarDiciplinas();

    std::vector<Sala*> salas;
    CD->setSalas(&salas);


    CD->CarregarSalas();

    for (auto v:periodo->getDisciplinas()) {
        std::cout << v->getCodDisciplina() << std::endl;
        std::cout << v->getNomeProfessor() << std::endl;
        std::cout <<  v->getQuadroHorario()->getQntHorarios() << std::endl;
        for (int i = 0; i < v->getQuadroHorario()->getQntHorarios(); i++ ) {
            std::cout <<  v->getQuadroHorario()->getHorarios()[i] << std::endl;
        }
    }
//    for (auto v:salas) {
//        std::cout << v->getSala() << std::endl;
//    }
//    return 0;
}
