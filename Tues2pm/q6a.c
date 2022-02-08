/* Question 6: [5 marks] Consider the structs defined below.  Fill in the 
 * missing parts of the code labeled with TODO, so that it operates correctly.
 * You may remove the TODO comments
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30
struct player
{
    int score;
    char name[MAX_NAME];
};

struct game_state
{
    int num_players;
    struct player* players_in_game;
};

/* Initialize "gs" to contain "n" players.  Each player's "score" will be 
 * initialized to 0, and their "name" set to "default_name"
 */
void initialize_game(struct game_state *gs, int n, char *default_name)
{
    gs->players_in_game = malloc(sizeof(player)*(n));
    // Set the num_players field in gs.
    gs->num_players = n;
    
    for(int i = 0; i < n; i++) {
        //Set the score for the ith player to 0;
        (gs->players_in_game)[i]->score = 0;
        

        // Initialize the ith player's name to the default name;
        (gs->players_in_game)[i]->name = *default_name;
        /* TODO */
    }
}


int main() {
    struct game_state *game = malloc( /*TODO*/ );
    initialize_game(game, 9, "player");
}
