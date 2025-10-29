Young Uk Kim and WSU ID:011809991
[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# How to run my code.
1. Download the project.

2. Unzip the file.

3. Open the terminal.

4. Navigate to the folder you downloaded.

5. Use the command below to move into the cloned folder:
- cd pa3-inventory-management-BuildupCode

6. Use the command below to compile:
- make out for pa3
    - (Makefile will automatically compile the main project when you type 'make out' in terminal.)
- make test for pa3 simple_test
    - (Makefile will automatically compile the test project when you type 'make test' in terminal.)

7. Use the command below to run the program:
- ./mainexe for main project.
- ./testexe for test project.

## Programming Assignment 3 Overview
**Inventory Management System**
CPTS_223 Advanced Data Structures in C++
Young Uk Kim
WSU ID:011809991

This project implements a command line REPL application for querying an Amazon-style product inventory.
The system supports 2 primary commands:
1. **find <inventoryid>**
- Find a product whose Unique ID is matches with the given inventoryid.
- If found, prints details of product.(Id,name, and category)
- Otherwise, print Inventory/Product not found.
2. **listInventory <category_string>**
- Lists the Unique ID and Product Name of all products in the given category.
- If the category doesn't exist, prints Invalid Category.
The application is built using custom data structure(no STL containers) and includes some test cases to verify correctness and edge cases.

### Design and Data structures
1. Vector<T>
- Custom dynamic array implementation.
- Supports PushBack, Clear, Resize, Size, Reserve, and operator[] (const and non const).
- Implements copy constructor and copy assignment operator for deep copy.
- Used as the underlying container for hash table buckets and category lists.
**Complexity**
- PushBack: Amortized O(1), worst-case O(n) (resize).
- Resize: O(n)
- Reserve: O(n)
- operator[]: O(1)
- Clear: O(1)

2. HashMap<K,V>
- Implemented with open addressing+linear probing.
- Supports Insert,Find,FindMutable,Erase, and Contains.
- Uses std::hash for hashing keys.
- Initial capacity = 8, load factor threshold = 0.7.
- Optimization: Added FindMutable to allow direct modification of values without copying.
- Automatically resizes and rehashes when load factor is exceeded.
**Complexity**
- Insert: average O(1), worst-case O(n)
- Find: average O(1), worst-case O(n)
- FindMutable: average O(1), worst-case O(n)
- Contains: average O(1), worst-case O(n)
- Erase: O(1)
- Rehash: O(n) (amortized across inserts)

3. Inventory
- Maintains two hash maps:
    - by_id: HashMap<std::string, Product> (Maps product ID)
    - by_category: HashMap<std::string, Vector<std::string>> (Maps category which is list of product IDs)
- AddProduct: Inserts into both maps. Uses FindMutable to avoid unnecessary copy.
- FindId: Retrieves product by ID.
- CategoryList: Retrieves all products in a category.

4. Product
- Stores product attributes: ID, name, category_string_raw, categories.
    - uniq_id
    - product_name
    - category_string_raw (raw category string from CSV)
    - categories (category list which is parsed)
- Provides getters/setters for encapsulation.
- Supports category assignment by SetCategories.
- Includes PrintDetails for formatted output.

5. Parser
- Parses CSV input lines into structured records (ParsedRecord).
- Splits categories by '|'.
- If category is missing or empty, assigns "NA".
- Trims whitespace and removes surrounding quotes from fields.
- Handles CSV fields with commas inside quotes.
- Provides helper functions:
    - Trim: remove whitespace from the beginning and end.
    - RemoveQuote: strip surrounding quotes.
    - ReadCsvField: parse next CSV field, respecting quotes.
    - CheckWhitespace: detect space, tab, CR, LF.
- MakeProduct: Converts a parsed record into a Product with parsed categories.

#### Testing Strategy
-All containers and modules tested with cassert in simple_test.cpp.
-Each test function includes at least 2 cases. One for the normal case and one for the edge case.
**Test Coverage**
1. Vector
- TestVectorBasic:
    - Normal case: Push 2 integers, check size and value.
    - Edge Case: Access by index to check operator[] works correctly.
- TestVectorEdge: 
    - Normal case: Clear vector and check size resets to 0.
    - Edge Case: Insert empty string and non-empty string, check both are stored correctly.
2. HashMap
- TestHashmapBasic:
    - Normal case: Insert "A", "B", and retrieve values.
    - Edge Case: Overwrite existing key "A" and check new value is stored.
- TestHashmapEmptyKey:
    - Normal case: Insert empty string "" as key, retrieve value.
    - Edge Case: Erase empty key and check its existence.
- TestHashmapFindMutable:
    - Normal case: Insert "A", modify value by FindMutable, check update.
    - Edge Case: Attempt to modify non existent key returns nullptr.
3. Inventory
- TestInventoryBasic
    - Normal case: Add product "id1", check FindId retrieves it. 
    - Edge Case: Category missing then "NA" assigned, check CategoryList("NA") returns product.
- TestInventoryInvalidId:
    - Normal case: Find valid ID works.
    - Edge Case: Find invalid ID returns false.
- TestInventoryInvalidCategory:
    - Normal case: Find valid category works.
    - Edge Case: Find invalid category returns false.
**Why did I choose these tests?**
- Cover normal usage for insert,find,and list
- Cover edge cases for empty key, missing category, overwrite and etc.
- Validate optimization correctness (FindMutable updates in place)
- Ensure robustness against invalid queries.

##### Data Handling
- Categories are split by '|'.
- Missing categories are replaced with "NA".
- Whitespace at the beginning and end is removed.
- Surrounding quotes are deleted from fields.
- Empty fields are handled.
- CSV fields with commas inside quotes are parsed correctly.
- Design I choose: 
    - If a category string is empty after trimming and splitting, "NA" is inserted to ensure every product has at least 1 category. 
    - This guarantees consistent indexing in by_category.


# PA3 Skeleton Code
We expect a fully functioning command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.
