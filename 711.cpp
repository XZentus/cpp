#include <cstdio>

using namespace std;

void test(int n) {
	int a,b,c,d, ab, abc, abcd;
	double ad,bd,cd,dd;
	int tsum  = n;
	int tprod = tsum * 1000000;
	int t1 = tsum - 1, t2 = tsum - 2, t3 = tsum - 3;
	
	for(a =     1; a       <= t3;   ++a) {
	for(b = a + 1; a   + b <= t2;   ++b) { ab   = a   + b;
	for(c = b + 1; ab  + c <= t1;   ++c) { abc  = ab  + c;
	for(d = c + 1; abc + d <= tsum; ++d) { abcd = abc + d;
		if(abcd == tsum && (a * b * c * d == tprod)) {
			ad = double(a)/100.0;
			bd = double(b)/100.0;
			cd = double(c)/100.0;
			dd = double(d)/100.0;
			printf("\n%1.2f + %1.2f + %1.2f + %1.2f = %1.2f\n", ad, bd, cd , dd, ad+bd+cd+dd);
			printf(  "%1.2f * %1.2f * %1.2f * %1.2f = %1.2f\n", ad, bd, cd , dd, ad*bd*cd*dd);
			printf(  "--------------------------------\n");
		}
	}}}}
}

int main() {

	for(int i = 640; i < 1000; ++i)
		test(i);
	
	return 0;
}
	
	
