#include <bits/stdc++.h>

typedef int ulli;

int bigmod(int a, int b, int M) {
	if(b == 0) return 1 % M;
	int x = bigmod(a,b/2,M);
	x = (x*x) % M;
	if(b%2 == 1) x = (x*a) % M;
	return x;
}

int main() {
	ulli p,q,n,phi_n,e,d,m;
	std::cout << "Enter prime p and q (p != q): ";
	std::cin >> p >> q;
	n = p*q;
	phi_n = (p-1) * (q-1);
	std::cout << "Possible values of e: ";
	// 1 < e < phi_n
	for(int i=2; i<phi_n; i++)
		if(std::__gcd(phi_n, i) == 1) std::cout << i << " ";	
	std::cout << "\nSelect e: ";
	std::cin >> e;
	for(int i=2; i<phi_n; i++) {
		if((i*e) % phi_n == 1) {
			d = (ulli)i; break;
		}	
	}	

	std::cout << "Public Key: " << "{" << e << "," << n << "}" << std::endl; 
	std::cout << "Private Key: " << "{" << d << "," << n << "}" << std::endl; 

	std::cout << "Enter m (m<n): ";
	std::cin >> m;
	int C = bigmod(m,e,n);
	std::cout << "Cipher: " << C << std::endl;
	std::cout << "Message: " << bigmod(C,d,n) << std::endl;

	return 0;
}