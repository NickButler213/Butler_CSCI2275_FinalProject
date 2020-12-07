The skip list is similar to a tradiational linked list but with one extra area of functionality. Each
node in the list not only has a next and previous neighbor, but also an above and below neighbor.
The skip list, unlike a linked list, contains levels and each level can be thought of as having its own
linked list in it.  The number of levels or height of the skip list is determined by a probability.
When a node is inserted into the skip list, it has a 100% chance of residing in level 0, a 50% chance
of residing in level 1, a 25% chance of residing on level 2 and so on.  The height of the skip list is
thus the height of the node that resides in the highest level This means that if the input size is size
n, then the size of the graph will likely be around 2n.  Also, level 0 will have a definite size of n,
level 1 will likely have size n/2, level 2 will likely have size n/4 and so on.  The structure of the
skip list can be seen on a small scale by running test.cpp.

The list is defined by the head node.  The head is a node without information and it resides at the top
level of the skip list.  Each node below the head is also empty and they each act as the heads of
their own lists at each of their respective levels.

When a node is inserted a "coin" is flipped until the result is false.  For example, if heads is true
and tails is false, then one trial may be heads then tails or just heads or heads then heads then tails.
The result will always end in tails.  So, if the result is two heads then a tails, then three new nodes
are created, one inserted into level 2, the other level 1, and the last level 0.  The above and
below neighbors of each node will hold the same key value as the node itself.

The idea of the skip list is that there is an ordered list at level 0 like a typical linked list, but
by decreasing the nodes at higher levels and linking them together, the time to access those nodes can
take less time.
