# C++ implementation of paper: SpArch: Efficient Architecture for Sparse Matrix Multiplication
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