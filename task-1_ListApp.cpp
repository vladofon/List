#include <iostream>
#include <string>
#include <malloc.h>
#include "LinkedList.h"
#include "ArrayList.h"
#include "Formatter.h"
#include "FencingCompetition.h"

using namespace std;

void assignIfBigger(long& to, long from)
{
   if (from > to)
      to = from;
}

int main()
{
   FencingCompetition* competition = new FencingCompetition(5, 2);

   List<string>* firstTeam = new LinkedList<string>();
   firstTeam->addAll(16, new string[16]{
      "Edoardo Mangiarotti","Jeon Hee Suk",
      "Giovanna Trillini","Danuta Dmowska",
      "Valentina Vezzali","Mihai Covaliu",
      "Giuseppe Delfino","Johan Harmenberg",
      "Lucien Gaudin","Marcel Fischer",
      "Elena Novikova", "Sergei Golubitsky",
      "Viktor Sidyak", "Norman Armitage",
      "Stanislav Pozdnyakov", "George Worth" });

   List<string>* secondTeam = new LinkedList<string>();
   secondTeam->addAll(16, new string[16]{
      "Viktor Krovopuskov", "Camillo Agrippa",
      "Carlo Pavesi", "Francesco Alfieri",
      "Albert Bogen", "Domenico Angelo",
      "Ellen Osiier", "Salvator Fabris",
      "Irina Embrich", "Ridolfo Capo Ferro",
      "Helene Mayer", "George Silver",
      "Bob Anderson", "Hans Talhoffer",
      "Boaz Ellis", "Chevalier de Saint-Georges" });

   competition->setFirstTeam(firstTeam);
   competition->setSecondTeam(secondTeam);

   Formatter* formatter = new Formatter(2, 5, "Fencers");

   List<Pair>* pairs = competition->makeDraw();
   firstTeam->merge(secondTeam);

   cout << formatter->formatBySchema(firstTeam, pairs) << endl;

   /* cout << formatter->format(competition->makeDraw()) << endl;*/

   system("pause");
   return 0;
}


