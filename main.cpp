//
//  main.cpp
//  Chess
//
//  Created by Marcus Miller on 11/21/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

const int NUMBER_OF_FILES = 8; // number of columns
const int NUMBER_OF_RANKS = 8; // number of rows

class Coordinate
{
private:
    int x;
    int y;
public:
    // Getters
    int get_x() const
    {
        return x;
    }
    int get_y() const
    {
        return y;
    }
    // Setters
    void set_x(int x1)
    {
        x = x1;
    }
    void set_y(int y1)
    {
        y = y1;
    }
    Coordinate add(Coordinate other)
    {
         return Coordinate(this->get_x() + other.get_x(), this->get_y() + other.get_y());
    }
    Coordinate subtract(Coordinate other)
    {
        return Coordinate(this->get_x() - other.get_x(), this->get_y() - other.get_y());
    }
    bool equal (Coordinate &other_coordinate)
    {
        return this->get_x() == other_coordinate.get_x() && this->get_y() == other_coordinate.get_y();
    }
    
    // Constructors
    Coordinate()
    {
        set_x(0);
        set_y(0);
    }
    Coordinate(int x1, int y1)
    {
        set_x(x1);
        set_y(y1);
    }
    
    string get_string()
    {
        return "(" + to_string(get_x()) + ", "  + to_string(get_y()) + ")";
    }
};

const char PAWN_SYMBOL = 'p';
const char KING_SYMBOL = '+';
const char ROOK_SYMBOL = 'r';
const char KNIGHT_SYMBOL = 'k';
const char QUEEN_SYMBOL = 'q';
const char BISHOP_SYMBOL = 'b';

const int NUMBER_OF_BISHOP_MOVES = 28;
const Coordinate BISHOP_MOVES[NUMBER_OF_BISHOP_MOVES] =
{
    Coordinate(1,1),
    Coordinate(2,2),
    Coordinate(3,3),
    Coordinate(4,4),
    Coordinate(5,5),
    Coordinate(6,6),
    Coordinate(7,7),
    Coordinate(-1,-1),
    Coordinate(-2,-2),
    Coordinate(-3,-3),
    Coordinate(-4,-4),
    Coordinate(-5,-5),
    Coordinate(-6,-6),
    Coordinate(-7,-7),
    Coordinate(-1,1),
    Coordinate(-2,2),
    Coordinate(-3,3),
    Coordinate(-4,4),
    Coordinate(-5,5),
    Coordinate(-6,6),
    Coordinate(-7,7),
    Coordinate(1,-1),
    Coordinate(2,-2),
    Coordinate(3,-3),
    Coordinate(4,-4),
    Coordinate(5,-5),
    Coordinate(6,-6),
    Coordinate(7,-7)
};

const int NUMBER_OF_ROOK_MOVES = 28;
const Coordinate ROOK_MOVES[NUMBER_OF_ROOK_MOVES] =
{
    Coordinate(1,0),
    Coordinate(2,0),
    Coordinate(3,0),
    Coordinate(4,0),
    Coordinate(5,0),
    Coordinate(6,0),
    Coordinate(7,0),
    Coordinate(-1,0),
    Coordinate(-2,0),
    Coordinate(-3,0),
    Coordinate(-4,0),
    Coordinate(-5,0),
    Coordinate(-6,0),
    Coordinate(-7,0),
    Coordinate(0,1),
    Coordinate(0,2),
    Coordinate(0,3),
    Coordinate(0,4),
    Coordinate(0,5),
    Coordinate(0,6),
    Coordinate(0,7),
    Coordinate(0,-1),
    Coordinate(0,-2),
    Coordinate(0,-3),
    Coordinate(0,-4),
    Coordinate(0,-5),
    Coordinate(0,-6),
    Coordinate(0,-7)
};

const Coordinate BLACK_ROOK_START_CASTLING[] =
{
    Coordinate(0,7),
    Coordinate(7,7)
};

const Coordinate BLACK_ROOK_END_CASTLING[] =
{
    Coordinate(3,7),
    Coordinate(5,7)
};

const Coordinate BLACK_ROOK_CASTLING_MOVES[] =
{
    Coordinate(3,0),
    Coordinate(-2,0)
};

const Coordinate WHITE_ROOK_START_CASTLING[] =
{
    Coordinate(0,0),
    Coordinate(7,0)
};

const Coordinate WHITE_ROOK_END_CASTLING[] =
{
    Coordinate(3,0),
    Coordinate(5,0)
};

const Coordinate WHITE_ROOK_CASTLING_MOVES[] =
{
    Coordinate(3,0),
    Coordinate(-2,0)
};



const int NUMBER_OF_QUEEN_MOVES = 56;
const Coordinate QUEEN_MOVES[NUMBER_OF_QUEEN_MOVES] =
{
    Coordinate(1,1),
    Coordinate(2,2),
    Coordinate(3,3),
    Coordinate(4,4),
    Coordinate(5,5),
    Coordinate(6,6),
    Coordinate(7,7),
    Coordinate(-1,-1),
    Coordinate(-2,-2),
    Coordinate(-3,-3),
    Coordinate(-4,-4),
    Coordinate(-5,-5),
    Coordinate(-6,-6),
    Coordinate(-7,-7),
    Coordinate(-1,1),
    Coordinate(-2,2),
    Coordinate(-3,3),
    Coordinate(-4,4),
    Coordinate(-5,5),
    Coordinate(-6,6),
    Coordinate(-7,7),
    Coordinate(1,-1),
    Coordinate(2,-2),
    Coordinate(3,-3),
    Coordinate(4,-4),
    Coordinate(5,-5),
    Coordinate(6,-6),
    Coordinate(7,-7),
    Coordinate(1,0),
    Coordinate(2,0),
    Coordinate(3,0),
    Coordinate(4,0),
    Coordinate(5,0),
    Coordinate(6,0),
    Coordinate(7,0),
    Coordinate(-1,0),
    Coordinate(-2,0),
    Coordinate(-3,0),
    Coordinate(-4,0),
    Coordinate(-5,0),
    Coordinate(-6,0),
    Coordinate(-7,0),
    Coordinate(0,1),
    Coordinate(0,2),
    Coordinate(0,3),
    Coordinate(0,4),
    Coordinate(0,5),
    Coordinate(0,6),
    Coordinate(0,7),
    Coordinate(0,-1),
    Coordinate(0,-2),
    Coordinate(0,-3),
    Coordinate(0,-4),
    Coordinate(0,-5),
    Coordinate(0,-6),
    Coordinate(0,-7)
};

const int NUMBER_OF_KNIGHT_MOVES = 8;
const Coordinate KNIGHT_MOVES [NUMBER_OF_KNIGHT_MOVES] =
{
    Coordinate(2,1),
    Coordinate(1,2),
    Coordinate(-1,2),
    Coordinate(-2,1),
    Coordinate(-2,-1),
    Coordinate(-1,-2),
    Coordinate(1,-2),
    Coordinate(2,-1)
};


const Coordinate WHITE_PAWN_MOVE(0,1);
const Coordinate WHITE_PAWN_FIRST_MOVE(0,2);

const int NUMBER_OF_PAWN_ATTACKS = 2;
const Coordinate WHITE_PAWN_ATTACKS [NUMBER_OF_PAWN_ATTACKS] =
{
    Coordinate(1,1),
    Coordinate(-1,1)
};



const Coordinate BLACK_PAWN_MOVE(0,-1);
const Coordinate BLACK_PAWN_FIRST_MOVE(0,-2);

const Coordinate BLACK_PAWN_ATTACKS [NUMBER_OF_PAWN_ATTACKS] =
{
    Coordinate(1,-1),
    Coordinate(-1,-1)
};



