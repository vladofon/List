#pragma once
#include<string>
#include"List.h"
#include"ArrayList.h"
#include"Pair.h"
#include"FencingCompetition.h"

using namespace std;

class Formatter
{
public:
   Formatter(long cols, long rows)
   {
      this->cols = cols;
      this->rows = rows;
   }

   string format(List<Pair>* pairs)
   {
      List<string>* firstTeamNames = parseNames(pairs, true);
      List<string>* secondTeamNames = parseNames(pairs, false);

      long firstLength = maxCellLength(firstTeamNames);
      long secondLength = maxCellLength(secondTeamNames);

      long cellWidth = (firstLength > secondLength) ? firstLength : secondLength;

      string table;

      for (long i = 0; i < rows; i++)
      {
         Pair pair = pairs->get(i);

         string row = (i == rows - 1) ? createRow(pair, cellWidth) : createRow(pair, cellWidth, true);

         table += row;
      }

      return table;
   }

private:
   const string SEPARATOR = "+";
   const string ROW_SEPARATOR = "\r\n";
   const string ROW_FILLER = "-";
   const string COL_FILLER = "|";
   const string SPACING = " ";

   long cols;
   long rows;

   List<string>* parseNames(List<Pair>* pairs, bool isFirstTeam)
   {
      List<string>* teamNames = new ArrayList<string>();
      for (long i = 0; i < pairs->getSize(); i++)
      {
         if (isFirstTeam)
            teamNames->add(pairs->get(i).getFirstFencer());
         else
            teamNames->add(pairs->get(i).getSecondFencer());
      }

      return teamNames;
   }

   long maxCellLength(List<string>* names)
   {
      long maxLength = 0;

      for (long i = 0; i < names->getSize(); i++)
      {
         string name = names->get(i);

         if (name.length() > maxLength)
         {
            maxLength = name.length();
         }
      }

      return maxLength;
   }

   long calcWhiteSpace(string str, long width)
   {
      return width - str.length();
   }

   string createRow(Pair pair, long cellWidth, bool clossingCell = false)
   {
      long space = 2; // must be even number
      long paddingSpaces = space * cols;
      long colBorders = (cols - 1);
      string padding = repeat(SPACING, space / 2);

      string first = pair.getFirstFencer();
      string firstWhitespaces = repeat(SPACING, calcWhiteSpace(first, cellWidth));
      string firstCellContent = first + firstWhitespaces;

      string second = pair.getSecondFencer();
      string secondWhitespaces = repeat(SPACING, calcWhiteSpace(second, cellWidth));
      string secondCellContent = second + secondWhitespaces;

      string leftCell = padding + firstCellContent + padding;
      string rightCell = padding + secondCellContent + padding;
      string rowBody = leftCell + COL_FILLER + rightCell;

      string border = SEPARATOR + repeat(ROW_FILLER, rowBody.length()) + SEPARATOR + ROW_SEPARATOR;
      string main = COL_FILLER + rowBody + COL_FILLER + ROW_SEPARATOR;

      if (clossingCell)
      {
         return (border + main + border);
      }
      else
      {
         return (border + main);
      }
   }

   string repeat(string symbol, long count)
   {
      for (int i = 0; i < count - 1; i++)
      {
         symbol += symbol;
      }

      return symbol;
   }
};