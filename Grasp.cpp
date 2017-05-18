//
// Created by Alex on 14/05/2017.
//

#include <climits>
#include <iostream>
#include <time.h>
#include <ctime>
#include "Grasp.h"

void Grasp::execute() {
    int contadorIteracoes = 0;
    time_t inicio, fim, inicio2, fim2, inicio3, fim3;
    inicio = time(NULL);

    Solucao * solucaFinal = nullptr;
    unsigned __int64 bestAvaliacao = ULLONG_MAX;

    while(numeroIteracoes > contadorIteracoes){
        Periodo * periodoCopia  = new Periodo(*periodoOriginal);
        Solucao * solucaoAtual  = new Solucao(*salasOriginal);

        construcao(solucaoAtual, periodoCopia);

        buscaLocal(solucaoAtual, periodoCopia);
        std::cout << "avaliacao: " << solucaoAtual->getAvaliacao() << std::endl;
        if(solucaoAtual->getAvaliacao() < bestAvaliacao){
            solucaFinal = solucaoAtual;
            bestAvaliacao = solucaoAtual->getAvaliacao();
        }else{
            delete periodoCopia;
            delete solucaoAtual;
        }

        contadorIteracoes++;
//        std::cout << contadorIteracoes << std::endl;

    }

    fim = time(NULL);

    printTime(inicio, fim);

}

void Grasp::printTime(time_t inicio, time_t fim) {
    int minutos = 0;
    double segundos = difftime(fim, inicio);

    while (segundos > 59) {
        segundos = segundos - 60;
        minutos = minutos + 1;
    }
    std::cout<< minutos << ":" << segundos <<std::endl;
}

void Grasp::construcao(Solucao * solucaoAtual, Periodo * periodoCopia){

    int qntIteracoes = periodoCopia->getDisciplinas().size();
    unsigned __int64 taxaFinal = 0;

    for (int i = 0; i < qntIteracoes; ++i) {
        Candidatos * candidatos = new Candidatos();
        montarCandidatos(candidatos, solucaoAtual, periodoCopia);
        std::vector<Candidato> bestList;
        for (auto elemento: candidatos->getCandidatos()) {
            if(elemento.getRazao() <= candidatos->getMin()+alpha*(candidatos->getMax() - candidatos->getMin())){
                bestList.push_back(elemento);
            }
        }

        Candidato escolhido = bestList.at(numeroRandom(bestList.size()));

        Aula * aulaAnt = nullptr;
        for (auto elemento: escolhido.getSalasAula()) {
            unsigned __int64  taxaAvaliacao = 0;

            for (auto aulas: elemento.second->getHorario()){

                solucaoAtual->getSalas().at((unsigned int) elemento.first)->getQuadroHorario().at(
                        (unsigned int) (aulas.semana - 1)).at(
                        (unsigned int) (aulas.periodo - 1))->setDisciplina(periodoCopia->getDisciplinas().at(
                        (unsigned int) escolhido.getIdVectorDisciplina()));

                solucaoAtual->getSalas().at((unsigned int) elemento.first)->getQuadroHorario().at(
                        (unsigned int) (aulas.semana - 1)).at((unsigned int) (aulas.periodo - 1))->setOcupado(true);

                periodoCopia->getDisciplinas().at(
                        (unsigned int) escolhido.getIdVectorDisciplina())->setDisciplinaAlocada(true);

                elemento.second->setIdSala((unsigned int) elemento.first);

                taxaAvaliacao += getRazaoSimples(periodoCopia->getDisciplinas().at(
                        (unsigned int) escolhido.getIdVectorDisciplina()), solucaoAtual->getSalas().at((unsigned int) elemento.first));

//                taxaFinal += escolhido.getRazao();

            }
            if(aulaAnt){
                if(solucaoAtual->getSalas().at((unsigned int) aulaAnt->getIdSala())->getTipoBloco() != solucaoAtual->getSalas().at(
                        (unsigned int) elemento.second->getIdSala())->getTipoBloco())
                    taxaAvaliacao += BLOCO_DIFERENTE;
            }
            aulaAnt = elemento.second;
            elemento.second->setRazao(taxaAvaliacao);
            taxaFinal += taxaAvaliacao;
        }

        delete candidatos;
    }
    solucaoAtual->setAvaliacao(taxaFinal);
}

