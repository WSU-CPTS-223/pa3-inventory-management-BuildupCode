#include "simple_test.h"
#include <iostream>
//test basic operation
void TestVectorBasic(){
    std::cout<<"Running testVectorBasic"<<std::endl;
    Vector<int> vector;
    CheckEqualityInt(vector.Size(),0);
    //test PushBack and check vector size
    vector.PushBack(10);
    vector.PushBack(20);
    CheckEqualityInt(vector.Size(),2);
    //check value in vector
    CheckEqualityInt(vector[0],10);
    CheckEqualityInt(vector[1],20);
    std::cout<<"Pass testVectorBasic\n";
    std::cout<<"---------------------------------\n";

}
//test edge operation
void TestVectorEdge(){
    std::cout<<"Running testVectorEdge"<<std::endl;
    Vector<std::string> vector;
    vector.PushBack("A");
    vector.PushBack("B");
    CheckEqualityInt(vector.Size(),2);
    //test clear vector then check vector size
    vector.Clear();
    CheckEqualityInt(vector.Size(),0);
    vector.PushBack("");
    vector.PushBack("ABC");
    CheckEqualityInt(vector.Size(),2);
    //compare string in vector
    CheckEqualityString(vector[0],"");
    CheckEqualityString(vector[1],"ABC");
    std::cout<<"Pass testVectorEdge\n";
    std::cout<<"---------------------------------\n";

}
//test hashmap basic operation
void TestHashmapBasic(){
    std::cout<<"Running testHashmapBasic"<<std::endl;
    HashMap<std::string, int> hashmap;
    CheckTrue(hashmap.Insert("A",1));
    CheckTrue(hashmap.Insert("B",2));
    //try Insert A twice and check it success
    CheckTrue(hashmap.Insert("A",9));
    int value;
    CheckTrue(hashmap.Find("A",value));
    CheckEqualityInt(value,9);
    CheckTrue(hashmap.Find("B",value));
    CheckEqualityInt(value,2);
    //key which is not in hashmap
    CheckTrue(!hashmap.Find("W",value));
    CheckTrue(hashmap.Find("A",value));
    //remove A from hashmap
    CheckTrue(hashmap.Erase("A"));
    CheckTrue(!hashmap.Find("A",value));
    std::cout<<"Pass testHashmapBasic\n";
    std::cout<<"---------------------------------\n";

}
//test hashmap edge operation
void TestHashmapEmptyKey(){
    std::cout<<"Running testHashmapEmptyKey"<<std::endl;
    HashMap<std::string,int> hashmap;
    CheckTrue(hashmap.Insert("",42));
    int value;
    CheckTrue(hashmap.Find("",value));
    //check value
    CheckEqualityInt(value,42);
    CheckTrue(hashmap.Erase(""));
    //find string which is not exist
    CheckTrue(!hashmap.Find("",value));
    std::cout<<"Pass testHashmapEmptyKey\n";
    std::cout<<"---------------------------------\n";

}
//test inventory basic operation
void TestInventoryBasic(){
    std::cout<<"Running testInventoryBasic"<<std::endl;
    Inventory inventory;
    Product product1("id1","Toy car","");
    product1.SetCategories(Parser::ParseCategories(""));
    inventory.AddProduct(product1);
    Product out;
    //find by id
    CheckTrue(inventory.FindId("id1",out));
    CheckEqualityString(out.GetName(),"Toy car");
    Vector<Product> result;
    //find NA in inventory
    CheckTrue(inventory.CategoryList("NA",result));
    //check inventory size and value
    CheckEqualityInt(result.Size(),1);
    CheckEqualityString(result[0].GetId(),"id1");
    std::cout<<"Pass testInventoryBasic\n";
    std::cout<<"---------------------------------\n";

}
//test inventory edge operation
void TestInventoryInvalidId(){
    std::cout<<"Running testInventoryInvalidId"<<std::endl;
    Inventory inventory;
    Product product("id","Toy car","");
    product.SetCategories(Parser::ParseCategories(""));
    inventory.AddProduct(product);
    Product out;
    //find id which is not exist
    CheckTrue(!inventory.FindId("id1",out));
    std::cout<<"Pass testInventoryInvalidId\n";
    std::cout<<"---------------------------------\n";

}
//test inventory edge operation
void TestInventoryInvalidCategory(){
    std::cout<<"Running testInventoryInvalidCategory"<<std::endl;
    Inventory inventory;
    Product product("id","Toy car","");
    product.SetCategories(Parser::ParseCategories(""));
    inventory.AddProduct(product);
    Vector<Product> result;
    //find category which is not exist
    CheckTrue(!inventory.CategoryList("Sports",result));
    std::cout<<"Pass testInventoryInvalidCategory\n";
    std::cout<<"---------------------------------\n";
    
}
//Run all test functions
void TestAll(){
    std::cout<<"Running all tests.\n"<<std::endl;
    TestVectorBasic();
    TestVectorEdge();
    TestHashmapBasic();
    TestHashmapEmptyKey();
    TestInventoryBasic();
    TestInventoryInvalidId();
    TestInventoryInvalidCategory();
    std::cout<<"All test passed.\n"<<std::endl;

}
//run code
int main(){
    TestAll();
    return 0;
}