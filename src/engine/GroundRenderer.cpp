//
// Created by Martin on 17. 11. 2015.
//

#include "src/engine/GroundRenderer.hpp"

GroundRenderer::GroundRenderer(GroundShader *shader) {
    this->shader = shader;
};

void GroundRenderer::render(std::vector<nsGround::Ground> grounds, glm::mat4 projection, glm::mat4 view) {
    for ( std::vector<nsGround::Ground>::iterator it = grounds.begin(); it != grounds.end(); it++ ) {
        prepareGround(&(*it), projection, view);

        prepareInstance(&(*it));

        glBindVertexArray(it->mesh->texturedModel->vao);
        glDrawElements(GL_TRIANGLES, it->mesh->texturedModel->mesh_indices_count, GL_UNSIGNED_INT, 0);

        unbindMesh();
    }
}

void GroundRenderer::render(Mesh *mesh, glm::mat4 projection, glm::mat4 view) {
    shader->loadProjectionMatrix(projection);
    shader->loadViewMatrix(view);

    shader->loadTextureUni(mesh->texturedModel->texture->textureId);
    shader->loadModelMatrix(mesh->texturedModel->matrix);

    glBindVertexArray(mesh->texturedModel->vao);
    glDrawElements(GL_TRIANGLES, mesh->texturedModel->mesh_indices_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(NULL);

}

void GroundRenderer::prepareGround(const nsGround::Ground *model, glm::mat4 projection, glm::mat4 view) {
    shader->loadProjectionMatrix(projection);
    shader->loadViewMatrix(view);

    shader->loadTextureUni(model->mesh->texturedModel->texture->textureId);
}

void GroundRenderer::unbindMesh() {
    glBindVertexArray(NULL);
}

void GroundRenderer::prepareInstance(nsGround::Ground *ground ) {
    loadModelMatrix(ground);
}

void GroundRenderer::loadModelMatrix(nsGround::Ground *ground) {
    ground->mesh->position = glm::vec3(ground->x, 0.0f, ground->z);
    ground->mesh->rotX = 0;
    ground->mesh->rotY = 0;
    ground->mesh->rotZ = 0;
    ground->mesh->scale = 1.0f;

    shader->loadModelMatrix(ground->mesh->createTransformationMatrix());
}