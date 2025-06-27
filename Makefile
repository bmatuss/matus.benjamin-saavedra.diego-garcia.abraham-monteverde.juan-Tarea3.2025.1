# Makefile multiplataforma para un proyecto C++/Qt basado en CMake

# Detección automática del sistema operativo
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXECUTABLE_EXT := .exe
    PATH_SEP := \\
    # Comando para abrir/ejecutar aplicación en Windows (se ejecuta desde BUILD_DIR)
    RUN_CMD = start "" "$(APP_NAME)$(EXECUTABLE_EXT)"
    # Rutas típicas de Qt en Windows (ajustar según instalación)
    QT_PATHS := "C:\\Qt\\6.9.1\\msvc2022_64" "C:\\Qt\\6.8.0\\msvc2022_64" "C:\\Qt\\6.7.0\\msvc2022_64"
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        DETECTED_OS := Linux
        EXECUTABLE_EXT :=
        PATH_SEP := /
        RUN_CMD = ./$(APP_NAME)$(EXECUTABLE_EXT)
        # Rutas típicas de Qt en Linux
        QT_PATHS := "/opt/Qt/6.9.1/gcc_64" "/usr/lib/x86_64-linux-gnu/qt6" "/usr/local/Qt-6.9.1"
    endif
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS := macOS
        EXECUTABLE_EXT := .app
        PATH_SEP := /
        RUN_CMD = open $(BUILD_DIR)/$(APP_NAME)$(EXECUTABLE_EXT)
        # Rutas típicas de Qt en macOS
        QT_PATHS := "$(HOME)/Qt/6.9.1/macos" "/usr/local/Qt-6.9.1" "/opt/homebrew/opt/qt@6"
    endif
endif

# Configuración del proyecto
BUILD_DIR = build
BUILD_TYPE ?= Debug
APP_NAME = simulador

# Función para encontrar Qt automáticamente
define find_qt_path
$(foreach path,$(QT_PATHS),$(if $(wildcard $(path)),$(path),))
endef

# Detectar ruta de Qt automáticamente
QT_PATH := $(word 1,$(call find_qt_path))

# Si no se encuentra Qt automáticamente, usar variable de entorno o valor por defecto
ifndef QT_PATH
    ifdef QT_DIR
        QT_PATH := $(QT_DIR)
    else
        ifeq ($(DETECTED_OS),Windows)
            QT_PATH := C:\Qt\6.9.1\msvc2022_64
        else ifeq ($(DETECTED_OS),Linux)
            QT_PATH := /usr/lib/x86_64-linux-gnu/qt6
        else ifeq ($(DETECTED_OS),macOS)
            QT_PATH := $(HOME)/Qt/6.9.1/macos
        endif
    endif
endif

# Configuración específica de CMake según el SO
ifeq ($(DETECTED_OS),Windows)
    CMAKE_GENERATOR ?= Visual Studio 17 2022
    CMAKE_EXTRA_FLAGS = -G "$(CMAKE_GENERATOR)" -A x64
else
    CMAKE_GENERATOR ?= Unix Makefiles
    CMAKE_EXTRA_FLAGS = -G "$(CMAKE_GENERATOR)"
endif

# Los objetivos "phony" no son archivos reales
.PHONY: all configure build run test clean help create_build_dir info install-deps

# Objetivo por defecto: configurar y luego construir
all: build

# Muestra información del sistema detectado
info:
	@echo "=== Información del Sistema ==="
	@echo "Sistema Operativo Detectado: $(DETECTED_OS)"
	@echo "Directorio de Construcción: $(BUILD_DIR)"
	@echo "Tipo de Construcción: $(BUILD_TYPE)"
	@echo "Nombre de la Aplicación: $(APP_NAME)"
	@echo "Ruta de Qt: $(QT_PATH)"
	@echo "Generador de CMake: $(CMAKE_GENERATOR)"
	@echo "==============================="

# Crea el directorio de construcción si no existe
create_build_dir:
	@echo "--- Creando directorio de construcción ---"
ifeq ($(DETECTED_OS),Windows)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
else
	@mkdir -p $(BUILD_DIR)
endif

