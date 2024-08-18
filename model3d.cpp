#include "model3d.h"

#include <iostream>

Model3D::Model3D() {
    initializeOpenGLFunctions();
}

Model3D::~Model3D() {}

bool Model3D::loadModel(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    file.close();


    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFileFromMemory(data.data(), data.size(), aiProcess_Triangulate  | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << importer.GetErrorString() << std::endl;
        return false;
    }

    processNode(scene->mRootNode, scene);
    return true;
}

void Model3D::changeVertexColors(const QVector4D &color)
{
    vertexColor = color;
}

const QVector<float> &Model3D::getVertices() const
{
    return vertices;
}

const QVector<float> &Model3D::getNormals() const
{
    return normals;
}

const QVector<float> &Model3D::getTexCoords() const
{
    return texCoords;
}

const QVector<float> &Model3D::getTangents() const
{
    return tangents;
}

const QVector<float> &Model3D::getBitangents() const
{
    return bitangents;
}

const QVector4D &Model3D::getColor() const
{
    return vertexColor;
}

const QMap<QString, QImage> &Model3D::getTextures() const
{
    return textures;
}

void Model3D::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        processNode(node->mChildren[i], scene);
}

void Model3D::processMesh(aiMesh *mesh, const aiScene *scene)
{
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Vertices
        vertices.append(mesh->mVertices[i].x);
        vertices.append(mesh->mVertices[i].y);
        vertices.append(mesh->mVertices[i].z);

        // Normals
        normals.append(mesh->mNormals[i].x);
        normals.append(mesh->mNormals[i].y);
        normals.append(mesh->mNormals[i].z);

        // Texture coordinates
        if (mesh->mTextureCoords[0]) {
            texCoords.append(mesh->mTextureCoords[0][i].x);
            texCoords.append(mesh->mTextureCoords[0][i].y);
        } else {
            texCoords.append(0.0f);
            texCoords.append(0.0f);
        }

        // Tangents and Bitangents
        if (mesh->HasTangentsAndBitangents()) {
            tangents.append(mesh->mTangents[i].x);
            tangents.append(mesh->mTangents[i].y);
            tangents.append(mesh->mTangents[i].z);

            bitangents.append(mesh->mBitangents[i].x);
            bitangents.append(mesh->mBitangents[i].y);
            bitangents.append(mesh->mBitangents[i].z);
        }

        // Vertex colors
        if (mesh->HasVertexColors(0)) {
            vertexColor.setX(mesh->mColors[0][i].r);
            vertexColor.setY(mesh->mColors[0][i].g);
            vertexColor.setZ(mesh->mColors[0][i].b);
            vertexColor.setW(mesh->mColors[0][i].a);
        } else {
            vertexColor.setX(1.0f);  // Default color white
            vertexColor.setY(1.0f);
            vertexColor.setZ(1.0f);
            vertexColor.setW(1.0f);
        }

        // Textures
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            QImage diffuseMap = loadTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
            if (!diffuseMap.isNull()) {
                textures["diffuse"] = diffuseMap;
            }

            QImage normalMap = loadTexture(material, aiTextureType_NORMALS, "texture_normal");
            if (!normalMap.isNull()) {
                textures["normal"] = normalMap;
            }

            QImage parallaxMap = loadTexture(material, aiTextureType_HEIGHT, "texture_parallax");
            if (!parallaxMap.isNull()) {
                textures["parallax"] = parallaxMap;
            }
        }
    }
}


QImage Model3D::loadTexture(const aiMaterial *material, aiTextureType type, const QString &typeName) {
    if (material->GetTextureCount(type) > 0) {
        aiString str;
        material->GetTexture(type, 0, &str);
        QString texturePath = QString(str.C_Str());

        QFile textureFile(texturePath);
        if (textureFile.exists()) {
            QImage textureImage;
            if (textureImage.load(texturePath)) {
                return textureImage;
            }
        }
    }
    return QImage();
}
