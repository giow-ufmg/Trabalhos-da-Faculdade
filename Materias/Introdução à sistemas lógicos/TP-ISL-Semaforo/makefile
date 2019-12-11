#USO: 'make FILE=[nome sem .v]' para compilar, rodar e visualizar
#um testbench
#		'make clean' para remover os logs e o arquivo de objeto

modulos = semaforo.v

#warnings sao importantes para pegar erros
#de implementacao
flags = -Wall

#abrindo o visualizador de waveforms. Expanda os itens no buscador
#a esquerda e arraste as variaves desejadas para o espaco preto.
#areas vermelhas significam X, cristas significam 1 e vales 0.
all: $(FILE).vcd
	gtkwave $^

.vcd:
	$(error Tente make FILE=nome_do_modulo_sem_extensao)

#rodando o arquivo objeto para conseguir o log (.vcd)
%.vcd: %.vvp
	vvp $^

#compilando o modulo verilog para um arquivo objeto .vvp
%.vvp: %.v $(modulos)
	iverilog $^ -o $@ $(flags)

clean:
	rm -f *.vcd
	rm -f *.vvp
