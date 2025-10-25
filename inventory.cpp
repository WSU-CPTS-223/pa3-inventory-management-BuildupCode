#include "inventory.h"


    //add new product (id,category)
    void AddProduct(const Product& item);
    //find product by id 
    //if find, return true(bool) and store in output
    bool FindId(const std::string& id, Product& output)const;
    //list all stuff in category
    //if category exist, return true(bool) and store in output
    bool CategoryList(const std::string& cat, Vector<Product>& output)const;