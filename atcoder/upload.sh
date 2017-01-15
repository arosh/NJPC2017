#!/bin/bash
set -ue

#arr="A B C D E F G H"
arr="A"
for x in $arr; do
  # フォルダがなければ作成する
  if [ ! -d ./$x/in ]; then
    mkdir -p ./$x/in
  fi
  rm ./$x/in/*.in

  if [ ! -d ./$x/out ]; then
    mkdir -p ./$x/out
  fi
  rm ./$x/out/*.out
done


cp ../InputForm/rime-out/tests/*.in ./A/in
cp ../InputForm/rime-out/solution/*.out ./A/out

php ./imojudge_upload.php 2308 ./A
#php ./imojudge_upload.php 2309 ./B
#php ./imojudge_upload.php 2310 ./C
#php ./imojudge_upload.php 2311 ./D
#php ./imojudge_upload.php 2312 ./E
#php ./imojudge_upload.php 2313 ./F
#php ./imojudge_upload.php 2314 ./G
#php ./imojudge_upload.php 2315 ./H
