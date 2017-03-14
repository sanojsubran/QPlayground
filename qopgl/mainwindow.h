#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QComboBox>

namespace Shape {
    enum ShapeCode {
        line = 0,
        rectangle,
        circle
    };
}


class CGLWidget : public QOpenGLWidget
{
public:
    explicit CGLWidget( QWidget *parent = 0 )
        : QOpenGLWidget( parent ) {
       m_shape = Shape::line;

    }

    void setShapeCode( const QString &shape );
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool m_mousePressed;
    int m_initX;
    int m_initY;
    int m_finX;
    int m_finY;
    Shape::ShapeCode m_shape;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVBoxLayout *m_Layout;
    CGLWidget *m_glWidget;
    QComboBox *m_combo;
    QWidget *m_mainWidget;

public slots:
    void onCurrentIndexChanged(const QString &);
};

#endif // MAINWINDOW_H
