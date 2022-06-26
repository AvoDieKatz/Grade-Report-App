extern void emptyBuffer();
extern int isIdDuplicated(int input);
extern int validateIdInput(int input, int scf_rtn, char end_term);
extern int validateGradeInput(float input, int scf_rtn, char end_term);
extern int validateName(const char *input, int scf_rtn);
extern int isInteger(const char *input);
//adding color to the programming
extern void red();
extern void green();
extern void cyan();
extern void purple();
extern void yellow();
extern void reset();