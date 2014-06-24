###Lab 5 report

Note: The performance timings are reported inside the console output regardless of
the `FILE` flag.

Note2: The remove code could be further refactored (e.g. two frequently used
routine is "get inorder predecessor" and "get inorder successor"). However,
deadline is drawing near and we've had quite a bit of trouble with remove(),
so we don't want to mess with it unnecessarily.

Note3: Helper routines are located directly underneath the logic routines in
the .cpp file.

---

##Instructions on tree usage:

#To perform recursive traversal:

- write a function that processes a `Node` pointer; see node.h for `Node`'s functionalities
- pass this function into `yourTree->traverse(_____, ostream&, int)`
- the `ostream` object reference is a necessary evil to accomplish the 7-nodes-per-line print behavior
- the `int` argument specifies the traversal order: 1 = preorder, 0 = inorder, -1 = postorder

#To perform iterative traversal:
- Do the same, except use `yourTree->iterativeInorder(function, ostream&)` instead.



#Example command for lab5main.cpp:

---
    $ g++ -Wall -g lab5main.cpp
    $ ./a.out NOFILE NODEBUG
---

#Example output for each input file:

    his-279 not-299 !-301 is-313 it-361 HAMLET-385 in-400 
    --421 ?-428 my-441 a-465 you-499 :-535 I-542 
    ;-582 to-626 of-628 and-703 the-989 .-1301 ,-3269 

    'A-1 'Adam-1 'Adieu-1 'And-1 'Anon-1 'As-1 'As'es-1 
    'But-1 'Choose-1 'Doubt-1 'For-1 'Fore-1 'Forgive-1 'Gainst-1 
    'HAMLET-1 'He-1 'High-1 'Horatio-1 'If-1 'In-1 'It-1 

    hamlet.txt: 0.06404 sec
    ======================================

---