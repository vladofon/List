#pragma once
#include<string>
#include"List.h"

using namespace std;

class TableSchema
{
private:

   class Row
   {
   private:

      class Column
      {
      private:

         class Cell
         {
         private:
            string data;

         public:
            Cell(string data)
            {
               this->data = data;
            }

            Cell() {}

            string getData()
            {
               return data;
            }
         };

         List<Cell>* cells;
         string columnName;

      public:
         Column(string columnName)
         {
            this->cells = new LinkedList<Cell>();
            this->columnName = columnName;
         }

         Column() { this->cells = new LinkedList<Cell>(); }

         Cell createCell(string data)
         {
            Cell newCell = Cell(data);
            cells->add(newCell);

            return newCell;
         }

         Cell getCell(long index)
         {
            return cells->get(index);
         }

         string getName()
         {
            return this->columnName;
         }

         long cellsCount()
         {
            return cells->getSize();
         }
      };

      List<Column>* columns;
      string rowName;

   public:
      Row(string rowName)
      {
         this->columns = new LinkedList<Column>();
         this->rowName = rowName;
      }

      Row() { this->columns = new LinkedList<Column>(); }

      Column createColumn(string columnName)
      {
         Column newColumn = Column(columnName);
         columns->add(newColumn);

         return newColumn;
      }

      Column getColumn(long index)
      {
         return columns->get(index);
      }

      string getName()
      {
         return this->rowName;
      }

      long colsCount()
      {
         return columns->getSize();
      }
   };

   List<Row>* rows = new LinkedList<Row>();

public:

   Row createRow(string rowName)
   {
      Row newRow = Row(rowName);
      rows->add(newRow);

      return newRow;
   }

   Row getRow(long index)
   {
      return rows->get(index);
   }

   long rowsCount()
   {
      return rows->getSize();
   }
};