# Configura el proyecto CMake
configure: create_build_dir info
	@echo "--- Configurando el proyecto CMake en $(BUILD_DIR) (Tipo: $(BUILD_TYPE)) ---"
	@echo "Usando Qt desde: $(QT_PATH)"
	cmake -S . -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_PREFIX_PATH="$(QT_PATH)" \
		$(CMAKE_EXTRA_FLAGS)

# Construye el proyecto
build: configure
	@echo "--- Construyendo el proyecto en $(BUILD_DIR) ---"
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --parallel

# Ejecuta la aplicación
run: build
	@echo "--- Ejecutando la aplicación ---"
ifeq ($(DETECTED_OS),Windows)
	@cd $(BUILD_DIR) && $(RUN_CMD)
else ifeq ($(DETECTED_OS),macOS)
	@$(RUN_CMD)
else
	@cd $(BUILD_DIR) && $(RUN_CMD)
endif

# Ejecuta las pruebas
test: build
	@echo "--- Ejecutando pruebas ---"
	@cd $(BUILD_DIR) && ctest --output-on-failure --parallel || true

# Instala dependencias (comando informativo)
install-deps:
	@echo "=== Instrucciones para instalar dependencias ==="
ifeq ($(DETECTED_OS),Windows)
	@echo "Windows:"
	@echo "1. Descargar Qt desde: https://www.qt.io/download"
	@echo "2. Instalar Visual Studio con herramientas de C++"
	@echo "3. Instalar CMake desde: https://cmake.org/download/"
endif
ifeq ($(DETECTED_OS),Linux)
	@echo "Linux (Ubuntu/Debian):"
	@echo "  sudo apt update"
	@echo "  sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential"
	@echo ""
	@echo "Linux (Fedora/CentOS):"
	@echo "  sudo dnf install qt6-qtbase-devel qt6-qttools-devel cmake gcc-c++"
	@echo ""
	@echo "Linux (Arch):"
	@echo "  sudo pacman -S qt6-base qt6-tools cmake gcc"
endif
ifeq ($(DETECTED_OS),macOS)
	@echo "macOS:"
	@echo "  brew install qt6 cmake"
	@echo "  # O descargar Qt desde: https://www.qt.io/download"
endif
	@echo "=================================================="

# Limpia el directorio de construcción
clean:
	@echo "--- Limpiando el directorio de construcción $(BUILD_DIR) ---"
ifeq ($(DETECTED_OS),Windows)
	@rmdir /s /q "$(BUILD_DIR)" 2>nul || exit 0
else
	@rm -rf $(BUILD_DIR)
endif

# Instala la aplicación (solo en Linux/macOS)
install: build
ifeq ($(DETECTED_OS),Windows)
	@echo "Instalación no implementada para Windows. Use 'make run' para ejecutar."
else
	@echo "--- Instalando la aplicación ---"
	@cd $(BUILD_DIR) && cmake --install . --config $(BUILD_TYPE)
endif

# Objetivo de ayuda para mostrar los comandos disponibles
help:
	@echo "=== Makefile Multiplataforma para C++/Qt ==="
	@echo "Sistema detectado: $(DETECTED_OS)"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make all          - Configura y construye el proyecto (por defecto)"
	@echo "  make info         - Muestra información del sistema"
	@echo "  make configure    - Solo configura el proyecto CMake"
	@echo "  make build        - Solo construye el proyecto"
	@echo "  make run          - Construye y ejecuta la aplicación"
	@echo "  make test         - Construye y ejecuta las pruebas"
	@echo "  make clean        - Elimina el directorio de construcción"
	@echo "  make install-deps - Muestra cómo instalar dependencias"
	@echo "  make install      - Instala la aplicación (Linux/macOS)"
	@echo "  make help         - Muestra esta ayuda"
	@echo ""
	@echo "Variables personalizables:"
	@echo "  BUILD_TYPE        - Tipo de construcción (Debug, Release, RelWithDebInfo)"
	@echo "  QT_DIR           - Ruta personalizada de Qt"
	@echo "  APP_NAME         - Nombre de la aplicación (default: simulador)"
	@echo ""
	@echo "Ejemplos:"
	@echo "  make all BUILD_TYPE=Release"
	@echo "  make run QT_DIR=/path/to/qt"
	@echo "  make test BUILD_TYPE=Debug"
	@echo "=============================================="