# Tarea 3 - Simulador Gráfico con Patrón Publicador-Suscriptor

**Curso:** ELO329 - Diseño y Programación Orientada a Objetos  
**Autores:**  
- Benjamín Matus  
- Diego Saavedra  
- Abraham García  
- Juan Monteverde

## 🔍 Descripción General

Este proyecto consiste en un **simulador gráfico** desarrollado en **C++ con Qt**, que implementa el **patrón de diseño Publicador-Suscriptor**. El simulador permite crear publicadores de:

- **Videos (URLs)**
- **Posiciones GPS de un móvil**

Y sus respectivos suscriptores, los cuales reaccionan a las publicaciones con elementos gráficos en la interfaz.

---

## 🎯 Objetivos de la Tarea

- Modelar objetos reales como clases de software.
- Implementar el patrón Publicador-Suscriptor en C++ y Qt.
- Desarrollar una aplicación gráfica funcional desde Qt Creator.
- Aplicar desarrollo incremental en etapas.
- Usar Git para el manejo de versiones y colaboración.
- Documentar y entregar el proyecto profesionalmente.

---

## 🧩 Funcionalidades Implementadas

### ✅ Publicador y Suscriptor de Video

- El **publicador de video** permite ingresar URLs mediante un campo de texto.
- El **suscriptor de video** muestra un botón que se actualiza con la última URL publicada.
- Al presionar el botón, el video se reproduce en una nueva ventana.

### ✅ Publicador y Suscriptor de GPS

- El publicador permite cargar un archivo `.txt` con posiciones GPS.
- Se interpola linealmente entre posiciones para generar movimiento continuo.
- Cada segundo se emite una nueva posición.
- El **suscriptor de GPS** muestra una ventana con la posición actual del móvil (círculo en movimiento), el tiempo y las coordenadas.
