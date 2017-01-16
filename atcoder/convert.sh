#!/bin/bash
set -ue
arr="A B C D E F G H"
for x in $arr; do
  cd ./$x/task
  python md2atcoder.py statement.md > ${x}_jp.html
  cd ../..
done
