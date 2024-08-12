#include "diceroll3dwidget.h"

DiceRoll3DWidget::DiceRoll3DWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_AlwaysStackOnTop);

    if (parent)
        setGeometry(0,0, parent->width(), parent->height());
}

void DiceRoll3DWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void DiceRoll3DWidget::paintGL()
{
    glClearColor(0.f,0.f,0.f,0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void DiceRoll3DWidget::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);

    int width = event->size().width();
    int height = event->size().height();

    // Example: Adjust the OpenGL viewport
    glViewport(0, 0, width, height);

    // Update any other aspects of the scene that depend on size
}
