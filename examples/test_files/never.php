<?php
function dummy(): never {

// return; results in compile-time error:
//never.php: 4 [E]: Returning from a ':never' function is not permitted
//Compile error


// Empty function, no explicit return statement: runtime error:
//never.php Error: Return from a never returning function is detected. Aborted.

}

dummy();

echo "This will not be printed\n";
?>
