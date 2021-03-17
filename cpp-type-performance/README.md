# C++ type performance study
**Test:** for looping the type until 127, and running the for loop thousands of times to get more accurate numbers

Tested with an AMD Ryzen 5 3600.

The first 3 decimal characters are accurate.


This study took me about 7 or so hours to make.

Every number was averaged like 100 times by std::accumulator then averaged multiple times with [Average Calculator](https://www.calculator.net/average-calculator.html),

The tests were then ran again for the new study at the bottom and those numbers were averaged out with the old ones.

All the numbers are in `study.txt`.

There is also a chart (`chart.png`). Lower numbers are better.

uint32_t and unsigned int (they're both technically the same) are the fastest ones (on AMD CPUs at least)
