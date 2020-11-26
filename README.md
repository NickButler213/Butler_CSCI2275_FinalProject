# FinalProject2275
The first part of this project will compare the efficiency of a skip list and a Binary Search
Tree (BST). The BST time complexity is known to be O(log n). The skip list is a little more 
complicated since it is built on probabilities and it best measured by timing many trials.
Large data sets will be inserted into the skip list and BST, timing the insert, search, and
delete operations of each. Both structures will be used to store information in an ordered 
set (i.e. each node has two members, a key and count). In the end the skip list will print 
out all items in order faster, but this project explores if whether the timing of the search,
delete, and insert operations make the skip list worth it compared to the BST.

The second part of this project will test the resilliency of the skip list.  In another data
structure, the skip graph, this property has already been shown.  The skip graph can be thought
of as a tree of skip lists, and it main benefit is that it can tolerate a large number of node
failures and still remain connected.  This project will test a similar property of the skip
list.  For the skip list, instead of trying to keep connectivity between the nodes from a node
failures, a simulation will show how many node failures it takes before information is
completely lost.  So, in the event that the information of multiple nodes is lost, the skip
list may be able to recover that information by backtracking through the higher levels of the
skip list.  In application this may be helpful for debugging during a boot sequence or a program
with multiple sequential steps.
