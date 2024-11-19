# Graficación por Computadora Proyecto1

Repositorio: https://github.com/Santi24Yt/cpp-objrender/tree/main


## Especificaciones
- El programa leerá el modelo desde un archivo OBJ y se guardará en una
estructura de datos que utilicen en el programa.
- En la terminal, después de leer el OBJ, desplegar el número de vértices y
el número de caras del modelo.
- El modelo debe de visualizarse como una nube de puntos, solo se pintan
los vertices y también como el esqueleto (wireframe), uniendo los vértices
con líneas formando caras.
- El modelo debe de girar sobre el eje Y.
- Los modelos pueden variar de tamaño y de posición en el espacio del
mundo. Obtener un punto máximo y un punto mínimo donde puedan
encerrar para que automaticamente la cámara lo pueda visualizar correctamente.

### Extra
Para este proyecto habrá tres puntos extra
-  Solo mostrar las caras que ve a la cámara al pintar
el modelo.
- Implementar el algoritmo de Recorte (Clipping),
si el modelo se sale del marco de la cámara.
- Implementar entradas del usuario. Utilizando el
teclado o ratón para cambiar el ángulo de rotación, la posición de la
cámara, cambiar el modelo a otro que ya esté precargado, etc.

Para ejecución y compilación ver: `README`



https://github.com/user-attachments/assets/8b66c1cb-c2b4-4cdc-8032-8a71865b13b5



Se puede ver en el video como se leen y se muestran los modelos desde un archivo .obj,
que despliega su cantidad de vértices y caras, que se ve la nube de puntos y el wireframe,
que gira sobre el eje y y que la cámara automáticamente se ajusta al tamaño de modelo (en
caso de modelos muy pequeños o muy grandes no es 100% preciso pero si se intenta ajustar \[ver código\])

Adicionalmente se puede ver que solo se pintan las caras que ven hacia la cámara (los vértices si se pintan pero
las líneas no, se pudede cambiar el código para que no pinte vértices en ningun caso).
Se implemento una clase de Clipping (no es como tal el algoritmo que genera nuevos puntos) pero si permite
que lo que no esté en pantalla no se calcule y evita que haya casos en los que se vean líneas extrañas.
Finalmente se acepta la entrada del usuario para realizar distitntas funciones demostradas en el video.

También se añadió una opción de optimización la cuál hace que no se calculen todos los vértices y caras
del modelo ya que puede ser muy pesado para algunas computadoras, se va saltando vértices y caras de 2^n,
por ej. optimización 1 calcula uno si y una no, optimización 2 calcula 1 si 3 no, etc.
