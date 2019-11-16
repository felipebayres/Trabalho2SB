#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

struct  TabelaSimbolos {
bool definido = false;
vector<int> LugaresUsados;

// Guarda a linha do arquivo pre processado em que o simbolo aparece
vector<int> LinhasUsadas;

// Esse campo define se ele é um endereco ou uma constante
    // 0 - Label
    // 1 - constante
    // 2 - dado (Space)
int Tipo;
//Se o simbolo for definido o Valor guarda o lugar em que ele foi definido
int Valor;
//O valor do Simbolo se ele for constante
int constante = -1;
int QuantidadeSpace = 0;
bool externo = false;
bool publico = false;
};

struct TabelaUsos {
//Lugares em que o label externo foi utilizado
vector<int> LugaresUsados;

};
struct TabelaDefinicao{
// Lugar aonde o label é encontrado
int Valor;
bool definido;
};
string MontadorUmaPassada(string NomeArquivo,bool DoisArquivos);
bool ValidaToken(string token);
bool ValidaLabel(string Label);
bool VerificaHexa(string Numero);
int ValidaInstrucao(string instrucao);
string PadronizaSection(string NomeArquivo, bool DoisArquivos);