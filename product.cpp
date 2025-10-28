#include "product.h"
#include <iostream>
//constructor
Product::Product() {}

Product::Product(const std::string& id, const std::string& name, const std::string& cat_raw)
: uniq_id(id), product_name(name), category_string_raw(cat_raw){}
//return id
std::string Product::GetId() const{
    return uniq_id;
}
//return name
std::string Product::GetName() const{
    return product_name;
}
//return original category 
std::string Product::GetCategoryRaw() const{
    return category_string_raw;
}
//return parsed category list
const Vector<std::string>& Product::GetCategories() const{
    return categories;
}
//set parsed category list
void Product::SetCategories(const Vector<std::string>& cats){
    categories = cats;
}
//printing informations
void Product::PrintDetails() const{
    std::cout<<"ID: "<<uniq_id<<"\nName: "<<product_name<<"\nCategories: "<<category_string_raw<<std::endl;
}
