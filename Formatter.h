#pragma once
#include<string>
#include"List.h"
#include"ArrayList.h"
#include"Pair.h"
#include "TableSchema.h"
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

   TableSchema* initDefaultSchema(List<string>* participants, List<Pair>* pairs)
   {
      string rowCompetition = "============+ Fencing competition +============";
      string colParticipants = "List of participants";

      string rowDraw = "Draw results";
      string colFirstTeam = "First team";
      string colSecondTeam = "Second team";

      schema = new TableSchema();

      schema->createRow(rowCompetition);
      schema->getRow(0).createColumn(colParticipants);

      schema->createRow(rowDraw);
      schema->getRow(1).createColumn(colFirstTeam);
      schema->getRow(1).createColumn(colSecondTeam);

      fillColumn(0, 0, schema, participants);
      fillColumn(1, 0, schema, parseNames(pairs, true));
      fillColumn(1, 1, schema, parseNames(pairs, false));

      return schema;
   }

   string formatBySchema(List<string>* participants, List<Pair>* pairs)
   {
      List<string>* firstTeamNames = parseNames(pairs, true);
      List<string>* secondTeamNames = parseNames(pairs, false);
      List<string>* headersNames = new LinkedList<string>();

      initDefaultSchema(participants, pairs);

      long firstLength = maxCellLength(firstTeamNames);
      long secondLength = maxCellLength(secondTeamNames);
      long headersLength = maxHeaderLength();

      long cellWidth = 0;

      if (firstLength > secondLength)
      {
         cellWidth = firstLength;
      }
      if (secondLength > firstLength)
      {
         cellWidth = secondLength;
      }
      if (headersLength > cellWidth)
      {
         cellWidth = headersLength;
      }

      cellWidth = (cellWidth % 2 == 0) ? cellWidth : cellWidth + 1;

      return parseSchema(cellWidth);
   }

   string parseSchema(long cellWidth)
   {
      string table = "";

      for (long row = 0; row < schema->rowsCount(); row++)
      {
         List<string>* rowHeader = new LinkedList<string>();
         List<string>* colHeader = new LinkedList<string>();
         List<List<string>*>* colsCells = new LinkedList<List<string>*>();

         rowHeader->add(schema->getRow(row).getName());

         for (long col = 0; col < schema->getRow(row).colsCount(); col++)
         {
            List<string>* colCells = new LinkedList<string>();

            colHeader->add(schema->getRow(row).getColumn(col).getName());
            colsCells->add(colCells);

            for (long cell = 0; cell < schema->getRow(row).getColumn(col).cellsCount(); cell++)
            {
               colCells->add(schema->getRow(row).getColumn(col).getCell(cell).getData());
            }
         }

         List<List<string>*>* rowsDataContainer = new LinkedList<List<string>*>();

         /* all columns must have the same size! */
         long colCapacity = colsCells->get(0)->getSize();

         for (long rowNumber = 0; rowNumber < colCapacity; rowNumber++)
         {
            /* one row to be created */
            List<string>* rowData = new LinkedList<string>();

            rowsDataContainer->add(rowData);
         }

         for (long col = 0; col < colsCells->getSize(); col++)
         {
            for (long rowPiece = 0; rowPiece < colCapacity; rowPiece++)
            {
               string cellData = colsCells->get(col)->get(rowPiece);

               rowsDataContainer->get(rowPiece)->add(cellData);
            }
         }

         long totalColsCount = maxColumnCountInRow();

         table += createRow(rowHeader, cellWidth, totalColsCount, true);

         table += createRow(colHeader, cellWidth, totalColsCount, true);

         for (long completedRow = 0; completedRow < rowsDataContainer->getSize(); completedRow++)
         {
            List<string>* rowToCreate = rowsDataContainer->get(completedRow);

            if (row == schema->rowsCount() - 1 && completedRow == rowsDataContainer->getSize() - 1)
               table += createRow(rowToCreate, cellWidth, totalColsCount, false, true);
            else
               table += createRow(rowToCreate, cellWidth, totalColsCount, false);
         }
      }

      return table;
   }

   string createRow(List<string>* rowData, long cellWidth, long totalColsCount, bool isHeader, bool isClossingCell = false)
   {
      string row = "";

      long colsCount = rowData->getSize();

      long contentWidth = cellWidth * totalColsCount;
      long totalCellWidth = cellWidth * (totalColsCount / colsCount);
      long colsBorders = colsCount - 1;
      long voidColsBorders = totalColsCount - 1;
      long cellSpaces = space * colsCount;
      long voidCellSpaces = space * totalColsCount;

      const long width = contentWidth + voidCellSpaces + voidColsBorders;

      List<long>* paddings = new LinkedList<long>();

      for (long cell = 0; cell < colsCount; cell++)
      {
         long cellPadding = calcWhiteSpace(rowData->get(cell), totalCellWidth + (voidColsBorders - colsBorders));
         paddings->add(cellPadding);
      }

      string contentBody = "";
      long colsBordersCounter = colsBorders;

      for (long cell = 0; cell < colsCount; cell++)
      {
         long cellPadding = paddings->get(cell);
         string cellSpace = repeat(SPACING, (space / 2) + (totalColsCount - colsCount));

         bool isPaddingEven = true;
         if (cellPadding % 2 != 0)
         {
            cellPadding++;
            isPaddingEven = false;
         }

         string content = rowData->get(cell);
         string alignedContent;

         if (isHeader)
         {
            string leftPadding = repeat(SPACING, (cellPadding / 2));
            string rightPadding = (!isPaddingEven) ? repeat(SPACING, ((cellPadding - 1) / 2)) : repeat(SPACING, (cellPadding / 2));

            alignedContent = (leftPadding + content + rightPadding);
         }
         else
         {
            alignedContent = (!isPaddingEven) ? (content + repeat(SPACING, cellPadding - 1)) : (content + repeat(SPACING, cellPadding));
         }

         contentBody += (cellSpace + alignedContent + cellSpace);

         if (colsBordersCounter != 0)
         {
            contentBody += COL_FILLER;
            colsBordersCounter--;
         }

      }

      string rowBody = (COL_FILLER + contentBody + COL_FILLER) + ROW_SEPARATOR;

      if (isHeader)
      {
         string verticalPadding = repeat(SPACING, contentBody.length());
         string verticalPaddingBody = (COL_FILLER + verticalPadding + COL_FILLER) + ROW_SEPARATOR;

         verticalPaddingBody = replaceAllCharsFromTo(rowBody, verticalPaddingBody, COL_FILLER);

         rowBody = (verticalPaddingBody + rowBody + verticalPaddingBody);
      }

      string borderBody = repeat(ROW_FILLER, width);

      string border = (SEPARATOR + borderBody + SEPARATOR) + ROW_SEPARATOR;

      (isClossingCell) ? (row = border + rowBody + border) : (row = border + rowBody);

      return row;
   }

