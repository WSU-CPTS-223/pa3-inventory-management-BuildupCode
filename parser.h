#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "vector.h"
#include "product.h"

class Parser{
public:
    //change comment later here
    //read from csv(expected)
    struct ParsedRecird{
        std::string uniq_id;
        std::string product_name;
        std::string category_raw;
    };
    //parse 1 line from csv
    //if success, return true.
    static bool  parseCsvLine(const std::string& line, ParsedRecird& output);
    //divide category  string by '|'. If raw is empty, fill 'NA'
    static Vector<std::string> parseCategories(const std::string& category_new);
    //make product from parsed record
    static Product makeProduct(const ParsedRecird& record);
    //remove whitespace from string
    static std::string trim(const std::string& string);
    //remove quote from string
    static std::string removeQuote(const std::string& string);

private:
    //extract next csv field starting at position
    static std::string readCsvField(const std::string& line, std::size_t& position);
    //check whitespace is space, tab, CR or LF
    static bool checkWhitespace(char w);

};

#endif