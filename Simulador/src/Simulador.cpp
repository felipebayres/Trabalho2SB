#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string>
#include <sstream>
#include "Simulador.hpp"
using namespace std;

void Simulador(string NomeArqObjeto){

  ifstream Arquivo; // ponteiro arquivo
  string linha; // linha do arquivo objeto
  vector<int> vectorObjeto; // vector para códigos (int)

  int16_t memoria[2]; // memoria simulada
  int PC = 0; // PC
  int ACC = 0;  // registrador acumulador
  int posOP1 = 0; // endereço do primeiro operando da instrução no vetor de códigos
  int posOP2 = 0; // endereço do segundo operando da instrução no vetor de códigos
  int buffer; // auxiliar para entrada da instrução INPUT

  Arquivo.open(NomeArqObjeto);
  if (!Arquivo.is_open()){
    cout << "Não foi possível abrir o arquivo objeto " << NomeArqObjeto << "\n";
    return ;
  }
  else{
    getline(Arquivo, linha);
    istringstream iss(linha);
    string subs;  // buffer para substrings da linha do arquivo .obj
    int subs_int; // opcode ou operando inteiro do arquivo .obj
    while (iss)
    {
      iss >> subs;
      if (subs != "OO"){  // "códigos" gerados pela diretiva SPACE
        subs_int = stoi(subs);
        vectorObjeto.push_back(subs_int); // push do código inteiro para o vetor objeto
      }
      else{
        subs_int = 0;
        vectorObjeto.push_back(subs_int); // push do código inteiro para o vetor objeto
      }
    }
  }

  while(vectorObjeto.at(PC) != STOP){
    switch (vectorObjeto.at(PC)){
      case ADD: // 1
        cout << "*ADD*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        ACC = ACC + (vectorObjeto.at(posOP1));
        PC++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case SUB: //2
        cout << "*SUB*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        ACC = ACC - (vectorObjeto.at(posOP1));
        PC++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case MUL: //3
        cout << "*MUL*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        ACC = ACC * (vectorObjeto.at(posOP1));
        PC++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case DIV: //4
        cout << "*DIV*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        ACC = ACC / (vectorObjeto.at(posOP1));
        PC++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMP: //5
        cout << "*JMP*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        PC = posOP1;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMPN:  //6
        cout << "*JMPN*" << endl;
        if(ACC < 0){
          posOP1 = vectorObjeto.at(++PC);
          PC = posOP1;
        }else{
          PC = PC + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMPP:  //7
        cout << "*JMPP*"<< endl;
        if(ACC > 0){
          posOP1 = vectorObjeto.at(++PC);
          PC = posOP1;
        }else{
          PC = PC + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMPZ:  //8
        cout << "*JMPZ*" << endl;
        if(ACC == 0){
          posOP1 = vectorObjeto.at(++PC);
          PC = posOP1;
        }else{
          PC = PC + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case COPY:  //9
        cout << "*COPY*" << endl;
        posOP1 = vectorObjeto.at(PC + 1);
        posOP2 = vectorObjeto.at(PC + 2);
        vectorObjeto.at(posOP2) = vectorObjeto.at(posOP1);
        memoria[0] = posOP2;
        memoria[1] = vectorObjeto.at(posOP2);
        PC = PC + 3;

        cout << "Endereço de memoria:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;

        break;
      
      case LOAD:  //10
        cout << "*LOAD*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        ACC = vectorObjeto.at(posOP1);
        PC++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case STORE: //11
        cout << "*STORE*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        vectorObjeto.at(posOP1) = ACC;
        memoria[0] = posOP1;
        memoria[1] = ACC;
        cout << "Endereço de memoria:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;
        PC++;
        break;

      case INPUT: //12
        cout << "*INPUT*" << endl;

        cout << "Favor inserir um valor numérico: ";
        cin >> buffer;
        posOP1 = vectorObjeto.at(++PC);
        vectorObjeto.at(posOP1) = buffer;
        memoria[0] = posOP1;
        memoria[1] = buffer;
        PC++;

        cout << "Endereço de Memória:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;
        break;

      case OUTPUT:  //13
        cout << "*OUTPUT*" << endl;
        posOP1 = vectorObjeto.at(++PC);
        cout << "O valor de saída é:" << vectorObjeto.at(posOP1) << endl;
        PC++;
        break;

      default:
        break;
    }
    cout << endl;
  }
}