//
// Created by Alex on 15/05/2017.
//

#include "Elemento.h"
#include "Avaliacao.h"

unsigned __int64 Elemento::getTaxaAtualAvaliacao(){
    if(salaCandidata->getTipoSala() != disciplinaCandidata->getReqTipoSala())
        taxaAvaliacao += TIPO_SALA;
    if(salaCandidata->getQuantidade() < disciplinaCandidata->getQntAlunos())
        taxaAvaliacao += CAPACIDADE_SALA;
    if(disciplinaCandidata->getQuadroHorario()->getQntDiasHorario() > 1){
        if(prev != nullptr){
            if(prev->getSalaCandidata()->getTipoBloco() != salaCandidata->getTipoBloco()){
                taxaAvaliacao += BLOCO_DIFERENTE;
            }
        }
    }
    return taxaAvaliacao;
}


