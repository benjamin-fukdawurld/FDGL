#include <FDGL/BufferedMeshComponent.h>

std::function<void (FDGL::BufferedMeshComponent&)> FDGL::BufferedMeshComponent::defaultVAOFunction;

float *FDGL::BufferedMeshComponent::getVertices()
{
    return const_cast<float*>(
        const_cast<const FDGL::BufferedMeshComponent*>(
            this)->getVertices());
}

const float *FDGL::BufferedMeshComponent::getVertices() const
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

uint32_t *FDGL::BufferedMeshComponent::getIndices()
{
    return const_cast<uint32_t*>(
        const_cast<const FDGL::BufferedMeshComponent*>(
            this)->getIndices());
}

const uint32_t *FDGL::BufferedMeshComponent::getIndices() const
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

void FDGL::BufferedMeshComponent::setVertices(const float *data)
{
    FDGL::OpenGLBufferWrapper(m_vbo).setData(0, getVerticesDataSize(), data);
}

void FDGL::BufferedMeshComponent::setIndices(const uint32_t *data)
{
    FDGL::OpenGLBufferWrapper(m_ebo).setData(0, getIndicesDataSize(), data);
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite> FDGL::BufferedMeshComponent::getVerticesMap()
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite>(
                m_vbo, getVerticesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read> FDGL::BufferedMeshComponent::getVerticesMap() const
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read>(
            m_vbo, getVerticesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite> FDGL::BufferedMeshComponent::getIndicesMap()
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::ReadWrite>(
            m_vbo, getIndicesDataSize()
        );
}

FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read> FDGL::BufferedMeshComponent::getIndicesMap() const
{
    return FDGL::OpenGLBufferMappingGuard<FDGL::BufferMappingAccess::Read>(
            m_vbo, getIndicesDataSize()
        );
}

size_t FDGL::BufferedMeshComponent::getNumberOfVertices() const
{
    return m_nbVertices;
}

void FDGL::BufferedMeshComponent::setNumberOfVertices(size_t val)
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

size_t FDGL::BufferedMeshComponent::getNumberOfIndices() const
{
    return m_nbIndices;
}

void FDGL::BufferedMeshComponent::setNumberOfIndices(size_t val)
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

void FDGL::BufferedMeshComponent::updateBuffers()
{
    unmapBuffer(m_vbo, m_vertexMap);
    unmapBuffer(m_ebo, m_indexMap);
}

const char *FDGL::BufferedMeshComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<BufferedMeshComponent>::code;
}

size_t FDGL::BufferedMeshComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<BufferedMeshComponent>::hash();
}

bool FDGL::BufferedMeshComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FDGL::BufferedMeshComponent::getTypeCodeHash() || AbstractMeshComponent::matchTypeCodeHash(hash);
}

std::function<void (FDGL::BufferedMeshComponent &)> FDGL::BufferedMeshComponent::getDefaultVAOFunction()
{
    return FDGL::BufferedMeshComponent::defaultVAOFunction;
}

uint32_t FDGL::BufferedMeshComponent::createBuffer(FDGL::BufferTarget target, FDGL::BufferUsage usage, size_t size)
{
    FDGL::OpenGLBuffer buffer;
    uint32_t id = 0;

    buffer.create();
    buffer.bind(target);
    if(buffer.allocate(size, usage))
        id = buffer.release();

    return id;
}

void FDGL::BufferedMeshComponent::destroyBuffer(uint32_t id)
{
    FDGL::OpenGLBufferWrapper(id).destroy();
}

uint32_t FDGL::BufferedMeshComponent::createVertexArray()
{
    FDGL::OpenGLVertexArray vao;
    vao.create();

    return vao.release();
}

void FDGL::BufferedMeshComponent::destroyVertexArray(uint32_t id)
{
    FDGL::OpenGLVertexArrayWrapper(id).destroy();
}

