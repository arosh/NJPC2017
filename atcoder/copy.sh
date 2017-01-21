#!/bin/bash
set -ue

# http://stackoverflow.com/questions/1469849
arr="A B C D E F G H"
for x in $arr; do
  # フォルダがあれば削除する
  if [ -d ./$x/in ]; then
    rm -rf ./$x/in
  fi
  mkdir -p ./$x/in

  if [ -d ./$x/out ]; then
    rm -rf ./$x/out
  fi
  mkdir -p ./$x/out
done

cp ../InputForm/rime-out/tests/*.in ./A/in
cp ../InputForm/rime-out/tests/*.diff ./A/out
rename 's/\.diff$/\.out/' ./A/out/*.diff

cp ../GridGraph/rime-out/tests/*.in ./B/in
cp ../GridGraph/rime-out/tests/*.diff ./B/out
rename 's/\.diff$/\.out/' ./B/out/*.diff

cp ../HurdleRace/rime-out/tests/*.in ./C/in
cp ../HurdleRace/rime-out/tests/*.diff ./C/out
rename 's/\.diff$/\.out/' ./C/out/*.diff

cp ../NMPuzzle/rime-out/tests/*.in ./D/in
cp ../NMPuzzle/rime-out/tests/*.diff ./D/out
rename 's/\.diff$/\.out/' ./D/out/*.diff
# cp ../NMPuzzle/tests/judge.cc ./D/etc/output_checker.cpp

cp ../SparselyPopulatedRegions/rime-out/tests/*.in ./E/in
cp ../SparselyPopulatedRegions/rime-out/tests/*.diff ./E/out
rename 's/\.diff$/\.out/' ./E/out/*.diff

cp ../MixedDoubles/rime-out/tests/*.in ./F/in
cp ../MixedDoubles/rime-out/tests/*.diff ./F/out
rename 's/\.diff$/\.out/' ./F/out/*.diff
# cp ../MixedDoubles/tests/judge.cc ./F/etc/output_checker.cpp

cp ../CommutativeLaw/rime-out/tests/*.in ./G/in
cp ../CommutativeLaw/rime-out/tests/*.diff ./G/out
rename 's/\.diff$/\.out/' ./G/out/*.diff

cp ../BlackWhiteTree/rime-out/tests/*.in ./H/in
cp ../BlackWhiteTree/rime-out/tests/*.diff ./H/out
rename 's/\.diff$/\.out/' ./H/out/*.diff
