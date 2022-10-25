#!/bin/bash

IDL_DIR="./types"
GEN_DIR="./generated"
GEN_XML_DIR="./xmltypes"

FILES="$IDL_DIR/*.idl"
for f in $FILES
  do
    if [ -f "$f" ]; then
      echo $f
      $NDDSHOME/bin/rtiddsgen -d "$GEN_DIR" -language C++11 -update typefiles $f
      $NDDSHOME/bin/rtiddsgen -d "$GEN_XML_DIR" -convertToXml $f
    else
     echo "ERROR: Check \"$f\""
  fi
done