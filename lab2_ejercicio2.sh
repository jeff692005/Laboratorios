#1.Argumento de ejucución
echo "Inserte el comando"
read argumento;

#2.Ejecución del comando 
if command -v "$argumento" &> /dev/null; then
    echo "Ejecutando el comando: $argumento"
    $argumento
else
    echo "Error:comando$argumento' invalido."
    exit 1
fi
#3.Lectura y registro de cpu y memoria
  archlog="consumo_log.txt"
    echo "Monitoreo del consumo de cpu y memoria en $archlog"

    while true; do
        uso_cpu=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
        uso_mem=$(free | grep Mem | awk '{print $3/$2 * 100.0}')

        echo "$(date +'%Y-%m-%d %H:%M:%S') $uso_cpu $uso_mem" >> $archlog
        if ! kill -0 $pid 2>/dev/null; then
            break
        fi
    done
#4.Graficación del tiempo
awk '{print $1, $2, $3}' $archlog > data_for_gnuplot.txt
gnuplot <<-EOF
set terminal png size 800,600 enhanced
set output 'grafico_consumo.png'
set title "Consumo de CPU y memoria"
set xlabel "Tiempo"
set ylabel "Uso"
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S"
set format x "%H:%M:%S"
set xtics rotate
set yrange [0:100]
set xrange ["2025-03-28 14:30:00":"2025-03-28 14:30:20"] 
plot 'data_for_gnuplot.txt' using 1:2 with lines title 'CPU', \
     'data_for_gnuplot.txt' using 1:3 with lines title 'memoria'
EOF
echo "Gráfico creado"
