## Edit distance
### By Yigan Zhang(18324490) & Yuting Xue(31323149)
  The program would read input from a file. The output is a list of edit distance and their corresponding sequence of transformation operations.
### How to use it?
  Tap in teminal
```
cd hw4
make
./edit
```
  You will see the output both in a file and your teminal. 
### How to modify it?
####Change outputs
  Find `fpt`in edit.cpp (line 142)
  This is where you can change your output's name.
  ```
  FILE *fpt = fopen("output1.txt", "w");
  ```
####Change inputs
Find `fp`in main function in edit.cpp (line 234)
  This is where you can change your intput's name.
  ```
  FILE*fp = fopen("input1.txt", "r");
  ```
### my little SAMPLE!
  I wrote a sample at the bottom of program, you can test it first if you are interest.

### For question 1
  You need to change input strings to be `electrical engineering,`and `computer science.`. 
  First, you need to add `/* `before `int main()` and add another `*/` at the end of `return 0}` of paragraph of `INPUT FILES`.
  Then, release 
  ```
 int main()
{ 
  char str1[]="electrical engineering,";
  char str2[]="computer science.";
		
    int edit=0;
    edit = edit_distance(str1, str2);
		
    return 0;
}

  ```
  by removing `/*` and `*/`before and after paragraph of `For question 1`.
  Finally, run the program you will see the output of question 1.
### For question 2
  You need to release `INPUT FILES` paragraph and keep annotation for both `For question 1` and `my little SAMPLE!`.
  
  If you don't want to see corresponding sequence of transformation operations, you need to add `//` before line 147, 148, 153, 154, and also add `/* and */` for paragraph below:
```
    k--;
    int m=k;
    for(int i=0;i<m;i++)
    ......
  
    //printf("right:%d,insert:%d,delete:%d,substitute:%d\n",right,insert,delet,substit);
```
  Then, By changing `input1.txt` to `input2.txt`and`input3.txt`, you will get result of those three both on your teminal and output files.

### For question 3
  All the tansformation operations can be implemented in O(1) time if you use two empty stacks, L and R, instead of only z.
  At first, we need to insert all char in x to R by sequence and keep L empty.

  If letter is `right` in x and y, do nothing.
  
  If `insert` is needed, POP letters in R, which are before the insert position, PUSH them to L. Then PUSH the one you want to insert into L, print L, R.
  
  If `delete` is needed, POP letters in R, which are before the delete position, PUSH them to L. Then POP the one you want to delete in R, print L, R.
  
  If `replace` is needed, POP letters in R, which are before the replace position, PUSH them to L. Then POP the one you want to replace in R, PUSH the one you want to insert into L, print L, R.
  
  Each stack operation requires O(1) time, and each transformation operation requires only O(1) stack operations. 
  So, now we can do each operation in O(1) time.

  
  Thanks for reading :blush:
  
    
