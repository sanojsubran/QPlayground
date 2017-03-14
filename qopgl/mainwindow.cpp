#include <QPainter>
#include <QPaintEvent>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Layout( new QVBoxLayout() )
    , m_mainWidget( new QWidget( this ) )
    , m_glWidget( new CGLWidget( this ) )
    , m_combo( new QComboBox( this ) )
{
    m_glWidget->setFixedSize( 300, 250 );
    m_combo->addItem( "Line" );
    m_combo->addItem( "Rectangle" );
    m_combo->addItem( "Circle" );
    m_Layout->addWidget( m_combo );
    m_Layout->addWidget( m_glWidget );
    m_mainWidget->setLayout( m_Layout );
    setCentralWidget( m_mainWidget );
    setFixedSize( 400, 300 );
    QObject::connect( m_combo, SIGNAL( currentTextChanged(const QString & ) ),
                      this, SLOT( onCurrentIndexChanged(const QString & )),
                      Qt::UniqueConnection );
}

MainWindow::~MainWindow()
{

}

void MainWindow::onCurrentIndexChanged(const QString &text )
{
    m_glWidget->setShapeCode( text );
}

void CGLWidget::setShapeCode( const QString &shape)
{
    if( "Line" == shape ) {
        m_shape = Shape::line;
    } else if( "Rectangle" == shape ) {
        m_shape = Shape::rectangle;
    } else if( "Circle" == shape ) {
        m_shape = Shape::circle;
    }
}

void CGLWidget::paintEvent(QPaintEvent *event)
{
    if( m_shape == Shape::line ) {
        QPixmap *m_nPTargetPixmap = new QPixmap( 400, 300 );
        if( m_mousePressed )
        {
        QPainter PixmapPainter( m_nPTargetPixmap );
        QPen pen(Qt::red);
        PixmapPainter.setPen(pen);
        PixmapPainter.drawLine(m_initX, m_initY, m_finX, m_finY);
        }
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_nPTargetPixmap);

    } else if( m_shape == Shape::rectangle ) {
        QPixmap *m_nPTargetPixmap = new QPixmap( 400, 300 );
        if( m_mousePressed )
        {
        QPainter PixmapPainter( m_nPTargetPixmap );
        QPen pen(Qt::red);
        PixmapPainter.setPen(pen);
        PixmapPainter.drawRect(    m_initX,
                                   m_initY,
                                   m_finX - m_initX,
                                   m_finY - m_initY );
        }
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_nPTargetPixmap);
    } else if( m_shape == Shape::circle ) {
        QPixmap *m_nPTargetPixmap = new QPixmap( 400, 300 );
        if( m_mousePressed )
        {
        QPainter PixmapPainter( m_nPTargetPixmap );
        QPen pen(Qt::red);
        PixmapPainter.setPen(pen);
        PixmapPainter.drawEllipse( m_initX,
                                   m_initY,
                                   m_finX - m_initX,
                                   m_finY - m_initY );
        }
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_nPTargetPixmap);
    }

}

void CGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePressed = true;
    m_initX = event->x();
    m_initY = event->y();

}

void CGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
}

void CGLWidget::mouseMoveEvent(QMouseEvent *event)
{
       m_finX = event->x();
       m_finY = event->y();
       update(); // update your view
}
