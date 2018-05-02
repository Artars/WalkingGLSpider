all:
	g++ -o spider.o Main.cpp Spider.cpp Legs.cpp -lglut -lGLU -lGL -lm

clean:
	rm spider.o

run:
	./spider.o