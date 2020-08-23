# share
This and that

msort.c is a near verbatim C implementation of Knuth's second mergesort,
 Algorithm S from Volume 3. Same variable names, same steps with same numbers, and
 even an extra element on the array so we can keep the same "from 1" array numbering.
 Knuth assumes the "scratch" array can be adjacent to the source array, which is not all
 that realistic, but that's what we do here. 

msort0.c is the same as msort.c but with arrays indexed by 0 

msort2.c is the same as msort0.c but with 2 arrays instead of a single one - which
makes the whole thing more straightforward.

