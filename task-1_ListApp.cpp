#include <iostream>
#include <string>
#include "LinkedList.h"
#include "FencingCompetition.h"
#include "FencersFormatter.h"

using namespace std;

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

   List<Pair>* pairs = competition->makeDraw();
   firstTeam->merge(secondTeam);

   FencersFormatter* formatter = new FencersFormatter();
   cout << formatter->format(firstTeam, pairs) << endl;

   system("pause");
   return 0;
}


