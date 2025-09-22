#!/bin/bash


set -e

cd ~/teste

echo "iniciando a compilação do projeto com CMake"

cmake --build build

echo "compilação finalizada"
echo "executando programa teste"


./build/src/exec8

cd ../..