
#include <iostream>
#include <cmath>
#include <typeinfo>
#include "bigInt.h"

bool bigIntMatrixTest(long long maxSize); 
bool testIncrementing(long long numIncrements);
bool testPowers(long long maxPow);
int main() {
	long long num1 = 65;
	long long num2 = 8009;
	bigInt num1Big = bigInt(num1);
	bigInt num2Big = bigInt(num2);

	bigInt n1 = bigInt(176234515);
	bigInt n2 = bigInt(421332);

	std::cout << n1 / n2 << std::endl;
	
	if (bigIntMatrixTest(1000)) { std::cout << "Matrix test passed!\n"; }
	else { std::cout << "Matrix test failed!\n"; }
	if (testIncrementing(1000)) { std::cout << "Increment test passed\n"; }
	else { std::cout << "Increment test failed!\n"; }
	if (testPowers(20)) { std::cout << "Power test passed\n"; }
	else { std::cout << "Power test failed!\n"; }

}

bool bigIntMatrixTest(long long maxSize) {
	
	for( long long num1 = 1; num1 <= maxSize; num1++) {
		for( long long num2 = 1; num2 <= maxSize; num2++) {
			bigInt b1 = bigInt(num1);
			bigInt b2 = bigInt(num2);
			
			if (num1 + num2 != (b1 + b2).toInt64()) { 
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << num1 + num2 << std::endl;
				std::cout << (b1 + b2).toInt64() << std::endl;
				std::cout << "Failed addition..." << std::endl;
				return false; 
			}
			if (num1 + -num2 != (b1 + -b2).toInt64()) {
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << num1 + -num2 << std::endl;
				std::cout << (b1 + -b2).toInt64() << std::endl;
				std::cout << "Failed adding a negative..." << std::endl;
				return false; 
			}
			if (num1 - num2 != (b1 - b2).toInt64()) { 
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << num1 - num2 << std::endl;
				std::cout << (b1 - b2).toInt64() << std::endl;
				std::cout << "Failed subtraction..." << std::endl;
				return false; 
			}
			if (num1 - -num2 != (b1 - -b2).toInt64()) { 
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << num1 - -num2 << std::endl;
				std::cout << (b1 - -b2).toInt64() << std::endl;
				std::cout << "Failed subtracting a negative..." << std::endl;
				return false; 
			}
			if (num1 * num2 != (b1 * b2).toInt64()) {
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << num1 * num2 << std::endl;
				std::cout << (b1 * b2).toInt64() << std::endl;
				std::cout << "Failed multiplication..." << std::endl;
				return false; 
			}
		}
	}
	std::cout << "Starting division tests...\n";
	for( long long num1 = 10; num1 <= maxSize; num1++) {
		for( long long num2 = 1; num2 <= num1; num2++) {
			bigInt b1 = bigInt(num1);
			bigInt b2 = bigInt(num2);
			//std::cout << num1 << std::endl;
			//std::cout << num2 << std::endl;
			long long lilDiv = num1 / num2;
			bigInt bigDiv = b1 / b2;
			if (lilDiv != bigDiv.toInt64()) {
				std::cout << num1 << std::endl;
				std::cout << num2 << std::endl;
				std::cout << lilDiv << std::endl;
				std::cout << bigDiv << std::endl;
				return false; 
			}
		}
	}
	return true; //all numbers passed
}

bool testIncrementing(long long numIncrements) {
	bigInt toDecrement;
	bigInt toIncrement;
	long long base = toDecrement.getBase();
	long long inc = base - numIncrements / 2;
	long long dec = base + numIncrements / 2;
	toDecrement = dec;
	toIncrement = inc;

	for (long long i = base - numIncrements / 2; i < base + numIncrements / 2; i++) {
		toDecrement--;
		dec--;
		toIncrement++;
		inc++;
		if (toDecrement.toInt64() != dec) { 
			std::cout << "Decrementing failed...\n";
			std::cout << toDecrement << "\n";
			std::cout << toDecrement.toInt64() << "\n";
			std::cout << dec << std::endl;
			return false; 
		}
		if (toIncrement.toInt64() != inc) { 
			std::cout << "Incrementing failed...\n";
			std::cout << toIncrement << "\n";
			std::cout << toIncrement.toInt64() << "\n";
			std::cout << inc << std::endl;
			return false; 
		}
	}
	return true;
}

bool testPowers(long long maxPow) {
	long long base = 3;
	for (long long i = 0; i <= maxPow; i++) {
		long long result = std::pow(base, i);
		bigInt bigBase = bigInt(base);
		bigInt bigExp = bigInt(i);
		bigInt bigResult = bigBase ^ bigExp;
		if (bigResult.toInt64() != result) { 
			std::cout << base << "\n" << i << "\n" << result << "\n" 
					  << bigResult << std::endl;
			return false; 
		}
	}
	base = 4;
	for (long long i = 0; i <= maxPow; i++) {
		long long result = std::pow(base, i);
		bigInt bigBase = bigInt(base);
		bigInt bigExp = bigInt(i);
		bigInt bigResult = bigBase ^ bigExp;
		if (bigResult.toInt64() != result) { 
			std::cout << base << "\n" << i << "\n" << result << "\n" 
					  << bigResult << std::endl;
			return false; 
		}
	}
	base = 5;
	for (long long i = 0; i <= maxPow; i++) {
		long long result = std::pow(base, i);
		bigInt bigBase = bigInt(base);
		bigInt bigExp = bigInt(i);
		bigInt bigResult = bigBase ^ bigExp;
		if (bigResult.toInt64() != result) { 
			std::cout << base << "\n" << i << "\n" << result << "\n" 
					  << bigResult << std::endl;
			return false; 
		}
	}
	return true;
}
