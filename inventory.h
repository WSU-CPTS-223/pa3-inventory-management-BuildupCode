#ifndef INVENTORY_H
#define INVENTORY_H

#include"hashmap.h"
#include"product.h"
#include "vector.h"

class Inventory {
private:
    //hashmap to find product by id
    HashMap<std::string, Product> id;
    //hashmap mapping category to product id
    HashMap<std::string, Vector<std::string>> category;
public:
    //add new product (id,category)
    void AddProduct(const Product& item);
    //find product by id 
    //if find, return true(bool) and store in output
    bool FindId(const std::string& id, Product& output)const;
    //list all stuff in category
    //if category exist, return true(bool) and store in output
    bool CategoryList(const std::string& cat, Vector<Product>& output)const;
};

#endif