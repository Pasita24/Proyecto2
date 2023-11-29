# The Guardians Battles
## Descripción
Este proyecto implementa un juego llamado "The Guardians Battles" donde los guardianes son héroes con habilidades únicas que protegen las ciudades en la tierra. Los guardianes pueden mejorar sus habilidades a través de batallas y ascender en el ranking para convertirse en Guardianes del Reino.

## Estructuras de Datos Utilizadas
Struct Guardian: Almacena información sobre un guardián, como su nombre, nivel de poder, maestro, ciudad y una lista de aprendices.

- Struct Node: Define un nodo para un árbol binario de búsqueda (BST) que organiza a los guardianes por su nivel de poder.

- Struct GuardianTreeNode: Define un nodo para un árbol de guardianes, donde cada nodo tiene un guardián y una lista de aprendices.

- UndirectedGraph: Define un grafo no dirigido que representa las conexiones entre las ciudades y métodos para trabajar con él.

## Funciones Principales
- bstInsert: Inserta un guardián en un árbol binario de búsqueda basado en su nivel de poder.

- printDescendingPower: Imprime los guardianes en orden descendente según su nivel de poder.

- actualizarNivelDePoder: Actualiza el nivel de poder de un guardián después de una batalla.

- main: Punto de entrada de la aplicación donde se manejan las interacciones con el usuario a través de un menú.

### Flujo Principal del Programa
Carga de Datos: Lee dos archivos (Ciudades.txt y Guardianes.txt) que contienen información sobre las ciudades y los guardianes.

### Interacción con el Usuario: Menú interactivo para:

- Ver ranking de guardianes
- Ver detalles de guardianes
- Conocer información sobre conexiones entre ciudades
- Presenciar batallas entre guardianes
- Salir
### Funcionalidades Destacadas:
- Gestión de información de guardianes y sus relaciones
- Simulación de batallas y actualización de niveles de poder

## Puntos Importantes
- Uso de estructuras de datos como BST, árboles y grafos para modelar la información
- Interacción con el usuario a través de menús interactivos
- Lectura de información inicial desde archivos de configuración

## El sistema del juego


### Viajes entre Ciudades:
- Selección de Ciudad: Cuando un jugador decide viajar, se le muestra un menú con las ciudades disponibles desde su ubicación actual.
- Elegir Destino: El usuario elige una ciudad a la que quiere viajar y el código actualiza la ciudad del guardián seleccionado a la nueva ubicación. Utiliza la función getConnectedCities del grafo para mostrar las opciones disponibles y luego actualiza la información del guardián.

### Sistema de Batalla:
- Selección de Guardianes: El sistema muestra los guardianes disponibles para la batalla que no tienen un nivel de poder entre 90 y 99. Esto se realiza con un bucle que filtra los guardianes que cumplen esa condición.
- Elección del Contrincante: El jugador elige a quién desea desafiar. Puede ser el maestro o uno de los aprendices del árbol de guardianes de la ciudad.
- Batalla Simulada: Se simula la batalla utilizando un generador de números aleatorios para determinar si el jugador gana o pierde. Luego se actualiza el nivel de poder del guardián involucrado y se refleja en el árbol binario de búsqueda que organiza a los guardianes por su poder.

### Creación de Nuevos Caminos:
- Menú de Opciones: El jugador puede elegir agregar nuevas conexiones entre ciudades.
- Selección de Ciudades: Se muestra una lista de ciudades disponibles para elegir las que se conectarán.

### Consulta de Caminos del Reino:
- Opciones de Consulta: Permite conocer las conexiones entre ciudades de diferentes maneras:
1. Mostrar todas las ciudades y sus conexiones.
2. Conocer las conexiones de una ciudad específica.
3. Verificar si dos ciudades están directamente conectadas.
### Consulta de Ciudades:
- Menú de Opciones: Ofrece la posibilidad de listar todas las ciudades disponibles.
- Mostrar Conexiones de una Ciudad: Permite al usuario seleccionar una ciudad y ver sus conexiones con otras ciudades, utilizando la función printCityConnections del grafo.
### Mostrar Información de Guardianes en una Ciudad:
- Selección de Ciudad: El usuario elige la ciudad de interés.
- Impresión de Información: Se muestra información sobre los guardianes en esa ciudad, incluyendo el maestro y sus aprendices, si existen, utilizando la función printGuardiansInCity del grafo.

  # Enlace a video a YouTube
  - https://youtu.be/4ewCoQLqv1A
