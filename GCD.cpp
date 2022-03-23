#include <bits/stdc++.h>

int gcd(int a, int b) {
	if(a == 0) return b;
	gcd(b % a, a);
}

int main(int argc, char const *argv[])
{
	int a, b;
	std::cout << "Enter two integer numbers: ";
	std::cin >> a >> b;
	std::cout << "GCD of " << a << " " << b << " is " << gcd(b,a) << std::endl;
	return 0;
}