# Check if the bin directory exists, if not create it
if (-not (Test-Path -Path "bin")) {
	New-Item -ItemType Directory -Path "bin"
}

# Check if the data directory exists, if not create it
if (-not (Test-Path -Path "data")) {
	New-Item -ItemType Directory -Path "data"
}

# Compile the program
g++ -std=c++11 ./src/main.cpp ./src/**/*.cpp ./src/**/**/*.cpp -o ./bin/main.exe

# Run the program
.\bin\main.exe
