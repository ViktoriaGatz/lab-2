#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'collision.png'
#сделать экспоненциал. разметку по оси (y)
set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 1 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 1
#set logscale y
set format y "%.0f"
set xlabel "Number of elements" font "Arial, 16"
set format x "%.0f"
set ylabel "collision" font "Arial, 16"
set xtics 5000 font "Arial, 8"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics
plot "exp6_XOR.dat" using 1:2 title "XOR" with linespoints ls 1,\
"exp6_KR.dat" using 1:2 title "KR" with linespoints ls 2
