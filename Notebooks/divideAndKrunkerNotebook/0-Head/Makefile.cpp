CC = g++ -std=c++20
FLAGS = -Wall -Wextra -Wfloat-equal -DLOCAL -O3
INCLUDES = -lm -I .

default: a.out b.out combined.cpp

a.out: solve.cpp bits/stdc++.h.gch
    $(CC) $(FLAGS) $(INCLUDES) solve.cpp -o a.out

b.out: brute.cpp bits/stdc++.h.gch
    $(CC) $(FLAGS) $(INCLUDES) brute.cpp -o b.out

combined.cpp: solve.cpp

python expander.py solve.cpp

bits/stdc++.h.gch: bits/stdc++.h
    $(CC) $(FLAGS) bits/stdc++.h

clean:
    $(RM) a.out a.out.out b.out *.class
    $(RM) bits/stdc++.h.gch
    $(RM) combined.cpp
    $(RM) out.txt
    $(RM) myAnswer correctAnswer
    $(RM) gmon.out