set title "Solución de la Ecuación de Laplace 2D"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "Potencial φ(x,y) (V)"

set terminal png enhanced size 800,600
set output "results/graficas/laplace_3d.png"

set style data lines
splot "solucion_laplace.txt" using 1:2:3 with lines title "φ(x,y)"

set terminal png enhanced size 800,600
set output "results/graficas/laplace_contour.png"

set view 0,0
set contour base
set cntrparam levels 20
splot "solucion_laplace.txt" using 1:2:3 with lines notitle
