#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "inventory.h"

using namespace std;
Inventory inventory;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        //start from index 5
        //This will work if input is 'find something'
        if(line.size()<=5||line[4] = ' '){
            cout<<"Invalid command format."<<endl;
            return;
        }
        string id = line.substr(5);
        Product product_for_find;
        //find product by id from inventory
        if(inventory.FindId(id,product_for_find)){
            product_for_find.printDetails();
        }else{
            cout<<"Inventory/Product not found"<<endl;
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory", 0) == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        //start from index 13
        //This will work if input is 'listInventory something'
         if(line.size()<=13||line[12] = ' '){
            cout<<"Invalid command format."<<endl;
            return;
        }
        string cat = line.substr(13);
        Vector<Product> result;
        //find product by category
        if(inventory.CategoryList(cat,result)){
            //print all id and name in product
            for(size_t i = 0;i<result.size();i++){
                cout<<result[i].getId()<<"|"<<result[i].getName()<<endl;
            }
        }else{
            cout<<"Invalid category"<<endl;
        }
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices

    //open csv file 
    //change name later
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    //cannot open file
    if(!file){
        cout<<"Cannot open csv file"<<endl;
        return;
    }
    string line;
    //skip header
    getline(file,line);
    while(getline(file,line)){
        Parser::ParsedRecord record;
        //parse line into record
        if(Parser::parseCsvLine(line,record)){
            //create product by record
            Product new_product = Parser::makeProduct(record);
            //add product in inventory
            inventory.AddProduct(new_product);
        }
    }
    cout<<"Inventory loaded"<<endl;
}

int main(int argc, char const *argv[])
{
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
