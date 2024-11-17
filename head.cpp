#include "head.h"

Head::Head(const QPointF& head_pos,QObject *parent) : QObject(parent), QGraphicsItem()
{
    m_dir_now = Dir::right;
    this->setPos(head_pos);
}

Head::~Head()
{
    qDebug() << "Destructor head";
}

QRectF Head::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Head::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(-10,-10,20,20);
    painter->setRenderHint(QPainter::Antialiasing);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Head::keyPressEvent(QKeyEvent *event)
{
    //здесь происходит обработка событий нажаитя на кнопки управления змейкой
    if(event->key() == Qt::Key_W)
    {
        if(this->y() > m_previous_pos.y()  || this->y() == 10 && m_previous_pos.y() == 390)//запрет на движение в первый элемент хвоста
        {
            return;
        }
        else{ m_dir_now = Dir::up;}//установка нового направления
    }
    if(event->key() == Qt::Key_A)
    {
        if(this->x() > m_previous_pos.x()  || this->x() == 10 && m_previous_pos.x() == 390)//запрет на движение в первый элемент хвоста
        {
            return;
        }
        else{m_dir_now = Dir::left;}//установка нового направления
    }
    if(event->key() == Qt::Key_D)
    {
        if(this->x() < m_previous_pos.x() || this->x() == 390 && m_previous_pos.x() == 10)//запрет на движение в первый элемент хвоста
        {
            return;
        }
        else{m_dir_now = Dir::right;}//установка нового направления
    }
    if(event->key() == Qt::Key_S)
    {
        if(this->y() < m_previous_pos.y() || this->y() == 390 && m_previous_pos.y() == 10)//запрет на движение в первый элемент хвоста
        {
            return;
        }
        else{m_dir_now = Dir::down;}//установка нового направления
    }
}

void Head::keyReleaseEvent(QKeyEvent *event)
{

}

void Head::setPreviousPos(const QPointF &previous_pos)
{
    m_previous_pos = previous_pos;
}


void Head::checkDirUp()
{
    //создаем новую позицию для проверок, присваеваем значение актуальбной позиции
    QPointF new_pos = this->pos();

     new_pos.setY(new_pos.y()-20);//новая позиция в соотвествии с направлением

        if(this->y() == 10)//если текущая позиция хоста уже была в самом верху
        {
            //присваиваем значение актуальной позиции в предыдущую позицию для передачи хвосту далее
            m_previous_pos = this->pos();
            this->setY(390);//устанавливаем позицию в самый низ поля
        }
        else
        {
            //если все впорядке, просто устанавливаем новую позицию, в предыдущий сохраняем текущую
            m_previous_pos = this->pos();
            this->setY(this->y()-20);
        }

}

void Head::checkDirDown()
{
    //создаем новую позицию для проверок, присваеваем значение актуальбной позиции
    QPointF new_pos = this->pos();

     new_pos.setY(new_pos.y()+20);//новая позиция в соотвествии с направлением

    if(this->y() == 390)//если текущая позиция хоста уже была в самом верху
    {
        //присваиваем значение актуальной позиции в предыдущую позицию для передачи хвосту далее
        m_previous_pos = this->pos();
        this->setY(10);//устанавливаем позицию в самый низ поля
    }
    else
    {
        //если все впорядке, просто устанавливаем новую позицию, в предыдущий сохраняем текущую
        m_previous_pos = this->pos();
        this->setY(this->y()+20);
    }

}

void Head::checkDirLeft()
{
    //создаем новую позицию для проверок, присваеваем значение актуальбной позиции
    QPointF new_pos = this->pos();

    new_pos.setX(new_pos.x()-20);//новая позиция в соотвествии с направлением

    if(this->x() == 10)//если текущая позиция хоста уже была в самом верху
    {
        //присваиваем значение актуальной позиции в предыдущую позицию для передачи хвосту далее
        m_previous_pos = this->pos();
        this->setX(390);//устанавливаем позицию в самый низ поля
    }
    else
    {
        //если все впорядке, просто устанавливаем новую позицию, в предыдущий сохраняем текущую
        m_previous_pos = this->pos();
        this->setX(this->x()-20);
    }

}

void Head::checkDirRight()
{
    //создаем новую позицию для проверок, присваеваем значение актуальбной позиции
    QPointF new_pos = this->pos();

    new_pos.setX(new_pos.x()+20);//новая позиция в соотвествии с направлением

    if(this->x() == 390)//если текущая позиция хоста уже была в самом верху
    {
        //присваиваем значение актуальной позиции в предыдущую позицию для передачи хвосту далее
        m_previous_pos = this->pos();
        this->setX(10);//устанавливаем позицию в самый низ поля
    }
    else
    {
        //если все впорядке, просто устанавливаем новую позицию, в предыдущий сохраняем текущую
        m_previous_pos = this->pos();
        this->setX(this->x()+20);
    }

}

const QPointF &Head::getPreviousPos()
{
    return m_previous_pos;
}


const QPointF& Head::Move()
{   
    switch (m_dir_now)
 {
    case Dir::up:
    {      
        checkDirUp();//проверка позиции вверх
        break;
    }
    case Dir::left:
    {
        checkDirLeft();//проверка позиции влево
        break;
    }
    case Dir::right:
    {
        checkDirRight();//проверка позиции вправо
        break;
    }
    case Dir::down:
    {      
        checkDirDown();//проверка позиции вниз
        break;
    }
  }
    return m_previous_pos;
}
