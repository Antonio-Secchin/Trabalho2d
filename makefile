all: compila
 	
compila:	
	g++ -o trabalhocg *.cpp -lGL -lGLU -lglut

clean: 
	$(RM) trabalhocg