#1.Directorio a monitorear
directorio="/home/ubuntu/Music"

#2.Monitoreo
if [ ! -d "$directorio" ]; then
    echo "Error: El directorio '$directorio' no existe."
    exit 1
fi

archlog="monitoreo_eventos.log"

echo "Monitoreo de eventos en: $directorio" > "$archlog"
echo "Fecha y hora, evento, archivo" >> "$archlog"

get_file_state() {
    find "$directorio" -type f -exec stat --format="%Y %n" {} \; | sort
}

estado_pre=$(get_file_state)

#3.Monitoreo continuo
echo "Monitoreando el directorio '$directorio'..."
while true; do
    estado_act=$(get_file_state)
    added=$(comm -13 <(echo "$estado_pre") <(echo "$estado_act"))
    removed=$(comm -23 <(echo "$estado_pre") <(echo "$estado_act"))
    modified=$(comm -12 <(echo "$estado_pre") <(echo "$estado_act"))

    if [ -n "$added" ]; then
        tiempo=$(date "+%Y-%m-%d %H:%M:%S")
        for file in $added; do
            Narch=$(echo $file | cut -d' ' -f2-)
            if ! grep -q "$Narch" "$arclog"; then
                echo "$tiempo, Creado, $Narch" >> "$archlog"
                echo "Creado: $Narch"
            fi
        done
    fi

    if [ -n "$removed" ]; then
        tiempo=$(date "+%Y-%m-%d %H:%M:%S")
        for file in $removed; do
            Narch=$(echo $file | cut -d' ' -f2-)
            if ! grep -q "$Narch" "$archlog"; then
                echo "$tiempo, Eliminado, $Narch" >> "$archlog"
                echo "Eliminado: $Narch"
            fi
        done
    fi

    if [ -n "$modified" ]; then
        tiempo=$(date "+%Y-%m-%d %H:%M:%S")
        for file in $modified; do
            Narch=$(echo $file | cut -d' ' -f2-)
            if ! grep -q "$Narch" "$archlog"; then
                echo "$tiempo, Modificado, $Narch" >> "$archlog"
                echo "Modificado: $Narch"
            fi
        done
    fi

    estado_pre="$estado_act"

    sleep 1
done

