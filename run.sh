FLAG=
:<<H
INPUT=""
for i in src/*.cpp;
do
	g++  $FLAG --std=c++11 -fPIC -c $i -o $i.o
	INPUT=$INPUT" "$i.o
done

for i in src/Collections/*.cpp;
do
	g++ $FLAG --std=c++11 -fPIC -c $i -o $i.o
	INPUT=$INPUT" "$i.o
done

for i in src/Stream/*.cpp;
do
	g++ $FLAG --std=c++11 -fPIC -c $i -o $i.o
	INPUT=$INPUT" "$i.o
done

for i in src/Regex/*.cpp;
do
	g++ $FLAG --std=c++11 -fPIC -c $i -o $i.o
	INPUT=$INPUT" "$i.o
done

for i in src/UnitTest/*.cpp;
do
	g++ $FLAG --std=c++11 -fPIC -c $i -o $i.o
	INPUT=$INPUT" "$i.o
done

g++ $FLAG --std=c++11 -shared -fPIC $INPUT -o lib/libregex_compiler.so
H
g++ $FLAG --std=c++11 tool.cpp -o tool -I src/ -L lib  -lregex_compiler -lpthread
