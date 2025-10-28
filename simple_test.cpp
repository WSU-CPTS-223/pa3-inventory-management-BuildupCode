#include "simple_test.h"
#include <iostream>
//test basic operation
void testVectorBasic(){
    std::cout<<"Running testVectorBasic"<<std::endl;
    Vector<int> vector;
    checkEqualityInt(vector.size(),0);
    //test push_back and check vector size
    vector.push_back(10);
    vector.push_back(20);
    checkEqualityInt(vector.size(),2);
    //check value in vector
    checkEqualityInt(vector[0],10);
    checkEqualityInt(vector[1],20);
    std::cout<<"Pass testVectorBasic\n";
    std::cout<<"---------------------------------\n";

}
//test edge operation
void testVectorEdge(){
     std::cout<<"Running testVectorEdge"<<std::endl;
    Vector<std::string> vector;
    vector.push_back("A");
    vector.push_back("B");
    checkEqualityInt(vector.size(),2);
    //test clear vector then check vector size
    vector.clear();
    checkEqualityInt(vector.size(),0);
    vector.push_back("");
    vector.push_back("ABC");
    checkEqualityInt(vector.size(),2);
    //compare string in vector
    checkEqualityString(vector[0],"");
    checkEqualityString(vector[1],"ABC");
    std::cout<<"Pass testVectorEdge\n";
    std::cout<<"---------------------------------\n";

}
//test hashmap basic operation
void testHashmapBasic(){
    std::cout<<"Running testHashmapBasic"<<std::endl;
    HashMap<std::string, int> hashmap;
    checkTrue(hashmap.insert("A",1));
    checkTrue(hashmap.insert("B",2));
    //try insert A twice and check it success
    checkTrue(hashmap.insert("A",9));
    int value;
    checkTrue(hashmap.find("A",value));
    checkEqualityInt(value,9);
    checkTrue(hashmap.find("B",value));
    checkEqualityInt(value,2);
    //key which is not in hashmap
    checkTrue(!hashmap.find("W",value));
    checkTrue(hashmap.find("A",value));
    //remove A from hashmap
    checkTrue(hashmap.erase("A"));
    checkTrue(!hashmap.find("A",value));
    std::cout<<"Pass testHashmapBasic\n";
    std::cout<<"---------------------------------\n";

}
//test hashmpa edge operation
void testHashmapEmptyKey(){
    std::cout<<"Running testHashmapEmptyKey"<<std::endl;
    HashMap<std::string,int> hashmap;
    checkTrue(hashmap.insert("",42));
    int value;
    checkTrue(hashmap.find("",value));
    //check value
    checkEqualityInt(value,42);
    checkTrue(hashmap.erase(""));
    //find string which is not exist
    checkTrue(!hashmap.find("",value));
    std::cout<<"Pass testHashmapEmptyKey\n";
    std::cout<<"---------------------------------\n";

}
//test inventory basic operation
void testInventoryBasic(){
    std::cout<<"Running testInventoryBasic"<<std::endl;
    Inventory inventory;
    Product product1("id1","Toy car","");
    product1.setCategories(Parser::parseCategories(""));
    inventory.AddProduct(product1);
    Product out;
    //find by id
    checkTrue(inventory.FindId("id1",out));
    checkEqualityString(out.getName(),"Toy car");
    Vector<Product> result;
    //find NA in inventory
    checkTrue(inventory.CategoryList("NA",result));
    //check inventory size and value
    checkEqualityInt(result.size(),1);
    checkEqualityString(result[0].getId(),"id1");
    std::cout<<"Pass testInventoryBasic\n";
    std::cout<<"---------------------------------\n";

}
//test inventory edge operation
void testInventoryInvalidId(){
    std::cout<<"Running testInventoryInvalidId"<<std::endl;
    Inventory inventory;
    Product product("id","Toy car","");
    product.setCategories(Parser::parseCategories(""));
    inventory.AddProduct(product);
    Product out;
    //find id which is not exist
    checkTrue(!inventory.FindId("id1",out));
    std::cout<<"Pass testInventoryInvalidId\n";
    std::cout<<"---------------------------------\n";

}
//test inventory edge operation
void testInventoryInvalidCategory(){
    std::cout<<"Running testInventoryInvalidCategory"<<std::endl;
    Inventory inventory;
    Product product("id","Toy car","");
    product.setCategories(Parser::parseCategories(""));
    inventory.AddProduct(product);
    Vector<Product> result;
    //find category which is not exist
    checkTrue(!inventory.CategoryList("Sports",result));
    std::cout<<"Pass testInventoryInvalidCategory\n";
    std::cout<<"---------------------------------\n";
    
}
//Run all test functions
void testAll(){
    std::cout<<"Running all tests.\n"<<std::endl;
    testVectorBasic();
    testVectorEdge();
    testHashmapBasic();
    testHashmapEmptyKey();
    testInventoryBasic();
    testInventoryInvalidId();
    testInventoryInvalidCategory();
    std::cout<<"All test passed.\n"<<std::endl;

}
//run code
int main(){
    testAll();
    return 0;
}