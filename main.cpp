#include <iostream>
#include <vector>
#include "gramatica.h"
#include "automato.h"

int main() {
  Gramatica gmc;

  // gmc("S", {{"A", "A"}});
  // gmc("A", {{"a", "A"}, {"b"}});
  // gmc.setTerminais({"a", "b"});
  // gmc.setNaoTerminais({"S", "A"});

  // gmc("S", {{"(", "L", ")"}, {"x"}});
  // gmc("L", {{"S"}, {"L", ";", "S"}});
  // gmc.setTerminais({"(", ")", ";", "x"});
  // gmc.setNaoTerminais({"S", "L"});

  gmc("E", {{"E", "+", "T"}, {"T"}});
  gmc("T", {{"T", "*", "F"}, {"F"}});
  gmc("F", {{"(", "E", ")"}, {"id"}});
  gmc.setTerminais({"+", "*", "(", ")", "id"});
  gmc.setNaoTerminais({"E", "T", "F"});

  // Gramatica gmc("&");
  // gmc("P", {{"K", "V", "C"}});
  // gmc("K", {{"c", "K"}, {"&"}});
  // gmc("V", {{"v", "V"}, {"F"}});
  // gmc("F", {{"f", "P", ";", "F"}, {"&"}});
  // gmc("C", {{"b", "V", "C", "e"}, {"com", ";", "C"}, {"&"}});
  // gmc.setTerminais({"c", "v", "f", ";", "b", "e", "com"});
  // gmc.setNaoTerminais({"P", "K", "V", "F", "C"});

  // gmc("S", {{"L", "=", "R"}, {"R"}});
  // gmc("L", {{"*", "R"}, {"id"}});
  // gmc("R", {{"L"}});
  // gmc.setTerminais({"=", "*", "id"});
  // gmc.setNaoTerminais({"S", "L", "R"});

  // gmc("S", {{"E"}});
  // gmc("E", {{"T"}, {"E", "+", "T"}});
  // gmc("T", {{"int"}, {"(", "E", ")"}});
  // gmc.setTerminais({"+", "int", "(", ")"});
  // gmc.setNaoTerminais({"S", "E", "T"});

  gmc.extender();

  Automato aut = Automato(gmc);
  return 0;
}
