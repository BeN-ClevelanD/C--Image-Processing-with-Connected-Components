CC=g++
LIBS=-lm



findcomp: PGMimageProcessor.o ConnectedComponent.o driver.o
	g++ PGMimageProcessor.o ConnectedComponent.o driver.o -o findcomp -std=c++20

%.o : %.cpp
	$(CC) -c $< -o $@ -std=c++20


clean:
	rm *.o driver
	

	
	
