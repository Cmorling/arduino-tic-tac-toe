
//Tic-tac-toe arduino project

//tic-tac-toe cells(2d array)
int cells[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

int *cells_1d[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

//definying placeholders
#define A 8
#define B 9
#define C 10
#define D 11
#define E 12

int ledLights[18][2] = {{A,B},{A,C},{A,D},{A,E},{B,A},{B,C},{B,D},{B,E},{C,A},{C,B},{C,D},{C,E},{D,A},{D,B},{D,C},{D,E},{E,A},{E,B}};

int current_selected_counter = 0;

int current_player = 1;

void play_winner(int player){
  for(int i = 0; i < sizeof(cells_1d); i++){
    *cells_1d[i] = player;
  }
}

void write_draw(){
  for(int i = 0; i < sizeof(cells_1d); i++){
    *cells_1d[i] = 3;
  }
}

void check_for_draw(){
  int zero_counter = 0;
  for(int i = 0; i < sizeof(cells_1d); i++){
    if(cells_1d[i] == 0){
      zero_counter++;
      break;
    }
  }
  if(zero_counter == 0){
    write_draw();
  }
}
void swap_cell(){
  while(true){
    if(cells_1d[current_selected_counter] == 0){
      *cells_1d[current_selected_counter] = 3;
      break;
    } else {
      current_selected_counter++;
    }
  }
}

void reset_select(){
  for(int i = 0; i < sizeof(cells_1d); i++){
    if(*cells_1d[i] == 3){
      *cells_1d[i] = 0;
    }
  }
  while(true){
    if(cells_1d[current_selected_counter] == 0){
      *cells_1d[current_selected_counter] = 3;
      break;
    } else {
      current_selected_counter++;
    }
  }
}

void write_cell(){
  for(int i = 0; i < sizeof(cells_1d); i++){
    if(*cells_1d[i] == 3){
      if(current_player == 1){
        *cells_1d[i] = 1;
        current_player = 2;
        if(i < 3){
          cells[0][i] == 1;
        }
        else if(i < 6){
          cells[1][i - 3] == 1;
        }
        else if(i < 9){
          cells[2][i - 6] == 1;
        }
      }
      else if(current_player == 2){
        *cells_1d[i] = 2;
        current_player = 1;
        if(i < 3){
          cells[0][i] == 2;
        }
        else if(i < 6){
          cells[1][i - 3] == 2;
        }
        else if(i < 9){
          cells[2][i - 6] == 2;
        }
      }
    }
  }
  current_selected_counter = 0;
  if(check_for_winner() == 1){
    play_winner(1);
  }
  else if(check_for_winner() == 2){
    play_winner(2);
  }
  check_for_draw();
  reset_select();
}

int check_for_winner(){
  //Check verticaly
  for(int i = 0; i < (sizeof(cells) / sizeof(cells[0])); i++){
    int player1_total = 0;
    int player2_total = 0;
     for(int j = 0; j < (sizeof(cells[i]) / sizeof(cells[i][0])); j++){

      if(cells[i][j] == 1){
        player1_total++;
      }
      else if(cells[i][j] == 2){
        player2_total++;
      }

    }
    if(player1_total == 3){
      return 1;
    }
    else if (player2_total == 3){
      return 2;
    }
  }
  //Horizantely
  for(int i = 0; i < (sizeof(cells[0]) / sizeof(cells[0][0])); i++){
    int player1_total = 0;
    int player2_total = 0;
      for(int j = 0; j < (sizeof(cells) / sizeof(cells[0])); j++){
        if(cells[j][i] == 1){
          player1_total++;
        }
        else if(cells[j][i]){
          player2_total++;
        }
      }
      if(player1_total == 3){
      return 1;
      }
      else if(player2_total == 3){
      return 2;
    }
  }
  //Check Diagnoally
  if((cells[0][0] == 1 && cells[1][1] == 1 && cells[2][2] == 1) || (cells[2][0] == 1 && cells[1][1] == 1 && cells[0][2] == 1)){
    return 1;
  }
  else if((cells[0][0] == 2 && cells[1][1] == 2 && cells[2][2] == 2) || (cells[2][0] == 2 && cells[1][1] == 2 && cells[0][2] == 2)){
    return 2;
  }
  return 0;
}

void setup_pins(){
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
}

void lights(int cell, int index){
  if(cell == 1){
    pinMode(ledLights[index][0], OUTPUT);
    digitalWrite(ledLights[index][0], HIGH);

    pinMode(ledLights[index][1], OUTPUT);
    digitalWrite(ledLights[index][1], LOW);
  }
  else if(cell == 2){
    pinMode(ledLights[index + 9][0], OUTPUT);
    digitalWrite(ledLights[index + 9][0], HIGH);

    pinMode(ledLights[index + 9][1], OUTPUT);
    digitalWrite(ledLights[index + 9][1], LOW);
  }
  else if(cell = 3){
    pinMode(ledLights[index + 9][0], OUTPUT);
    digitalWrite(ledLights[index + 9][0], HIGH);

    pinMode(ledLights[index + 9][1], OUTPUT);
    digitalWrite(ledLights[index + 9][1], LOW);

    setup_pins();

    pinMode(ledLights[index][0], OUTPUT);
    digitalWrite(ledLights[index][0], HIGH);

    pinMode(ledLights[index][1], OUTPUT);
    digitalWrite(ledLights[index][1], LOW);
  }
 setup_pins();

}

void hold_lights_alive(){
  for(int i = 0; i < sizeof(cells_1d); i++){
    lights(*cells_1d[i], i);
  }
}

void check_for_button_input(){
  if(digitalRead(3) == HIGH){
    swap_cell();
  }
  if(digitalRead(2) == HIGH){
    write_cell();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
}

void loop(){
  hold_lights_alive();
  check_for_button_input();
}

