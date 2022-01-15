#include <iostream>
#include <string>
#include <malloc.h>
#include "LinkedList.h"
#include "ArrayList.h"
#include "Formatter.h"
#include "FencingCompetition.h"

using namespace std;

int main()
{
   FencingCompetition* competition = new FencingCompetition(5, 2);

   List<string>* firstTeam = new LinkedList<string>();
   firstTeam->addAll(10, new string[10]{
      "f.first","f.second",
      "f.third","f.fourth",
      "f.fifth","f.sixth",
      "f.seventh","f.eighth",
      "f.ninth","f.tenth" });

   List<string>* secondTeam = new LinkedList<string>();
   secondTeam->addAll(10, new string[10]{
      "s.first", "s.second",
      "s.third", "s.fourth",
      "s.fifth", "s.sixth",
      "s.seventh", "s.eighth",
      "s.ninth", "s.tenth" });

   competition->setFirstTeam(firstTeam);
   competition->setFirstTeam(secondTeam);

   Formatter* formatter = new Formatter(2, 5);
   cout << formatter->format(competition->makeDraw()) << endl;

   return 0;
}
