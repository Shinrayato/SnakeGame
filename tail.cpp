#include "tail.h"

Tail::Tail(const QPointF& tail_first_el_pos, QObject *parent)
{
    //указатель на родительскую сцену, нужен для передачи в конструктор части хвоста, при добавлении нового элемента в него
    m_tail.emplace_back(tail_first_el_pos);
}

Tail::~Tail()
{
    qDebug() << "Destructor tail";
}


void Tail::moveTail(const QPointF previous_head_pos)
{
    if(m_tail.size() != 0)
    {
        QPointF temp = previous_head_pos;//инициализация временной переменной предыдущей позицией головы
        end_tail_previous_pos = m_tail.back().pos();//запоминаем позицию крайнего элемента хвоста до смещения
        QPointF prev_patr_pos;//предыдущая позиция элемента
        for (auto tail_part = m_tail.begin(); tail_part !=  m_tail.end(); ++tail_part)
        {
            prev_patr_pos = tail_part->pos();//запись позиции элемента хвоста до ее смены
            tail_part->setPos(temp);//установка новой позиции хвоста, которая была объявлена во временной переменной
            temp = prev_patr_pos;//перезапись временной позиции хвоста
        }
    }
}

void Tail::growTail()
{
    m_tail.emplace_back(end_tail_previous_pos);
}

int Tail::getTailSize()
{
    return m_tail.size();
}

TailPart *Tail::getEndofTail()
{
    return &this->m_tail.back();
}

std::list<TailPart> &Tail::getTailList()
{
    return this->m_tail;
}
