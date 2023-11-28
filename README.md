The Guardians Battles
Descripción
Este proyecto implementa un juego llamado "The Guardians Battles" donde los guardianes son héroes con habilidades únicas que protegen las ciudades en la tierra. Los guardianes pueden mejorar sus habilidades a través de batallas y ascender en el ranking para convertirse en Guardianes del Reino.

Estructuras de Datos Utilizadas
Struct Guardian: Almacena información sobre un guardián, como su nombre, nivel de poder, maestro, ciudad y una lista de aprendices.

Struct Node: Define un nodo para un árbol binario de búsqueda (BST) que organiza a los guardianes por su nivel de poder.

Struct GuardianTreeNode: Define un nodo para un árbol de guardianes, donde cada nodo tiene un guardián y una lista de aprendices.

UndirectedGraph: Define un grafo no dirigido que representa las conexiones entre las ciudades y métodos para trabajar con él.

Funciones Principales
bstInsert: Inserta un guardián en un árbol binario de búsqueda basado en su nivel de poder.

printDescendingPower: Imprime los guardianes en orden descendente según su nivel de poder.

actualizarNivelDePoder: Actualiza el nivel de poder de un guardián después de una batalla.

main: Punto de entrada de la aplicación donde se manejan las interacciones con el usuario a través de un menú.

Flujo Principal del Programa
Carga de Datos: Lee dos archivos (Ciudades.txt y Guardianes.txt) que contienen información sobre las ciudades y los guardianes.

Interacción con el Usuario: Menú interactivo para:

Ver ranking de guardianes
Ver detalles de guardianes
Conocer información sobre conexiones entre ciudades
Presenciar batallas entre guardianes
Salir
Funcionalidades Destacadas:

Gestión de información de guardianes y sus relaciones
Simulación de batallas y actualización de niveles de poder
Mejoras Posibles
Interfaz gráfica de usuario
Validación más robusta de entradas de usuario
Puntos Importantes
Uso de estructuras de datos como BST, árboles y grafos para modelar la información
Interacción con el usuario a través de menús interactivos
Lectura de información inicial desde archivos de configuración