/**
 * Filename: htmltablegenerator.h
 * Author: //TO DO: Teamname
 * Date: 27 April 2016
 * Description: The class stores rows then outputs an HTML table on demand
 */

#ifndef HTMLTABLEGENERATOR_H
#define HTMLTABLEGENERATOR_H

#include <vector>

class HTMLTableGenerator {
public:
    HTMLTableGenerator();

    void addRowToTable(std::vector<std::string>);

    /**
     * Outputs the whole table from (and including) <table> to </table>
     */
    std::string outputTable();

protected:
    std::vector<std::string> rows;
};

#endif // HTMLTABLEGENERATOR_H
