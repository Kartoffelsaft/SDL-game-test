compiler = g++
arguments = -lSDL2
sources = ./*.cpp
headers = ./
output = game

compileAll:
	$(compiler) -o $(output) $(sources) -I $(headers) $(arguments)

compileAllDebug:
	$(compiler) -o $(output) $(sources) -I $(headers) $(arguments) -g
