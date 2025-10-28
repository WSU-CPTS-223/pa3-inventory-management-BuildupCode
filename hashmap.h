#ifndef HASHMAP_H
#define HASHMAP_H

#include "vector.h"
#include <string>
//for using std::hash
#include <functional>

template <typename K, typename V>
class HashMap{
private:
    class Entry{
    public:
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
        //check table size
        if(table.size()==0){
            throw std::runtime_error("HashMap is empty");
        }
        return std::hash<K>{}(key) % table.size();
    }
    //make table larger and insert all valid stuff again if load factor is exceed
    void rehash(){
        Vector<Entry> old_table = table;
        table.clear();
        std::size_t new_size = old_table.size() == 0 ? 8 : old_table.size()*2;
        table.resize(new_size);
        count = 0;

        for(std::size_t i = 0;i<old_table.size();i++){
            //access each entry
            const Entry& entry = old_table[i];
            //insert again
            if(entry.occupied&&!entry.deleted){
                insert(entry.key,entry.value);
            }
        }
    }
public:
//constructor
    HashMap() : count(0), load_factor(0.7){
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
    //erase key and value pair if exist
    bool erase(const K& key){
        //set initial index
        std::size_t index = hashKey(key);
        //probe through table(linear probing)
        for(std::size_t i = 0;i<table.size();i++){
            std::size_t probe = (index+i)%table.size();
            Entry& entry = table[probe];
            //check empty slot
            if(!entry.occupied&&!entry.deleted){
                //stop finding
                return false;
            }
            //if slot is occupied and key is same.
            if(entry.occupied&&!entry.deleted&&entry.key == key){
                entry.deleted = true;
                count--;
                return true;
            }
        }
        //cannot find key in whole probe
        return false;
    }

    bool contains(const K& key) const{
        //temporary variable
        V temp;
        //use find to check
        return find(key,temp);
    }
};

#endif