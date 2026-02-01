#include "game.h"

/**** LAB 1 - given functions ****/
void print_options()
{
    printf("Options:\n");
    printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(Option o)
{
    return ((MOVE_UP <= o) && (o <= QUIT_GAME));
}

bool set_level(State *s, unsigned level)
{
    switch (level)
    {
    case 1:
        s->rows = 3;
        s->columns = 8;
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#.A.B.G#");
        strcpy(s->grid[2], "########");
        break;
    case 2:
        s->rows = 5;
        s->columns = 8;
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#....###");
        strcpy(s->grid[2], "#.B#.#A#");
        strcpy(s->grid[3], "#..B.GG#");
        strcpy(s->grid[4], "########");
        break;
    case 3:
        s->rows = 7;
        s->columns = 7;
        strcpy(s->grid[0], "#######");
        strcpy(s->grid[1], "###G###");
        strcpy(s->grid[2], "###B###");
        strcpy(s->grid[3], "#GBABG#");
        strcpy(s->grid[4], "###B###");
        strcpy(s->grid[5], "###G###");
        ;
        strcpy(s->grid[6], "#######");
        break;
    case 4:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 6;
        s->columns = 8;
        strcpy(s->grid[0], "#######.");
        strcpy(s->grid[1], "#.B.AG##");
        strcpy(s->grid[2], "#.XXG..#");
        strcpy(s->grid[3], "#....B.#");
        strcpy(s->grid[4], "#..#####");
        strcpy(s->grid[5], "####....");
        break;
    default:
        printf("[ERROR]: level not found!\n");
        return false;
    };

    return true;
}

void init_game(Game *game)
{
    game->score = 0;
    game->level = 0;
    game->state.rows = MAX_ROWS;
    game->state.columns = MAX_COLUMNS;
    for (int i = 0; i < MAX_ROWS; ++i)
        for (int j = 0; j < MAX_COLUMNS; ++j)
            game->state.grid[i][j] = '.';
}

void choose_level(Game *game)
{
    game->score = 0;
    do
    {
        printf("[INFO] Choose the level [1-4]: ");
        game->level = read_int();
    } while (!set_level(&game->state, game->level));
}

/**** LAB 1 - functions to program (start here) ****/
void print_state(State s)
// imprime en pantalla el grid del estado actual
{
    for (int i = 0; i < s.rows; i++)
    {
        printf("%s\n", s.grid[i]);
    }
}

void print_game(Game game)
{
    // imprime el score actual y el estado del juego
    printf("[INFO] Level #%d | current score: %d\n", game.level, game.score);
    print_state(game.state);
}

bool is_terminal(State s)
{
    // retorna true si todos los goals (G) están ocupados por cajas (X)
    for (int i = 0; i < s.rows; i++)
    {
        for (int j = 0; j < s.columns; j++)
        {
            if (s.grid[i][j] == 'G')
            {
                return false;
            }
        }
    }
    return true;
}

State move(State s, Option o)
{
    // manejo de movimientos del agente, agente sobre metas y movimiento de las cajas
    int actual_col;
    int actual_row;
    bool is_on_meta;
    int d_row = 0;
    int d_col = 0;

    for (int i = 0; i < s.rows; i++)
    {
        for (int j = 0; j < s.columns; j++)
        {
            if (s.grid[i][j] == 'A')
            {
                actual_row = i;
                actual_col = j;
                is_on_meta = false;
                break;
            }
            else if (s.grid[i][j] == 'Y')
            {
                actual_row = i;
                actual_col = j;
                is_on_meta = true;
                break;
            }
        }
    }

    switch (o) {
    // UP
    case MOVE_UP:
        d_row = -1;
        break;

    // RIGHT
    case MOVE_RIGHT:
        d_col = 1;
        break;

    // DOWN
    case MOVE_DOWN:
        d_row = 1;
        break;

    // LEFT
    case MOVE_LEFT:
        d_col = -1;
        break;

    case SHOW_BEST_MOVE:
        break;

    case QUIT_GAME:
        
        break;
    }

    // calcular siguiente posicion
    int next_row = actual_row + d_row;
    int next_col = actual_col + d_col;

    // evitar moverse fuera del tablero
    if(next_row < 0 || next_row >= s.rows || next_col < 0 || next_col >= s.columns) return s;

    char next_cell = s.grid[next_row][next_col];


    if(next_cell == '#'){
        return s;
    } else if(next_cell == '.' || next_cell == 'G'){
            // restaurar la casilla anterior
        if (is_on_meta) {
            s.grid[actual_row][actual_col] = 'G';
        } else {
            s.grid[actual_row][actual_col] = '.';
        }

        // colocar al agente en la nueva posición
        if (next_cell == 'G') {
            s.grid[next_row][next_col] = 'Y';   
        } else {
            s.grid[next_row][next_col] = 'A';   
        }
    return s;
    } else if(next_cell == 'B' || next_cell == 'X'){
        //calcular posicion de la caja
        int box_next_row = next_row + d_row;
        int box_next_col = next_col + d_col;

        // evitar moverse fuera del tablero
        if(box_next_row < 0 || box_next_row >= s.rows || box_next_col < 0 || box_next_col >= s.columns) return s;

        // calcular siguiente posicion de la caja
        char box_next_cell = s.grid[box_next_row][box_next_col];

        // la caja no se puede mover
        if (box_next_cell == '#' || box_next_cell == 'B' || box_next_cell == 'X') {
            return s;
        }

        // mover caja
        if(box_next_cell == '.' || box_next_cell == 'G'){
            if (box_next_cell == 'G') {
                s.grid[box_next_row][box_next_col] = 'X';  // caja sobre meta
            } else {
                 s.grid[box_next_row][box_next_col] = 'B';  // caja normal
            }
        }

        if (next_cell == 'X') {
            s.grid[next_row][next_col] = 'Y';  // agente sobre meta
            is_on_meta = true;
        } else {
            s.grid[next_row][next_col] = 'A';
            is_on_meta = false;
        }

        if (is_on_meta) {
            s.grid[actual_row][actual_col] = 'G';
        } else {
            s.grid[actual_row][actual_col] = '.';
        }

        return s;
    }

    return s;
}

/**** LAB 1 - functions to program (end here) ****/
