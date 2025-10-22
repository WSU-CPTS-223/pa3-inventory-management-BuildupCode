#ifndef PRODUCT_H
#define PRODUCT_H
//for using std::string
#include <string>
//my own vector.h
#include "vector.h"

class Product{
private:
    std::string uniq_id;
    std::string product_name;
    //category list from csv
    std::string category_string_raw;
    //return parsed category 
    Vector<std::string> categories;
public:
    Product();
    Product(const std::string& id, const std::string& name, const std::string& cat_raw);
    //return id
    std::string getId() const;
    //return name
    std::string getName() const;
    //return original category from csv
    std::string getCategoryRaw() const;
    //return parsed category list
    const Vector<std::string>& getCategories() const;
    //set parsed category list
    void setCategories(const Vector<std::string>& cats);
    //printing informations
    void printDetails() const;

};

#endif