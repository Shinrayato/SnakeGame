#include "snake.h"

Snake::Snake(const QPointF& head_pos, const QPointF& tail_first_el_pos)
{
    m_head = new Head(head_pos);

    m_tail = std::make_unique<Tail>(tail_first_el_pos);
}

Snake::~Snake()
{
  qDebug() << "Destructor Snake";
}

void Snake::moveSnake(const QPointF& apple_pos)
{
    m_tail->moveTail(m_head->Move());

    if(this->GetHead()->pos() == apple_pos)//если позиция головы и яблока совпали
    {
        m_tail->growTail();//рост хвоста
        emit this->GetHead()->signal_apple_eating();//излучение сигнала по поедании яблока
    }

    auto i = m_tail->getTailList().cbegin();
    ++i;
    for (; i != m_tail->getTailList().cend(); ++i)
    {
        if(m_head->pos() == i->pos())//если позиция головы совпала с позицией элемета хвоста
        {
            emit this->GetHead()->signal_tail_eating();//излучение сигнала о поедании хвоста
        }
    }
}

Head *Snake::GetHead()
{
    return m_head;
}

Tail *Snake::GetTail()
{
    return &*m_tail;
}
