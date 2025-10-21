#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "vector.h"

class Product{
private:
    std::string uniq_id;
    std::string product_name;
    std::string category_string_raw;
    Vector<std::string> categories;
public:
    Product();
    Product(const std::string& id, const std::string& name, const std::string& cat_raw);
    std::string getId() const;
    std::string getName() const;
    std::string getCategoryRaw() const;
    const Vector<std::string>& getCategories() const;
    void setCategories(const Vector<std::string>& cats);
    void printDetails() const;

};

#endif