#include "lcrypto.h"

/*
 * 欧几里德算法
 *
 * E1.[求余数] 以n除m并令r为所得余数 (我们将有0<=r<n)
 * E2.[余数为零?] 若r = 0,算法结束,n即为答案
 * E3.[减少] 置m<-n, n<-r, 并返回步骤E1
 */
__integer __API__ EuclidAlgorithm(__integer m, __integer n) {
	__integer r = 0;

	while (1) {
		r = m % n;

		if (r == 0)
			return n;

		m = n;
		n = r;
	}

	return 1;
}

/*
 * 扩展欧几里德算法
 * 给定两个正整数m和n,我们计算它们的最大公约因子d和两个整数a和b,使得am+bn=d
 *
 * E1.[初始化] 置a'<-b<-1, a<-b'<-0,c<-m,d<-n
 * E2.[除] 设q和r分别是c除以d的商和余数。(我们有c=qd+r,且0<=r<d)
 * E3.[余数为0?] 如果r = 0,算法终止;在此情况下,我们如愿地有am+bn=d
 * E4.[循环] 置c<-d,d<-r,t<-a',a'<-a,a<-t-qa,t<-b',b'<-b,b<-t-qb,并返回E2
 */
__integer __API__ EuclidAlgorithmEx(__integer m, __integer n, __integer *pa, __integer *pb) {
	__integer a = 0, b = 0, c = 0, d = 0, a_ = 0, b_ = 0, q = 0, r = 0, t = 0;


	// 初始化
	a = 0;
	a_ = 1;
	b = 1;
	b_ = 0;
	c = m;
	d = n;

	while (1) {
		q = c / d;
		r = c / d;

		// 余数为0
		if (r == 0) {
			*pa = a;
			*pb = b;
			return d;
		}

		c = d;
		d = r;
		t = a_;
		a_ = a;
		a = t - q * a;
		t = b_;
		b_ = b;
		b = t - q * b;
	}

	return d;
}
