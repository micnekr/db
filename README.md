# db

A simple proof-of-concept database that I worked on to practice using C++. Not for use in serious projects.

Currently, insert and select functions on tables work, as well as basic math, e.g. `2*(2+2)` returns `8`

## Usage
Run `cmake-build-debug-visual-studio/main.exe` and place it in the same folder as the `.dll` files, which creates a local server on port 9000 which listens to post requests.  
Use some software, such as Postman, to make a post request to the server with the body containing an array with the query,
 such as `["testDb.testTable.insert(\"Index1\", 3)"]` (note the escaped quotes). 
 This is done to provide flexibility in the future.
 
## Language:

### IdComponent
These are components which can have child components, which can be accessed with `.`  
The Database and Table classes inherit from IdComponent class.  
There are a few global variables, such as `testDb`, which is an instance of a database.  
Each database has children tables, (`testTable` for the default `testDb`).
  
Each table has built-in functions (currently `select(key)` and `insert(key, value)`)

### ArrayComponent

Extends IdComponent to have some array functionality (currently there is not much difference)

### NullComponent
A null value

### NumberComponent
A number (a double) value

### StringComponent
A string value

## Underlying formats of data:

### Structure of the database
There are two files: .pm and .sm
.pm is a primary map file. When a key is looked up, its value is hashed and used to assign the index in the secondary map to the buckets in the primary map.  Because it uses a principle similar to hashmaps, its complexity is O(1)
  
.sm is a secondary map file. A primary map entry points to a chosen location in the secondary map. Then, a linked list is used to find the correct value. It also has a complexity of O(1) because it is a pointer, except for the cases where the linked list is used.

### Secondary map entry
length | nextObject | KeyLength | Key | Value


length - length of the whole field  
nextObject - a pointer to the next object in the map with the same assigned bucket. This is used to prevent hash collisions by creating a linked list of entries.  
KeyLength - length of the key in bytes
Key - the key component (serialised)
Value - the value component (serialised)

### Serialised components 

typeByte | serialisedValue

typeByte - a byte encodes the type of data stored in a cell, e.g. the byte `0x10` corresponds to a `StringComponent`.  This is used to choose the correct method to decode the serialised data
serialisedValue - the component that was converted to a series of bytes.  
