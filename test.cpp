//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;

const char SEP[] = ",.;:/|-&%$+=*?";

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }
    string gen_word() {
        string s;
        int n;

        n = 2 + (rand() % 32);
        while (n-- > 0) s += (char)('a'+(rand() % 26));
        return s;

    }

    char rand_char() {
        return SEP[rand()%(sizeof(SEP)-1)];
    }

    string gen_sep(int lensep) {
        string sep;
        while (lensep > 0) {
            char c = rand_char();
            if (sep.find(c) == string::npos) {
                sep += c;
                lensep--;
            }
        }
        return sep;
    }

    string gen_string(string & s, list<string> & q, int lensep) {
        string sep = gen_sep(lensep);
        string w;

        int j = 2+(rand()%20); // qtde de substrings
        while (j-- > 1) {
            w = gen_word();
            q.push_back(w);
            s += w;
            s += sep;
        }
        w = gen_word();
        q.push_back(w);
        s += w;

        return sep;
    }

    string junta(list<string> & l, const string & sep) {
        string r;

        if (l.empty()) return r;
        auto it = l.begin();
        r = *it;
        for (it++; it != l.end(); it++) r += sep + *it;

        return r;
    }

    void teste(int lensep)
    {
        string s;
        string sep;

        try {
            for (int n=0; n < 10; n++) {
                list<string> q1, q2;
                s = "";
                sep = gen_string(s, q1, lensep);
                q2 = separa(s, sep);

                if (q1 != q2) {
                    string r1 = junta(q1, ", ");
                    string r2 = junta(q2, ", ");

                    FAIL() << "Após separar: string="+s+" separador="+sep
                    << "; Obteve resultado: "+r2
                    << "; Esperado: "+r1;
                    return;
                }
            }
        } catch (...) {
            FAIL() << "ocorreu uma exceção: string="+s
            << ">>> sep="+sep;
        }
    }

};

TEST_F(TesteQuestao, Vazia)
{
    for (int i=0; i < 10; i++) {
        try {
            list<string> q;
            q = separa("", gen_sep(4));

            if (q.size() > 0) {
                FAIL() << "lista tem tamanho maior que 0 após enfileirar substrings de uma string vazia";
                return;
            }

        } catch (...) {
            FAIL() << "ocorreu uma exceção";
        }
    }
}

TEST_F(TesteQuestao, Simples)
{
    for (int i=0; i < 10; i++) {
        try {
            list<string> q;
            string w = gen_word();
            string sep = gen_sep(4);
            q = separa(w, sep);

            if (q.size() != 1) {
                FAIL() << "lista tem tamanho "+to_string(q.size())+", mas deveria ter size 1: string="+w+" separador="+sep;
                return;
            }

        } catch (...) {
            FAIL() << "ocorreu uma exceção";
        }
    }
}

TEST_F(TesteQuestao, Normal) {
    teste(1);
}

TEST_F(TesteQuestao, Multiplo)
{
    teste(2+(rand() % 3));
}

