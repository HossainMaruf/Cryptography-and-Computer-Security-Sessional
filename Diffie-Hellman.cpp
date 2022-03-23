#include <bits/stdc++.h>


int bigmod(int a, int b, int M) {
	if(b == 0) return 1 % M;
	int x = bigmod(a, b/2, M);
	x = (x*x) % M;
	if(b % 2 == 1) x = (x*a) % M;
	return x;
}

int primRoot(int q) {
	int alpha;
	bool ok = true;
	std::vector<bool> isExist(q, false);
	std::cout << "Primitive root of q: ";
	for(int i=2; i<q; i++) {
		for(int j=1; j<q; j++) {
			int result = bigmod(i,j,q);
			if(isExist[result]) {
				ok = false;
				break;
			} else {
			  isExist[result] = true;
			}
		}
		if(ok) std::cout << i << " ";
		std::fill(isExist.begin(), isExist.end(), false);	
		ok = true;
	}	
	std::cout << std::endl << "Select one primitive root: ";
	std::cin >> alpha;
	return alpha;
}

int main() {
	int q, xa, xb, ya, yb, secret_a, secret_b;
	std::cout << "Enter prime q: ";
	std::cin >> q;
	int alpha = primRoot(q);
	std::cout << "Enter private key xa<q of user A: ";
	std::cin >> xa;
	std::cout << "Enter private key xb<q of user B: ";
	std::cin >> xb;
	ya = bigmod(alpha, xa, q);
	yb = bigmod(alpha, xb, q);
	std::cout << "Public key of user A: " << ya << std::endl;
	std::cout << "Public key of user B: " << yb << std::endl;
	secret_a = bigmod(yb, xa, q);
	secret_b = bigmod(ya, xb, q);
	std::cout << "Secret key of user A: " << secret_a << std::endl;
	std::cout << "Secret key of user B: " << secret_a << std::endl;
	return 0;
}