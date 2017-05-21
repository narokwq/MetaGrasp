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
        unsigned __int64 razao = getRazaoTotal(periodoCopia, solucaoAtual);
        buscaLocal(solucaoAtual, periodoCopia);

        razao = getRazaoTotal(periodoCopia, solucaoAtual);

        if(razao < bestAvaliacao){
            delete solucaFinal;
            std::cout << "avaliacao: " << razao << " " << contadorIteracoes <<std::endl;
            solucaFinal = solucaoAtual;
            bestAvaliacao = razao;
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
        int con = 0;
        for (auto elemento: candidatos->getCandidatos()) {
            if(elemento.getRazao() <= candidatos->getMin()+alpha*(candidatos->getMax() - candidatos->getMin())){
                bestList.push_back(elemento);
                if(con++ > 5)
                    break;
            }
        }

        Candidato escolhido = bestList.at(numeroRandom(bestList.size()));

        Aula * aulaAnt = nullptr;
        for (auto elemento: escolhido.getSalasAula()) {
            unsigned __int64  taxaAvaliacao = 0;

            for (auto aulas: elemento.second->getHorario()){
                Sala * sala = solucaoAtual->getSalas().at((unsigned int) elemento.first);

                sala->getQuadroHorario().at((unsigned int) (aulas.semana == 0 ? 0: aulas.semana - 1)).at(
                        (unsigned int) (aulas.periodo == 0 ? 0: aulas.periodo - 1))->setDisciplina(periodoCopia->getDisciplinas().at(
                        (unsigned int) escolhido.getIdVectorDisciplina()));


                if(sala->getTipoSala() != Fantasma) {
                    sala->getQuadroHorario().at(
                            (unsigned int) (aulas.semana == 0 ? 0 : aulas.semana - 1)).at(
                            (unsigned int) (aulas.periodo == 0 ? 0 : aulas.periodo - 1))->setOcupado(true);
                }

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
    for (unsigned int i = 0; i < periodoCopia->getDisciplinas().size() ; i++) {

        Disciplina * disciplinaAtual = periodoCopia->getDisciplinas().at(i);

        Candidato candidato = Candidato(i);

        Elemento elemnetoAnt = Elemento();

        if(disciplinaAtual->isDisciplinaAlocada())
            continue;

        for (unsigned int k = 0; k < disciplinaAtual->getQuadroHorario()->getQntDiasHorario(); k++) {
            Elemento bestElemento = Elemento();


            bestElemento.setTaxaAvaliacao(ULLONG_MAX);

            for (unsigned int j = 0; j < solucaoAtual->getSalas().size() ; ++j) {

                Sala * salaAtual = solucaoAtual->getSalas().at(j);

                bool salaOcupada = false;
                Aula * qh = disciplinaAtual->getQuadroHorario()->getAulas().at(k);
                for (int x = 0; x < qh->getHorario().size(); x++) {
                    if(salaAtual->getQuadroHorario().at(qh->getSemana(x)).at(qh->getPeriodo(x))->isOcupado()){
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

void Grasp::buscaLocal(Solucao *solucaoTemp, Periodo *periodoCopia) {
    bool melhora = true;
//    Solucao * solucaoTemp  = new Solucao(*solucaoAtual);

    while(melhora) {

        melhora = false;

        unsigned int randomNumberDisc = numeroRandom(periodoCopia->getDisciplinas().size());
        Disciplina *disciplinaOgigem = periodoCopia->getDisciplinas().at(randomNumberDisc);
        unsigned int randomNumberAula = numeroRandom(disciplinaOgigem->getQuadroHorario()->getAulas().size());
        Aula *aula = disciplinaOgigem->getQuadroHorario()->getAulas().at(randomNumberAula);
        Sala *salaOrigem = solucaoTemp->getSalas().at((unsigned int) aula->getIdSala());

        for (unsigned int i = 0; i < solucaoTemp->getSalas().size();) {
            Sala *sala = solucaoTemp->getSalas().at(i);
            if (sala == solucaoTemp->getSalas().at((unsigned int) aula->getIdSala())) {
                i++;
                continue;
            }

            unsigned __int64 valoOrigem = getValorFuncaoObjetivo(disciplinaOgigem, aula, salaOrigem);
            unsigned __int64 valoDestino = getValorFuncaoObjetivo(disciplinaOgigem, aula, sala);


            QuadroHorario *quadroHorarioDestino = sala->getQuadroHorario().at(aula->getSemana(0)).at(
                    aula->getPeriodo(0));
            if (!quadroHorarioDestino->isOcupado()) {
                //mover

                if (valoDestino < valoOrigem) {
                    moveSwap(disciplinaOgigem, aula, salaOrigem, sala, true);
                    melhora = true;
                    break;
                }



            } else {
                //troca
                Disciplina *disciplinaDestino = quadroHorarioDestino->getDisciplina();
                Aula *aulaDistino = nullptr;
                for (auto d: disciplinaDestino->getQuadroHorario()->getAulas()) {
                    if (d->getSemana(0) == aula->getSemana(0) && d->getPeriodo(0) == aula->getPeriodo(0))
                        aulaDistino = d;
                }
                if (aulaDistino) {
                    unsigned __int64 valoDestinoDiscD = getValorFuncaoObjetivo(disciplinaDestino, aulaDistino,
                                                                               salaOrigem);
                    unsigned __int64 valoOrigemDiscD = getValorFuncaoObjetivo(disciplinaDestino, aulaDistino,
                                                                              solucaoTemp->getSalas().at(
                                                                                      (unsigned int) aulaDistino->getIdSala()));
                    if ((valoDestinoDiscD + valoDestino) < (valoOrigemDiscD + valoOrigem)) {
                        moveSwap(disciplinaOgigem, aula, salaOrigem, sala, false);
                        moveSwap(disciplinaDestino, aulaDistino, sala, salaOrigem, false);
                        melhora = true;
                        break;
                    }
                }
            }
            i++;
        }
    }
}

void Grasp::moveSwap(Disciplina * disciplina, Aula * aula, Sala * salaOrigem, Sala * salaDestino, bool reset){

    for (int i = 0; i < aula->getHorario().size(); ++i) {
        salaDestino->getQuadroHorario().at(aula->getSemana(i)).at(aula->getPeriodo(i))->setDisciplina(disciplina);
        salaDestino->getQuadroHorario().at(aula->getSemana(i)).at(aula->getPeriodo(i))->setOcupado(true);
        aula->setIdSala(salaDestino->getId());

        if(reset)
            salaOrigem->getQuadroHorario().at(aula->getSemana(i)).at(aula->getPeriodo(i))->reset();
    }


}
unsigned __int64 Grasp::getValorFuncaoObjetivo(Disciplina * disciplina, Aula * aula, Sala * sala){
    unsigned __int64 taxaFinal = 0;

    if(sala->getTipoSala() == Fantasma){
        return SEM_SALA;
    }

    taxaFinal += getRazaoSimples(disciplina, sala);

        for (auto aulas: disciplina->getQuadroHorario()->getAulas()) {
            if(aulas != aula){
                taxaFinal += getRazaoBloco(sala, salasOriginal->getSalas().at((unsigned int) aulas->getIdSala()));
            }
        }


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

unsigned __int64 Grasp::getRazaoBloco(Sala * sala, Sala * sala1){
    if(sala->getTipoBloco() == sala1->getTipoBloco())
        return 0;
    return BLOCO_DIFERENTE;
}

unsigned __int64 Grasp::getRazaoTotal(Periodo * periodo, Solucao * solucao){
    unsigned __int64  taxaAvaliacao = 0;
    for (auto displina: periodo->getDisciplinas()) {
        Sala * antSala = nullptr;
//        std::cout<< displina->getNomeDisciplina() << std::endl;
//        std::cout<< displina->getQntAlunos() << std::endl;
        for (auto aulas: displina->getQuadroHorario()->getAulas()) {
            Sala * sala = solucao->getSalas().at((unsigned int) aulas->getIdSala());
//            std::cout<< sala->getSala() << std::endl;
//            for (auto a : aulas->getHorario()) {
//                QuadroHorario * quadro =sala->getQuadroHorario().at(a.semana == 0 ? 0 : a.semana - 1).at(a.periodo == 0 ? 0 : a.periodo - 1);
//                std::cout<<  quadro->getDisciplina()->getNomeDisciplina() << std::endl;
//            }

            if(sala->getTipoSala() == Fantasma){
                taxaAvaliacao += SEM_SALA;

            }else{
                taxaAvaliacao += aulas->getHorario().size()*getRazaoSimples(displina, sala);

                if(antSala){
                    taxaAvaliacao += getRazaoBloco(sala, antSala);
                }
            }


            antSala = sala;
        }
//        std::cout<< taxaAvaliacao << std::endl;
//        std::cout << "" << std::endl;
    }
    return taxaAvaliacao;
}