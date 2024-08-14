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
#include <QTimer>
#include <QElapsedTimer>

class DiceRoll3DWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
    using vboint = quint32;
    using vaoint = quint32;
    using vshader = quint32;
    using fshader = quint32;
    using shaderprogram = quint32;

public:
    DiceRoll3DWidget(QWidget *parent = nullptr);
    ~DiceRoll3DWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:

    vboint VBO;
    vaoint VAO;
    vshader shader;
    fshader fragment;
    shaderprogram shaderProgram;

    QElapsedTimer timer;
};

#endif // DICEROLL3DWIDGET_H
