#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session){
    // ToDo
    init_game(&(session->current_game));
}

void init_session(Session *session){
    for(int i = 0; i <= MAX_LEVELS; i++){
       session->best_score[i] = 0;
    }
    restart_session_game(session);
}

void print_session(Session *session){
    int lvl = session->current_game.level;

    printf("[INFO] Level #%d | best score: %d\n",
           lvl,
           session->best_score[lvl]);

    print_game(session->current_game);
}

void new_game_score(Session *session){
    // ToDo
}
/**** LAB 1 - functions to program (end here) ****/
