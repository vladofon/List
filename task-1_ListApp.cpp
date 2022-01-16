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
   firstTeam->addAll(16, new string[16]{
      "f.first","f.second",
      "f.third","f.fourth",
      "f.fifth","f.sixth",
      "f.seventh","f.eighth",
      "f.ninth","f.tenth",
      "s.eleventh", "s.twelfth",
      "s.thirteenth", "s.fourteenth",
      "s.fifteenth", "s.sixteenth" });

   List<string>* secondTeam = new LinkedList<string>();
   secondTeam->addAll(16, new string[16]{
      "s.first", "s.second",
      "s.third", "s.fourth",
      "s.fifth", "s.sixth",
      "s.seventh", "s.eighth",
      "s.ninth", "s.tenth",
      "s.eleventh", "s.twelfth",
      "s.thirteenth", "s.fourteenth",
      "s.fifteenth", "s.sixteenth" });

   competition->setFirstTeam(firstTeam);
   competition->setSecondTeam(secondTeam);

   Formatter* formatter = new Formatter(2, 5, "Fencers");
   cout << formatter->format(competition->makeDraw()) << endl;

   return 0;
}
