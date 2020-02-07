#ifndef QFIND_H_INCLUDED
#define QFIND_H_INCLUDED

/**
 @brief Returns the first element in the range [first, first+total_elem) that satisfies specific criteria

 @param [in] first - pointer to a first element of sequence
 @param [in] total_elem - number of elements in sequence
 @param [in] size - size (in byte) one element of sequence
 @param [in] cmp - pointer to a faunction that compares two elements, return zero if elements are equals
 @param [in] criteria - pointer to the data to be found in the sequence

 @return index of element witch equal the criteria
*/
 
int qfind (void* first, size_t total_elem, size_t size, int (*cmp)(const void*,const void*), const void* criteria );

#endif /* QFIND_H_INCLUDED */
