#include "inventory.h"

//add new product (id,category)
void Inventory::AddProduct(const Product& item){
    by_id.Insert(item.GetId(),item);
    const Vector<std::string>& cats = item.GetCategories();

    for(std::size_t i = 0;i<cats.Size();i++){
        Vector<std::string> ids;
        //if category already exist
        if(by_category.Find(cats[i],ids)){
            bool exist = false;
            //check id is already exist
            for(std::size_t j = 0;j<ids.Size();j++){
                if(ids[j] == item.GetId()){
                    exist = true;
                    break;
                }
            }
            //add in that vector
            if(!exist){
                ids.PushBack(item.GetId());
            }
            by_category.Insert(cats[i],ids);
        //if category not exist
        }else{
            //create new one
            Vector<std::string> new_vector;
            new_vector.PushBack(item.GetId());
            by_category.Insert(cats[i],new_vector);
        }
    }
}

//find product by id 
//if find, return true(bool) and store in output
bool Inventory::FindId(const std::string& id, Product& output)const{
    return by_id.Find(id,output);
}

//list all stuff in category
//if category exist, return true(bool) and store in output
bool Inventory::CategoryList(const std::string& cat, Vector<Product>& output)const{
    //remove old data
    output.Clear();
    Vector<std::string> ids;
    //if category not found
    if(!by_category.Find(cat,ids)){
        return false;
    } 
    for(std::size_t i = 0;i<ids.Size();i++){
        Product product;
        //if product found
        if(by_id.Find(ids[i],product)){
            output.PushBack(product);
        }
    }
    return true;
}