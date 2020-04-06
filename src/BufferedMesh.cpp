#include <FDGL/BufferedMesh.h>

std::function<void (FDGL::BufferedMesh&)> FDGL::BufferedMesh::defaultVAOFunction;

float *FDGL::BufferedMesh::getVertices()
{
    return const_cast<float*>(
        const_cast<const FDGL::BufferedMesh*>(
            this)->getVertices());
}

const float *FDGL::BufferedMesh::getVertices() const
{
    if(m_vertexMap == nullptr)
    {
        m_vertexMap =
            reinterpret_cast<float *>(
                glMapNamedBufferRange(m_vbo, 0,
                                      static_cast<GLsizeiptr>(getVerticesDataSize()),
                                      static_cast<GLenum>(
                                          FDGL::BufferMappingAccess::ReadWrite)
                                      )
                );
    }

    return m_vertexMap;
}

uint32_t *FDGL::BufferedMesh::getIndices()
{
    return const_cast<uint32_t*>(
        const_cast<const FDGL::BufferedMesh*>(
            this)->getIndices());
}

const uint32_t *FDGL::BufferedMesh::getIndices() const
{
    if(m_indexMap == nullptr)
    {
        m_indexMap =
            reinterpret_cast<uint32_t *>(
                glMapNamedBufferRange(m_ebo,
                                      0,
                                      static_cast<GLsizeiptr>(getIndicesDataSize()),
                                      static_cast<GLenum>(
                                          FDGL::BufferMappingAccess::ReadWrite)
                                 )
                );
    }

    return m_indexMap;
}

void FDGL::BufferedMesh::setVertices(const float *data)
{
    FDGL::OpenGLBufferWrapper(m_vbo).setData(0, getVerticesDataSize(), data);
}

void FDGL::BufferedMesh::setIndices(const uint32_t *data)
{
    FDGL::OpenGLBufferWrapper(m_ebo).setData(0, getIndicesDataSize(), data);
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite> FDGL::BufferedMesh::getVerticesMap()
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite>(
                m_vbo, getVerticesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read> FDGL::BufferedMesh::getVerticesMap() const
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read>(
            m_vbo, getVerticesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite> FDGL::BufferedMesh::getIndicesMap()
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite>(
            m_vbo, getIndicesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read> FDGL::BufferedMesh::getIndicesMap() const
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read>(
            m_vbo, getIndicesDataSize()
        );
}

size_t FDGL::BufferedMesh::getNumberOfVertices() const
{
    return m_nbVertices;
}

void FDGL::BufferedMesh::setNumberOfVertices(size_t val)
{
    if(m_nbVertices == val)
        return;

    if(m_vbo != 0)
        destroyBuffer(m_vbo);

    m_vbo = createBuffer(FDGL::BufferTarget::VertexIndex,
                         m_usage,
                         sizeof(float) * getVertexSize() * val);
    if(m_vbo != 0)
        m_nbVertices = val;
}

size_t FDGL::BufferedMesh::getNumberOfIndices() const
{
    return m_nbIndices;
}

void FDGL::BufferedMesh::setNumberOfIndices(size_t val)
{
    if(m_nbIndices == val)
        return;

    if(m_ebo != 0)
        destroyBuffer(m_ebo);

    m_ebo = createBuffer(FDGL::BufferTarget::VertexIndex,
                         m_usage,
                         sizeof(uint32_t) * val);
    if(m_ebo != 0)
        m_nbIndices = val;
}

void FDGL::BufferedMesh::updateBuffers()
{
    unmapBuffer(m_vbo, m_vertexMap);
    unmapBuffer(m_ebo, m_indexMap);
}

const char *FDGL::BufferedMesh::getTypeCode() const
{
    return FDCore::TypeCodeHelper<BufferedMesh>::code;
}

size_t FDGL::BufferedMesh::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<BufferedMesh>::hash();
}

bool FDGL::BufferedMesh::matchTypeCodeHash(size_t hash) const
{
    return hash == FDGL::BufferedMesh::getTypeCodeHash() || AbstractMesh::matchTypeCodeHash(hash);
}

std::function<void (FDGL::BufferedMesh &)> FDGL::BufferedMesh::getDefaultVAOFunction()
{
    return FDGL::BufferedMesh::defaultVAOFunction;
}

uint32_t FDGL::BufferedMesh::createBuffer(FDGL::BufferTarget target, FDGL::BufferUsage usage, size_t size)
{
    FDGL::OpenGLBuffer buffer;
    uint32_t id = 0;

    buffer.create();
    buffer.bind(target);
    if(buffer.allocate(size, usage))
        id = buffer.release();

    return id;
}

void FDGL::BufferedMesh::destroyBuffer(uint32_t id)
{
    FDGL::OpenGLBufferWrapper(id).destroy();
}

uint32_t FDGL::BufferedMesh::createVertexArray()
{
    FDGL::OpenGLVertexArray vao;
    vao.create();

    return vao.release();
}

void FDGL::BufferedMesh::destroyVertexArray(uint32_t id)
{
    FDGL::OpenGLVertexArrayWrapper(id).destroy();
}
