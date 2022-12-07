#!/bin/sh

make

for ((i = 1; ; ++i)); do
    echo "test #$i"
    ./gen.py "$i" > in.txt
    ./a.out < in.txt > myAnswer 2> /dev/null
    ./b.out < in.txt > correctAnswer 2> /dev/null
    diff -Z myAnswer correctAnswer > /dev/null || break
done

printf "\nWA on test #%d:\n\n" "$i"
cat in.txt
printf "\nYour answer is:\n"
cat myAnswer
printf "\nCorrect answer is:\n"
cat correctAnswer