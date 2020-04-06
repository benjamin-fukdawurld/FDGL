#ifndef BUFFEREDMESH_H
#define BUFFEREDMESH_H

#include <FD3D/Mesh/AbstractMesh.h>

#include <FDGL/OpenGLVertexArray.h>
#include <FDGL/OpenGLBuffer.h>
#include <FDGL/OpenGLUtils.h>

#include <memory>

namespace FDGL
{
    class BufferedMesh : public FD3D::AbstractMesh
    {
        protected:
            mutable float *m_vertexMap;
            mutable uint32_t *m_indexMap;
            size_t m_nbVertices;
            size_t m_nbIndices;
            uint32_t m_ebo;
            uint32_t m_vbo;
            uint32_t m_vao;
            FDGL::BufferUsage m_usage;

            static std::function<void(BufferedMesh&)> defaultVAOFunction;

        public:
            explicit BufferedMesh(FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw) :
                m_vertexMap(nullptr),
                m_indexMap(nullptr),
                m_nbVertices(0),
                m_nbIndices(0),
                m_ebo(0),
                m_vbo(0),
                m_vao(0),
                m_usage(usage)
            {}

            explicit BufferedMesh(const FD3D::AbstractMesh &mesh,
                                  FDGL::BufferUsage usage = FDGL::BufferUsage::StaticDraw):
                BufferedMesh(usage)
            {
                setNumberOfIndices(mesh.getNumberOfIndices());
                setIndices(mesh.getIndices());
                setNumberOfVertices(mesh.getNumberOfVertices());
                setVertices(mesh.getVertices());
                setVAOFunctionToDefault();
            }

            BufferedMesh(const BufferedMesh &) = delete;
            BufferedMesh(BufferedMesh &&) = default;

            ~BufferedMesh() override
            {
                FDGL::OpenGLVertexArrayWrapper(m_vao).destroy();
                FDGL::OpenGLBufferWrapper(m_ebo).destroy();
                FDGL::OpenGLBufferWrapper(m_vbo).destroy();
            }

            BufferedMesh &operator=(const BufferedMesh &) = delete;
            BufferedMesh &operator=(BufferedMesh &&) = default;

            OpenGLBufferWrapper getVBO()
            {
                return OpenGLBufferWrapper(m_vbo);
            }

            OpenGLBufferWrapper getEBO()
            {
                return OpenGLBufferWrapper(m_ebo);
            }

            OpenGLVertexArrayWrapper getVAO()
            {
                return OpenGLVertexArrayWrapper(m_vao);
            }

            template<typename VAOFunction, typename ...Args>
            void setVAOFunction(VAOFunction f, Args ...args)
            {
                if(m_vao != 0)
                    destroyVertexArray(m_vao);

                m_vao = createVertexArray();
                getVAO().setFunction(f, args...);
            }

            void setVAOFunctionToDefault()
            {
                setVAOFunction(defaultVAOFunction, std::ref(*this));
            }

            float *getVertices() override;
            const float *getVertices() const override;

            void setVertices(const float *data) override;

            uint32_t *getIndices() override;
            const uint32_t *getIndices() const override;

            void setIndices(const uint32_t *data) override;

            OpenGLBufferMappingGuard<BufferMappingAccess::ReadWrite> getVerticesMap();
            OpenGLBufferMappingGuard<BufferMappingAccess::Read> getVerticesMap() const;

            OpenGLBufferMappingGuard<BufferMappingAccess::ReadWrite> getIndicesMap();
            OpenGLBufferMappingGuard<BufferMappingAccess::Read> getIndicesMap() const;

            size_t getNumberOfVertices() const override;
            void setNumberOfVertices(size_t val) override;

            size_t getNumberOfIndices() const override;
            void setNumberOfIndices(size_t val) override;

            void updateBuffers();

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;


            template<typename VAOFunction>
            static void setDefaultVAOFunction(VAOFunction f)
            {
                defaultVAOFunction = f;
            }

            template<typename VAOFunction, typename ...Args>
            static void setDefaultVAOFunction(VAOFunction f, Args ...args)
            {
                defaultVAOFunction = std::bind(f, args...);
            }

            static std::function<void(BufferedMesh&)> getDefaultVAOFunction();

        protected:
            static uint32_t createBuffer(FDGL::BufferTarget target,
                                         FDGL::BufferUsage usage,
                                         size_t size);
            static void destroyBuffer(uint32_t id);

            static uint32_t createVertexArray();
            static void destroyVertexArray(uint32_t id);

            template<typename T>
            static void unmapBuffer(uint32_t buffer, T *&map)
            {
                if(map)
                {
                    glUnmapNamedBuffer(buffer);
                    map = nullptr;
                }
            }
    };

}

generateTypeCode(FDGL::BufferedMesh);

#endif // BUFFEREDMESH_H
