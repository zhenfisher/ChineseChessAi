#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "stone.h"

#define MAXIMIZER_COLOR -1 //default maximizer color is -1

class chessboard : public QObject
{
    Q_OBJECT

public:
    // chessboard();
    chessboard(bool is_show_=true);
    chessboard(const chessboard&);
    chessboard(const chessboard &, bool);
    chessboard& operator=(const chessboard&);
    void init();


    Stone *get(int x, int y) { return c[x][y]; }
    int getVertical() { return vertical; }
    std::vector<Stone *> getStones() const;
    std::vector<move_type> getMoves_quick();
    std::vector<move_type> getMoves();
    move_type greedyMove(std::vector<move_type> &);
    void sortMoves(std::vector<move_type> &);
    int getid(int x, int y)
    {
        if (c[x][y] != NULL)
            return c[x][y]->get();
        return 0;
    }
    move_type getLastMove(){
        if (!records.empty()){
            return records.top();
        }
        return {{-1,-1},{-1,-1}};
    }
    void setShow(bool is_show_) { is_show = is_show_; }


    void show();
    void play();
    bool judge(move_type candidate_move);
    bool judge(int startx, int starty, int aimx, int aimy);
    void move_quick(move_type candidate_move);
    void move_quick(int startx, int starty, int aimx, int aimy);
    bool move(move_type candidate_move);
    bool move(int startx, int starty, int aimx, int aimy);
    void dummy_move();
    void random_move();
    int boardEval(int);
    int boardEvalNegMax();
    int boardPosEval();
    bool isVolatile(){ return capturedStones.find(records.size()-1) != capturedStones.end(); }
    std::string boardHash();
    ~chessboard(); //析构函数

public:

    static const char chessword[15][4];
    static const int stonevalue[15];
    static const unsigned int random_seed;
    static std::unordered_map<int, std::vector<std::vector<int>>> stone2val;
    int color;         //current player color, red: -1, black: 1
    int vertical;      // first hand vertical position, -1: down, 1: up
    bool game_running; //判断结束
    bool is_show;      //computer self played chessboard will not be shown


private:
    // Stone *c[10][9];//用指针调用各个棋子，实现多态
    // std::vector<std::vector<Stone*>> c(10, std::vector<Stone*>(9,nullptr));
    std::vector<std::vector<Stone *>> c;
    std::stack<move_type> records;
    std::map<int, Stone *> capturedStones;
    std::multiset<std::string> seen;
    

private:
    //utility methods
    bool checkCycle(int,int,int,int);
    void readBoard();
    void readPosVal();
    void flipMat(std::vector<std::vector<int>>&);
    void placeStone(int color_, int vertical_);

signals:
    void update();


public slots:
    void undo();
    void flip();
};

#endif // GAMEENGINE_H
