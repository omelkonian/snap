unset log
unset label
unset key

set title 'Degree Distribution'
set size 1, 1

set xlabel "Degree - k"
set ylabel "Relative degree - p(k)-%"

set yr [0:]
set xr [0:]

set xtics 2
set ytics 5

set style data histogram
set style fill solid border

plot 'data.txt' using 2

pause mouse keypress