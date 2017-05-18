//
// Created by Alex on 15/05/2017.
//

#ifndef METAG_ELEMENTO_H
#define METAG_ELEMENTO_H


#include "Sala.h"

class Elemento {
private:
    Sala * salaCandidata;
    Disciplina * disciplinaCandidata;
    Aula * aula;
    int indexSala, indexDisciplina;
    unsigned __int64 taxaAvaliacao;
    Elemento * prev;

public:
    Elemento(){
        salaCandidata = nullptr;
        disciplinaCandidata = nullptr;
        aula = nullptr;
        prev = nullptr;
    }
    Elemento(Disciplina *disciplinaCandidata, int indexDisciplina, Aula * aula) :
            indexDisciplina(indexDisciplina), aula(aula), disciplinaCandidata(disciplinaCandidata)
    {
        taxaAvaliacao = 0;
        prev = nullptr;
    }

    void setSala(Sala *sC, int iS)
    {
        salaCandidata = sC;
        indexSala = iS;
    }

    Sala *getSalaCandidata() const { return salaCandidata; }
    void setSalaCandidata(Sala *salaCandidata) { Elemento::salaCandidata = salaCandidata; }

    Disciplina *getDisciplinaCandidata() const { return disciplinaCandidata; }
    void setDisciplinaCandidata(Disciplina *disciplinaCandidata) { Elemento::disciplinaCandidata = disciplinaCandidata; }

    int getIndexSala() const { return indexSala; }
    void setIndexSala(int indexSala) { Elemento::indexSala = indexSala; }

    int getIndexDisciplina() const { return indexDisciplina; }
    void setIndexDisciplina(int indexDisciplina) { Elemento::indexDisciplina = indexDisciplina; }

    unsigned __int64 getTaxaAvaliacao() const { return taxaAvaliacao; }
    void setTaxaAvaliacao(unsigned __int64 taxaAvaliacao) { Elemento::taxaAvaliacao = taxaAvaliacao; }

    Aula *getAula() const { return aula; }
    void setAula(Aula *aula) { Elemento::aula = aula; }

    Elemento *getPrev() const { return prev; }

    void setPrev(Elemento *prev) { Elemento::prev = prev; }

    unsigned __int64 getTaxaAtualAvaliacao();
};


#endif //METAG_ELEMENTO_H
