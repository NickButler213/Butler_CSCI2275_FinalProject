When comparing the run time of a BST to a skip list, the BST is faster for all
insert, search, and remove operations.  The largest time difference is with
the insert operation shown by the graph insert.png.  For the search and
remove operations, the skip list takes somewhere around twice the amount of
time that the BST takes.  The graphs searchTimes.png, insertTimes.png, and
removeTimes.png do their respective operations with 10 different input sizes.

Analyzing just these run times, one may come to the conclusion that skip lists
are not worth the time for large datasets; however, a skip list has one
functionality that the BST does not.  This is the capability of the skip list
to still have a connection between the beginng node and the end node.  Since
the skip list can make copies of data, this alone helps the list to not lose
information.  But since the list can skip over nodes, then there is a better
chance that if some nodes are lost to error or data corruption, then the last
node still has a chance of being recovered.  In this project this last node
was search by using a functionality of a graph, the depth first search.  By
connecting the nodes together, not just by the members next, prev, and below
but also by above, the depth first search could navigate through the list of
failed nodes and see if the last node was still accessable.  The results of
this are shown in the graph connectivity.png.  This graph shows what percent
of skip lists can recover their last node, if each node in the list has an n
percent change of failure.  The results show that as the failure probabaility
increases, there is a linear decrease in probability that the last node can
be recovered.  Once the failure probabilty reaches about 40%, the relationship
is no longer linear and the chance of recovery is so poor that the skip list
is not usefil in recovering the data. 

Lastly, the connectivity was tested with variable input size, and the
result was that the size does not have a significant role in the connectivity
of a graph and it is only the probability of failure that has a role.  This is shown
in the graph inputSize.png.

In conclusion the skip list is slower in run time than a BST; however,
information can likely be recovered independent of input size and if the probability
of a single node failure is less than 10%.
