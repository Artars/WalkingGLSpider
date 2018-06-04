all:
	g++ -o spider.o Test3D.cpp Spider3D.cpp Objector.cpp Spider.cpp Legs.cpp Transform.cpp Vector3.cpp -lglut -lGLU -lGL -lm

clean:
	rm spider.o

run:
	./spider.o