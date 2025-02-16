#!/bin/bash

PROJECT_NAME="HotelManagementService"

Build ()
{
  bear -- ./premake/premake5 gmake
  make
}

Clean ()
{
  make clean
}

Run ()
{
  exedir=$(find -name "$PROJECT_NAME.out")
  if [ -z "$exedir" ]
  then 
    echo "--------"
    echo "$PROJECT_NAME.out not found"
    echo "--------"
  else
    clear
    echo
    echo "==== Running ===="
    echo
    $exedir
    echo
    echo "========"
  fi
}

Clean
Build
Run
