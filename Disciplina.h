//
// Created by Alex on 24/02/2017.
//

#ifndef METAG_DISCIPLINA_H
#define METAG_DISCIPLINA_H

#include <string>
#include "TipoStruct.h"
#include "Horario.h"

class Disciplina {
private:
    std::string codDisciplina, nomeDisciplina, nomeProfessor;
    int qntAlunos;
    TipoCurso tipoCurso;
    TipoSala reqTipoSala;
    bool disciplinaAlocada;
    Horario * quadroHorario;

public:
    Disciplina(const Disciplina &disc):
            codDisciplina(disc.codDisciplina),
            nomeDisciplina(disc.nomeDisciplina),
            nomeProfessor(disc.nomeProfessor),
            qntAlunos(disc.qntAlunos),
            tipoCurso(disc.tipoCurso),
            reqTipoSala(disc.reqTipoSala),
            disciplinaAlocada(disc.disciplinaAlocada),
            quadroHorario(new Horario(*disc.quadroHorario))
    {};
    Disciplina(){
        disciplinaAlocada = false;
    }

    virtual ~Disciplina() {
        delete quadroHorario;
    }

    std::string getNomeDisciplina(){return nomeDisciplina;}
    void setNomeDisciplina(std::string nome){nomeDisciplina = nome;}

    std::string getNomeProfessor(){ return nomeProfessor; }
    void setNomeProfessor(std::string n) { nomeProfessor = n; }

    std::string getCodDisciplina(){ return codDisciplina; }
    void setCodDisciplina(std::string c) { codDisciplina = c; }

    TipoCurso getTipoCurso(){ return tipoCurso; }
    void setTipoCurso(TipoCurso t) { tipoCurso = t; }

    TipoSala getReqTipoSala(){ return reqTipoSala; }
    void setReqTipoSala(TipoSala r) { reqTipoSala = r; }

    int getQntAlunos(){ return qntAlunos; }
    void setQntAlunos(int q) { qntAlunos = q; }

    bool isDisciplinaAlocada(){ return disciplinaAlocada; }
    void setDisciplinaAlocada(bool d) { disciplinaAlocada = d; }

    Horario * getQuadroHorario() { return quadroHorario; }
    void setQuadroHorario(Horario * q) { quadroHorario = q;}
};


#endif //METAG_DISCIPLINA_H
