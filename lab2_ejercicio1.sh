#1.Verificacion de root del usuario
ls -al
if uid=root; then
	echo "Error. El usuario no es root"
fi

#2.Parametros recibidos
echo "Ingrese el nombre de usuario:"
	read N_user;
	echo "Ingrese el nombre del grupo"
		read N_group;
		echo "Ingrese la ruta del archivo en el sistema"
			read ruta;
			echo "$N_user"
			echo "$N_group"
			echo "$ruta"
#3.Verificación de la ruta
if [ ! -d "$ruta" ]; then
    echo "Error: el directorio '$ruta' no existe."
    exit 1
fi

echo "El directorio '$ruta' existe"

#4.Creación del grupo
grep -q "$N_group" /etc/group
if [ $? -ne 0 ]; then
    echo "El grupo '$N_group' no existe, creando grupo"
    sudo groupadd "$N_group"
    echo "Grupo '$N_group' creado."
else
    echo "El grupo '$N_group' ya existe."
fi

#5.Creacion del usuario
id "$N_user" &>/dev/null
if [ $? -ne 0 ]; then
    echo "El usuario '$N_user' no existe, creando usuario"
    sudo useradd -m "$N_user"
    echo "Usuario '$N_user' creado."
else
    echo "El usuario '$N_user' ya existe, agregando al grupo '$N_group'..."
    sudo usermod -a -G "$N_group" "$N_user"
    echo "Usuario '$N_user' agregado al grupo '$N_group'."
fi

#6.Modificacion de pertenecia del archivo
echo "Ingrese el nombre del archivo a modificar:"
read N_arch
archivo="$ruta/$N_arch"
if [ ! -f "$archivo" ]; then
    echo "Error: El archivo '$archivo' no existe."
    exit 1
else
    echo "Cambiando la propiedad del archivo '$archivo' al usuario '$N_user' y grupo '$N_group'..."
    chown "$N_user":"$N_group" "$archivo"
    echo "Propiedad del archivo '$archivo' modificada correctamente."
fi

#7.Cambiar permisos
chmod 740 "$archivo"
    echo "Permisos del archivo '$archivo' modificados"

