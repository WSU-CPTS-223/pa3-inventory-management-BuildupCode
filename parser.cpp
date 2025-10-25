#include "parser.h"
//split string - using stingstream
//functions for divide char
#include <cctype>
#include <sstream>

//parse 1 line from csv
    //if success, return true.
    bool  Parser::parseCsvLine(const std::string& line, ParsedRecord& output){
        std::size_t position = 0;
        //get info from csv file
        std::string id = readCsvField(line,position);
        std::string name = readCsvField(line,position);
        std::string category = readCsvField(line,position);
        //if no id or name
        if(id.empty()||name.empty()){
            return false;
        }
        //store in output
        output.uniq_id = id;
        output.product_name = name;
        output.category_raw = category;
        return true;
    }
    //divide category  string by '|'. If raw is empty, fill 'NA'
    Vector<std::string> Parser::parseCategories(const std::string& category_raw){
        Vector<std::string> cats;
        //if category string is empty, put "NA"
        if(category_raw.empty()){
            cats.push_back("NA");
            return cats;
        }
        std::stringstream str_stream(category_raw);
        std::string token;
        while(std::getline(str_stream,token,'|')){
            //remove whitespace from token
            std::string trimed_token = trim(token);
            //if category is not empty, add it in cats
            if(!trimed_token.empty()){
                cats.push_back(trimed_token);
            }
        }
        //if category is not found, pur "NA"
        if(cats.size()==0){
            cats.push_back("NA");
        }
        return cats;
    }
    //make product from parsed record
    Product Parser::makeProduct(const ParsedRecord& record){
        //make product and set parsed category
        Product item(record.uniq_id,record.product_name, record.category_raw);
        item.setCategories(parseCategories(record.category_raw));
        return item;
    }
    //remove whitespace from string
    std::string Parser::trim(const std::string& str){
        size_t start = 0, end = str.size();
        //skip front whitespace
        while (start<end&&checkWhitespace(str[start])){
            start++;
        }
        //skip back whitespace
        while (start<end&&checkWhitespace(str[end-1])){
            end--;
        }
        return str.substr(start,end-start);
    }
    //remove quote from string
    std::string Parser::removeQuote(const std::string& str){
        //remove quotation mark if it exist
        if(str.size()>=2&&str.front()=='"'&&str.back()=='"'){
            return str.substr(1,str.size()-2);
        }
        return str;
    }
    //extract next csv field starting at position
    std::string Parser::readCsvField(const std::string& line, std::size_t& position){
        std::string field;
        bool quote=false;
        //check there is quote or not
        while(position<line.size()){
            char current_char = line[position++];
            if(current_char == '"'){
                quote = !quote;
            }else if(current_char == ','&&!quote){
                break;
            }else{
                field.push_back(current_char);
            }
        }
        return trim(removeQuote(field));
    }
    //check whitespace is space, tab, CR or LF
    bool Parser::checkWhitespace(char whitespace_char){
        //check whitespace type
        return whitespace_char == ' '||whitespace_char == '\t'||whitespace_char == '\r'||whitespace_char == '\n';
    }