#ifndef DICEROLL3DWIDGET_H
#define DICEROLL3DWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QResizeEvent>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLTexture>

class DiceRoll3DWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    DiceRoll3DWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
};

#endif // DICEROLL3DWIDGET_H
