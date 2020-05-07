build:
	g++ main.cpp Utils/utils.cpp Utils/api.cpp Utils/buffer.cpp -o program

clean:
	rm -rf program

run:
	./program
