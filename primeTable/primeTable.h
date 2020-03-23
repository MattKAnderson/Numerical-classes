/*
	@author M. Anderson
	@date March 23, 2020
	@brief class to represent a prime number truth table
*/
#ifndef PRIME_TABLE_INCL_GUARD
#define PRIME_TABLE_INCL_GUARD
#include <vector>

class primeTable {
public:
	primeTable(size_t max);       // create prime table of given size
	bool isPrime(size_t number);  // check if a given number is prime
	size_t size();                // check size of the table
private:
	std::vector<bool> truthTable;
}
#endif
