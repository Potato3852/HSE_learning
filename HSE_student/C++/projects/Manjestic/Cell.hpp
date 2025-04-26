#ifndef CELL_HPP
#define CELL_HPP

class Cell {
private:
    bool alive;
public:
    Cell() : alive(false) {}
    bool isAlive() const { return alive; }
    void setState(bool state) { alive = state; }
};

#endif // CELL_HPP