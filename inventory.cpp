#include "inventory.h"

//add new product (id,category)
void Inventory::AddProduct(const Product& item){
    by_id.insert(item.getId(),item);
    const Vector<std::string>& cats = item.getCategories();

    for(std::size_t i = 0;i<cats.size();i++){
        Vector<std::string> ids;
        //if category already exist
        if(by_category.find(cats[i],ids)){
            bool exist = false;
            //check id is already exist
            for(std::size_t j = 0;j<ids.size();j++){
                if(ids[j] == item.getId()){
                    exist = true;
                    break;
                }
            }
            //add in that vector
            if(!exist){
                ids.push_back(item.getId());
            }
            by_category.insert(cats[i],ids);
        //if category not exist
        }else{
            //create new one
            Vector<std::string> new_vector;
            new_vector.push_back(item.getId());
            by_category.insert(cats[i],new_vector);
        }
    }
}

//find product by id 
//if find, return true(bool) and store in output
bool Inventory::FindId(const std::string& id, Product& output)const{
    return by_id.find(id,output);
}

//list all stuff in category
//if category exist, return true(bool) and store in output
bool Inventory::CategoryList(const std::string& cat, Vector<Product>& output)const{
    //remove old data
    output.clear();
    Vector<std::string> ids;
    //if category not found
    if(!by_category.find(cat,ids)){
        return false;
    } 
    for(std::size_t i = 0;i<ids.size();i++){
        Product p;
        //if product found
        if(by_id.find(ids[i],p)){
            output.push_back(p);
        }
    }
    return true;
}