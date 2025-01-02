#!/bin/bash

if [ -d "bsnes-plus" ]; then
  echo "bsnes-plus already exists."
else
  

  git clone https://github.com/devinacker/bsnes-plus.git || {
    echo "Could not clone bsnes-plus."
    exit 1
  }

  cd bsnes-plus
  git submodule update --init --recursive
  echo "bsnes-plus cloned."

  cd bsnes/

  make -j$(nproc) || {
    echo "Could not build bsnes-plus."
    exit 1
  }

  echo "bsnes-plus built."

  cd ../../

fi

if [ -d "pvsneslib" ]; then
  echo "pvsneslib already exists."
else
  
  wget https://github.com/alekmaul/pvsneslib/releases/download/4.3.0/pvsneslib_430_64b_linux_release.zip

  unzip pvsneslib_430_64b_linux_release.zip

  rm pvsneslib_430_64b_linux_release.zip

fi

export PVSNESLIB_HOME=$(pwd)/pvsneslib
export PATH=$PATH:$PVSNESLIB_HOME/bin

echo "done!"