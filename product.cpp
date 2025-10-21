#include "product.h"
#include <iostream>

Product::Product() {}

Product::Product(const std::string& id, const std::string& name, const std::string& cat_raw)
: uniq_id(id), product_name(name), category_string_raw(cat_raw){}

std::string Product::getId() const{
    return uniq_id;
}
std::string Product::getName() const{
    return product_name;
}
std::string Product::getCategoryRaw() const{
    return category_string_raw;
}
const Vector<std::string>& Product::getCategories() const{
    return categories;
}

void Product::setCategories(const Vector<std::string& cats){
    categories = cats;
}

void Product::printDetails() const{
    std::cout<<"ID: "<<uniq_id<<"\nName: "<<product_name<<"\nCategories: "<<category_string_raw<<std::endl;
}
