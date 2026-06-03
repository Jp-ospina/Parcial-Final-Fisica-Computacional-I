CXX = g++
CXXFLAGS = -Wall -O2

VERDE = \033[32m
AZUL = \033[34m
AMARILLO = \033[33m
ROJO = \033[31m
RESET = \033[0m

.PHONY: all clean help menu

all: menu

menu:
	@clear
	@echo -e "$(AZUL)════════════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo -e "$(AZUL)║          EXAMEN FINAL - FÍSICA COMPUTACIONAL 1 - GRUPO 3                 ║$(RESET)"
	@echo -e "$(AZUL)╚════════════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo -e "$(VERDE)Seleccione qué ejercicio desea ejecutar:$(RESET)"
	@echo ""
	@echo "  1) Punto 1 - Sistemas Acoplados de Lotka-Volterra"
	@echo "  2) Punto 2 - Ecuación de Laplace 2D"
	@echo "  3) Salir"
	@echo ""
	@echo "------------------------------------"
	@echo -ne "$(AMARILLO)Opción [1-3]: $(RESET)"; \
	read opcion; \
	if [ "$$opcion" = "1" ]; then \
		$(MAKE) punto1; \
	elif [ "$$opcion" = "2" ]; then \
		$(MAKE) punto2; \
	elif [ "$$opcion" = "3" ]; then \
		echo -e "\n$(VERDE)¡Hasta luego!$(RESET)\n"; \
	else \
		echo -e "\n$(ROJO)Opción inválida.$(RESET)"; \
		sleep 1; $(MAKE) menu; \
	fi

punto1:
	@echo -e "\n$(AZUL)► Compilando Punto 1 (Sistemas Acoplados)...$(RESET)"
	@mkdir -p punto1_sistema_acoplado/results/graficas/{gnuplot,python}
	@$(CXX) $(CXXFLAGS) -I./punto1_sistema_acoplado/include -o punto1_sistema_acoplado/sistema_acoplado.exe \
		punto1_sistema_acoplado/src/main.cpp \
		punto1_sistema_acoplado/src/sistema_acoplado.cpp
	@echo -e "$(AZUL)► Ejecutando simulación...$(RESET)\n"
	@cd punto1_sistema_acoplado && ./sistema_acoplado.exe
	@$(MAKE) menu_grafica_punto1

punto2:
	@echo -e "\n$(AZUL)► Compilando Punto 2 (Ecuación de Laplace)...$(RESET)"
	@mkdir -p punto2_edp/results/graficas/{gnuplot,python}
	@$(CXX) $(CXXFLAGS) -I./punto2_edp/include -o punto2_edp/laplace.exe \
		punto2_edp/src/main.cpp \
		punto2_edp/src/laplace.cpp
	@echo -e "$(AZUL)► Ejecutando simulación...$(RESET)\n"
	@cd punto2_edp && ./laplace.exe
	@$(MAKE) menu_grafica_punto2

menu_grafica_punto1:
	@echo -e "\n$(AZUL)=== OPCIONES DE GRAFICACIÓN (Punto 1) ===$(RESET)"
	@echo "  1) Gnuplot"
	@echo "  2) Python"
	@echo "  3) Ambos"
	@echo "  4) Menú Principal"
	@echo "-------------------------------"
	@echo -ne "$(AMARILLO)Seleccione [1-4]: $(RESET)"; \
	read grafica; \
	if [ "$$grafica" = "1" ]; then \
		$(MAKE) graficar_gnuplot_punto1; \
	elif [ "$$grafica" = "2" ]; then \
		$(MAKE) graficar_python_punto1; \
	elif [ "$$grafica" = "3" ]; then \
		$(MAKE) graficar_gnuplot_punto1; \
		$(MAKE) graficar_python_punto1; \
	elif [ "$$grafica" = "4" ]; then \
		$(MAKE) menu; \
	else \
		echo -e "$(ROJO)Opción inválida.$(RESET)\n"; \
		$(MAKE) menu_grafica_punto1; \
	fi

menu_grafica_punto2:
	@echo -e "\n$(AZUL)=== OPCIONES DE GRAFICACIÓN (Punto 2) ===$(RESET)"
	@echo "  1) Gnuplot"
	@echo "  2) Python"
	@echo "  3) Ambos"
	@echo "  4) Menú Principal"
	@echo "-------------------------------"
	@echo -ne "$(AMARILLO)Seleccione [1-4]: $(RESET)"; \
	read grafica; \
	if [ "$$grafica" = "1" ]; then \
		$(MAKE) graficar_gnuplot_punto2; \
	elif [ "$$grafica" = "2" ]; then \
		$(MAKE) graficar_python_punto2; \
	elif [ "$$grafica" = "3" ]; then \
		$(MAKE) graficar_gnuplot_punto2; \
		$(MAKE) graficar_python_punto2; \
	elif [ "$$grafica" = "4" ]; then \
		$(MAKE) menu; \
	else \
		echo -e "$(ROJO)Opción inválida.$(RESET)\n"; \
		$(MAKE) menu_grafica_punto2; \
	fi

graficar_gnuplot_punto1:
	@mkdir -p punto1_sistema_acoplado/results/graficas/gnuplot
	@echo -e "\n$(AZUL)► Generando gráficas Gnuplot (Punto 1)...$(RESET)"
	@if command -v gnuplot >/dev/null 2>&1; then \
		echo 'set title "Sistema Acoplado de Lotka-Volterra"' > /tmp/sistema.gp; \
		echo 'set xlabel "Presas"' >> /tmp/sistema.gp; \
		echo 'set ylabel "Depredadores"' >> /tmp/sistema.gp; \
		echo 'set terminal png enhanced size 900,700' >> /tmp/sistema.gp; \
		echo 'set output "punto1_sistema_acoplado/results/graficas/gnuplot/plano_fase.png"' >> /tmp/sistema.gp; \
		echo 'plot "punto1_sistema_acoplado/results/datos_sistema_acoplado.dat" using 2:3 title "Sistema 1" with lines, "" using 4:5 title "Sistema 2" with lines' >> /tmp/sistema.gp; \
		gnuplot /tmp/sistema.gp; \
		echo -e "$(VERDE)✓ Gráficas guardadas en punto1_sistema_acoplado/results/graficas/gnuplot/$(RESET)"; \
	else \
		echo -e "$(ROJO)✗ Gnuplot no instalado$(RESET)"; \
	fi

graficar_python_punto1:
	@mkdir -p punto1_sistema_acoplado/results/graficas/python
	@echo -e "\n$(AZUL)► Generando gráficas Python (Punto 1)...$(RESET)"
	@if command -v python3 >/dev/null 2>&1; then \
		cd punto1_sistema_acoplado && python3 ../scripts/graficar_sistema_acoplado.py; \
	else \
		echo -e "$(ROJO)✗ Python3 no instalado$(RESET)"; \
	fi

graficar_gnuplot_punto2:
	@mkdir -p punto2_edp/results/graficas/gnuplot
	@echo -e "\n$(AZUL)► Generando gráficas Gnuplot (Punto 2)...$(RESET)"
	@if command -v gnuplot >/dev/null 2>&1; then \
		echo 'set title "Solución de la Ecuación de Laplace 2D"' > /tmp/laplace.gp; \
		echo 'set xlabel "x (m)"' >> /tmp/laplace.gp; \
		echo 'set ylabel "y (m)"' >> /tmp/laplace.gp; \
		echo 'set zlabel "Potencial φ(x,y) (V)"' >> /tmp/laplace.gp; \
		echo 'set terminal png enhanced size 900,700' >> /tmp/laplace.gp; \
		echo 'set output "punto2_edp/results/graficas/gnuplot/laplace_3d.png"' >> /tmp/laplace.gp; \
		echo 'splot "punto2_edp/results/solucion_laplace.dat" using 1:2:3 with lines title "φ(x,y)"' >> /tmp/laplace.gp; \
		gnuplot /tmp/laplace.gp; \
		echo -e "$(VERDE)✓ Gráficas guardadas en punto2_edp/results/graficas/gnuplot/$(RESET)"; \
	else \
		echo -e "$(ROJO)✗ Gnuplot no instalado$(RESET)"; \
	fi

graficar_python_punto2:
	@mkdir -p punto2_edp/results/graficas/python
	@echo -e "\n$(AZUL)► Generando gráficas Python (Punto 2)...$(RESET)"
	@if command -v python3 >/dev/null 2>&1; then \
		cd punto2_edp && python3 ../scripts/graficar_laplace.py; \
	else \
		echo -e "$(ROJO)✗ Python3 no instalado$(RESET)"; \
	fi

clean:
	@echo -e "$(AMARILLO)Limpiando archivos...$(RESET)"
	@rm -f punto1_sistema_acoplado/*.o punto1_sistema_acoplado/*.exe punto1_sistema_acoplado/results/*.dat
	@rm -f punto2_edp/src/*.o punto2_edp/*.exe punto2_edp/results/*.dat
	@rm -rf punto1_sistema_acoplado/results/graficas/gnuplot/*.png punto1_sistema_acoplado/results/graficas/python/*.png
	@rm -rf punto2_edp/results/graficas/gnuplot/*.png punto2_edp/results/graficas/python/*.png
	@echo -e "$(VERDE)Limpieza completada.$(RESET)"

help:
	@echo "Targets disponibles:"
	@echo "  make           - Muestra el menú principal"
	@echo "  make punto1    - Compila y ejecuta Punto 1"
	@echo "  make punto2    - Compila y ejecuta Punto 2"
	@echo "  make clean     - Elimina archivos compilados y resultados"
	@echo "  make help      - Muestra esta ayuda"
