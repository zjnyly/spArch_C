# C++ implementation of paper: SpArch: Efficient Architecture for Sparse Matrix Multiplication
https://sparch.mit.edu/
### Implemented:

* CSR format storage
* Comparator Array based Merger
* Matrix Condensing
* Huffman Tree Scheduler

### TO DO:
*  Row Prefetcher
*  Hierarchical Parallel Merge Unit

### Notice:
This is just C implementation of the hardware architechture, so can't achieve hardware level parallelism, thus can't hide memory delay.

Hard to turn into HDL

```
inner product
Total time:0.063ms
0 42 0 42 0 42 0 42 0 42 0 42 
0 84 0 84 0 84 0 84 0 84 0 84 
0 126 0 126 0 126 0 126 0 126 0 126 
0 168 0 168 0 168 0 168 0 168 0 168 
0 210 0 210 0 210 0 210 0 210 0 210 
0 252 0 252 0 252 0 252 0 252 0 252 
0 294 0 294 0 294 0 294 0 294 0 294 
0 336 0 336 0 336 0 336 0 336 0 336 
0 378 0 378 0 378 0 378 0 378 0 378 
0 420 0 420 0 420 0 420 0 420 0 420 
0 462 0 462 0 462 0 462 0 462 0 462 
0 504 0 504 0 504 0 504 0 504 0 504 

sparse product
Total time:0.663ms
0 42 0 42 0 42 0 42 0 42 0 42 
0 84 0 84 0 84 0 84 0 84 0 84 
0 126 0 126 0 126 0 126 0 126 0 126 
0 168 0 168 0 168 0 168 0 168 0 168 
0 210 0 210 0 210 0 210 0 210 0 210 
0 252 0 252 0 252 0 252 0 252 0 252 
0 294 0 294 0 294 0 294 0 294 0 294 
0 336 0 336 0 336 0 336 0 336 0 336 
0 378 0 378 0 378 0 378 0 378 0 378 
0 420 0 420 0 420 0 420 0 420 0 420 
0 462 0 462 0 462 0 462 0 462 0 462 
0 504 0 504 0 504 0 504 0 504 0 504 
```
