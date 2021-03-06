//
// Created by Alex on 24/02/2017.
//

#ifndef METAG_TIPOSTRUCT_H
#define METAG_TIPOSTRUCT_H

enum TipoSala { Carteiras, Computadores, Fantasma };
enum TipoCurso { CC, SPI, GTI, REDE, ARQ };
enum TipoBloco { EVA, F, Q, G, C, J};

unsigned __int64 const TIPO_SALA = 1000000ULL;
unsigned __int64 const CAPACIDADE_SALA = 1000000000ULL;
unsigned __int64 const BLOCO_DIFERENTE = 1000ULL;
unsigned __int64 const SEM_SALA = 1000000000ULL;

#endif //METAG_TIPOSTRUCT_H
