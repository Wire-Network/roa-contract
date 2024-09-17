# This script builds the smart contract for the ROA project

cdt-cpp -abigen -contract=roa -R=./ricardian -I=./include -o=./roa/roa.wasm ./src/roa.cpp