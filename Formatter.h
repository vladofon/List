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
   Formatter(long cols, long rows, string header)
   {
      this->header = header;
      this->cols = cols;
      this->rows = rows;
      this->space = 2;
   }

   string format(List<Pair>* pairs)
   {
      List<string>* firstTeamNames = parseNames(pairs, true);
      List<string>* secondTeamNames = parseNames(pairs, false);

      long firstLength = maxCellLength(firstTeamNames);
      long secondLength = maxCellLength(secondTeamNames);

      long cellWidth = (firstLength > secondLength) ? firstLength : secondLength;
      cellWidth = (cellWidth % 2 == 0) ? cellWidth : cellWidth + 1;

      string table = createHeader(header, cellWidth);

      for (long i = 0; i < rows; i++)
      {
         Pair pair = pairs->get(i);

         string row = (i == rows - 1) ? createRow(pair, cellWidth, true) : createRow(pair, cellWidth);

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

   string header;
   long cols;
   long rows;
   long space;

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

   string createHeader(string text, long cellWidth)
   {
      long paddingSpaces = space * cols;
      long colBorders = (cols - 1);
      long headerWhitespaces = calcWhiteSpace(text, cellWidth) + paddingSpaces + colBorders;
      string padding = repeat(SPACING, headerWhitespaces + (space / 2));
      string headerBody = padding + text + padding;
      string borderBody = repeat(ROW_FILLER, headerBody.length());

      string border = SEPARATOR + borderBody + SEPARATOR + ROW_SEPARATOR;
      string header = COL_FILLER + headerBody + COL_FILLER + ROW_SEPARATOR;

      return (border + header);
   }

   string createRow(Pair pair, long cellWidth, bool clossingCell = false)
   {
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
      string contentBody = leftCell + COL_FILLER + rightCell;
      string borderBody = repeat(ROW_FILLER, contentBody.length());

      string border = SEPARATOR + borderBody + SEPARATOR + ROW_SEPARATOR;
      string main = COL_FILLER + contentBody + COL_FILLER + ROW_SEPARATOR;

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
      string result;
      if (count != 0)
         result = symbol;

      for (int i = 0; i < count - 1; i++)
      {
         result += symbol;
      }

      return result;
   }
};