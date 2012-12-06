all: algo_wars

algo_wars: anneal.cpp main.cpp make_input.cpp verify.cpp
	g++ -I<pathToBoostIncludes> -L<pathToProgramOptionsLib> -o algo_wars anneal.cpp main.cpp make_input.cpp verify.cpp

clean:
	rm -f algo_wars
