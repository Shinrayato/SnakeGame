#ifndef TAIL_H
#define TAIL_H

#include "list"

//my includes
#include "tailpart.h"

class Tail
{
public:
    Tail(const QPointF& tail_first_el_pos, QObject *parent = nullptr);
    ~Tail();
    void moveTail(const QPointF previous_head_pos);//метод отвечающий за перемещение хвоста, принимает в себя предыдущую позицию головы
    void growTail();//метод роста хвоста
    int getTailSize();
    TailPart* getEndofTail();
    std::list<TailPart>& getTailList();


private:
    std::list<TailPart> m_tail;//сам хвост, вектор из частей хвоста
    QPointF end_tail_previous_pos;
};

#endif // TAIL_H
