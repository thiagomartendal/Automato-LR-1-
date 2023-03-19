#include "automato.h"

Automato::Automato(Gramatica gmc) {
  this->gmc = gmc;
  Item primeiroItem = {this->gmc.getInicial(), this->gmc[this->gmc.getInicial()][0], 0, {"$"}};
  Estado estado = Automato::formarEstado({primeiroItem});
  estados.push_back(estado);
  Automato::construirAutomato(estado);

  for (Estado e: estados) {
    std::cout << e.getId() << '\n';
    int i = 1;
    for (Item item: e.getItens()) {
      std::cout << i << " (" << item.cabeca << " [";
      for (std::string str: item.prod.corpo)
        std::cout << str << ' ';
      std::cout << item.prod.numero << "] " << item.posPonto<< " {";
      for (std::string str: item.lookahead)
        std::cout << str << ' ';
      std::cout << "})\n";
      i++;
    }
    std::cout << "------------------\n";
  }

  for (auto& it: transicoes)
    std::cout << '(' << std::get<0>(it.first) << ',' << std::get<1>(it.first) << ") = " << it.second << '\n';

  std::cout << "Total de estados: " << estados.size() << '\n';
  std::cout << "Total de transições: " << transicoes.size() << '\n';
}

Estado Automato::formarEstado(std::vector<Item> itens) {
  Estado estado = Estado(idEstado);
  idEstado++;
  for (Item item: itens) {
    estado.inserirItem(item);
    std::set<std::string> novoLookahead = Automato::formarLookahead(item);
    Automato::procurarItens(estado, item, novoLookahead);
  }
  return estado;
}

std::set<std::string> Automato::formarLookahead(Item item) {
  std::set<std::string> lookahead;
  if (item.prod.corpo.size() > 1 && item.posPonto+1 < item.prod.corpo.size()) {
    std::string simbolo = item.prod.corpo[item.posPonto+1];
    if (gmc.naoTerminal(simbolo))
      lookahead = gmc.first()[simbolo];
    else
      lookahead.insert(simbolo);
  } else lookahead = item.lookahead;
  return lookahead;
}

void Automato::procurarItens(Estado &estado, Item item, std::set<std::string> lookahead) {
  if (item.posPonto < item.prod.corpo.size()) {
    std::string simbolo = item.prod.corpo[item.posPonto];
    if (gmc.naoTerminal(simbolo))
      for (Producao prod: gmc[simbolo]) {
        Item novoItem = {simbolo, prod, 0, lookahead};
        if (!estado.existeItem(novoItem)) {
          estado.inserirItem(novoItem);
          std::set<std::string> novoLookahead = Automato::formarLookahead(novoItem);
          Automato::procurarItens(estado, novoItem, novoLookahead);
        }
      }
  }
}

std::vector<Item> Automato::formarNucleo(Estado estado, std::string simboloTransicao) {
  std::set<Item> nucleo;
  for (Item item: estado.getItens())
    if (item.posPonto < item.prod.corpo.size()) {
      std::string simbolo = item.prod.corpo[item.posPonto];
      if (simbolo == simboloTransicao) {
        Item itemNucleo = {item.cabeca, item.prod, item.posPonto+1, item.lookahead};
        if (std::find(nucleo.begin(), nucleo.end(), itemNucleo) == nucleo.end())
          nucleo.insert(itemNucleo);
      }
    }
  std::vector<Item> tmp = std::vector<Item>(nucleo.begin(), nucleo.end());
  std::sort(tmp.begin(), tmp.end(), [](Item i1, Item i2) {
    return i1.lookahead < i2.lookahead;
  });
  return tmp;
}

void Automato::construirAutomato(Estado estado) {
  for (Item item: estado.getItens())
    if (item.posPonto < item.prod.corpo.size()) {
      std::string simbolo = item.prod.corpo[item.posPonto];
      std::vector<Item> nucleo = Automato::formarNucleo(estado, simbolo);
      Estado novoEstado = Automato::formarEstado(nucleo);
      auto busca = std::find(estados.begin(), estados.end(), novoEstado);
      if (busca == estados.end()) {
        estados.push_back(novoEstado);
        transicoes[std::make_tuple(estado.getId(), simbolo)] = novoEstado.getId();
        Automato::construirAutomato(novoEstado);
      } else {
        int indice = busca-estados.begin();
        transicoes[std::make_tuple(estado.getId(), simbolo)] = estados[indice].getId();
        idEstado--;
      }
    }
}
