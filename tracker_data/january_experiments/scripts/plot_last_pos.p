set title "Last positions"
set xrange [0:50]
set yrange [70:120]
set zrange [20:70]

splot 'last_pos_0.txt' u 1:2:3 with points, 'last_pos_1.txt' u 1:2:3 with points, 'last_pos_2.txt' u 1:2:3 with points, 'last_pos_3.txt' u 1:2:3 with points, 'last_pos_4.txt' u 1:2:3 with points, 'last_pos_5.txt' u 1:2:3 with points, 'last_pos_6.txt' u 1:2:3 with points, 'last_pos_7.txt' u 1:2:3 with points, 'last_pos_8.txt' u 1:2:3 with points, 'bowl.txt' u 1:2:3 with lines
pause 5

# Hungarian rhapsody number 2
