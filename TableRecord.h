#pragma once
#include"List.h"
#include<string>

using namespace std;

class TableRecord
{
public:

   List<string>* getTableRecord()
   {
      return tableRecord;
   }

   long getCellWidth()
   {
      return cellWidth;
   }

   long getTotalColsCount()
   {
      return totalColsCount;
   }

   long getSize()
   {
      return tableRecord->getSize();
   }

   long getSpace()
   {
      return tableRecord->getSize();
   }

   bool isHeader()
   {
      return header;
   }

   bool isClossingCell()
   {
      return clossingCell;
   }

private:

   List<string>* tableRecord;
   long cellWidth;
   long space;
   long totalColsCount;
   bool header;
   bool clossingCell;
};