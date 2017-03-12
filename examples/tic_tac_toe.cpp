#include <clairvoyant.hpp>

#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <memory>

template<typename T, int R, int C = R> using Matrix = std::array<std::array<T, C>, R>;

struct TicTacToe {
    
    using Square = char;
    using Player = Square;
    using Move = Square;
    
    static const Player player1 = 'x', player2 = 'o';
    
    enum Status {
        Playing = 'P',
        Winner = 'W',
        Tie = 'T'
    };
    
    struct Board {
        Matrix<Square, 3> squares = {{
            {'1', '2', '3'}, 
            {'4', '5', '6'}, 
            {'7', '8', '9'} 
        }};
        Player active = player1;
    };
    
    static inline std::pair<int, int> coord(const Move &move) {
        int index = int(move) - int('0') - 1; 
        
        int row = index / 3;
        int col = index % 3;
        
        return std::make_pair(row, col);
    }
    
    static inline Board make_move(Board board, const Move& move) {
        
        auto coordinates = coord(move);
        int row = coordinates.first;
        int col = coordinates.second;
        
        board.squares[row][col] = board.active;
        
        // next player's turn 
        board.active = board.active == player1 ? player2 : player1; 
        
        return board;
    }
    
    public: inline static std::vector<Move> legal_moves(const Board& board) {
        
        std::vector<Move> moves;
        
        if (TicTacToe::status(board) == TicTacToe::Status::Playing) {
            for (auto row : board.squares) {
                for (auto square : row) {
                    if (!(square == player1 || square == player2)) {
                        moves.push_back(square);
                    }
                }
            }
        }
        
       
        
        return moves;
    }
    
    public: inline static bool is_legal(const Board& board, const Move& move) {
        std::vector<Move> moves = legal_moves(board);
        return std::find(moves.begin(), moves.end(), move) != moves.end();
    }
    
    inline static Player winner(const Board& board) {
        return (board.active == TicTacToe::player1 ? TicTacToe::player2 : TicTacToe::player1);
    }
    
    inline static Status status(const Board& board) {
        using RowOf3 = std::array<Move, 3>;
        
        std::vector<RowOf3> combinations = {{
            {0,1,2},
            {3,4,5},
            {6,7,8},
            {0,3,6},
            {1,4,7},
            {2,5,8},
            {0,4,8},
            {2,4,6} 
        }}; // winning possibilities
        
        for (auto rowOf3 : combinations) {
            auto get_square = [&board](int index){ 
                int row = index / 3;
                int col = index % 3;
                
                return board.squares[row][col];
            };
            
            Square s1 = get_square(rowOf3[0]);
            Square s2 = get_square(rowOf3[1]);
            Square s3 = get_square(rowOf3[2]);
            
            if (s1 == s2 && s2 == s3) return Status::Winner;
        }
        
        for (auto row : board.squares) {
            for (auto s : row) {
                if (!(s == TicTacToe::player1 || s == TicTacToe::player2)) {
                    return Status::Playing;
                }
            }
        }
        
        return Status::Tie;
    }
    
    
    
    inline static std::string board_str(const Board& board) {
        std::stringstream ss;
        
        int r = 1;
        for (auto row : board.squares) {
            ss << " ";
            int c = 1;
            for (auto square : row) {
                ss << square;
                if (c++ < 3) ss << " | ";
            }
            ss << std::endl;
            if (r++ < 3) ss << "---|---|---" << std::endl;
        }
        
        return ss.str();
    }
};

bool operator<(const TicTacToe::Board &a, const TicTacToe::Board &b) {
    return a.squares < b.squares;
}


class AI {
    
    using Board = TicTacToe::Board;
    using Move = TicTacToe::Move;
    using Cost = int;
    /*
    cvt::dynamic_graph<Board, Move> graph;
    
    public: AI() {
        
        graph.callback = [](const Board &board){
                
            auto moves = TicTacToe::legal_moves(board);
            std::vector<std::pair<Move, Board> > connections; 

            for (auto move : moves) {
                connections.push_back(std::make_pair(move, TicTacToe::make_move(board, move)) );
            }

            return connections;
        };
        
            
    }*/
    
    public: Move best_move(Board board) {
        
        std::set<Board> visited;
        
        auto moves = TicTacToe::legal_moves(board);
        
        // Wins
        
        std::cout << "Searching Wins...\n";
        
        for (Move move : moves) {
            
            Board future = this->find_win(board, move, visited);
            
            if (TicTacToe::status(future) == TicTacToe::Status::Winner) {

                if (board.active == TicTacToe::winner(future)) {

                    return move;
                }
                
            }
        
        }
        
        std::cout << "Searching Draws...\n";
        
        // Draws
        
        for (Move move : moves) {
            
            Board future = this->find_win(board, move, visited);
            
            if (TicTacToe::status(future) == TicTacToe::Status::Tie) {

                return move;
                
            }
            
        }
        
        return moves.front();
    }
    
    Board find_win(Board board, Move move, std::set<Board> &visited) {
        
        if (visited.count(board)) {
            return board;
        }
        
        visited.insert(board);
        
        std::cout << TicTacToe::board_str(board) << std::endl;
        
        Board next = TicTacToe::make_move(board, move);
            
        if (TicTacToe::status(next) != TicTacToe::Playing) {
            return next;
        }
        
        auto moves = TicTacToe::legal_moves(board);
        
        // Wins
        
        for (Move move : moves) {
            
            Board future = find_win(next, move, visited);
            
            if (TicTacToe::status(future) == TicTacToe::Status::Winner) {

                if (board.active == TicTacToe::winner(future)) {

                    return future;
                }
                
            }
        }
        /*
        // Draws
        
        for (Move move : moves) {
            
            Board future = this->find_win(board, move);
            
            if (TicTacToe::status(future) == TicTacToe::Status::Tie) {

                return future;
                
            }
        }*/
        
        
        
        return next;
        
    }
    
};




int main() {
    TicTacToe::Board board;
    
    TicTacToe::Status status = TicTacToe::status(board);
    
    AI ai;
    
    do {
        std::cout << TicTacToe::board_str(board) << std::endl;
        
        TicTacToe::Move move;
        if (board.active == TicTacToe::player2) {
            std::cout << "Ai: ";
            move = ai.best_move(board);
            std::cout << move << std::endl;
        }
        else {
            std::cout << "Move: ";
            std::cin >> move;
        }
        
        if (TicTacToe::is_legal(board, move)) {
            board = TicTacToe::make_move(board, move);
        }
        else std::cout << "Illegal move!" << std::endl;
    
        status = TicTacToe::status(board);
        
    } while (status == TicTacToe::Status::Playing);
    
     std::cout << TicTacToe::board_str(board) << std::endl;
    
    switch (status) {
        
        case TicTacToe::Status::Winner:
            std::cout << "Winner is " << TicTacToe::winner(board) << "!" << std::endl; 
            break;
        
        default:
            std::cout << "Game over." << std::endl;
    }
    
    return 0;
}
