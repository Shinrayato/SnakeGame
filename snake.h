#ifndef SNAKE_H
#define SNAKE_H

#include "memory"
//my includes
#include "head.h"
#include "tail.h"



class Snake
{
public:
    explicit Snake(const QPointF& head_pos, const QPointF& tail_first_el_pos);
    ~  Snake();
    Head* GetHead();
    Tail* GetTail();

    void moveSnake(const QPointF& apple_pos);//метод движения змеи

private:

    Head* m_head;
    std::unique_ptr<Tail> m_tail;

};

#endif // SNAKE_H
