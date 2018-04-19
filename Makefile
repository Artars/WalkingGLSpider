all:
	g++ -o spider Main.cpp -lglut -lGLU -lGL -lm

clean:
	rm spider

run:
	./spider