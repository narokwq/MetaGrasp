#include <iostream>
#include "CarregarDados.h"
#include "Solucao.h"
#include "Grasp.h"

int main() {
    CarregarDados *CD = new CarregarDados();
    Solucao * solucao  = new Solucao();
    Periodo * periodo  = new Periodo();
    CD->setDisciplina(periodo);
    CD->CarregarDiciplinas();
    CD->setSalas(solucao);


    CD->CarregarSalas();

    Grasp(periodo, solucao, 100000, 0.5f).execute();

//    for (auto v:periodo->getDisciplinas()) {
//        std::cout << v->getCodDisciplina() << std::endl;
//        std::cout << v->getNomeProfessor() << std::endl;
//        std::cout <<  v->getQuadroHorario()->getQntHorarios() << std::endl;
//        for (auto aulas : v->getQuadroHorario()->getAulas()) {
//            for (auto point: aulas->getHorario()) {
//                std::cout <<  point.semana << ":" << point.periodo <<std::endl;
//            }
//
//        }
//    }
//    for (auto v:solucao->getSalas()) {
//        std::cout << v->getSala() << std::endl;
//    }
    return 0;
}
