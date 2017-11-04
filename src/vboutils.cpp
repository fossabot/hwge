#include <hwge/vboutils.hpp>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string>
#include <string.h>

struct PackedVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    bool operator<(const PackedVertex that) const {
        return memcmp((void*) this, (void*) &that, sizeof(PackedVertex)) > 0;
    };
};

bool isNear(float v1, float v2) {
    return fabs(v1 - v2) < 0.01f;
}

bool getSimilarVertexIndex(glm::vec3 &inVertex, glm::vec2 &inUV, glm::vec3 &inNormal, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals, unsigned short &result) {
    for(unsigned int i = 0; i < outVertices.size(); i++) {
        if(
            isNear(inVertex.x, outVertices[i].x) &&
            isNear(inVertex.y, outVertices[i].y) &&
            isNear(inVertex.z, outVertices[i].z) &&
            isNear(inUV.x, outUVs[i].x) &&
            isNear(inUV.y, outUVs[i].y) &&
            isNear(inNormal.x, outNormals[i].x) &&
            isNear(inNormal.y, outNormals[i].y) &&
            isNear(inNormal.z, outNormals[i].z)
        ) {
            result = i;
            return true;
        }
    }

    return false;
}

bool getSimilarVertexIndexFast(PackedVertex &packed, std::map<PackedVertex, unsigned short> &vertexToOutIndex, unsigned short &result) {
    std::map<PackedVertex, unsigned short>::iterator it = vertexToOutIndex.find(packed);

    if(it == vertexToOutIndex.end()) {
        return false;
    } else {
        result = it->second;
        return true;
    }
}

void HWGE::Utils::VBO::indexVBO(std::vector<glm::vec3> &inVertices, std::vector<glm::vec2> &inUVs, std::vector<glm::vec3> &inNormals, std::vector<unsigned short> &outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals) {
    std::map<PackedVertex, unsigned short> vertexToOutIndex;

    for(unsigned int i = 0; i < inVertices.size(); i++) {
        PackedVertex packed = { inVertices[i], inUVs[i], inNormals[i] };

        // try to find similar vertex
        unsigned short index;
        bool found = getSimilarVertexIndexFast(packed, vertexToOutIndex, index);
        
        if(found) {
            outIndices.push_back(index);
        } else {
            outVertices.push_back(inVertices[i]);
            outUVs.push_back(inUVs[i]);
            outNormals.push_back(inNormals[i]);
            unsigned short newIndex = (unsigned short) outVertices.size() - 1;
            outIndices.push_back(newIndex);
            vertexToOutIndex[packed] = newIndex;
        }
    }
}