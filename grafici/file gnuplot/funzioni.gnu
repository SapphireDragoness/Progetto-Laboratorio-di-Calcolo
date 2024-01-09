set terminal pngcairo size 600,400 enhanced font 'Verdana,10'
set output 'funzioni.png'

set border linewidth 1.5
set key fixed left top vertical

set xlabel 'x'
set ylabel 'y'

set xrange[-5:5]
set yrange[-1.5:4]

plot sin(x) title 'sin(x)' with lines linestyle 1, \
     cos(x) title 'cos(x)' with lines linestyle 2, \
     sqrt(x) title 'sqrt(x)' with lines linestyle 3, \
     log(x) title 'log(x)' with lines linestyle 4, \
     exp(x) title 'exp(x)' with lines linestyle 5
