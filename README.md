# templated_segment_tree

The tree needs you to define type of nodes, functions for requests and updating and neutral elements for both.
All these things will be turned into a segment_tree.

*get(l, r)* returns result of request function for interval [l, r)

*set(l, r)* applies update function for interval [l, r)
