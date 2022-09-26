set -e
g++ toTest.cpp -o toTest
g++ gen.cpp -o gen
g++ correctSolution.cpp -o correctSolution
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./toTest < input_file > myAnswer
    ./correctSolution < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer