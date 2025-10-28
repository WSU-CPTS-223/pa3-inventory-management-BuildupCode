#include "parser.h"
//split string - using stingstream
//functions for divide char
#include <cctype>
#include <sstream>

//parse 1 line from csv
    //if success, return true.
    bool  Parser::ParseCsvLine(const std::string& line, ParsedRecord& output){
        std::size_t position = 0;
        //get info from csv file
        std::string id = ReadCsvField(line,position);
        std::string name = ReadCsvField(line,position);
        std::string brand = ReadCsvField(line,position);
        std::string asin = ReadCsvField(line,position);
        std::string category = ReadCsvField(line,position);
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
    Vector<std::string> Parser::ParseCategories(const std::string& category_raw){
        Vector<std::string> cats;
        //if category string is empty, put "NA"
        if(category_raw.empty()){
            cats.PushBack("NA");
            return cats;
        }
        std::stringstream str_stream(category_raw);
        std::string token;
        while(std::getline(str_stream,token,'|')){
            //remove whitespace from token
            std::string trimed_token = Trim(token);
            //if category is not empty, add it in cats
            if(!trimed_token.empty()){
                cats.PushBack(trimed_token);
            }
        }
        //if category is not found, pur "NA"
        if(cats.Size()==0){
            cats.PushBack("NA");
        }
        return cats;
    }
    //make product from parsed record
    Product Parser::MakeProduct(const ParsedRecord& record){
        //make product and set parsed category
        Product item(record.uniq_id,record.product_name, record.category_raw);
        item.SetCategories(ParseCategories(record.category_raw));
        return item;
    }
    //remove whitespace from string
    std::string Parser::Trim(const std::string& str){
        size_t start = 0, end = str.size();
        //skip front whitespace
        while (start<end&&CheckWhitespace(str[start])){
            start++;
        }
        //skip back whitespace
        while (start<end&&CheckWhitespace(str[end-1])){
            end--;
        }
        return str.substr(start,end-start);
    }
    //remove quote from string
    std::string Parser::RemoveQuote(const std::string& str){
        //remove quotation mark if it exist
        if(str.size()>=2&&str.front()=='"'&&str.back()=='"'){
            return str.substr(1,str.size()-2);
        }
        return str;
    }
    //extract next csv field starting at position
    std::string Parser::ReadCsvField(const std::string& line, std::size_t& position){
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
        return Trim(RemoveQuote(field));
    }
    //check whitespace is space, tab, CR or LF
    bool Parser::CheckWhitespace(char whitespace_char){
        //check whitespace type
        return whitespace_char == ' '||whitespace_char == '\t'||whitespace_char == '\r'||whitespace_char == '\n';
    }