#pragma once

#include<string>
#include"List.h"
#include"ArrayList.h"
#include"TableRecord.h"

using namespace std;

// string createRow(List<string>* tableRecord, long cellWidth, long totalColsCount, bool isHeader, bool isClossingCell = false)

class SchemaFormatter
{
public:

   string createRow(TableRecord record)
   {
      string row = "";

      long colsCount = tableRecord->getSize();

      long contentWidth = cellWidth * totalColsCount;
      long totalCellWidth = cellWidth * (totalColsCount / colsCount);
      long colsBorders = colsCount - 1;
      long voidColsBorders = totalColsCount - 1;
      long cellSpaces = space * colsCount;
      long voidCellSpaces = space * totalColsCount;

      const long width = contentWidth + voidCellSpaces + voidColsBorders;

      List<long>* paddings = new ArrayList<long>();

      for (long cell = 0; cell < colsCount; cell++)
      {
         long cellPadding = calcWhiteSpaces(tableRecord->get(cell), totalCellWidth + (voidColsBorders - colsBorders));
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

         string content = tableRecord->get(cell);
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
   const string SEPARATOR = "+";
   const string ROW_SEPARATOR = "\r\n";
   const string ROW_FILLER = "-";
   const string COL_FILLER = "|";
   const string SPACING = " ";

   class RecordInfo
   {
   public:
      RecordInfo(TableRecord record)
      {
         this->colsCount = record.getSize();
         this->contentWidth = record.getCellWidth() * record.getTotalColsCount();
         this->totalCellWidth = record.getCellWidth() * (record.getTotalColsCount() / colsCount);
         this->colsBorders = colsCount - 1;
         this->voidColsBorders = record.getTotalColsCount() - 1;
         this->cellSpaces = record.getSize() * colsCount;
         this->voidCellSpaces = record.getSize() * record.getTotalColsCount();
         this->width = contentWidth + voidCellSpaces + voidColsBorders;
      }

      long getColsCount()
      {
         return colsCount;
      }

      long getContentWidth()
      {
         return contentWidth;
      }

      long getTotalCellWidth()
      {
         return totalCellWidth;
      }

      long getColsBorders()
      {
         return colsBorders;
      }

      long getVoidColsBorders()
      {
         return voidColsBorders;
      }

      long getCellSpaces()
      {
         return cellSpaces;
      }

      long getVoidCellSpaces()
      {
         return voidCellSpaces;
      }

      long getWidth()
      {
         return width;
      }

   private:
      long colsCount;
      long contentWidth;
      long totalCellWidth;
      long colsBorders;
      long voidColsBorders;
      long cellSpaces;
      long voidCellSpaces;
      long width;
   };

   long calcWhiteSpaces(string str, long width)
   {
      return width - str.length();
   }

   List<long>* calcPaddings(List<string>* record, long colsCount, long totalCellWidth, long voidColsBorders, long colsBorders)
   {
      List<long>* paddings = new ArrayList<long>();

      for (long cell = 0; cell < colsCount; cell++)
      {
         long cellPadding = calcWhiteSpaces(record->get(cell), totalCellWidth + (voidColsBorders - colsBorders));
         paddings->add(cellPadding);
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
};