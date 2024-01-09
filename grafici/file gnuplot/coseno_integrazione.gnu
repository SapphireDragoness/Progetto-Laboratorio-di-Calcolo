set terminal pngcairo size 600,400 enhanced font 'Verdana,10'
set output 'coseno_integrazione.png'

set border linewidth 1.5
set key fixed left top vertical

set xlabel 'x'
set ylabel 'y'

set xrange[0:0.5]
set yrange[-2.05:-1.85]

plot 'dati/coseno_puntomedio.dat' title 'punto medio' with lines linestyle 1, \
     'dati/coseno_CS.dat' title 'Cavalieri-Simpson' with lines linestyle 2