#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *m_mainWidget = nullptr;

    QGraphicsView *m_gfxView = nullptr;

    QGraphicsScene *m_gfxScene = nullptr;

    QPushButton *m_btnLoad = nullptr;

    QPushButton *m_btnSave = nullptr;

    QHBoxLayout *m_layoutBtns = nullptr;

    QVBoxLayout *m_layoutMain = nullptr;

public slots:
    void onBtnLoadClicked( bool dummy );

    void onBtnSaveClicked( bool dummy );
};

#endif // MAINWINDOW_H
