#ifndef LISTFONTS_H_
#define LISTFONTS_H_
#include "Bmplist.h"
class ListFonts : public Bmplist{
public:
	ListFonts(double size=0.0016);
	virtual ~ListFonts();
	void call_string(const char *string);
	void call_string(int num);
protected:
	std::vector<GLuint>cap_fonts;
	std::vector<GLuint>fonts;
	std::vector<GLuint>numbs;
	void creat_all_list();
	double size;
};

#endif /* LISTFONTS_H_ */
