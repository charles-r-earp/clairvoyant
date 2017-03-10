#include <clairvoyant.hpp>

#include <sstream>

template<typename T, int R, int C = R> using Matrix = std::array<std::array<T, C>, R>;

class TicTacToe {
    
    using Square = char;
    using Player = Square;
    using Move = Square;
    
    public: using Board = Matrix<Square, 3>;
    
    public: static const Player Player1 = 'x', Player2 = 'o';
    
    public: inline Board get_board() {
        return this->board;
    }
    
    public: inline static std::vector<Move> legal_moves(const Board& board) {
        std::vector<Move> moves;
        
        for (auto row : board) {
            for (auto square : row) {
                if (!(square == Player1 || square == Player2)) {
                    moves.push_back(square);
                }
            }
        }
        
        return moves;
    }
    
    public: inline static std::string board_str(const Board& board) {
        std::stringstream ss;
        
        int r = 1;
        for (auto row : board) {
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
    
    private: Board board = {{ 
        {'1', '2', '3'}, 
        {'4', '5', '6'}, 
        {'7', '8', '9'} 
    }};
};



int main() {
    TicTacToe game;
    
    std::cout << TicTacToe::board_str(game.get_board()) << std::endl;
}