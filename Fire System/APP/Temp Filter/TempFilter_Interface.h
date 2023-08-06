

#ifndef TEMPFILTER_INTERFACE_H_
#define TEMPFILTER_INTERFACE_H_

void Filter_Init(void);
void Filter_Runnable(void);

u16 Filter_GetFilteredTemp(void);
u16 Filter_GetUnFilteredTemp(void);


#endif /* TEMPFILTER_INTERFACE_H_ */