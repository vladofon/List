#pragma once
#include "List.h"
#include "Pair.h"
#include "LinkedList.h"
#include<string>
#include<ctime>
#include <stdexcept>

using namespace std;

class FencingCompetition
{
public:
   FencingCompetition(long countOfPairs, long maxRange)
   {
      this->countOfPairs = countOfPairs;
      this->maxRange = maxRange;
   }

   List<Pair>* makeDraw()
   {
      validate();

      List<Pair>* pairs = new LinkedList<Pair>();

      srand(time(0));
      int n = rand() % maxRange + 1;
      int m = rand() % maxRange + 1;

      for (int i = 0; i < countOfPairs; i++)
      {
         pairs->add(Pair(firstTeam->get(n + n * i), secondTeam->get(m + m * i)));
      }

      return pairs;
   }

   void setFirstTeam(List<string>* team)
   {
      this->firstTeam = team;
   }

   void setSecondTeam(List<string>* team)
   {
      this->secondTeam = team;
   }

private:
   long countOfPairs;
   long maxRange;
   List<string>* firstTeam;
   List<string>* secondTeam;

   void validate() {
      if (firstTeam->getSize() < (countOfPairs * maxRange) + countOfPairs)
      {
         throw invalid_argument("First team is too small!");
      }
      if (secondTeam->getSize() < (countOfPairs * maxRange) + countOfPairs)
      {
         throw invalid_argument("Second team is too small!");
      }
   }
};