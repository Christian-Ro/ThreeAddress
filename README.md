# ThreeAddress
makes a file into 3ac
gets a txt file with statements and
converts them into three address code format.
Ex.
=================================
program
program
nest
ID
=
ASSIGNMENT
source
ID
+
ADDITION
data
ID
-
SUBTRACTION
res
ID
;
SEMICOLON
end
end
.
PERIOD
====================
which translate to:
Add source data t1
Sub t1     res  t2
move nest   t2

Still need to fix various bugs and add more functions to take 
more expressions. 
