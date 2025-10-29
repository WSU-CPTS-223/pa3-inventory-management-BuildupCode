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

    //number for initial
    static constexpr double DEFAULT_LOAD_FACTOR = 0.7;
    static const std::size_t INITIAL_CAPACITY = 8;

    //array,number for count,number for rehashing
    Vector<Entry> table;
    std::size_t count;
    double load_factor;

    std::size_t HashKey(const K& key) const{
        //check table size
        if(table.Size()==0){
            throw std::runtime_error("HashMap is empty");
        }
        return std::hash<K>{}(key) % table.Size();
    }
    //make table larger and insert all valid stuff again if load factor is exceed
    void Rehash(){
        Vector<Entry> old_table = table;
        table.Clear();
        std::size_t new_size = old_table.Size() == 0 ? INITIAL_CAPACITY : old_table.Size()*2;
        table.Resize(new_size);
        count = 0;

        for(std::size_t i = 0;i<old_table.Size();i++){
            //access each entry
            const Entry& entry = old_table[i];
            //insert again
            if(entry.occupied&&!entry.deleted){
                Insert(entry.key,entry.value);
            }
        }
    }
public:
//constructor
    HashMap() : count(0), load_factor(DEFAULT_LOAD_FACTOR){
        table.Resize(INITIAL_CAPACITY);
    }
    //insert key value pair in map
    bool Insert(const K& key, const V& value){
        if((double)count/table.Size()>=load_factor){
            //make table larger
            Rehash();
        }
        //set initial index
        std::size_t index = HashKey(key);
        for(std::size_t i = 0;i<table.Size();i++){
            std::size_t probe = (index+i)%table.Size();
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
    bool Find(const K& key, V& out) const{
        //set initial index
        std::size_t index = HashKey(key);
        for(std::size_t i = 0;i<table.Size();i++){
            std::size_t probe = (index+i)%table.Size();
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
    V* FindMutable(const K& key){
        std::size_t index = HashKey(key);
        for(std::size_t i = 0;i<table.Size();i++){
            std::size_t probe = (index+i)%table.Size();
            Entry& entry = table[probe];
            if(!entry.occupied&&!entry.deleted){
                return nullptr;
            }
            if(entry.occupied&&!entry.deleted&&entry.key == key){
                return &entry.value;
            }
        }
        return nullptr;
    }

    //erase key and value pair if exist
    bool Erase(const K& key){
        //set initial index
        std::size_t index = HashKey(key);
        //probe through table(linear probing)
        for(std::size_t i = 0;i<table.Size();i++){
            std::size_t probe = (index+i)%table.Size();
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

    bool Contains(const K& key) const{
        //temporary variable
        V temp;
        //use find to check
        return Find(key,temp);
    }
};

#endif