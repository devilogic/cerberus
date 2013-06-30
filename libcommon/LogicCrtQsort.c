#include "TypeDef.h"
#include "Configure.h"

#define	__LOGICQSORT_THRESH__		4		/* threshold for insertion */
#define	__LOGICQSORT_MTHRESH__		6		/* threshold for median */

__STATIC__ __void LogicQst(__integer iSize, __sinteger (__INTERNAL_FUNC__ *pComparFunc)(__CONST__ __void *, __CONST__ __void *), __char *pBase, __char *pMax) {
	__char c, *i, *j, *jj;
	__integer ii;
	__char *mid, *tmp;
	__integer lo, hi;
	__integer thresh;
	__integer mthresh;

	thresh = iSize * __LOGICQSORT_THRESH__;
	mthresh = iSize * __LOGICQSORT_MTHRESH__;

	/*
	 * At the top here, lo is the number of characters of elements in the
	 * current partition.  (Which should be max - base).
	 * Find the median of the first, last, and middle element and make
	 * that the middle element.  Set j to largest of first and middle.
	 * If max is larger than that guy, then it's that guy, else compare
	 * max with loser of first and take larger.  Things are set up to
	 * prefer the middle, then the first in case of ties.
	 */
	lo = pMax - pBase;		/* number of elements as chars */
	do	{
		mid = i = pBase + iSize * ((lo / iSize) >> 1);
		if (lo >= mthresh) {
			j = (pComparFunc((jj = pBase), i) > 0 ? jj : i);
			if (pComparFunc(j, (tmp = pMax - iSize)) > 0) {
				/* switch to first loser */
				j = (j == jj ? i : jj);
				if (pComparFunc(j, tmp) < 0)
					j = tmp;
			}
			if (j != i) {
				ii = iSize;
				do	{
					c = *i;
					*i++ = *j;
					*j++ = c;
				} while (--ii);
			}
		}
		/*
		 * Semi-standard quicksort partitioning/swapping
		 */
		for (i = pBase, j = pMax - iSize; ; ) {
			while (i < mid && pComparFunc(i, mid) <= 0)
				i += iSize;
			while (j > mid) {
				if (pComparFunc(mid, j) <= 0) {
					j -= iSize;
					continue;
				}
				tmp = i + iSize;	/* value of i after swap */
				if (i == mid) {
					/* j <-> mid, new mid is j */
					mid = jj = j;
				} else {
					/* i <-> j */
					jj = j;
					j -= iSize;
				}
				goto __swap;
			}
			if (i == mid)
				break;
			else {
				/* i <-> mid, new mid is i */
				jj = mid;
				tmp = mid = i;		/* value of i after swap */
				j -= iSize;
			}
__swap:
			ii = iSize;
			do	{
				c = *i;
				*i++ = *jj;
				*jj++ = c;
			} while (--ii);
			i = tmp;
		}
		/*
		 * Look at sizes of the two partitions, do the smaller
		 * one first by recursion, then do the larger one by
		 * making sure lo is its size, base and max are update
		 * correctly, and branching back.  But only repeat
		 * (recursively or by branching) if the partition is
		 * of at least size THRESH.
		 */
		i = (j = mid) + iSize;
		if ((lo = j - pBase) <= (hi = pMax - i)) {
			if (lo >= thresh)
				LogicQst(iSize, pComparFunc, pBase, j);
			pBase = i;
			lo = hi;
		}
		else
		{
			if (hi >= thresh)
				LogicQst(iSize, pComparFunc, i, pMax);
			pMax = j;
		}
	} while (lo >= thresh);
}

/*
 * qsort:
 * First, set up some global parameters for qst to share.  Then, quicksort
 * with qst(), and then a cleanup insertion sort ourselves.  Sound simple?
 * It's not...
 *
 * @implemented
 */
__void __INTERNAL_FUNC__ LogicQsort(__void *pBase0, __integer n, __integer iSize, __sinteger (__INTERNAL_FUNC__ *pComparFunc)(__CONST__ __void *, __CONST__ __void *)) {
	__char *base = (__char *)pBase0;
	__char c, *i, *j, *lo, *hi;
	__char *min, *max;
	__integer thresh;

	if (n <= 1)
		return;

	thresh = iSize * __LOGICQSORT_THRESH__;
	max = base + n * iSize;
	if (n >= __LOGICQSORT_THRESH__) {
		LogicQst(iSize, pComparFunc, base, max);
		hi = base + thresh;
	} else
		hi = max;
	/*
	 * First put smallest element, which must be in the first THRESH, in
	 * the first position as a sentinel.  This is done just by searching
	 * the first THRESH elements (or the first n if n < THRESH), finding
	 * the min, and swapping it into the first position.
	 */
	for (j = lo = base; (lo += iSize) < hi; )
		if (pComparFunc(j, lo) > 0)
			j = lo;
	if (j != base) {
		/* swap j into place */
		for (i = base, hi = base + iSize; i < hi; ) {
			c = *j;
			*j++ = *i;
			*i++ = c;
		}
	}
	/*
	 * With our sentinel in place, we now run the following hyper-fast
	 * insertion sort.  For each remaining element, min, from [1] to [n-1],
	 * set hi to the index of the element AFTER which this one goes.
	 * Then, do the standard insertion sort shift on a character at a time
	 * basis for each element in the frob.
	 */
	for (min = base; (hi = min += iSize) < max; ) {
		while (pComparFunc(hi -= iSize, min) > 0)
			/* void */;
		if ((hi += iSize) != min) {
			for (lo = min + iSize; --lo >= min; ) {
				c = *lo;
				for (i = j = lo; (j -= iSize) >= hi; i = j)
					*i = *j;
				*i = c;
			}
		}
	}
}
