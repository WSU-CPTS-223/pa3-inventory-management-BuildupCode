#ifndef HASHMAP_H
#define HASHMAP_H

#include "vector.h"
#include <string>
//for using std::hash
#include <functional>

template <typename K, typename V>
class HashMap{
private:
    struct Entry{
        K key;
        V value;
        bool occupied;
        bool deleted;
        Entry() : occupied(false), deleted(false){}
    };
    //array,number for count,number for rehashing
    Vector<Entry> table;
    std::size_t count;
    double load_factor;

    std::size_t hashKey(const K& key) const{
        return std::hash<K>{}(key) % table.size();
    }
    //make table larger and insert all valid stuff again if load factor is exceed
    void rehash(){
        Vector<Entry> oldTable = table;
        table.clear();
        table.resize(oldTable.size()*2);
        count = 0;

        for(std::size_t i = 0;i<oldTable.size();i++){
            //access each entry
            const Entry& entry = oldTable[i];
            //insert again
            if(entry.occupied&&!entry.deleted){
                insert(entry.key,entry.value);
            }
        }
    }
public:
//constructor
    HashMap() : count(0), load_factor(0.7){
        table = Vector<Entry>();
        table.resize(8);
    }
    //insert key value pair in map
    bool insert(const K& key, const V& value){
        if((double)count/table.size()>=load_factor){
            //make table larger
            rehash();
        }
        //set initial index
        std::size_t index = hashKey(key);
        for(std::size_t i = 0;i<table.size();i++){
            std::size_t probe = (index+i)%table.size();
            Entry& entry = table[probe];

            if(!entry.occupied || entry.deleted){
                //storing...
                entry.key = key;
                entry.value = value;
                entry.occupied = true;
                entry.deleted = false;
                count++;
                return true;
            }else if(entry.occupied&&!entry.deleted&&entry.key == key){
                entry.value = value;
                return true;
            }
        }
        //no empty slot
        return false;
    }
    //find value by key and store it in 'out'
    bool find(const K& key, V& out) const{
        //set initial index
        std::size_t index = hashKey(key);
        for(std::size_t i = 0;i<table.size();i++){
            std::size_t probe = (index+i)%table.size();
            //access the probe slot to check(below)
            const Entry& entry = table[probe];
            //key is not found
            if(!entry.occupied&&!entry.deleted){
                return false;
            }
            //key is exist
            if(entry.occupied&&!entry.deleted&&entry.key == key){
                out = entry.value;
                return true;
            }
        }
        //key is not exist in any probe
        return false;
    }
    //need function for erase to use in test case
    bool contains(const K& key) const{
        //temporary variable
        V temp;
        //use find to check
        return find(key,temp);
    }
};

#endif