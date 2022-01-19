#pragma once
#include<string>
#include"List.h"
#include"ArrayList.h"
#include"Pair.h"
#include "TableSchema.h"
#include "SchemaParser.h"

using namespace std;

class FencersFormatter
{
public:
   FencersFormatter(TableSchema* schema)
   {
      this->schema = schema;
   }

   FencersFormatter()
   {
      // If constructor empty define default schema
      this->schema = new TableSchema();
      initDefaultSchema();
   }

   string format(List<string>* participants, List<Pair>* pairs)
   {
      List<string>* firstTeamParticipants = parseTeam(pairs, true);
      List<string>* secondTeamParticipants = parseTeam(pairs, false);

      schema->fillColumn(0, 0, participants);
      schema->fillColumn(1, 0, firstTeamParticipants);
      schema->fillColumn(1, 1, secondTeamParticipants);

      SchemaParser* parser = new SchemaParser(*schema);
      return parser->parseSchema();
   }

private:
   TableSchema* schema;

   void initDefaultSchema()
   {
      schema->createRow("============+ Fencing competition +============");
      schema->getRow(0).createColumn("List of participants");

      schema->createRow("Draw results");
      schema->getRow(1).createColumn("First team");
      schema->getRow(1).createColumn("Second team");
   }

   List<string>* parseTeam(List<Pair>* pairs, bool isFirstTeam)
   {
      List<string>* team = new ArrayList<string>();

      for (long i = 0; i < pairs->getSize(); i++)
      {
         if (isFirstTeam)
            team->add(pairs->get(i).getFirstFencer());
         else
            team->add(pairs->get(i).getSecondFencer());
      }

      return team;
   }
};