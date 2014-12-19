#include <DPfield.h>

DPfield::DPfield(Mouse *mou) : Display(mou){
	field=0;
	LBC = new ListBasicCubes();
	LBD = new ListBuildings();
	LCT = new ListCreature();
	LRC = new ListResources();
	LMC = new ListMisc();
	LBR = new ListBar();

	dp_range=20;
	read_file();
}
DPfield::~DPfield() {
	save_file();
	delete LBC;
	delete LBD;
	delete LCT;
	delete LRC;
	delete LMC;
	delete LBR;
}
void DPfield::set_field(Field* _field){
	field=_field;
	if(!field)return;
	look_maxx=field->map->MSX()*0.1+0.05;
	look_maxy=field->map->MSY()*0.1+0.05;
	look_maxz=field->map->MSZ()*0.1+0.05;
}
void DPfield::dp_building(unsigned min_x,unsigned min_z,unsigned max_x,unsigned max_z){
	bool extra_light=false;
	unsigned size=field->map->buildings.size();
	Building *b;
	for(unsigned i=0;i<size;i++){
		b=field->map->buildings.front();
		field->map->buildings.pop();
		if(b->get_x()>=min_x&&b->get_x()<max_x&&b->get_z()>=min_z&&b->get_z()<max_z&&b->get_y()<field->dp_height){
			glPushMatrix();
			if(b==field->s_building()||b->selected()){
				if(field->mode->get_mode()==DESTRUCTED_MODE)glEnable(GL_LIGHT5);
				else glEnable(GL_LIGHT2);
				extra_light=true;
			}
			glTranslatef(0.1*b->get_x(),0.1*b->get_y(),0.1*b->get_z());
			b->dp_players_building();
			glPopMatrix();
			if(extra_light){
				if(field->mode->get_mode()==DESTRUCTED_MODE)glDisable(GL_LIGHT5);
				else glDisable(GL_LIGHT2);
			}
		}
		if(field->mode->get_mode()==DESTRUCTED_MODE)glDisable(GL_LIGHT5);
		field->map->buildings.push(b);
	}

}
void DPfield::read_file(){
	FILE *f=fopen("files/settings/dpsittings","r");
	fscanf(f,"%d\n",&dp_range);
	fclose(f);
}
void DPfield::save_file(){
	FILE *f=fopen("files/settings/dpsittings","w+t");
	fprintf(f,"%d\n",dp_range);
	fclose(f);
}
void DPfield::dp_creature(int min_x,int min_z,int max_x,int max_z){
	int size=field->creatures.size();
	CubeCreature *buff;
	bool extra_light=false;
	for(int i=0;i<size;i++){
		buff=field->creatures.front();
		field->creatures.pop();
		field->creatures.push(buff);
		if(buff->stay_in_building())continue;
		if(buff->get_x()>=0.1*min_x&&buff->get_x()<0.1*max_x&&buff->get_z()>=0.1*min_z
		&&buff->get_z()<0.1*max_z&&buff->get_y()<(field->dp_height*0.1+0.09)){
			glPushMatrix();
			if(buff==field->s_creature()||buff->selected()){
				extra_light=true;
				glEnable(GL_LIGHT2);
			}
			glTranslatef(buff->get_x(),buff->get_y(),buff->get_z());
			buff->dp_players_creature();
			if(extra_light){
				glDisable(GL_LIGHT2);
			}
			glPopMatrix();
		}
	}
}
void DPfield::dp_field_mode(){
	switch(field->mode->get_mode()){
		default:
		look.y=field->dp_height*0.1+look_dy;
		field->mode->display_alter(this);
	}
}
void DPfield::dp_map(){
	dp_field_mode();

	bool lighton=false;
	glPushMatrix();
	look_at_func();

	glPushMatrix();
	glTranslatef(0.0505,0.05,0.0495);
	unsigned min_x=0>look.x*10-dp_range?0:look.x*10-dp_range;
	unsigned min_z=0>look.z*10-dp_range?0:look.z*10-dp_range;
	if(min_x>field->map->MSX()-2*dp_range)min_x=field->map->MSX()-2*dp_range;
	if(min_z>field->map->MSZ()-2*dp_range)min_z=field->map->MSZ()-2*dp_range;

	unsigned max_x=min_x+2*dp_range;
	unsigned max_z=min_z+2*dp_range;
	for(unsigned i=min_x;i<max_x;i++){
		for(unsigned j=0;j<field->dp_height;j++){
			for(unsigned k=min_z;k<max_z;k++){
				Cube *c=field->map->get_map(i,j,k);
				if(i==field->mou->select_x&&j==field->mou->select_y&&k==field->mou->select_z){
					if(field->mode->get_mode()==DESTRUCTED_MODE)glEnable(GL_LIGHT5);
					else glEnable(GL_LIGHT2);
					lighton=true;
				}
				if(c->typ()>C_NULL){//exist
					if(c->C_TYP()==C_CUBE){
						glPushMatrix();
						glTranslatef(0.1*i,0.1*j,0.1*k);
						dp_Cube(i,j,k);
						glPopMatrix();
					}
				}
				if(lighton){
					if(field->mode->get_mode()==DESTRUCTED_MODE)glDisable(GL_LIGHT5);
					else glDisable(GL_LIGHT2);
					lighton=false;
				}
			}
		}
	}
	dp_building(min_x,min_z,max_x,max_z);
	glPopMatrix();
	dp_creature(min_x,min_z,max_x,max_z);

	compute_mouse_location();

	field->mode->dp_mode();
	glPopMatrix();
}
void DPfield::dp_Cube(unsigned i,unsigned j,unsigned k){
	int cube_type=field->map->get_map(i,j,k)->typ();
	if(field->map->get_map(i,j+1,k)->C_TYP()!=C_CUBE||j+1==field->dp_height){
		if(j+1==field->dp_height&&field->map->get_map(i,j+1,k)->typ()>0)light_off();
		glPushMatrix();
		glTranslatef(0,0.0485,0);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)),0.05,0.05);
		glPopMatrix();
		if(j+1==field->dp_height)light_on();
	}
	if(field->map->get_map(i,j-1,k)->C_TYP()!=C_CUBE){
		glPushMatrix();
		glTranslatef(0,-0.0485,0);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)),0.05,0.05);
		glPopMatrix();
	}
	if(field->map->get_map(i+1,j,k)->C_TYP()!=C_CUBE){
		glPushMatrix();
		glTranslatef(0.0485,0,0);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)+1),0.05,0.05,90,90);
		glPopMatrix();
	}
	if(field->map->get_map(i-1,j,k)->C_TYP()!=C_CUBE){
		glPushMatrix();
		glTranslatef(-0.0485,0,0);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)+1),0.05,0.05,90,90);
		glPopMatrix();
	}
	if(field->map->get_map(i,j,k+1)->C_TYP()!=C_CUBE){
		glPushMatrix();
		glTranslatef(0,0,0.0485);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)+1),0.05,0.05,90,0);
		glPopMatrix();
	}
	if(field->map->get_map(i,j,k-1)->C_TYP()!=C_CUBE){
		glPushMatrix();
		glTranslatef(0,0,-0.0485);
		Bmplist::dp_tex(LBC->cube_tex.at(2*(cube_type-C_BASIC)+1),0.05,0.05,90,0);
		glPopMatrix();
	}
}
