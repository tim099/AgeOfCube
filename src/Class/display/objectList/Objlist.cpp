#include <Objlist.h>

Objlist::Objlist() {


}
Objlist::~Objlist() {
	while(!all_obj.empty()){
		glDeleteLists(all_obj.front(),1);
		all_obj.pop();
	}
}
void Objlist::creat_list(GLuint &list, char *file_name, float size) {
	GLMmodel *glm_model;
	glm_model = glmReadOBJ(file_name);
	glmUnitize(glm_model);
	glmScale(glm_model, size);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);
	list = glmList(glm_model, GLM_MATERIAL|GLM_TEXTURE|GLM_SMOOTH);//| GLM_SMOOTH
	glmDelete(glm_model);
	all_obj.push(list);
}
GLuint Objlist::creat_list(char *file_name, float size,float x,float y,float z) {
	GLuint list;
	GLMmodel *glm_model;
	glm_model = glmReadOBJ(file_name);
	glmUnitize(glm_model);
	glmScale(glm_model, size);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);
    list = glGenLists(1);
    glNewList(list,GL_COMPILE);
    glPushMatrix();
    glTranslatef(x,y,z);
    glmDraw(glm_model, GLM_MATERIAL|GLM_TEXTURE|GLM_SMOOTH); //| GLM_SMOOTH
    glPopMatrix();
    glEndList();
	//list = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH |GLM_TEXTURE);
	glmDelete(glm_model);
	all_obj.push(list);
	return list;
}
void Objlist::creat_obj_list(char*file_name,GLuint list,float size,float x,float y,float z){
	GLMmodel *glm_model;
	glm_model = glmReadOBJ(file_name);
	glmUnitize(glm_model);
	glmScale(glm_model, size);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model,90);
    glNewList(list,GL_COMPILE);
    glPushMatrix();
    glTranslatef(x,y,z);
    glmDraw(glm_model,GLM_MATERIAL|GLM_TEXTURE|GLM_SMOOTH);//|GLM_FLAT
    glPopMatrix();
    glEndList();
	glmDelete(glm_model);
	all_obj.push(list);
}