const int NUMBER_OF_KING_MOVES = 8;
const Coordinate KING_MOVES [NUMBER_OF_KING_MOVES] =
{
    Coordinate(1,1),
    Coordinate(0,1),
    Coordinate(-1,1),
    Coordinate(-1,0),
    Coordinate(-1,-1),
    Coordinate(0,-1),
    Coordinate(1,-1),
    Coordinate(1,0)
};

const Coordinate BLACK_KING_START(4,7);
const Coordinate WHITE_KING_START(4,0);

const int NUMBER_OF_CASTLING_MOVES = 2;

const Coordinate BLACK_KING_CASTLING_MOVES[] =
{
    Coordinate(-2,0),
    Coordinate(2,0)
};

const Coordinate BETWEEN_BLACK_KING_CASTLING_MOVES[] =
{
    Coordinate(3,7),
    Coordinate(5,7),
};

const Coordinate WHITE_KING_CASTLING_MOVES[] =
{
    Coordinate(-2,0),
    Coordinate(2,0)
};

const Coordinate BETWEEN_WHITE_KING_CASTLING_MOVES[] =
{
    Coordinate(3,0),
    Coordinate(5,0),
};

struct Move
{
    Coordinate start = Coordinate(0,0);
    Coordinate end = Coordinate(0,0);
};

bool PLAYER1 = true;
bool PLAYER2 = false;

Move get_move_func();
int get_promotion_func();
class Piece;

class Player
{
public:
    Move get_move(Piece *board[][NUMBER_OF_RANKS], Move last_move)
    {
        
        return get_move_func();
    }
    int get_promotion(Piece *board[][NUMBER_OF_RANKS], Move last_move)
    {
        return get_promotion_func();
    }
    // Constructor
    Player()
    {
        set_player(true);
    }
    // Getters
    bool get_player()
    {
        return player;
    }
    // Setters
    void set_player(bool p)
    {
        player = p;
    }
private:
    bool player;
};

int get_all_moves(bool player, Move moves[], Piece *board[][NUMBER_OF_RANKS], Move last_move);

class Computer_Player:public Player
{
public:
    Move get_move(Piece *board[][NUMBER_OF_RANKS], Move last_move)
    {
        Move moves[200];
        int num_moves;
        num_moves = get_all_moves(PLAYER2, moves, board, last_move);
        return moves[rand()%num_moves];
    }
    int get_promotion(Piece *board[][NUMBER_OF_RANKS], Move last_move)
    {
        return 4; // Queen promotion number
    }
};

class Piece
{
private:
    int num_moves;
    bool player;
    Coordinate position;
    char piece_symbol;
    
public:
    // Getters
    int get_num_moves()
    {
        return num_moves;
    }
    bool get_player()
    {
        return player;
    }
    Coordinate get_position()
    {
        return position;
    }
    char get_piece_symbol()
    {
        return piece_symbol;
    }
    // Setters
    void set_num_moves(int nm)
    {
        num_moves = nm;
    }
    void set_player(bool p)
    {
        player = p;
    }
    void set_position(Coordinate p)
    {
        position = p;
    }
    void set_piece_symbol(char ps)
    {
        piece_symbol = ps;
    }
    // Constructors
    Piece()
    {
        set_num_moves(0);
        set_player(true);
        set_position(Coordinate(0,0));
        set_piece_symbol('x');
    }
    Piece(int nm, bool p, Coordinate coordinate, char ps)
    {
        set_num_moves(nm);
        set_player(p);
        set_position(coordinate);
        set_piece_symbol(ps);
    }
};



void start_new_game(Piece *board[][NUMBER_OF_RANKS])
{
    // Create Black Pieces
    // Create Black Pawns
    board[0][6] = new Piece(0, PLAYER2, Coordinate(0,6), PAWN_SYMBOL);
    board[1][6] = new Piece(0, PLAYER2, Coordinate(1,6), PAWN_SYMBOL);
    board[2][6] = new Piece(0, PLAYER2, Coordinate(2,6), PAWN_SYMBOL);
    board[3][6] = new Piece(0, PLAYER2, Coordinate(3,6), PAWN_SYMBOL);
    board[4][6] = new Piece(0, PLAYER2, Coordinate(4,6), PAWN_SYMBOL);
    board[5][6] = new Piece(0, PLAYER2, Coordinate(5,6), PAWN_SYMBOL);
    board[6][6] = new Piece(0, PLAYER2, Coordinate(6,6), PAWN_SYMBOL);
    board[7][6] = new Piece(0, PLAYER2, Coordinate(7,6), PAWN_SYMBOL);
    // Create Black Rooks
    board[0][7] = new Piece(0, PLAYER2, Coordinate(0,7), ROOK_SYMBOL);
    board[7][7] = new Piece(0, PLAYER2, Coordinate(7,7), ROOK_SYMBOL);
    // Create Black Bishops
    board[2][7] = new Piece(0, PLAYER2, Coordinate(2,7), BISHOP_SYMBOL);
    board[5][7] = new Piece(0, PLAYER2, Coordinate(5,7), BISHOP_SYMBOL);
    // Create Black Knights
    board[1][7] = new Piece(0, PLAYER2, Coordinate(1,7), KNIGHT_SYMBOL);
    board[6][7] = new Piece(0, PLAYER2, Coordinate(6,7), KNIGHT_SYMBOL);
    // Create Black Queen
    board[3][7] = new Piece(0, PLAYER2, Coordinate(3,7), QUEEN_SYMBOL);
    // Create Black King
    board[4][7] = new Piece(0, PLAYER2, Coordinate(4,7), KING_SYMBOL);
    
    // Create White Pieces
    // Create White Pawns
    board[0][1] = new Piece(0, PLAYER1, Coordinate(0,1), PAWN_SYMBOL);
    board[1][1] = new Piece(0, PLAYER1, Coordinate(1,1), PAWN_SYMBOL);
    board[2][1] = new Piece(0, PLAYER1, Coordinate(2,1), PAWN_SYMBOL);
    board[3][1] = new Piece(0, PLAYER1, Coordinate(3,1), PAWN_SYMBOL);
    board[4][1] = new Piece(0, PLAYER1, Coordinate(4,1), PAWN_SYMBOL);
    board[5][1] = new Piece(0, PLAYER1, Coordinate(5,1), PAWN_SYMBOL);
    board[6][1] = new Piece(0, PLAYER1, Coordinate(6,1), PAWN_SYMBOL);
    board[7][1] = new Piece(0, PLAYER1, Coordinate(7,1), PAWN_SYMBOL);
    // Create White Rooks
    board[0][0] = new Piece(0, PLAYER1, Coordinate(0,0), ROOK_SYMBOL);
    board[7][0] = new Piece(0, PLAYER1, Coordinate(7,0), ROOK_SYMBOL);
    // Create White Bishops
    board[2][0] = new Piece(0, PLAYER1, Coordinate(2,0), BISHOP_SYMBOL);
    board[5][0] = new Piece(0, PLAYER1, Coordinate(5,0), BISHOP_SYMBOL);
    // Create White Knights
    board[1][0] = new Piece(0, PLAYER1, Coordinate(1,0), KNIGHT_SYMBOL);
    board[6][0] = new Piece(0, PLAYER1, Coordinate(6,0), KNIGHT_SYMBOL);
    // Create White Queen
    board[3][0] = new Piece(0, PLAYER1, Coordinate(3,0), QUEEN_SYMBOL);
    // Create White King
    board[4][0] = new Piece(0, PLAYER1, Coordinate(4,0), KING_SYMBOL);
}

void delete_board(Piece *board[][NUMBER_OF_RANKS])
{
    for(int x = 0; x < NUMBER_OF_FILES; x++)
    {
        for(int y = 0; y < NUMBER_OF_RANKS; y++)
        {
            if (board[x][y] != nullptr)
            {
                delete board[x][y];
                board[x][y] = nullptr;
            }
        }
    }
}

