<?php


/* Typed enum: type affects how function arguments are processed.
 * No type checks inside enum
 */
enum z :int {
  case waka;          // 0  (auto)
  case zopas;         // 1  (auto)
  case hello = '66.6'; // a string in :int enum, no errors
  case nex;           // 2  (auto)
  case ub = '10';       // 10
  case xen;           // 3  (auto)
  case A = 10, B = 11, C = 12;
}

/* Un-typed enum - no conversions 
*/
enum untyped_enum {
  case hello = '66.6'; // a string in :int enum, no errors
  case nex;           // 2  (auto)
  case ub = '10';       // 10
}


function test (z $g) {  // technically: function test(int $g), because of enum :int type

    var_dump($g); 
}

function test_untyped (untyped_enum $g) {  // technically: function test($g), enum has no type

    var_dump($g); 
}


// no casting, string variable
// displays "string(3, '66.6')"
var_dump(z::hello); 

// displays "int(66)"
// a string value will be auto cast to an enum type (i.e. 'int'): function test's input arg is of type z, which is int
test(z::hello);  

var_dump(z::ub); 
var_dump(untyped_enum::ub); 

?>
