# FinalProject2275
The first part of this project compares the efficiency of a skip list and a Binary Search
Tree (BST). The BST time complexity is known to be O(log n). The skip list is a little more 
complicated since it is built on probabilities and is best measured by timing many trials.
To compare the data structures large data sets are inserted, searched, and removed in both
the skip list and the BST and the run time of measured for each method. Both structures will
be used to store information in an ordered set (i.e. each node has two members, a key and count).
In the end the skip list will have all the benefits as a traditional linked list with a
marginally better search time and costing around twice memory. This project explores if whether
the timing of the search, delete, and insert operations and is other inherent benefits make the
skip list worth it compared to the BST.

The second part of this project tests the resilliency of the skip list.  In another data
structure, the skip graph, this property has already been tested and  shown.  The skip graph
can be thought of as a tree of skip lists, and its main benefit is that it can tolerate a large
number of node failures and still remain connected.  This project tests a similar property of the
skip list.  For the skip list a simulation declares nodes as either online or failed.  After this,
a connectivity test is run to see if by starting at the head of the skip list, the end of the 
list can still be reached.  This would be helpful in diagnosing problems in sequential operations
like boot sequences or long programs.  If a problem occurs in the middle of a squence, the
skip list may still be able to show the end result even if some steps in the middle are missing.

This Repository has two class files, skipList.h and Tree.h.  To test these there is a file test.cpp
that reads a small file testWords.txt.  The main testing of the project is in driver.cpp.  This
file reads a large file will 1,000,000 words, bigData.txt, into a BST and a skipList.  The first
two data sets generated by driver.cpp, connectivity.txt and inputSize.txt, takes nearly 20 minutes
to run, so if you want to see the .txt files after the program runs, it may be desired to decrease
the input size of the data in driver.cpp or simply comment those out.  The output of the driver.cpp
is only stored into files, these are the .txt files in the repository used for ease in graphing the
data.  There is no actual output in the terminal. This is not true for the test.cpp, since there is
output in the terminal.  The .txt files, .png files, and conclusions for the project are explained
in the file REPORT.md.  The functionality of a skip list is explained in SKIPLIST.md for reference.

to run
$ g++ -std=c++11 driver.cpp Tree.cpp skipList.cpp -o driver
$ ./driver

or just compile and run the run.cpp file
(again please note the output of this file is only in .txt files)
(these .txt files will open automatically in the current directory if not present)

the test.cpp if run in the same way as driver.cpp
$ g++ -std=c++11 test.cpp Tree.cpp skipList.cpp -o test
$ ./test
