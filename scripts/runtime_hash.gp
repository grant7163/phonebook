reset
set ylabel 'time(sec)'
set style fill solid
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.15]'output_hash.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'optimized'  , \
'' using 4:xtic(1) with histogram title 'ELFHash'  , \
'' using ($0-0.017):($2+0.004):2 with labels title ' ' textcolor lt 1, \
'' using ($0+0.22):($3+0.003):3 with labels title ' ' textcolor lt 2, \
'' using ($0+0.4):($4+0.013):4 with labels title ' ' textcolor lt 3, \

