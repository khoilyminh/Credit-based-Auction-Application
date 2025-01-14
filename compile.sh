# Check if the bin directory exists
# If not create it
if [ ! -d "./bin" ]; then
	mkdir bin
fi

# Check if the data directory exists
# If not create it
if [ ! -d "./data" ]; then
	mkdir data
fi

# Compile the program
g++ -std=c++11 ./src/main.cpp ./src/**/*.cpp -o ./bin/main