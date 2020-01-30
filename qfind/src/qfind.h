#ifndef QFIND_H_INCLUDED
#define QFIND_H_INCLUDED

/**
 @Returns the first element in the range [first, first+total_elem) that satisfies specific criteria
 @Parametrs:
 @ first - pointer to a first element of sequence
 @ total_elem - number elements sequence
 @ size - size (in byte) one element of sequence
 @ cmp - pointer to a faunction that compares two elements, return zero if elements are equals
 @ criteria - pointer to the data to be found in the sequence
 @Return valuel:
 @ index of element witch equal criteria
*/
 
int qfind (void* first, size_t total_elem, size_t size, int (*cmp)(const void*,const void*), const void* criteria );

#endif /* QFIND_H_INCLUDED */
