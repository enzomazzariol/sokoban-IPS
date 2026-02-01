#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session){
    // llamada a la funcion para volver a iniciar una sesion nueva
    init_game(&(session->current_game));
}

void init_session(Session *session){
    // restablecer marcador de best score e iniciar sesion
    for(int i = 0; i <= MAX_LEVELS; i++){
       session->best_score[i] = 0;
    }
    restart_session_game(session);
}

void print_session(Session *session){
    // imprimir mejor score del nivel
    int lvl = session->current_game.level;

    printf("[INFO] Level #%d | best score: %d\n",
           lvl,
           session->best_score[lvl]);

    print_game(session->current_game);
}

void new_game_score(Session *session){
    // actualizar variable de best score 
    unsigned level = session->current_game.level;

    if(session->best_score[level] == 0 || session->best_score[level] > session->current_game.score){   
        session->best_score[level] = session->current_game.score;
    }
}
/**** LAB 1 - functions to program (end here) ****/
