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

    timer.start();

    QTimer *updateTimer = new QTimer(this);

    connect(updateTimer, &QTimer::timeout, this, QOverload<>::of(&DiceRoll3DWidget::update));
    updateTimer->start(16);
}

DiceRoll3DWidget::~DiceRoll3DWidget()
{}



void DiceRoll3DWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0,0, parentWidget()->width(), parentWidget()->height());

    setupShaders();

    setupLighting();

    Model3D testModel;
    if(testModel.loadModel(":/ui/3DAssets/testCube/cube.glb"))
        models.append(testModel);

}

void DiceRoll3DWidget::paintGL()
{
    glClearColor(0.f,0.f,0.f,0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 view, projection;
    projection.ortho(0.f, float(width()), float(height()), 0.f, 0.1f, 100.f);
    view.lookAt(QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 0.f, 0.f));

    shaderProgram.bind();
    shaderProgram.setUniformValue("view", view);
    shaderProgram.setUniformValue("projection", projection);
    shaderProgram.setUniformValue("lightPos", lightPos);
    shaderProgram.setUniformValue("lightColor", lightColor);
    shaderProgram.setUniformValue("viewPos", viewPos);

    for (const auto &model : models) {
        QMatrix4x4 modelMatrix;

        modelMatrix.translate(0.f, 0.f, 0.f);

        shaderProgram.setUniformValue("model", modelMatrix);

        // Bind textures and draw the model
        const QMap<QString, QImage> &textures = model.getTextures();
        if (textures.contains("diffuse")) {
            QOpenGLTexture texture(textures["diffuse"]);
            texture.bind();
        }

        // Bind vertex data
        const QVector<float> &vertices = model.getVertices();
        const QVector<float> &normals = model.getNormals();
        const QVector<float> &texCoords = model.getTexCoords();

        shaderProgram.enableAttributeArray(0);
        shaderProgram.setAttributeArray(0, vertices.constData(), 3);

        shaderProgram.enableAttributeArray(1);
        shaderProgram.setAttributeArray(1, normals.constData(), 3);

        shaderProgram.enableAttributeArray(2);
        shaderProgram.setAttributeArray(2, texCoords.constData(), 2);

        // Draw the model
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

        shaderProgram.disableAttributeArray(0);
        shaderProgram.disableAttributeArray(1);
        shaderProgram.disableAttributeArray(2);
    }

    shaderProgram.release();
}

void DiceRoll3DWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
}

void DiceRoll3DWidget::setupShaders()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/ui/shaders/verts.vs");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/ui/shaders/frag.fs");
    shaderProgram.link();
}

void DiceRoll3DWidget::setupLighting()
{
    // Define initial lighting parameters
    lightPos = QVector3D(5.0f, 5.0f, 5.0f);
    lightColor = QVector3D(1.0f, 1.0f, 1.0f);
    viewPos = QVector3D(0.0f, 5.0f, 10.0f);
}
