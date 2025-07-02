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
- **🔊 Control de Volumen:** Se implementó la funcionalidad extra para manejar el volumen del video mediante controles deslizantes.

### ✅ Publicador y Suscriptor de GPS

- El publicador permite cargar un archivo `.txt` con posiciones GPS.
- Se interpola linealmente entre posiciones para generar movimiento continuo.
- Cada segundo se emite una nueva posición.
- El **suscriptor de GPS** muestra una ventana con la posición actual del móvil (círculo en movimiento), el tiempo y las coordenadas.

---

## 🛠️ Compilación y Ejecución

### Requisitos Previos

- **Qt Creator 6.x** o superior
- **Qt 6.9.1** o superior
- **MinGW 64-bit** (Windows) o **Clang** (macOS/Linux)
- **C++17** o superior

### Pasos de Compilación

**Se recomienda compilar desde Qt Creator para obtener los mejores resultados:**

1. **Abrir Qt Creator**
2. **Abrir el proyecto:**
   - Ve a `File > Open File or Project...`
   - Selecciona el archivo `simulador.pro` en la raíz del proyecto
3. **Configurar el kit de compilación:**
   - Asegúrate de que tienes configurado un kit compatible (Qt 6.9.1 + MinGW 64-bit)
4. **Compilar:**
   - Presiona `Ctrl+B` (Windows/Linux) o `Cmd+B` (macOS)
   - O utiliza el botón "Build" en la interfaz
5. **Ejecutar:**
   - Presiona `Ctrl+R` (Windows/Linux) o `Cmd+R` (macOS)
   - O utiliza el botón "Run" en la interfaz

### Compilación desde Terminal (Alternativa)

Si prefieres compilar desde la línea de comandos:

```bash
# Generar Makefile
qmake simulador.pro

# Compilar
make

# Ejecutar (el ejecutable se encuentra en build/)
./build/simulador  # Linux/macOS
# o
./build/simulador.exe  # Windows
```

---

## 📁 Estructura del Proyecto

```
├── simulador.pro          # Archivo de proyecto Qt
├── includes/             # Archivos de cabecera (.h)
│   ├── Broker.h
│   ├── Component.h
│   ├── Follower.h
│   ├── GPSCarFollower.h
│   ├── GPSCarPublisher.h
│   ├── GPSMovementView.h
│   ├── Publisher.h
│   ├── Recorder.h
│   ├── Subscriber.h
│   ├── VideoFollower.h
│   └── VideoPublisher.h
├── src/                  # Archivos de implementación (.cpp)
│   ├── Broker.cpp
│   ├── Component.cpp
│   ├── Follower.cpp
│   ├── GPSCarFollower.cpp
│   ├── GPSCarPublisher.cpp
│   ├── GPSMovementView.cpp
│   ├── Publisher.cpp
│   ├── Recorder.cpp
│   ├── VideoFollower.cpp
│   ├── VideoPublisher.cpp
│   └── simulador/        # Ventana principal
│       ├── main.cpp
│       ├── mainwindow.cpp
│       ├── mainwindow.h
│       └── mainwindow.ui
├── build/                # Archivos de compilación
├── datos_gps_prueba.txt  # Archivo de prueba con datos GPS
└── README.md            # Este archivo
```

---

## 🎮 Uso del Simulador

### Publicador de Video

1. En la interfaz principal, localiza la sección de **Video Publisher**
2. Ingresa una URL válida de video en el campo de texto
3. Presiona el botón para publicar la URL
4. Los suscriptores de video recibirán automáticamente la nueva URL

### Suscriptor de Video

1. El botón del suscriptor se actualiza con la última URL publicada
2. Haz clic en el botón para abrir el reproductor de video
3. Utiliza los controles de volumen para ajustar el audio

### Publicador GPS

1. Carga un archivo `.txt` con coordenadas GPS en el formato adecuado
2. El publicador interpolará linealmente entre las posiciones
3. Se emitirá una nueva posición cada segundo

### Suscriptor GPS

1. Observa la ventana de movimiento GPS
2. El círculo representa la posición actual del móvil
3. La información de tiempo y coordenadas se actualiza en tiempo real

---


## 🏗️ Patrón de Diseño

El proyecto implementa el **patrón Publicador-Suscriptor** mediante las siguientes clases:

- **Broker**: Mediador central que gestiona las suscripciones y publicaciones
- **Publisher**: Clase base para los publicadores
- **Subscriber**: Clase base para los suscriptores
- **Component**: Clase base que puede actuar como publicador y/o suscriptor

### Jerarquía de Clases

```
Component
├── Publisher
│   ├── VideoPublisher
│   └── GPSCarPublisher
└── Subscriber (via Follower)
    ├── VideoFollower
    └── GPSCarFollower
```

---

## 🚀 Características Adicionales

- **Interpolación lineal** para movimiento suave del GPS
- **Control de volumen** para reproducción de video
- **Interfaz gráfica intuitiva** desarrollada con Qt Designer

---

## 🐛 Solución de Problemas

### Errores Comunes

1. **Error de compilación con Qt:**
   - Verifica que tienes Qt 6.9.1 o superior instalado
   - Asegúrate de que el kit de compilación esté correctamente configurado

2. **No se reproduce el video:**
   - Verifica que la URL sea válida y accesible
   - Comprueba tu conexión a internet

3. **Problemas con archivos GPS:**
   - Verifica el formato del archivo de coordenadas
   - Asegúrate de que el archivo esté en la ubicación correcta

---

