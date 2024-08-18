#ifndef DICEROLL3DWIDGET_H
#define DICEROLL3DWIDGET_H

#define FREE_IF_NNULL(X) if (X) delete X
#define Q_FREE_IF_NNULL(X) if (X) X->deleteLater()

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
#include <QImage>
#include <QFile>
#include <QBuffer>
#include <QVector3D>
#include <QVector2D>

#include "model3d.h"

#include <vector>
#include <string>

class DiceRoll3DWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    DiceRoll3DWidget(QWidget *parent = nullptr);
    ~DiceRoll3DWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void setupShaders();
    void setupLighting();

    QOpenGLShaderProgram shaderProgram;
    QList<Model3D> models;

    QElapsedTimer timer;

    QVector3D lightPos;
    QVector3D lightColor;
    QVector3D viewPos;
};

#endif // DICEROLL3DWIDGET_H
