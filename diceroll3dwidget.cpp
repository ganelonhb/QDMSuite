#include "diceroll3dwidget.h"

static float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f,
    0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
    0.0f,  0.5f, 0.0f, 0.f, 0.f, 1.f
};

const char *vertexShader ="#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}\0";

const char *fragShader = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(ourColor, 1.0f);\n"
                                   "}\n\0";

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
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}



void DiceRoll3DWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0,0, parentWidget()->width(), parentWidget()->height());

    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &vertexShader, NULL);
    glCompileShader(shader);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragShader, NULL);
    glCompileShader(fragment);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, shader);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    glDeleteShader(shader);
    glDeleteShader(fragment);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void DiceRoll3DWidget::paintGL()
{
    glUseProgram(shaderProgram);

    glClearColor(0.f,0.f,0.f,0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void DiceRoll3DWidget::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);

    int w2, h2;

    w2 = 2;
    h2 = !h ? 1: h;

    float aspect = float(w2) / float(h2);

    if (w2 >= h)
        glOrtho(-aspect, aspect, -1.f, 1.f, -1.f, 1.f);
    else
        glOrtho(-1.f, 1.f, -1.f / aspect, 1.f / aspect, -1.f, 1.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //QOpenGLWidget::resizeGL(w, h);
}
