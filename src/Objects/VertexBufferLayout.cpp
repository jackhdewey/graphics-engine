#include "VertexBufferLayout.hpp"
#include <iostream>

VertexBufferLayout::VertexBufferLayout(){
}

// Delete buffers that we have previously allocated
VertexBufferLayout::~VertexBufferLayout(){
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_indexBufferObject);
}

void VertexBufferLayout::Bind(){
    // Bind to our vertex array
    glBindVertexArray(m_VAOId);
    // Bind to our vertex information
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    // Bind to the index information
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
}

// Note: Calling Unbind is rarely done; if you need to draw something else then just bind to the new buffer
void VertexBufferLayout::Unbind(){
        // Bind to our vertex array
        glBindVertexArray(0);
        // Bind to our vertex information
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Bind to the elements we are drawing
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBufferLayout::CreatePositionBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata){

        // Because this layout is x, y, z
        m_stride = 3;
        
        static_assert(sizeof(GLfloat)==sizeof(float),
            "GLFloat and gloat are not the same size on this architecture");
       
        // Vertex Array
        glGenVertexArrays(1, &m_VAOId);
        glBindVertexArray(m_VAOId);

        // Vertex Buffer Object (VBO)
        glGenBuffers(1, &m_vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(float), vdata, GL_STATIC_DRAW);

        // Vertex Attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(  0,   // Attribute 0, which will match layout in shader
                                3,   // Number of components - 2=(x,y)  3=(x,y,z), etc.
                                GL_FLOAT, // Type of data
                                GL_FALSE, // Is the data normalized
                                sizeof(float)*m_stride, // Stride (amount of bytes between each vertex)
                                0               // Pointer to the starting point of our data
        );

        // Index buffer
        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), idata, GL_STATIC_DRAW);
    }


void VertexBufferLayout::CreateTextureBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata) {

        // This layout uses x,y,z,s,t
        m_stride = 5;
        
        static_assert(sizeof(GLfloat)==sizeof(float),
            "GLFloat and float are not the same size on this architecture");
       
        // Vertex Array
        glGenVertexArrays(1, &m_VAOId);
        glBindVertexArray(m_VAOId);

        // Vertex Buffer
        glGenBuffers(1, &m_vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        // Vertex Attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);
        // texture coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float)*m_stride, (char*)(sizeof(float)*3));

        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        // Index Buffer
        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }

void VertexBufferLayout::CreateNormalBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata){

        m_stride = 14;
        
        static_assert(sizeof(GLfloat) == sizeof(float),
                "GLFloat and float are not the same size on this architecture");
       
        // Vertex Array
        glGenVertexArrays(1, &m_VAOId);
        glBindVertexArray(m_VAOId);

        // Vertex Buffer
        glGenBuffers(1, &m_vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        // Vertex Attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);
        // texture coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, (char*)(sizeof(float)*3));
        // normal vectors
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, (char*)(sizeof(float)*5));
        // tangent vectors
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, (char*)(sizeof(float)*8));
        // bi-tangent vectors
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, (char*)(sizeof(float)*11));

        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        // Index Buffer
        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }
