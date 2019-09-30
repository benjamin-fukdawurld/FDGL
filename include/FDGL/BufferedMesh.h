#ifndef BUFFEREDMESH_H
#define BUFFEREDMESH_H

#include <FD3D/Mesh.h>
#include <FD3D/Vertex.h>
#include <FD3D/Texture.h>

#include <FDGL/OpenGLBuffer.h>
#include <FDGL/OpenGLVertexArray.h>

#include <functional>

namespace FDGL
{
    template<typename VertexType = FD3D::Vertex>
    class BufferedMesh
    {
        protected:
            std::vector<FD3D::Texture> m_textures;
            uint32_t m_vbo;
            uint32_t m_ebo;
            uint32_t m_vao;

        public:
            BufferedMesh() :
                m_vbo(0),
                m_ebo(0),
                m_vao(0)
            {}

            BufferedMesh(const FD3D::Mesh &mesh, FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw,
                         std::function<void(BufferedMesh &)> vaoFunction = std::function<void(BufferedMesh &)>()) :
                BufferedMesh(mesh.getVertices(), mesh.getIndices(), mesh.getTextures(), usage, vaoFunction)
            {}

            BufferedMesh(const std::vector<FD3D::Vertex> &vertices,
                 const std::vector<uint32_t> &indices,
                 const std::vector<FD3D::Texture> textures,
                 FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw,
                 std::function<void(BufferedMesh &)> vaoFunction = std::function<void(BufferedMesh &)>()) :
                m_textures(textures)
            {
                setVertices(vertices, usage);
                setIndices(indices, usage);
                setVaoFunction(vaoFunction);
            }

            OpenGLBufferWrapper getVBO()
            {
                return { m_vbo };
            }

            OpenGLBufferWrapper getEBO()
            {
                return { m_ebo };
            }

            OpenGLVertexArrayWrapper getVAO()
            {
                return { m_vao };
            }

            void setVertices(const std::vector<FD3D::Vertex> &vertices,
                             FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw)
            {
                FDGL::OpenGLBufferWrapper vbo(m_vbo);
                vbo.destroy();
                vbo.create();
                vbo.allocate(vertices.size() * VertexType::numberOfComponents * sizeof(float), usage, vertices.data());
                m_vbo = *vbo;
            }

            void setVBO(uint32_t vbo)
            {
                FDGL::OpenGLBufferWrapper v(m_vbo);
                v.destroy();
                m_vbo = vbo;
            }

            void setIndices(const std::vector<uint32_t> &indices,
                             FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw)
            {
                FDGL::OpenGLBufferWrapper ebo(m_ebo);
                ebo.destroy();
                ebo.create();
                ebo.allocate(indices.size() * sizeof(uint32_t), usage, indices.data());
                m_ebo = *ebo;
            }

            void setEBO(uint32_t ebo)
            {
                FDGL::OpenGLBufferWrapper e(m_ebo);
                e.destroy();
                m_ebo = ebo;
            }

            void setVaoFunction(std::function<void(BufferedMesh &)> vaoFunction)
            {
                FDGL::OpenGLVertexArray vao(m_vao);
                vao.destroy();
                vao.create();
                if(vaoFunction)
                    vao.setFunction(vaoFunction);
                else
                    vao.setFunction(&vaoDefaultFunction);
            }

            std::vector<FD3D::Texture> &getTextures() { return m_textures; }
            const std::vector<FD3D::Texture> &getTextures() const { return m_textures; }

            void setTexture(const std::vector<FD3D::Texture> &tex)
            {
                m_textures = tex;
            }

        protected:
            static void vaoDefaultFunction(BufferedMesh &mesh)
            {

            }
    };

}

#endif // BUFFEREDMESH_H
