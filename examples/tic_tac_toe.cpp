#include <clairvoyant.hpp>

#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>

template<typename T, int R, int C = R> using Matrix = std::array<std::array<T, C>, R>;

struct TicTacToe {
    
    using Square = char;
    using Player = Square;
    using Move = Square;
    
    static const Player player1 = 'x', player2 = 'o';
    
    enum Status {
        Playing,
        Winner,
        Tie
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
        
        for (auto row : board.squares) {
            for (auto square : row) {
                if (!(square == player1 || square == player2)) {
                    moves.push_back(square);
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
        
        if (TicTacToe::legal_moves(board).empty()) {
            return Status::Tie;
        }
        
        return Status::Playing;
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


struct AI {
    
    using EdgeGraph = cvt::graph::EdgeGraph<TicTacToe::Board, TicTacToe::Move>;
    using Callback = std::function<std::vector<std::pair<TicTacToe::Move, TicTacToe::Board> >(TicTacToe::Board)>;
    using DynamicGraph = cvt::graph::DynamicGraph<EdgeGraph, Callback>;
    using Cost = int;
    using Clairvoyant = cvt::Clairvoyant<DynamicGraph, Cost>;
    
    Clairvoyant clairvoyant;
    TicTacToe::Player player;
    
    //DynamicGraph::Callback callback;
    
    AI (TicTacToe::Player player) {
        
        this->player = player;

        auto callback = [](TicTacToe::Board board) { 
            
            std::cout << "1";
            
            std::vector<std::pair<TicTacToe::Move, TicTacToe::Board> > moves;
            for (auto move : TicTacToe::legal_moves(board)) {
                moves.push_back(std::make_pair(move, TicTacToe::make_move(board, move)));
            }
            
            return moves;
        };
        
        
        DynamicGraph graph = { EdgeGraph(), callback };
        
        Clairvoyant clairvoyant;
        clairvoyant.graph = graph;
        
        graph[TicTacToe::Board()];
    }
    
    TicTacToe::Move next_move(const TicTacToe::Board &board) {
        std::cout << "5";
        clairvoyant.update(board);
        std::cout << "5.1";
        
        TicTacToe::Player player = this->player;
        
        auto completed = [player](TicTacToe::Board board){ 
            std::cout << "2";
            return TicTacToe::status(board) == TicTacToe::Status::Winner && TicTacToe::winner(board) == player;
        };
        
        auto cost_function = [](TicTacToe::Board board, typename DynamicGraph::Type t) -> Cost { std::cout << "3"; return 0; };
        
        auto cost_heuristic = [player](TicTacToe::Board board) -> Cost {
            std::cout << "4";
            if (TicTacToe::status(board) == TicTacToe::Status::Winner) {
                if (TicTacToe::winner(board) == player) {
                    return -1;
                } else return 1;
            }
            
            return 0;
        };
        
        auto best = clairvoyant.best(board, completed, cost_function, cost_heuristic);
        std::cout << "5.2";
        return best;
    }
    
};




int main() {
    TicTacToe::Board board;
    
    TicTacToe::Status status = TicTacToe::status(board);
    
    std::cout << "6";
    
    AI ai(TicTacToe::player1);
    
    do {
        std::cout << TicTacToe::board_str(board) << std::endl;
        
        TicTacToe::Move move;
        if (board.active == ai.player) {
            std::cout << "Ai: ";
            move = ai.next_move(board);
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
    
    switch (status) {
        
        case TicTacToe::Status::Winner:
            std::cout << "Winner is " << TicTacToe::winner(board) << "!" << std::endl; 
            break;
        
        default:
            std::cout << "Game over." << std::endl;
    }
    
    return 0;
}
