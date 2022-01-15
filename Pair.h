#pragma once
#include<string>

using namespace std;

class Pair
{
public:
   Pair(string firstFencer, string secondFencer)
   {
      this->firstFencer = firstFencer;
      this->secondFencer = secondFencer;
   }

   Pair()
   {

   }

   string getFirstFencer()
   {
      return this->firstFencer;
   }

   string getSecondFencer()
   {
      return this->secondFencer;
   }

private:
   string firstFencer;
   string secondFencer;
};