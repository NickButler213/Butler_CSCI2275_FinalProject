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
the skip list can make copies of the data, this alone helps the list to not lose
information; but since the list can skip over nodes, then there is a better
chance that nodes are lost to error or data corruption still have a chance of
being recovered.  In this project this last node was searched by using a
functionality of a graph data structure, the depth first search or DFS.  By
connecting the nodes together, not just by the members next, prev, and below
but also by above, the DFS could navigate through the list of failed nodes and
see if the last node was still accessable.  The results of this are shown in the
graph connectivity.png.  This graph shows what percent of skip lists can recover
their last node, if each node in the list has an n percent change of failure.
The results show that as the failure probabaility increases, there is an
approximate linear decrease in probability that the last node can be recovered.
Once the failure probabilty reaches about 40%, the relationship is no longer
linear and the chance of recovery is so poor that the skip list is not usefil in
recovering the data. 

The fail test was to see how the connectivity was tested with variable input size.
The result was that the size did not have a significant role in the connectivity
of a graph and it is only the percent of node failures that has a significant role.
This is shown in the graph inputSize.png.

In conclusion the skip list is slower in run time than a BST; however, unlike a BST
or traditional linked list the skip list can potentially recover lost data
independently of input size.  This recovery of data has a high chance of success if
if the probability of any given node failing is less than 10%.
