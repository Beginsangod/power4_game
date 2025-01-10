#include <iostream> 
#include <stdlib.h> 
#include <string> 
#include <cstdlib>
#include <ctime>

void drawGrid(int grid[7][6]); 
bool playTurn(int grid[7][6], int column, int player); 
int game_ia(int grid[7][6], int player);
int findEmptyRow(int grid[7][6], int col);
bool checkWin(int grid[7][6], int player); 
bool checkHorizontal(int grid[7][6], int player); 
bool checkVertical(int grid[7][6], int player); 
bool checkDiagonal(int grid[7][6], int player);

int main(int argc, char** argv){ 
    srand(time(NULL));

    int grille[7][6] = {}; 
    std::string choix; 
    bool victory = false; 
    int player = 1; 
    int winner = 0; 
    int ia;

    std::cout<<"si vous voulez jouer contre l'ordinateur entrer 1 sinon un autre nombre: ";
    std::cin>>ia;
    drawGrid(grille); 

    while (!victory){ 
        std::cout << "player_" << player << " -> col : ";
        bool success = false;

        if (ia == 1 && player == 2) {
            // IA joue
            choix = std::to_string(game_ia(grille, 2));
            if (choix.size() == 1 && choix[0] >= '1' && choix[0] <= '7') { 
                int col = choix[0] - '0';  
                success = playTurn(grille, col, player);
            }
        } else {
            // Le joueur humain joue
            std::cin >> choix; 
            if (choix == "exit") { 
                break; 
            } 
            if (choix.size() == 1 && choix[0] >= '1' && choix[0] <= '7') { 
                int col = choix[0] - '0'; 
                success = playTurn(grille, col, player); 
            } else {
                std::cout << "Entrée invalide, essayez à nouveau." << std::endl;
            }
        }

        system("CLS"); 

        if (!success) { 
            std::cout << "Jouez sérieusement, please!" << std::endl; 
        } else { 
            if (checkWin(grille, player)) { 
                winner = player; 
                victory = true; 
            } else { 
                player = (player == 1) ? 2 : 1; 
            } 
        } 
        if (ia == 1 && player == 2) { 
            std::cout << "IA joue en colonne " << choix << std::endl;
        }
        drawGrid(grille); 
    } 

    if (winner != 0) 
    {   
        std::cout << "Le gagnant est le player_" << winner << " congratulations!"; 
    } else 
    { 
        std::cout << "Jeu termine sans gagnant."; 
    } 
    return 0; 
} 
// 0, 1, 2 
void drawGrid(int grille[7][6]){
    for (int ligne = 0; ligne < 6; ligne++)
    { 
        std::cout << "|"; 
        for (int col = 0; col < 7; col++)
        { 
            std::cout << "_"; 
            if (grille[col][ligne] == 1)
            { 
                std::cout << "\033[34mO\033[37m"; 
            } else if (grille[col][ligne] == 2)
            { 
                std::cout << "\033[32mO\033[37m"; 
            } else 
            { 
                std::cout << "\033[37m_\033[37m"; 
            } 
            std::cout << "|"; 
        } 
        std::cout << "\n"; 
    } 
} 

bool playTurn(int grid[7][6], int column, int player){

    for (int line = 5 ; line >= 0; line--)
    { 
        if (grid[column - 1][line] == 0)
        { 
            grid[column - 1][line] = player; 
            return true; 
        } 
    } 
    return false; 
} 

int game_ia(int grid[7][6], int player) {
    int random_col = rand() % 7 + 1;
    return random_col;
}

int findEmptyRow(int grid[7][6], int col) {
    for (int i = 5; i >= 0; i--) {
        if (grid[col][i] == 0) {
            return i;
        }
    }
    return -1;
}

bool checkHorizontal(int grid[7][6], int player)
{ 
    for (int i = 0; i < 6; i++) 
    { 
        int count = 0; 
        for (int j = 0; j < 7; j++) 
        { 
            if (grid[j][i] == player) 
            { 
                count++; 
                if (count == 4) 
                return true; 
            } else 
            { 
                count = 0; 
            } 
        } 
    } 
    return false; 
} 

bool checkVertical(int grid[7][6], int player){ 
    
    for (int i = 0; i < 7; i++) 
    { 
        int count = 0; 
        for (int j = 0; j < 6; j++) 
        { 
            if (grid[i][j] == player)
            { 
                count++; 
                if (count == 4) 
                return true; 
            } else 
            { 
                count = 0; 
            } 
        } 
    } 
    return false; 
} 

bool checkDiagonal(int grid[7][6], int player){ 
    // Check for diagonal (top-left to bottom-right) 
    for (int i = 0; i < 7 - 3; i++) 
    { 
        for (int j = 0; j < 6 - 3; j++) 
        { 
            if (grid[i][j] == player && grid[i+1][j+1] == player && grid[i+2][j+2] == player && grid[i+3][j+3] == player) 
                return true; 
        } 
    } 
    // Check for diagonal (bottom-left to top-right) 
    for (int i = 0; i < 7 - 3; i++) 
    { 
        for (int j = 3; j < 6; j++) 
        { 
            if (grid[i][j] == player && grid[i+1][j-1] == player && grid[i+2][j-2] == player && grid[i+3][j-3] == player) 
                return true; 
        } 
    } 
    return false; 
} 

bool checkWin(int grid[7][6], int player){ 
    return checkHorizontal(grid, player) || checkVertical(grid, player) || checkDiagonal(grid, player); }