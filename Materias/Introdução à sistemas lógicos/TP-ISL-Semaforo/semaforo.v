`define true 1
`define false 0

module semaforo(input clk, input rst, input bt,
	        output reg [2:0] A, output reg [2:0] B);

  // Estado de A e prox Estado
  reg [1:0] state_a, next_state_a;
  // Contador para contar quanto tempo
  // vai ficar no estado
  reg [8:0] counter;

  // Estado de B
  reg [1:0] state_b;

  // Variaveis para controle 
  reg bt_pressed = `false;
  reg ciclo = `false;
  reg follow_a = `false;

  // Assíncrono: seta o seguinte estado
  always @(state_a, counter) begin
    case(state_a)
      0: // Cor Verde
        if (counter == `VERDE) 
          next_state_a = 1; // Prox estado
        else 
	  next_state_a = 0;
   
      1: // Cor Amarela
        if (counter == `AMARELO) 
          next_state_a = 2;
        else 
	  next_state_a = 1;
    
      2: // Cor Vermelha
        if (counter == `VERMELHO)
          next_state_a = 0;
        else 
	  next_state_a = 2;
	    
      default: 
	next_state_a = 0;
    endcase
  end

  // Quando tiver um reset (borda de descida)
  always @(negedge rst) begin
    counter = 1; // Seta contador como 01
    state_a = 0; // Estado de A vai para 0
    state_b = 0; // Estado de B vai para 0
    next_state_a = 0;
    follow_a = `false;
    bt_pressed = `false;
  end

  // Quando botao for acionado (borda de subida)
  always @(posedge bt) begin
    bt_pressed = `true;
  end

  // Sincrono: Atualizacao do estado
  always @(posedge clk) begin
    state_a = next_state_a;
    // Se o botao foi apertado e comecou um ciclo entao
    // comece a seguir o semaforo A
    if(bt_pressed == `true && ciclo == `true) begin
      bt_pressed = `false;
      ciclo = `false;
      follow_a = `true;
    end

    // Se o semaforo B esta seguindo A, seu estado sera o mesmo de A
    if(follow_a)
      state_b = state_a;
  end

  // Saida Estado A e configuracoes ao comecar um estado!
  always @(state_a) begin
    if(state_a == 0) 
      begin
        A = 3'b 100; // Cor Verde

        // Contador em um
        counter = 1;
      
        // Se B ja estiver seguindo A, coloque como falso o bt
        if (follow_a) 
	  bt_pressed = `false;
      
        // Semaforo B para de seguir A quando completa o cilo
        follow_a = `false;

        // Ciclo foi completado
        ciclo = `true;
      end
    else if(state_a == 1) begin
      A = 3'b 010; // Cor Amarela
      // Ao chegar nesse estado setar:

      // Contador em um
      counter = 1;
      // Ciclo em andamento
      ciclo = `false;
    end
    else begin
      A = 3'b 001; // Cor Vermelha
      // Contador em um:
      counter = 1;
    end
  end

  // Saida Estado B
  always @(state_b) begin
    if(state_b == 0) begin
      B = 3'b 100; // Cor Verde
    end
    else if(state_b == 1) begin
      B = 3'b 010; // Cor Amarela
    end
    else begin
      B = 3'b 001; // Cor Vermelha
    end
  end

  // Contador, aumenta com a borda de subida do clock
  always @(posedge clk) begin
    counter = counter + 1;
  end
	
endmodule
	
