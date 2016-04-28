#include "htmltablegenerator.h"

#include <vector>

HTMLTableGenerator::HTMLTableGenerator() {

}

void HTMLTableGenerator::addRowToTable(std::vector<std::string> row) {
    std::string toAdd;
    toAdd += "  <tr>\n";
    for (std::string element : row) {
        toAdd += "    <td>"+ element + "</td>/n";
    }
    toAdd += "  </tr>\n";
    rows.push_back(toAdd);
}

std::string HTMLTableGenerator::outputTable() {
    std::string toReturn;
    toReturn += "<table>\n";
    for (std::string row : rows) {
        toReturn += row;
    }
    toReturn += "</table>";
}
