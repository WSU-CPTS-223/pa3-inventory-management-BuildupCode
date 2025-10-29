#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <cassert>
#include "parser.h"
#include "hashmap.h"
#include <string>
#include "inventory.h"
#include "vector.h"
#include "product.h"
//check condition is true
inline void CheckTrue(bool condition){
    assert(condition);
}
//check two string is same
inline void CheckEqualityString(const std::string& a, const std::string& b){
    assert(a == b);
}
//check two integer is same
inline void CheckEqualityInt(int a, int b){
    assert(a == b);
}
//test functions
void TestVectorBasic();
void TestVectorEdge();

void TestHashmapBasic();
void TestHashmapEmptyKey();
void TestHashmapFindMutable();

void TestInventoryBasic();
void TestInventoryInvalidId();
void TestInventoryInvalidCategory();

void TestAll();

#endif