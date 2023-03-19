#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <iostream>
#include <tuple>
#include "estado.h"

class Automato {
private:
  Gramatica gmc;
  unsigned int idEstado{0};
  std::vector<Estado> estados;
  std::map<std::tuple<unsigned int, std::string>, unsigned int> transicoes;
  Estado formarEstado(std::vector<Item> itens);
  std::set<std::string> formarLookahead(Item item);
  void procurarItens(Estado &estado, Item item, std::set<std::string> lookahead);
  std::vector<Item> formarNucleo(Estado estado, std::string simboloTransicao);
  void construirAutomato(Estado estado);
  
public:
  Automato(Gramatica gmc);
};

#endif