string board_to_string(Piece *board[][NUMBER_OF_RANKS])
{
    string tmp = "";
    for(int y = NUMBER_OF_RANKS - 1; y >= 0; y--)
    {
        tmp += to_string(y);
        tmp += '|';
        for (int x = 0; x < NUMBER_OF_FILES; x++)
        {
            if (board[x][y] == nullptr)
            {
                tmp += "  |";
                continue;
            }
            else if (board[x][y]->get_player() == PLAYER1)
            {
                tmp+= '$';
            }
            else
            {
                tmp += '*';
            }
            tmp += board[x][y]->get_piece_symbol();
            tmp += '|';
        }
        tmp += '\n';
    }
    
    tmp += " |0 |1 |2 |3 |4 |5 |6 |7 |";
    return tmp;
}

double get_distance(Move move)
{
    return sqrt(pow(move.start.get_x()-move.end.get_x(),2)+pow(move.start.get_y()-move.end.get_y(), 2));
}
Coordinate get_direction(Move move)
{
    return Coordinate(move.end.get_x() - move.start.get_x(), (move.end.get_y() - move.start.get_y()));
}

bool in_between(Move move, Piece *board[][NUMBER_OF_RANKS])
{
    double dist = get_distance(move);
    Coordinate direction = get_direction(move);
    if (move.start.get_x() < 0 || move.start.get_x() > 7 || move.end.get_x() < 0 || move.end.get_x() > 7 ||
        move.start.get_y() < 0 || move.start.get_y() > 7 || move.end.get_y() < 0 || move.end.get_y() > 7)
    {
        throw "Move out of range\n";
        cout << "problem\n";
        return false;
    }
    if (dist < 2)
    {
        return false;
    }
    else
    {
        Move new_move;
        if (direction.get_x() > 0 && direction.get_y() == 0) // East
        {
            Coordinate new_start(move.start.get_x() + 1, move.start.get_y());
            if (board[move.start.get_x() + 1][move.start.get_y()] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() > 0 && direction.get_y() > 0) // North-East
        {
            Coordinate new_start(move.start.get_x() + 1, move.start.get_y() + 1);
            if (board[move.start.get_x() + 1][move.start.get_y() + 1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() == 0 && direction.get_y() > 0) // North
        {
            Coordinate new_start(move.start.get_x(), move.start.get_y() + 1);
            if (board[move.start.get_x()][move.start.get_y()+1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() < 0 && direction.get_y() > 0) // North-West
        {
            Coordinate new_start(move.start.get_x() - 1, move.start.get_y() + 1);
            if (board[move.start.get_x() - 1][move.start.get_y() + 1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() < 0 && direction.get_y() == 0) // West
        {
            Coordinate new_start(move.start.get_x() - 1, move.start.get_y());
            if (board[move.start.get_x() - 1][move.start.get_y()] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() < 0 && direction.get_y() < 0) // South-West
        {
            Coordinate new_start(move.start.get_x() - 1, move.start.get_y() - 1);
            if (board[move.start.get_x() - 1][move.start.get_y() - 1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() == 0 && direction.get_y() < 0) // South
        {
            Coordinate new_start(move.start.get_x(), move.start.get_y() - 1);
            if (board[move.start.get_x()][move.start.get_y() - 1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else if (direction.get_x() > 0 && direction.get_y() < 0) // South-East
        {
            Coordinate new_start(move.start.get_x() + 1, move.start.get_y() - 1);
            if (board[move.start.get_x() + 1][move.start.get_y() - 1] == nullptr)
            {
                new_move.start = new_start;
                new_move.end = move.end;
                return in_between(new_move, board);
            }
            else
            {
                return true;
            }
        }
        else
        {
            cout << "problem\n";
            return false;
        }
    }
}

void copy_piece(Piece *from_piece, Piece *to_piece)
{
    to_piece->set_position(from_piece->get_position());
    to_piece->set_piece_symbol(from_piece->get_piece_symbol());
    to_piece->set_player(from_piece->get_player());
    to_piece->set_num_moves(from_piece->get_num_moves());
}


void copy_board(Piece *board[][NUMBER_OF_RANKS], Piece *another_board[][NUMBER_OF_RANKS])
{
    for (int i = 0; i < NUMBER_OF_RANKS; i++) // y
    {
        for (int j = 0; j < NUMBER_OF_FILES; j++) // x
        {
            if (board[i][j] == nullptr)
            {
                another_board[i][j] = nullptr;
            }
            else
            {
                Piece *piece_ptr = new Piece;
                another_board[i][j] = piece_ptr;
                copy_piece(board[i][j], another_board[i][j]);
            }
        }
    }
}


bool attackable(bool, Piece *[][NUMBER_OF_RANKS], Coordinate, Move, int);
bool is_in_check(bool, Piece *board[][NUMBER_OF_RANKS], Move, int);
Coordinate find_king(bool, Piece *board[][NUMBER_OF_RANKS]);

bool valid_move(bool player, Piece *board[][NUMBER_OF_RANKS], Move move, Move last_move, int times_called)
{
    // Check to see if player has a piece at the start location
    // See if the player's piece can move to the end position
        // Special Moves
            // Castling
            // If it's the pawns first move then the pawn can move two spaces forward
    // Make sure the player doesn't have a piece at the end position
    // Make sure there isn't a piece inbetween the start and end position unless a knight is moving
    // Make sure the player doesn't put the king in check
    int start_x = move.start.get_x();
    int start_y = move.start.get_y();
    int end_x = move.end.get_x();
    int end_y = move.end.get_y();

    Piece *another_board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    copy_board(board, another_board);
    
    
    if (start_x < 0 || end_x < 0 || start_x > 7 || end_x > 7 || start_y < 0 || end_y < 0 || start_y > 7 || end_y > 7)
    // start or end position is off the board
    {
        delete_board(another_board);
        return false;
    }
    if (board[start_x][start_y] == nullptr) // no piece on start spot
    {
        delete_board(another_board);
        return false;
    }
    else if (board[start_x][start_y]->get_player() != player) // you don't have a piece at the start spot
    {
        delete_board(another_board);
        return false;
    }
    else if (board[end_x][end_y] != nullptr && board[end_x][end_y]->get_player() == player) // you have a piece at the end spot
    {
        delete_board(another_board);
        return false;
    }
    Piece *piece_ptr = board[start_x][start_y];
    double distance = get_distance(move);
    bool piece_in_between = in_between(move, board);
    
    switch(piece_ptr->get_piece_symbol())
    {
        case PAWN_SYMBOL:
            if (distance < 1 || distance > 2)
            {
                delete_board(another_board);
                return false;
            }
            else if (distance == 1)
            {
                if (player == PLAYER1)
                {
                    Coordinate tmp = move.start.add(WHITE_PAWN_MOVE);
                    if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.equal(move.end))
                    {
                        if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                        {
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        else
                        {
                            delete another_board[move.end.get_x()][move.end.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        bool check_status = false;
                        if (times_called == 0)
                        {
                            check_status = is_in_check(player, another_board, move, times_called);
                        }
                        delete_board(another_board);
                        if (check_status == true)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        delete_board(another_board);
                        return false;
                    }
                }
                else // Player 2
                {
                    Coordinate tmp = move.start.add(BLACK_PAWN_MOVE);
                    if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.equal(move.end))
                    {
                        if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                        {
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        else
                        {
                            delete another_board[move.end.get_x()][move.end.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        bool check_status = false;
                        if (times_called == 0)
                        {
                            check_status = is_in_check(player, another_board, move, times_called);
                        }
                        delete_board(another_board);
                        if (check_status == true)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        delete_board(another_board);
                        return false;
                    }
                }
            }
            else if (distance < 2)
            {
                if (player == PLAYER1)
                {
                    for (int i = 0; i < NUMBER_OF_PAWN_ATTACKS; i++)
                    {
                        Coordinate tmp = move.start.add(WHITE_PAWN_ATTACKS[i]);
                        if (!tmp.equal(move.end))
                        {
                            continue;
                        }
                        if (board[tmp.get_x()][tmp.get_y()] != nullptr && board[tmp.get_x()][tmp.get_y()]->get_player() == PLAYER2 &&
                            tmp.equal(move.end))
                        {
                            if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                            {
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            else
                            {
                                delete another_board[move.end.get_x()][move.end.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            bool check_status = false;
                            if (times_called == 0)
                            {
                                check_status = is_in_check(player, another_board, move, times_called);
                            }
                            delete_board(another_board);
                            if (check_status == true)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                        else if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.get_y() == 5 && // En passant pawn capture
                                 board[tmp.get_x()][tmp.get_y() - 1] != nullptr && board[tmp.get_x()][tmp.get_y() - 1]->get_player() == PLAYER2
                                 && tmp.equal(move.end) && board[tmp.get_x()][tmp.get_y() - 1]->get_piece_symbol() == 'p' &&
                                 board[tmp.get_x()][tmp.get_y() - 1]->get_num_moves() == 1 &&
                                 last_move.end.get_y() == tmp.get_y() - 1 && last_move.end.get_x() == tmp.get_x())
                        {
                            if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                            {
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            else
                            {
                                delete another_board[move.end.get_x()][move.end.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            bool check_status = false;
                            if (times_called == 0)
                            {
                                check_status = is_in_check(player, another_board, move, times_called);
                            }
                            delete_board(another_board);
                            if (check_status == true)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                    }
                    delete_board(another_board);
                    return false;
                }
                else // Player 2
                {
                    for (int i = 0; i < NUMBER_OF_PAWN_ATTACKS; i++)
                    {
                        Coordinate tmp = move.start.add(BLACK_PAWN_ATTACKS[i]);
                        if (!tmp.equal(move.end))
                        {
                            continue;
                        }
                        if (board[tmp.get_x()][tmp.get_y()] != nullptr && board[tmp.get_x()][tmp.get_y()]->get_player() == PLAYER1 &&
                            tmp.equal(move.end))
                        {
                            if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                            {
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            else
                            {
                                delete another_board[move.end.get_x()][move.end.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            bool check_status = false;
                            if (times_called == 0)
                            {
                                check_status = is_in_check(player, another_board, move, times_called);
                            }
                            delete_board(another_board);
                            if (check_status == true)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                        else if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.get_y() == 2 && // En passant pawn capture
                                 board[tmp.get_x()][tmp.get_y() + 1] != nullptr && board[tmp.get_x()][tmp.get_y() + 1]->get_player() == PLAYER1
                                 && tmp.equal(move.end) && board[tmp.get_x()][tmp.get_y() + 1]->get_piece_symbol() == 'p' &&
                                 board[tmp.get_x()][tmp.get_y() + 1]->get_num_moves() == 1 &&
                                 last_move.end.get_y() == tmp.get_y() + 1 && last_move.end.get_x() == tmp.get_x())
                        {
                            if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                            {
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            else
                            {
                                delete another_board[move.end.get_x()][move.end.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                                another_board[move.end.get_x()][move.end.get_y()]->
                                set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                                another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                            }
                            bool check_status = false;
                            if (times_called == 0)
                            {
                                check_status = is_in_check(player, another_board, move, times_called);
                            }
                            delete_board(another_board);
                            if (check_status == true)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                    }
                    delete_board(another_board);
                    return false;
                }
            }
            else // distance == 2
            {
                if (player == PLAYER1)
                {
                    Coordinate tmp = move.start.add(WHITE_PAWN_FIRST_MOVE);
                    if (!tmp.equal(move.end))
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (move.start.get_y() != 1) // pawn has already moved
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (board[move.start.get_x()][move.start.get_y()+1] != nullptr) // piece in-between start and end position
                    {
                        delete_board(another_board);
                        return false;
                    }
                    
                    if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.equal(move.end)) // A peice is on the ending position
                    {
                        if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                        {
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        else
                        {
                            delete another_board[move.end.get_x()][move.end.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        bool check_status = false;
                        if (times_called == 0)
                        {
                            check_status = is_in_check(player, another_board, move, times_called);
                        }
                        delete_board(another_board);
                        if (check_status == true)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        delete_board(another_board);
                        return false;
                    }
                }
                else // Player 2
                {
                    Coordinate tmp = move.start.add(BLACK_PAWN_FIRST_MOVE);
                    if (!tmp.equal(move.end))
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (move.start.get_y() != 6)
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (board[move.start.get_x()][move.start.get_y()-1] != nullptr) // piece in-between start and end position
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (board[tmp.get_x()][tmp.get_y()] == nullptr && tmp.equal(move.end)) // A peice is on the ending position
                    {
                        if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                        {
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        else
                        {
                            delete another_board[move.end.get_x()][move.end.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                            another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                            another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                        }
                        bool check_status = false;
                        if (times_called == 0)
                        {
                            check_status = is_in_check(player, another_board, move, times_called);
                        }
                        delete_board(another_board);
                        if (check_status == true)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        delete_board(another_board);
                        return false;
                    }
                }
            }
            break;
        case ROOK_SYMBOL:
            if (piece_in_between == true)
            {
                delete_board(another_board);
                return false;
            }
            for (int i = 0; i < NUMBER_OF_ROOK_MOVES; i++)
            {
                Coordinate start_plus_move;
                start_plus_move = move.start.add(ROOK_MOVES[i]);
                if (start_plus_move.equal(move.end))
                {
                    if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                    {
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    else
                    {
                        delete another_board[move.end.get_x()][move.end.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    bool check_status = false;
                    if (times_called == 0)
                    {
                        check_status = is_in_check(player, another_board, move, times_called);
                    }
                    delete_board(another_board);
                    if (check_status == true)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            delete_board(another_board);
            return false;
            break;
        case BISHOP_SYMBOL:
            if (piece_in_between == true)
            {
                delete_board(another_board);
                return false;
            }
            for (int i = 0; i < NUMBER_OF_BISHOP_MOVES; i++)
            {
                Coordinate start_plus_move;
                start_plus_move = move.start.add(BISHOP_MOVES[i]);
                if (start_plus_move.equal(move.end))
                {
                    if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                    {
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    else
                    {
                        delete another_board[move.end.get_x()][move.end.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    bool check_status = false;
                    if (times_called == 0)
                    {
                        check_status = is_in_check(player, another_board, move, times_called);
                    }
                    delete_board(another_board);
                    if (check_status == true)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            delete_board(another_board);
            return false;
            break;
        case KNIGHT_SYMBOL:
            for (int i = 0; i < NUMBER_OF_KNIGHT_MOVES; i++)
            {
                Coordinate start_plus_move;
                start_plus_move = move.start.add(KNIGHT_MOVES[i]);
                if (start_plus_move.equal(move.end))
                {
                    if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                    {
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    else
                    {
                        delete another_board[move.end.get_x()][move.end.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    bool check_status = false;
                    if (times_called == 0)
                    {
                        check_status = is_in_check(player, another_board, move, times_called);
                    }
                    delete_board(another_board);
                    if (check_status == true)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            delete_board(another_board);
            return false;
            break;
        case QUEEN_SYMBOL:
            if (piece_in_between == true)
            {
                delete_board(another_board);
                return false;
            }
            for (int i = 0; i < NUMBER_OF_QUEEN_MOVES; i++)
            {
                Coordinate start_plus_move;
                start_plus_move = move.start.add(QUEEN_MOVES[i]);
                if (start_plus_move.equal(move.end))
                {
                    if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                    {
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    else
                    {
                        delete another_board[move.end.get_x()][move.end.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                        set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    bool check_status = false;
                    if (times_called == 0)
                    {
                        check_status = is_in_check(player, another_board, move, times_called);
                    }
                    delete_board(another_board);
                    if (check_status == true)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            return false;
            break;
        case KING_SYMBOL:
            for (int k = 0; k < NUMBER_OF_KING_MOVES; k++)
            {
                Coordinate start_plus_move;
                start_plus_move = move.start.add(KING_MOVES[k]);
                Move new_move;
                new_move.start = start_plus_move;
                new_move.end = start_plus_move;
                if (start_plus_move.equal(move.end))
                {
                    if (another_board[move.end.get_x()][move.end.get_y()] == nullptr)
                    {
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    else
                    {
                        delete another_board[move.end.get_x()][move.end.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()] = another_board[move.start.get_x()][move.start.get_y()];
                        another_board[move.end.get_x()][move.end.get_y()]->
                            set_num_moves(another_board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
                        another_board[move.start.get_x()][move.start.get_y()] = nullptr;
                    }
                    bool is_attackable = attackable(player, another_board, move.end, new_move, times_called);
                    //cout << board_to_string(another_board) << endl;
                    delete_board(another_board);
                    if (is_attackable == false)
                    {
                        return true;
                    }
                }
            }
            bool is_attackable = attackable(player, board, move.end, last_move, times_called);
            if (is_attackable == true) // Can't castle when in check
            {
                delete_board(another_board);
                return false;
            }
            if (board[move.start.get_x()][move.start.get_y()]->get_num_moves() > 0) // Can't castle if king has moved
            {
                delete_board(another_board);
                return false;
            }
            for (int k = 0; k < NUMBER_OF_CASTLING_MOVES; k++)
            {
                Coordinate start_plus_move;
                if (player == PLAYER1)
                {
                    if (board[WHITE_ROOK_START_CASTLING[k].get_x()][WHITE_ROOK_START_CASTLING[k].get_y()] == nullptr || board[WHITE_ROOK_START_CASTLING[k].get_x()][WHITE_ROOK_START_CASTLING[k].get_y()]->get_num_moves() != 0)
                    {
                        continue;
                    }
                    start_plus_move = move.start.add(WHITE_KING_CASTLING_MOVES[k]);
                }
                else
                {
                    if (board[BLACK_ROOK_START_CASTLING[k].get_x()][BLACK_ROOK_START_CASTLING[k].get_y()] == nullptr || board[BLACK_ROOK_START_CASTLING[k].get_x()][BLACK_ROOK_START_CASTLING[k].get_y()]->get_num_moves() != 0)
                    {
                        continue;
                    }
                    start_plus_move = move.start.add(BLACK_KING_CASTLING_MOVES[k]);
                }
                if (start_plus_move.equal(move.end))
                {
                    if (attackable(player, board, start_plus_move, last_move, times_called))
                    {
                        delete_board(another_board);
                        return false;
                    }
                    if (player == PLAYER1 && attackable(player, board, BETWEEN_WHITE_KING_CASTLING_MOVES[k], last_move, times_called) == true)
                    {
                        delete_board(another_board);
                        return false;
                    }
                    else if (player == PLAYER2 && attackable(player, board, BETWEEN_BLACK_KING_CASTLING_MOVES[k], last_move, times_called) == true)
                    {
                        delete_board(another_board);
                        return false;
                    }
                    Move between_rook_king_move;
                    if (player == PLAYER1)
                    {
                        between_rook_king_move.start = WHITE_ROOK_START_CASTLING[k];
                        between_rook_king_move.end = WHITE_KING_START;
                    }
                    else
                    {
                        between_rook_king_move.start = BLACK_ROOK_START_CASTLING[k];
                        between_rook_king_move.end = BLACK_KING_START;
                    }
                    
                    if (in_between(between_rook_king_move, board) == true)
                    {
                        delete_board(another_board);
                        return false;
                    }
                    delete_board(another_board);
                    return true;
                }
            }
            break;
    }
    delete_board(another_board);
    return false;
}



bool attackable(bool player, Piece *board[][NUMBER_OF_RANKS], Coordinate position, Move last_move, int times_called)
{
    for (int i = 0; i < NUMBER_OF_FILES; i++) // x
    {
        for (int j = 0; j < NUMBER_OF_RANKS; j++) // y
        {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->get_player() == player)
                {
                    continue;
                }
                Coordinate start(i,j);
                Move move;
                move.start = start;
                switch (board[i][j]->get_piece_symbol())
                {
                    case PAWN_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_PAWN_ATTACKS; k++)
                        {
                            if (player == PLAYER1)
                            {
                                move.end = start.add(BLACK_PAWN_ATTACKS[k]);
                            }
                            else
                            {
                                move.end = start.add(WHITE_PAWN_ATTACKS[k]);
                            }
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                    case BISHOP_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_BISHOP_MOVES; k++)
                        {
                            move.end = start.add(BISHOP_MOVES[k]);
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                    case ROOK_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_ROOK_MOVES; k++)
                        {
                            move.end = start.add(ROOK_MOVES[k]);
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                    case QUEEN_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_QUEEN_MOVES; k++)
                        {
                            move.end = start.add(QUEEN_MOVES[k]);
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                    case KING_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_KING_MOVES; k++)
                        {
                            move.end = start.add(KING_MOVES[k]);
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                    case KNIGHT_SYMBOL:
                        for (int k = 0; k < NUMBER_OF_KNIGHT_MOVES; k++)
                        {
                            move.end = start.add(KNIGHT_MOVES[k]);
                            if (move.end.equal(position))
                            {
                                if (valid_move(!player, board, move, last_move, times_called+1))
                                {
                                    return true;
                                }
                            }
                        }
                        break;
                }
            }
        }
    }
    return false;
}


Coordinate find_king(bool player, Piece *board[][NUMBER_OF_RANKS])
{
    for (int x = 0; x < NUMBER_OF_FILES; x++)
    {
        for (int y = 0; y < NUMBER_OF_RANKS; y++)
        {
            if (board[x][y] == nullptr)
            {
                continue;
            }
            else if (board[x][y]->get_piece_symbol() == KING_SYMBOL && board[x][y]->get_player() == player)
            {
                return Coordinate(x,y);
            }
        }
    }
    return Coordinate(-1,-1);
}

bool is_in_check(bool player, Piece *board[][NUMBER_OF_RANKS], Move last_move, int times_called)
{
    Coordinate king_pos;
    king_pos = find_king(player, board);
    if (king_pos.get_x() == -1)
    {
        return false;
        throw "Error: No king found on board.\n";
    }
    else if (attackable(player, board, king_pos, last_move, times_called) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int move_piece(bool player, Piece *board[][NUMBER_OF_RANKS], Move move, Move last_move) // returns true if a promotion is needed
{
    if (valid_move(player, board, move, last_move, 0) == true)
    {
        if (board[move.end.get_x()][move.end.get_y()] == nullptr)
        {
            Piece *piece_ptr = new Piece;
            board[move.end.get_x()][move.end.get_y()] = piece_ptr;
            copy_piece(board[move.start.get_x()][move.start.get_y()], piece_ptr);
            board[move.end.get_x()][move.end.get_y()]->set_num_moves(board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
            delete board[move.start.get_x()][move.start.get_y()];
            board[move.start.get_x()][move.start.get_y()] = nullptr;
        }
        else
        {
            copy_piece(board[move.start.get_x()][move.start.get_y()], board[move.end.get_x()][move.end.get_y()]);
            board[move.end.get_x()][move.end.get_y()]->set_num_moves(board[move.end.get_x()][move.end.get_y()]->get_num_moves()+1);
            delete board[move.start.get_x()][move.start.get_y()];
            board[move.start.get_x()][move.start.get_y()] = nullptr;
        }
        if (board[move.end.get_x()][move.end.get_y()]->get_piece_symbol() == KING_SYMBOL && get_distance(move) == 2)
        {
            Coordinate direction = get_direction(move);
            if (direction.get_x() < 0)
            {
                if (player == PLAYER1)
                {
                    board[WHITE_ROOK_END_CASTLING[0].get_x()][WHITE_ROOK_END_CASTLING[0].get_y()] =
                        board[WHITE_ROOK_START_CASTLING[0].get_x()][WHITE_ROOK_START_CASTLING[0].get_y()];
                    board[WHITE_ROOK_START_CASTLING[0].get_x()][WHITE_ROOK_START_CASTLING[0].get_y()] = nullptr;
                }
                else
                {
                    board[BLACK_ROOK_END_CASTLING[0].get_x()][BLACK_ROOK_END_CASTLING[0].get_y()] =
                        board[BLACK_ROOK_START_CASTLING[0].get_x()][BLACK_ROOK_START_CASTLING[0].get_y()];
                    board[BLACK_ROOK_START_CASTLING[0].get_x()][BLACK_ROOK_START_CASTLING[0].get_y()] = nullptr;
                }
            }
            else
            {
                if (player == PLAYER1)
                {
                    board[WHITE_ROOK_END_CASTLING[1].get_x()][WHITE_ROOK_END_CASTLING[1].get_y()] =
                        board[WHITE_ROOK_START_CASTLING[1].get_x()][WHITE_ROOK_START_CASTLING[1].get_y()];
                    board[WHITE_ROOK_START_CASTLING[1].get_x()][WHITE_ROOK_START_CASTLING[1].get_y()] = nullptr;
                }
                else
                {
                    board[BLACK_ROOK_END_CASTLING[1].get_x()][BLACK_ROOK_END_CASTLING[1].get_y()] =
                        board[BLACK_ROOK_START_CASTLING[1].get_x()][BLACK_ROOK_START_CASTLING[1].get_y()];
                    board[BLACK_ROOK_START_CASTLING[1].get_x()][BLACK_ROOK_START_CASTLING[1].get_y()] = nullptr;
                }
            }
        }
        else if (board[move.end.get_x()][move.end.get_y()]->get_piece_symbol() == PAWN_SYMBOL && get_distance(move) < 2 // En passant player 1
                 && get_distance(move) > 1 && move.end.get_y() == 5 && player == PLAYER1 && board[move.end.get_x()][move.end.get_y()-1] != nullptr &&
                 board[move.end.get_x()][move.end.get_y()-1]->get_player() == PLAYER2 && board[move.end.get_x()][move.end.get_y()-1]->get_num_moves() == 1)
        {
            delete board[move.end.get_x()][move.end.get_y()-1];
            board[move.end.get_x()][move.end.get_y()-1] = nullptr;
        }
        else if (board[move.end.get_x()][move.end.get_y()]->get_piece_symbol() == PAWN_SYMBOL && get_distance(move) < 2 // En passant player 2
                 && get_distance(move) > 1 && move.end.get_y() == 2 && player == PLAYER2 && board[move.end.get_x()][move.end.get_y()+1] != nullptr &&
                 board[move.end.get_x()][move.end.get_y()+1]->get_player() == PLAYER1 &&  board[move.end.get_x()][move.end.get_y()+1]->get_num_moves() == 1)
        {
            delete board[move.end.get_x()][move.end.get_y()+1];
            board[move.end.get_x()][move.end.get_y()+1] = nullptr;
        }
        if (board[move.end.get_x()][move.end.get_y()]->get_piece_symbol() == PAWN_SYMBOL && move.end.get_y() == 7 && // Player 1 promotion
                 player == PLAYER1)
        {
            return 1;
        }
        else if (board[move.end.get_x()][move.end.get_y()]->get_piece_symbol() == PAWN_SYMBOL && move.end.get_y() == 0 && // Player 2 promotion
                 player == PLAYER2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}

bool load_game(const char *filename, Piece *board[][NUMBER_OF_RANKS])
{
    
    fstream ifp;
    char c;
    bool players_turn = true;
    bool current_player = true;
    int num_moves = 0;
    int num_spaces = 0;
    Coordinate position;
    Piece *piece_ptr = nullptr;
    
    int x = 0, y = 8;
    ifp.open(filename, ios::in);
    if (!ifp.is_open())
    {
        cout << "Couldn't open file!\n";
    }
    
    c = ifp.get();
    if (c == '*')
    {
        players_turn = PLAYER2;
    }
    else if (c == '$')
    {
        players_turn = PLAYER1;
    }
    else
    {
        throw "Error: Incorrect file format detected while loading game.\n";
    }
    c = ifp.get();
    while (c != EOF)
    {
        switch(c)
        {
            case '*':
                current_player = PLAYER2;
                break;
            case '$':
                current_player = PLAYER1;
                break;
            case 'f': // first move
                num_moves = 0;
                break;
            case 's': // second move
                num_moves = 1;
                break;
            case 't': // moved more than two times
                num_moves = 2;
                break;
            case ROOK_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(ROOK_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case KNIGHT_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(KNIGHT_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case BISHOP_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(BISHOP_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case QUEEN_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(QUEEN_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case KING_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(KING_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case PAWN_SYMBOL:
                piece_ptr = new Piece;
                piece_ptr->set_num_moves(num_moves);
                piece_ptr->set_player(current_player);
                piece_ptr->set_piece_symbol(PAWN_SYMBOL);
                position.set_x(x);
                position.set_y(y);
                piece_ptr->set_position(position);
                board[x++][y] = piece_ptr;
                break;
            case ' ':
                num_spaces++;
                if (num_spaces == 3)
                {
                    x++;
                    num_spaces = 0;
                }
                break;
            case '\n':
                y--;
                x = 0;
                break;
        }
        c = ifp.get();
    }
    ifp.close();
    return players_turn;

}

void test_valid_moves()
{
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    const char *fp = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/king_attack_protected_piece.test";
    const char *fp1 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/king_attack_piece.test";
    const char *fp2 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_into_check.test";
    const char *fp3 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant.test";
    const char *fp4 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant2.test";
    const char *fp5 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/start_in_check.test";
    const char *fp6 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant3.test";
    const char *fp7 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_out_of_check_by_attacking.test";
    const char *fp8 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling.test";
    const char *fp9 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling2.test";
    const char *fp10 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling3.test";
    const char *fp11 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_pawn1.test";
    const char *fp12 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_pawn2.test";
    const char *fp13 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player2castling.test";
    const char *fp14 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_out_of_check_by_blocking.test";
    const char *fp15 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/in_check.test";
    const char *fp16 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/in_check2.test";
    const char *fp17 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/bug.test";
    
    load_game(fp, board);
    cout << board_to_string(board) << endl;
    Move last_move;
    Coordinate lstart(1,6);
    Coordinate lend(1,4);
    last_move.start = lstart;
    last_move.end = lend;
    Coordinate start(3,2);
    Coordinate end(2,3);
    Move move;
    move.start = start;
    move.end = end;
    cout << "King is attacking protected piece: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp1, board);
    cout << board_to_string(board) << endl;
    cout << "King is attacking protected piece but the piece is protected by a king and the attacking king end in a protected position: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp2, board);
    cout << board_to_string(board) << endl;
    start.set_x(2);
    start.set_y(3);
    end.set_x(1);
    end.set_y(2);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries to attack a pawn using his bishop but that move would cause his king to be in check: Expected result 0: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp3, board);
    cout << board_to_string(board) << endl;
    start.set_x(2);
    start.set_y(4);
    end.set_x(1);
    end.set_y(5);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to attack a pawn using en passant: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp4, board);
    cout << board_to_string(board) << endl;
    start.set_x(2);
    start.set_y(4);
    end.set_x(1);
    end.set_y(5);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to attack a pawn using en passant but would be in check afterwards: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp5, board);
    cout << board_to_string(board) << endl;
    start.set_x(5);
    start.set_y(1);
    end.set_x(5);
    end.set_y(2);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to move a pawn while in check: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp5, board);
    cout << board_to_string(board) << endl;
    start.set_x(3);
    start.set_y(2);
    end.set_x(2);
    end.set_y(1);
    move.start = start;
    move.end = end;
    cout << "Player 1 moves bishop to get king out of check: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp6, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(2);
    end.set_x(1);
    end.set_y(5);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to attack a pawn using en passant but the players last move wasn't moving a pawn: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp7, board);
    cout << board_to_string(board) << endl;
    start.set_x(1);
    start.set_y(6);
    end.set_x(0);
    end.set_y(7);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to attack with bishop but his king is in check: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp7, board);
    cout << board_to_string(board) << endl;
    start.set_x(1);
    start.set_y(6);
    end.set_x(2);
    end.set_y(7);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries to attack with bishop to get his king out of check: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp8, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(0);
    end.set_x(2);
    end.set_y(0);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries castling but ends in check: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp9, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(0);
    end.set_x(2);
    end.set_y(0);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries castling: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp10, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(0);
    end.set_x(2);
    end.set_y(0);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries castling but the king has already moved: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp11, board);
    cout << board_to_string(board) << endl;
    start.set_x(3);
    start.set_y(1);
    end.set_x(3);
    end.set_y(3);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries moving pawn: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp11, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(2);
    end.set_x(4);
    end.set_y(4);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries moving pawn two spaces but the pawn has already moved: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp12, board);
    cout << board_to_string(board) << endl;
    start.set_x(3);
    start.set_y(1);
    end.set_x(3);
    end.set_y(3);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries moving pawn two spaces but there is a pawn in-between: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp12, board);
    cout << board_to_string(board) << endl;
    start.set_x(7);
    start.set_y(1);
    end.set_x(6);
    end.set_y(2);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries moving pawn diangle but it's not an attack: Expected result 0: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp12, board);
    cout << board_to_string(board) << endl;
    start.set_x(1);
    start.set_y(2);
    end.set_x(1);
    end.set_y(3);
    move.start = start;
    move.end = end;
    cout << "Player 1 tries moving pawn: Expected result 1: Actual result " << valid_move(PLAYER1, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp13, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(7);
    end.set_x(6);
    end.set_y(7);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries castling to the right: Expected result 1: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    delete_board(board);
    load_game(fp13, board);
    cout << board_to_string(board) << endl;
    start.set_x(3);
    start.set_y(7);
    end.set_x(0);
    end.set_y(4);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries to move queen dianglely: Expected result 1: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    
    delete_board(board);
    load_game(fp14, board);
    cout << board_to_string(board) << endl;
    start.set_x(6);
    start.set_y(7);
    end.set_x(4);
    end.set_y(6);
    move.start = start;
    move.end = end;
    cout << "Player 2 get out of check by blocking with knight: Expected result 1: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    
    delete_board(board);
    load_game(fp15, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(6);
    end.set_x(4);
    end.set_y(5);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries to move pawn while in check: Expected result 0: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    
    delete_board(board);
    load_game(fp16, board);
    cout << board_to_string(board) << endl;
    start.set_x(4);
    start.set_y(6);
    end.set_x(4);
    end.set_y(5);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries to move pawn while in check: Expected result 0: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    
    delete_board(board);
    load_game(fp17, board);
    cout << board_to_string(board) << endl;
    last_move.start.set_x(3);
    last_move.start.set_y(4);
    last_move.end.set_x(3);
    last_move.end.set_y(7);
    start.set_x(4);
    start.set_y(4);
    end.set_x(3);
    end.set_y(2);
    move.start = start;
    move.end = end;
    cout << "Player 2 tries to move knight while in check: Expected result 0: Actual result " << valid_move(PLAYER2, board, move, last_move, 0) << endl;
    
    delete_board(board);
}

void test_moves()
{
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    
    const char *fp = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/king_attack_protected_piece.test";
    const char *fp1 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/king_attack_piece.test";
    const char *fp2 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_into_check.test";
    const char *fp3 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant.test";
    const char *fp4 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant2.test";
    const char *fp5 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/start_in_check.test";
    const char *fp6 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/enpassant3.test";
    const char *fp7 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_out_of_check_by_attacking.test";
    const char *fp8 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling.test";
    const char *fp9 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling2.test";
    const char *fp10 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player1castling3.test";
    const char *fp11 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_pawn1.test";
    const char *fp12 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_pawn2.test";
    const char *fp13 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/player2castling.test";
    const char *fp14 = "/Users/darlenemiller/Dropbox/FirstApp/Chess/Chess/moving_out_of_check_by_blocking.test";
    
    
    load_game(fp7, board);
    cout << board_to_string(board) << endl;
    Move last_move;
    Coordinate lstart(1,6);
    Coordinate lend(1,4);
    last_move.start = lstart;
    last_move.end = lend;
    Coordinate start(1,6);
    Coordinate end(2,7);
    Move move;
    move.start = start;
    move.end = end;
    int move_result = move_piece(PLAYER1, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp9, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(4);
    move.start.set_y(0);
    move.end.set_x(2);
    move.end.set_y(0);
    move_result = move_piece(PLAYER1, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp8, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(4);
    move.start.set_y(0);
    move.end.set_x(2);
    move.end.set_y(0);
    move_result = move_piece(PLAYER1, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp3, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(2);
    move.start.set_y(4);
    move.end.set_x(1);
    move.end.set_y(5);
    move_result = move_piece(PLAYER1, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp13, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(4);
    move.start.set_y(7);
    move.end.set_x(6);
    move.end.set_y(7);
    move_result = move_piece(PLAYER2, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp13, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(3);
    move.start.set_y(7);
    move.end.set_x(0);
    move.end.set_y(4);
    move_result = move_piece(PLAYER2, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
    
    load_game(fp14, board);
    cout << board_to_string(board) << endl;
    move.start.set_x(6);
    move.start.set_y(7);
    move.end.set_x(4);
    move.end.set_y(6);
    move_result = move_piece(PLAYER2, board, move, last_move);
    cout << move_result << endl;
    cout << board_to_string(board) << endl;
    delete_board(board);
}

string print_coordinate(Coordinate coordinate)
{
    string coordinate_string = "(";
    coordinate_string += to_string(coordinate.get_x());
    coordinate_string += ", ";
    coordinate_string += to_string(coordinate.get_y());
    coordinate_string += ")";
    return coordinate_string;
}

string print_move(Move move)
{
    string move_string = print_coordinate(move.start);
    move_string += "->";
    move_string += print_coordinate(move.end);
    return move_string;
}

int get_moves(bool player, Coordinate start, Move moves[], Piece *board[][NUMBER_OF_RANKS], Move last_move)
{
    int x = start.get_x(), y = start.get_y();
    if (board[x][y] == nullptr || board[x][y]->get_player() != player)
    {
        return 0;
    }
    
    Move move;
    move.start = start;
    int index = 0;
    
    switch (board[x][y]->get_piece_symbol())
    {
        case PAWN_SYMBOL:
            for (int k = 0; k < NUMBER_OF_PAWN_ATTACKS; k++)
            {
                if (player == PLAYER1)
                {
                    move.end = start.add(WHITE_PAWN_ATTACKS[k]);
                }
                else
                {
                    move.end = start.add(BLACK_PAWN_ATTACKS[k]);
                }
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            if (player == PLAYER1)
            {
                move.end = start.add(WHITE_PAWN_MOVE);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
                move.end = start.add(WHITE_PAWN_FIRST_MOVE);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            else
            {
                move.end = start.add(BLACK_PAWN_MOVE);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
                move.end = start.add(BLACK_PAWN_FIRST_MOVE);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
        case BISHOP_SYMBOL:
            for (int k = 0; k < NUMBER_OF_BISHOP_MOVES; k++)
            {
                move.end = start.add(BISHOP_MOVES[k]);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
        case ROOK_SYMBOL:
            for (int k = 0; k < NUMBER_OF_ROOK_MOVES; k++)
            {
                move.end = start.add(ROOK_MOVES[k]);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
        case QUEEN_SYMBOL:
            for (int k = 0; k < NUMBER_OF_QUEEN_MOVES; k++)
            {
                move.end = start.add(QUEEN_MOVES[k]);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
        case KING_SYMBOL:
            for (int k = 0; k < NUMBER_OF_KING_MOVES; k++)
            {
                move.end = start.add(KING_MOVES[k]);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
        case KNIGHT_SYMBOL:
            for (int k = 0; k < NUMBER_OF_KNIGHT_MOVES; k++)
            {
                move.end = start.add(KNIGHT_MOVES[k]);
                if (valid_move(player, board, move, last_move, 0))
                {
                    moves[index++] = move;
                }
            }
            break;
    }

    return index;
}

int get_all_moves(bool player, Move moves[], Piece *board[][NUMBER_OF_RANKS], Move last_move)
{
    int index = 0;
    for (int x = 0; x < NUMBER_OF_FILES; x++)
    {
        for (int y = 0; y < NUMBER_OF_RANKS; y++)
        {
            Coordinate start(x,y);
            index += get_moves(player, start, &(moves[index]), board, last_move);
        }
    }
    return index;
}

void test_get_all_moves()
{
    Coordinate start(0,6);
    Move moves[200];
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    start_new_game(board);
    cout << board_to_string(board) << endl;
    Move last_move;
    last_move.start = start;
    last_move.end = start;
    int num_moves = get_all_moves(PLAYER1, moves, board, last_move);
    cout << num_moves << endl;
    for (int i = 0; i < num_moves; i++)
    {
        cout << print_move(moves[i]) << endl;
    }
    
    delete_board(board);
}

int new_game()
{
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    start_new_game(board);
    delete_board(board);
    return 1;
}

void test_print_move()
{
    Move move;
    Coordinate start(0,0);
    Coordinate end(1,1);
    move.start = start;
    move.end = end;
    cout << print_move(move);
}

void test_get_moves()
{
    Coordinate start(0,6);
    Move moves[100];
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    start_new_game(board);
    cout << board_to_string(board) << endl;
    Move last_move;
    last_move.start = start;
    last_move.end = start;
    int num_moves = get_moves(PLAYER2, start, moves, board, last_move);
    cout << num_moves << endl;
    for (int i = 0; i < num_moves; i++)
    {
        cout << print_move(moves[i]) << endl;
    }
    
    delete_board(board);
}

Move get_move_func()
{
    Move move;
    string string_move;
    int sx=-1,sy=-1,ex=-1,ey=-1;
    bool valid = false;
    do
    {
        sx=-1,sy=-1,ex=-1,ey=-1;
        cout << "Enter move i.e. (1, 3)->(2, 3)\n";
        getline(cin, string_move);
        if (isdigit(string_move[1]) && isdigit(string_move[4]) && isdigit(string_move[9]) && isdigit(string_move[12]))
        {
            valid = true;
        }
    }while(!valid);
    sx = string_move[1] - '0';
    sy = string_move[4] - '0';
    ex = string_move[9] - '0';
    ey = string_move[12] - '0';
    Coordinate start(sx, sy);
    Coordinate end(ex, ey);
    move.start = start;
    move.end = end;
    return move;
    
}

void test_get_move()
{
    cout << print_move(get_move_func());
}

int get_promotion_func()
{
    cout << "What would you like to promote your pawn to? (Enter number e.g. 1)" << endl;
    cout << "1 Rook" << endl;
    cout << "2 Knight" << endl;
    cout << "3 Bishop" << endl;
    cout << "4 Queen" << endl;
    bool valid = false;
    int choice = 4;
    string tmp;
    while (!valid)
    {
        getline(cin, tmp);
        char tmp2 = tmp[0];
        if (isdigit(tmp2))
        {
            choice = tmp2 - '0';
            if (choice >= 1 && choice <= 4)
            {
                valid = true;
            }
        }
    }
    return choice;
}

void promote(Piece *board[][NUMBER_OF_RANKS], Move last_move, int promotion_number)
{
    switch (promotion_number)
    {
    case 1: // Rook
        board[last_move.end.get_x()][last_move.end.get_y()]->set_piece_symbol(ROOK_SYMBOL);
        break;
    case 2: // Knight
        board[last_move.end.get_x()][last_move.end.get_y()]->set_piece_symbol(KNIGHT_SYMBOL);
        break;
    case 3: // Bishop
        board[last_move.end.get_x()][last_move.end.get_y()]->set_piece_symbol(BISHOP_SYMBOL);
        break;
    default: // 4 queen
        board[last_move.end.get_x()][last_move.end.get_y()]->set_piece_symbol(QUEEN_SYMBOL);
        break;
    }
}

void game()
{
    bool turn = PLAYER1;
    Piece *board[NUMBER_OF_FILES][NUMBER_OF_RANKS] =
    {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };
    start_new_game(board);
    Move moves[200];
    Move move;
    Move last_move;
    last_move.start = Coordinate(-1,-1);
    last_move.end = Coordinate(-1,-1);
    int num_moves = get_all_moves(turn, moves, board, last_move);
    Player player1;
    player1.set_player(PLAYER1);
    Computer_Player player2;
    player2.set_player(PLAYER2);
    bool valid = false;
    int is_promotion = 0;
    int promotion_number = 0;
    while(num_moves != 0)
    {
        cout << board_to_string(board) << endl << endl;
        if (turn == PLAYER1)
        {
            while (!valid)
            {
                move = player1.get_move(board, last_move);
                valid = valid_move(player1.get_player(), board, move, last_move, 0);
            }
            is_promotion = move_piece(player1.get_player(), board, move, last_move);
            if (is_promotion == 1)
            {
                promotion_number = player1.get_promotion(board, move);
                promote(board, move, promotion_number);
            }
        }
        else
        {
            while (!valid)
            {
                move = player2.get_move(board, last_move);
                valid = valid_move(player2.get_player(), board, move, last_move, 0);
            }
            is_promotion = move_piece(player2.get_player(), board, move, last_move);
            if (is_promotion == 1)
            {
                promotion_number = player2.get_promotion(board, move);
                promote(board, move, promotion_number);
            }
        }
        last_move = move;
        turn = !turn;
        num_moves = get_all_moves(turn, moves, board, last_move);
        valid = false;
    }
    
    cout << board_to_string(board) << endl << endl;
    delete_board(board);
    if (turn == PLAYER1)
    {
        cout << "PLAYER 2 WINS!\n";
    }
    else
    {
        cout << "PLAYER 1 WINS!\n";
    }
}

int main(int argc, const char * argv[]) {
    //test_valid_moves();
    game();
    return 0;
}


