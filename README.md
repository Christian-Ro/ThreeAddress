# ThreeAddress
Makes a file into 3ac  
gets a txt file with statements and
converts them into three address code format.
The style of the file must be the same as the one below.
The file must start with program follow by an idetenfier, in 
this case program again. It must also end with a period followed 
by the idenfier. 

# Example file.
```
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
```  
# Example of the output:
```
Add source data t1
Sub t1     res  t2
move nest   t2
```
Still need to fix various bugs and add more functions to take 
more expressions. 