private:
   TableSchema* schema;

   const string SEPARATOR = "+";
   const string ROW_SEPARATOR = "\r\n";
   const string ROW_FILLER = "-";
   const string COL_FILLER = "|";
   const string SPACING = " ";

   string header;
   long cols;
   long rows;
   long space;

   void fillColumn(long rowId, long columnId, TableSchema* schema, List<string>* data)
   {
      for (long i = 0; i < data->getSize(); i++)
      {
         schema->getRow(rowId)
            .getColumn(columnId)
            .createCell(data->get(i));
      }
   }

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

   long maxHeaderLength()
   {
      long maxLength = 0;
      for (long row = 0; row < schema->rowsCount(); row++)
      {
         long headerLength = schema->getRow(row).getName().length();
         if (headerLength > maxLength)
         {
            maxLength = headerLength;
         }

         for (long col = 0; col < schema->getRow(row).colsCount(); col++)
         {
            long headerLength = schema->getRow(row).getColumn(col).getName().length();
            if (headerLength > maxLength)
            {
               maxLength = headerLength;
            }
         }
      }

      return maxLength;
   }

   long maxColumnCountInRow()
   {
      long maxCount = 0;
      for (long row = 0; row < schema->rowsCount(); row++)
      {
         long localColumnCount = schema->getRow(row).colsCount();

         if (localColumnCount > maxCount)
         {
            maxCount = localColumnCount;
         }
      }

      return maxCount;
   }

   string replaceAllCharsFromTo(string from, string to, string character)
   {
      /* must be the same in [from] and [to] ! */
      long size = from.length();

      for (long i = 0; i < size; i++)
      {
         if (from[i] == character.c_str()[0])
         {
            to[i] = character.c_str()[0];
         }
      }

      return to;
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