#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainWidget( new QWidget )
    , m_gfxView( new QGraphicsView )
    , m_gfxScene( new QGraphicsScene )
    , m_btnLoad( new QPushButton )
    , m_btnSave( new QPushButton )
    , m_layoutBtns( new QHBoxLayout )
    , m_layoutMain( new QVBoxLayout )
{
    m_layoutBtns->addStretch( 1 );
    m_layoutBtns->addWidget( m_btnLoad );
    m_layoutBtns->addWidget( m_btnSave );

    m_layoutMain->addWidget( m_gfxView );
    m_layoutMain->addLayout( m_layoutBtns );


    m_btnLoad->setText( "Load" );
    m_btnLoad->setFixedWidth( 100 );
    m_btnSave->setText( "Save" );
    m_btnSave->setFixedWidth( 100 );

    m_gfxView->setScene( m_gfxScene );
    m_gfxView->setFixedSize( 640, 480 );

    m_mainWidget->setLayout( m_layoutMain );

    QObject::connect( m_btnLoad,
                      SIGNAL( clicked( bool ) ),
                      this,
                      SLOT( onBtnLoadClicked(bool) ),
                      Qt::UniqueConnection ) ;

    QObject::connect( m_btnSave,
                      SIGNAL( clicked( bool ) ),
                      this,
                      SLOT( onBtnSaveClicked(bool) ),
                      Qt::UniqueConnection ) ;

    setCentralWidget( m_mainWidget );

}

MainWindow::~MainWindow()
{
    m_gfxScene->clear();
}

void MainWindow::onBtnLoadClicked( bool dummy )
{
    QFileDialog dialog;
    QString filename = QFileDialog::getOpenFileName( this,
                 tr( "Open Image" ),
                 QStandardPaths::displayName( QStandardPaths::DesktopLocation ),
                 tr("Image Files (*.tiff *.tif )") );
    if( !filename.isEmpty() ) {
        QPixmap *pixmap = new QPixmap( filename );
        if( pixmap && ! pixmap->isNull() ) {
            QGraphicsPixmapItem *gfxImage = new QGraphicsPixmapItem( *pixmap );
            if( gfxImage ) {
                m_gfxScene->addItem( gfxImage );
            }
        }
    }
}

void MainWindow::onBtnSaveClicked( bool dummy )
{
    QList<QGraphicsItem* > list = m_gfxScene->items();
    QGraphicsPixmapItem* item0
            = dynamic_cast<QGraphicsPixmapItem*>( list.at( 0 ) );
    if( item0 ) {
        QPixmap pixmap = item0->pixmap();
        QString file = QFileDialog::getSaveFileName( this,
                 tr( "Save image" ),
                 QStandardPaths::displayName( QStandardPaths::DesktopLocation ),
                 tr( "Image files( *.tiff *.tif )") );
        if( ! file.isEmpty() ) {
            if( pixmap.save( file ) ) {
                QMessageBox::information( this,
                                          tr( "Save successful"),
                                          tr("File saved !!"),
                                          QMessageBox::Ok );

            } else {
                QMessageBox::warning( this,
                                      tr( "Save Failed"),
                                      tr("File saved !!"),
                                      QMessageBox::Ok );
            }
        }
    }

}
