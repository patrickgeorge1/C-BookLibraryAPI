all:
	rm -rf program
	g++ main.cpp Utils/utils.cpp Utils/api.cpp Utils/buffer.cpp -o program
	./program

clean:
	rm -rf program

build:
	g++ main.cpp Utils/utils.cpp Utils/api.cpp Utils/buffer.cpp -o program

run:
	./program
