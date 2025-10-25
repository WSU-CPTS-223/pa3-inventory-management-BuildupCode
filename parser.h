#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "vector.h"
#include "product.h"

class Parser{
public:
    //change comment later here
    //read from csv(expected)
    struct ParsedRecord{
        std::string uniq_id;
        std::string product_name;
        std::string category_raw;
    };
    //parse 1 line from csv
    //if success, return true.
    static bool  parseCsvLine(const std::string& line, ParsedRecord& output);
    //divide category  string by '|'. If raw is empty, fill 'NA'
    static Vector<std::string> parseCategories(const std::string& category_raw);
    //make product from parsed record
    static Product makeProduct(const ParsedRecord& record);
    //remove whitespace from string
    static std::string trim(const std::string& str);
    //remove quote from string
    static std::string removeQuote(const std::string& str);

private:
    //extract next csv field starting at position
    static std::string readCsvField(const std::string& line, std::size_t& position);
    //check whitespace is space, tab, CR or LF
    static bool checkWhitespace(char w);

};

#endif