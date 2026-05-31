CXX = g++
CXXFLAGS = -Wall -O2 -I./include

TARGET = laplace.exe
SOURCES = src/main.cpp src/laplace.cpp
OBJECTS = $(SOURCES:.cpp=.o)

VERDE = \033[32m
AZUL = \033[34m
AMARILLO = \033[33m
ROJO = \033[31m
RESET = \033[0m

.PHONY: all clean run graficar help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo -e "$(AZUL)► Enlazando...$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo -e "$(VERDE)✔ Compilación completada: $(TARGET)$(RESET)\n"

src/%.o: src/%.cpp
	@echo -e "$(AZUL)► Compilando $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@echo -e "\n$(AZUL)► Ejecutando simulación...$(RESET)\n"
	@./$(TARGET)
	@echo ""
	@$(MAKE) menu_grafica

menu_grafica:
	@echo -e "$(AZUL)=== OPCIONES DE GRAFICACIÓN ===$(RESET)"
	@echo " 1) Gnuplot"
	@echo " 2) Python"
	@echo " 3) Ambos"
	@echo " 4) Salir"
	@echo "-------------------------------"

graficar_gnuplot:
	@mkdir -p results/graficas/gnuplot
	@echo -e "\n$(AZUL)► Generando gráficas con Gnuplot...$(RESET)"
	@if command -v gnuplot >/dev/null 2>&1; then \
		echo 'set title "Solución de la Ecuación de Laplace 2D"' > /tmp/laplace.gp; \
		echo 'set xlabel "x (m)"' >> /tmp/laplace.gp; \
		echo 'set ylabel "y (m)"' >> /tmp/laplace.gp; \
		echo 'set zlabel "Potencial φ(x,y) (V)"' >> /tmp/laplace.gp; \
		echo 'set terminal png enhanced size 900,700' >> /tmp/laplace.gp; \
		echo 'set output "results/graficas/gnuplot/laplace_3d.png"' >> /tmp/laplace.gp; \
		echo 'splot "results/solucion_laplace.dat" using 1:2:3 with lines title "φ(x,y)"' >> /tmp/laplace.gp; \
		echo 'set view 0,0' >> /tmp/laplace.gp; \
		echo 'set contour base' >> /tmp/laplace.gp; \
		echo 'set cntrparam levels 20' >> /tmp/laplace.gp; \
		echo 'set output "results/graficas/gnuplot/laplace_contour.png"' >> /tmp/laplace.gp; \
		echo 'splot "results/solucion_laplace.dat" using 1:2:3 with lines notitle' >> /tmp/laplace.gp; \
		gnuplot /tmp/laplace.gp; \
		echo -e "$(VERDE)✓ Gráficas guardadas en results/graficas/gnuplot/$(RESET)"; \
	else \
		echo -e "$(ROJO)✗ Gnuplot no instalado$(RESET)"; \
	fi

graficar_python:
	@mkdir -p results/graficas/python
	@echo -e "\n$(AZUL)► Generando gráficas con Python...$(RESET)"
	@if command -v python3 >/dev/null 2>&1; then \
		python3 scripts/graficar_laplace.py; \
	else \
		echo -e "$(ROJO)✗ Python3 no instalado$(RESET)"; \
	fi

clean:
	@echo -e "$(AMARILLO)Limpiando archivos...$(RESET)"
	@rm -f $(OBJECTS) $(TARGET) results/solucion_laplace.dat
	@rm -rf results/graficas/gnuplot/*.png results/graficas/python/*.png
	@echo -e "$(VERDE)Limpieza completada.$(RESET)"

help:
	@echo "Targets disponibles:"
	@echo "  all                - Compila el programa"
	@echo "  run                - Compila y ejecuta la simulación"
	@echo "  graficar_gnuplot   - Genera gráficas con Gnuplot"
	@echo "  graficar_python    - Genera gráficas con Python"
	@echo "  clean              - Elimina archivos compilados y resultados"
	@echo "  help               - Muestra esta ayuda"

