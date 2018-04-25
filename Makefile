all:
	g++ -o spider Main.cpp Spider.cpp Legs.cpp -lglut -lGLU -lGL -lm

clean:
	rm spider

run:
	./spider