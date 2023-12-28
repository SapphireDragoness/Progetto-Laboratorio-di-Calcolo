set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
set output 'sin(x).png'

f(x) = sin(x)

set xrange[0:pi]
set yrange[0:1.5]

set xtics (0, "π/2" pi/2, "π" pi)
set ytics 1
set tics scale 0.75

plot 'sin(x)_tr.dat' with linespoints linestyle 1 title "trapezio, acc: 0.5", \
     f(x) title "sin(x)"

