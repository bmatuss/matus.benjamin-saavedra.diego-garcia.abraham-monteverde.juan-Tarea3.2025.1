# Makefile para un proyecto C++/Qt basado en CMake

# Define el directorio de construcción. Esto debe coincidir con lo que tienes en tu .gitignore.
BUILD_DIR = build

# Define el tipo de construcción (ej. Debug, Release).
# Puedes sobrescribirlo desde la línea de comandos: make BUILD_TYPE=Release
BUILD_TYPE ?= Debug

# Los objetivos "phony" no son archivos reales.
.PHONY: all configure build run test clean help create_build_dir

# Objetivo por defecto: configurar y luego construir
all: build

# Configura el proyecto CMake
configure: create_build_dir
	@echo "--- Configurando el proyecto CMake en $(BUILD_DIR) (Tipo de Construcción: $(BUILD_TYPE)) ---"
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_PREFIX_PATH="/Users/bmatus/Qt/6.9.1/macos"

# Crea el directorio de construcción si no existe
create_build_dir:
	mkdir -p $(BUILD_DIR)

# Construye el proyecto
build: configure
	@echo "--- Construyendo el proyecto en $(BUILD_DIR) ---"
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)

# Ejecuta la aplicación
run: build
	@echo "--- Ejecutando la aplicación ---"
	open $(BUILD_DIR)/simulador.app

# Ejecuta las pruebas (requiere que las pruebas estén definidas en CMakeLists.txt usando add_test)
test: build
	@echo "--- Ejecutando pruebas ---"
	# CTest es el ejecutor de pruebas para CMake.
	# La bandera --output-on-failure muestra la salida de las pruebas que fallan.
	# El || true asegura que el Makefile no se detenga si las pruebas fallan, permitiendo un informe completo.
	cd $(BUILD_DIR) && ctest --output-on-failure || true

# Limpia el directorio de construcción
clean:
	@echo "--- Limpiando el directorio de construcción $(BUILD_DIR) ---"
	rm -rf $(BUILD_DIR)

# Objetivo de ayuda para mostrar los comandos disponibles
help:
	@echo "Uso:"
	@echo "  make all        - Configura y construye el proyecto (por defecto: Debug)"
	@echo "  make configure  - Solo configura el proyecto CMake"
	@echo "  make build      - Solo construye el proyecto (después de configurar)"
	@echo "  make run        - Construye y ejecuta la aplicación"
	@echo "  make test       - Construye y ejecuta las pruebas"
	@echo "  make clean      - Elimina el directorio de construcción"
	@echo ""
	@echo "Para especificar el tipo de construcción (ej. Release):"
	@echo "  make all BUILD_TYPE=Release"
	@echo "  make test BUILD_TYPE=Release"