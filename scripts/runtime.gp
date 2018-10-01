reset
set ylabel 'time(sec)'
set style fill solid
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.150]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'optimized'  , \
'' using 4:xtic(1) with histogram title 'BKDRHash + mPool'  , \
'' using 5:xtic(1) with histogram title 'BSTTree'  , \
'' using ($0-0.0008):($2+0.004):2 with labels title ' ' textcolor lt 1, \
'' using ($0+0.13):($3+0.003):3 with labels title ' ' textcolor lt 2, \
'' using ($0+0.28):($4+0.01):4 with labels title ' ' textcolor lt 3, \
'' using ($0+0.45):($5+0.0038):5 with labels title ' ' textcolor lt 4
