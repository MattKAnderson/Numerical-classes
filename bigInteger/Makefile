
test: bigIntTest.o bigInt.o
	g++-9 -O3 -o $@ $^

%.o: %.cpp
	g++-9 -c -O3 -o $@ $<

.PHONY: clean

clean: 
	rm *.o
