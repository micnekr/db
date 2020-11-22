# db

A simple database system that is nowhere near being ready for use

Currently, only simple maths and strings logic works

Memory leaks will be fixed in the future

##Data structures:
### Secondary map
length|nextObject|KeyLength|Key|Value


length - 3 bytes default, first bit is a 1  
nextObject - a pointer to the next object in the map with the same assigned cell. 
This is used to prevent hash collisions.  
KeyLength - length of the key in bytes, default length of this field is 3 bytes  
Key - the key
Value - the value held in the record itself. May be of different data types, see the data types section when it is completed.  