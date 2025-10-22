#include "product.h"
#include <iostream>
//constructor
Product::Product() {}

Product::Product(const std::string& id, const std::string& name, const std::string& cat_raw)
: uniq_id(id), product_name(name), category_string_raw(cat_raw){}
//return id
std::string Product::getId() const{
    return uniq_id;
}
//return name
std::string Product::getName() const{
    return product_name;
}
//return original category 
std::string Product::getCategoryRaw() const{
    return category_string_raw;
}
//return parsed category list
const Vector<std::string>& Product::getCategories() const{
    return categories;
}
//set parsed category list
void Product::setCategories(const Vector<std::string>& cats){
    categories = cats;
}
//printing informations
void Product::printDetails() const{
    std::cout<<"ID: "<<uniq_id<<"\nName: "<<product_name<<"\nCategories: "<<category_string_raw<<std::endl;
}
