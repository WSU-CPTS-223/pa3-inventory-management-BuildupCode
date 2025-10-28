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
    static bool  ParseCsvLine(const std::string& line, ParsedRecord& output);
    //divide category  string by '|'. If raw is empty, fill 'NA'
    static Vector<std::string> ParseCategories(const std::string& category_raw);
    //make product from parsed record
    static Product MakeProduct(const ParsedRecord& record);
    //remove whitespace from string
    static std::string Trim(const std::string& str);
    //remove quote from string
    static std::string RemoveQuote(const std::string& str);

private:
    //extract next csv field starting at position
    static std::string ReadCsvField(const std::string& line, std::size_t& position);
    //check whitespace is space, tab, CR or LF
    static bool CheckWhitespace(char w);

};

#endif