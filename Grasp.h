//
// Created by Alex on 14/05/2017.
//

#ifndef METAG_GRASP_H
#define METAG_GRASP_H


#include "Periodo.h"
#include "Solucao.h"
#include "Candidatos.h"

class Grasp {
private:
    Periodo * periodoOriginal;
    Solucao * salasOriginal;
    int numeroIteracoes;
    float alpha;
public:
    Grasp(Periodo * periodo, Solucao * solucao, int iteracoes, float talpha){
        periodoOriginal = periodo;
        salasOriginal = solucao;
        numeroIteracoes = iteracoes;
        alpha = talpha;
    }

    Periodo *getPeriodoOriginal() const { return periodoOriginal; }

    void setPeriodoOriginal(Periodo *periodo) { periodoOriginal = periodo; }

    Solucao *getSalaOriginal() const { return salasOriginal; }

    void setSalaOriginal(Solucao *periodo) { salasOriginal = periodo; }

    int getNumeroIteracoes() const { return numeroIteracoes; }

    void setNumeroIteracoes(int iteracoes) { numeroIteracoes = iteracoes; }

    float getAuth() const { return alpha; }

    void setAuth(float tauth) { alpha = tauth; }

    void execute();
    void construcao(Solucao * solucao, Periodo * periodoCopia);
    void montarCandidatos(Candidatos *candidatos, Solucao * solucaoAtual, Periodo * periodoCopia);
    unsigned int numeroRandom(int max);
    void buscaLocal(Solucao * solucaoAtual, Periodo * periodoCopia);


    unsigned long long int getRazaoSimples(Disciplina *disciplina, Sala *sala);

    void printTime(time_t inicio, time_t fim);

    unsigned long long int getRazaoBloco(Sala *sala, Sala *sala1);

    unsigned long long int getRazaoTotal(Periodo *periodo, Solucao *solucao);

    unsigned long long int getValorFuncaoObjetivo(Disciplina *disciplina, Aula *aula, Sala *sala);

    void moveSwap(Disciplina *disciplina, Aula *aula, Sala *salaOrigem, Sala *salaDestino, bool reset);
};


#endif //METAG_GRASP_H
