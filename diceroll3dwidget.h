#ifndef DICEROLL3DWIDGET_H
#define DICEROLL3DWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QResizeEvent>

class DiceRoll3DWidget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit DiceRoll3DWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;

    void resizeEvent(QResizeEvent *event) override;

private:
    QOpenGLShaderProgram *shaderProgram;
    GLuint VAO;
    GLuint VBO;

};

#endif // DICEROLL3DWIDGET_H
