#ifndef MODEL3D_H
#define MODEL3D_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QVector4D>
#include <QImage>
#include <QString>
#include <QFile>
#include <QMap>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model3D : protected QOpenGLFunctions
{
public:
    Model3D();
    ~Model3D();

    bool loadModel(const QString &path);
    void changeVertexColors(const QVector4D &color);

    const QVector<float> &getVertices() const;
    const QVector<float> &getNormals() const;
    const QVector<float> &getTexCoords() const;
    const QVector<float> &getTangents() const;
    const QVector<float> &getBitangents() const;
    const QVector4D &getColor() const;

    const QMap<QString, QImage> &getTextures() const;

private:
    void processNode(aiNode *node, const aiScene *scend);
    void processMesh(aiMesh *mesh, const aiScene *scene);
    void loadMaterialTextures(aiMaterial *material, aiTextureType type, const QString &typeName);

    QImage loadTexture(const aiMaterial *material, aiTextureType type, const QString &typeName);

    QVector<float> vertices;
    QVector<float> normals;
    QVector<float> texCoords;
    QVector<float> tangents;
    QVector<float> bitangents;
    QVector4D vertexColor;

    QMap<QString, QImage> textures;
};

#endif // MODEL3D_H
