#!/bin/bash


set -e

cd ~/CompVision

echo "iniciando a compilação do projeto com CMake"

cmake --build build

echo "compilação finalizada"
echo "executando programa teste"


./build/src/exec8

cd ../..