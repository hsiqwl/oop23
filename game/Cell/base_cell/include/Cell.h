#ifndef LAB3_CELL_H
#define LAB3_CELL_H

class Cell{
public:
    enum class Type{
        door,
        floor,
        lava,
        essence,
        stairs,
        wall
    };
    Cell();
    Cell(Type type_);
    void set_type(Type type_){type = type_;};
    Type get_type() const {return type;};
    bool if_movable_to() const {return is_movable_to;};
    void set_if_movable_to(bool flag){is_movable_to = flag;};
    virtual ~Cell() = default;
private:
    bool is_movable_to;
    Type type;
};


#endif //LAB3_CELL_H
