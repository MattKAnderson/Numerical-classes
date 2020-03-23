/* member definitions for primeTable class */
#include "primeTable.h"
	
primeTable::primeTable(size_t max) {
	truthTable.resize(max + 1, true);
	for (int i = 0; i <= max; i++) {
		if (truthTable[i]) {
			for (int j = 2 * i; j <= max; j += i) {
				truthTable[j] = false;
			}
		}
	}
}
bool primeTable::isPrime(size_t number) {
	return truthTable.at(number);
}
size_t primeTable::size() {
	return truthTable.size();
}