void Grasp::montarCandidatos(Candidatos *candidatos, Solucao * solucaoAtual, Periodo * periodoCopia){
    for (unsigned int i = 0; i < periodoCopia->getDisciplinas().size() ; ++i) {

        Disciplina * disciplinaAtual = periodoCopia->getDisciplinas().at(i);

        Candidato candidato = Candidato(i);

        Elemento elemnetoAnt = Elemento();

        if(disciplinaAtual->isDisciplinaAlocada())
            continue;

        for (unsigned int k = 0; k < disciplinaAtual->getQuadroHorario()->getQntDiasHorario(); ++k) {
            Elemento bestElemento = Elemento();


            bestElemento.setTaxaAvaliacao(ULLONG_MAX);

            for (unsigned int j = 0; j < solucaoAtual->getSalas().size() ; ++j) {

                Sala * salaAtual = solucaoAtual->getSalas().at(j);

                bool salaOcupada = false;
                for (auto horaro : disciplinaAtual->getQuadroHorario()->getAulas().at(k)->getHorario()) {
                    if(salaAtual->getQuadroHorario().at(
                            (unsigned int)(horaro.semana)-1).at(
                            (unsigned int) (horaro.periodo)-1)->isOcupado()){
                        salaOcupada = true;
                    }
                }
                if(salaOcupada)
                    continue;

                Elemento elemento = Elemento(disciplinaAtual, i, disciplinaAtual->getQuadroHorario()->getAulas().at(k));
                elemento.setSala(salaAtual, j);

                if(elemnetoAnt.getSalaCandidata()) {
                    elemento.setPrev(&elemnetoAnt);

                }
                if(elemento.getTaxaAtualAvaliacao() < bestElemento.getTaxaAvaliacao()){

                    bestElemento = Elemento(elemento);
                    if(bestElemento.getTaxaAvaliacao() == 0)
                        break;
                }

            }

            elemnetoAnt =  Elemento(bestElemento);

            candidato.addSalas(bestElemento.getIndexSala(), disciplinaAtual->getQuadroHorario()->getAulas().at(k), bestElemento.getTaxaAvaliacao());

        }
//      TODO: checar se a candidato chegou no final. disciplina pode não ter nenhuma sala pra ser alocada;
        candidatos->addCandidato(candidato);

    }
}

unsigned int Grasp::numeroRandom(int max){
    std::srand((unsigned int) std::time(0));
    return (unsigned int) (max ? std::rand() % max : max);
}

void Grasp::buscaLocal(Solucao *solucaoAtual, Periodo *periodoCopia) {
    Solucao * solucaoTemp  = new Solucao(*solucaoAtual);
    Disciplina * disciplina = periodoCopia->getDisciplinas().at(numeroRandom(periodoCopia->getDisciplinas().size()));
    for (int i = 0; i < solucaoAtual->getSalas().size(); ) {
//        std::cout << getValorFuncaoObjetivo(solucaoTemp, periodoCopia) << std::endl;
        i++;
    }
    delete solucaoTemp;
}

unsigned __int64 Grasp::getValorFuncaoObjetivo(Solucao * solucao, Periodo *periodo){
    unsigned __int64 taxaFinal = 0;
    for (auto elemento: periodo->getDisciplinas()) {
        Aula * aulaAnt = nullptr;
        for (auto aula: elemento->getQuadroHorario()->getAulas()) {
            unsigned __int64 taxaAvaliacao = 0;
            for (auto aulaIndividual: aula->getHorario()) {
                taxaAvaliacao += getRazaoSimples(elemento, solucao->getSalas().at((unsigned int) aula->getIdSala()));
            }
            if(aulaAnt) {
                if (solucao->getSalas().at((unsigned int) aulaAnt->getIdSala())->getTipoBloco() !=
                    solucao->getSalas().at((unsigned int) aula->getIdSala())->getTipoBloco())
                    taxaAvaliacao += BLOCO_DIFERENTE;
            }
            aula->setRazao(taxaAvaliacao);
            taxaFinal += taxaAvaliacao;
            aulaAnt = aula;
        }
    }
    solucao->setAvaliacao(taxaFinal);
    return taxaFinal;
}

unsigned __int64 Grasp::getRazaoSimples(Disciplina * disciplina, Sala * sala){
    unsigned __int64  taxaAvaliacao = 0;
    if(sala->getTipoSala() != disciplina->getReqTipoSala())
        taxaAvaliacao += TIPO_SALA;
    if(sala->getQuantidade() < disciplina->getQntAlunos())
        taxaAvaliacao += CAPACIDADE_SALA;

    return taxaAvaliacao;
}