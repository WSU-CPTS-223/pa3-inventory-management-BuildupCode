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
inline void checkTrue(bool condition){
    assert(condition);
}
//check two string is same
inline void checkEqualityString(const std::string& a, const std::string& b){
    assert(a == b);
}
//check two integer is same
inline void checkEqualityInt(int a, int b){
    assert(a == b);
}
//test functions
void testVectorBasic();
void testVectorEdge();

void testHashmapBasic();
void testHashampEmptyKey();

void testInventoryBasic();
void testInventoryInvalidId();
void testInventoryInvalidCategory();

void testAll();

#endif