#include <stdio.h>

#define INPUT	0
#define OUTPUT	1
#define OR	2
#define AND	3	
#define NOT	4
#define XOR	5
#define NOR	6
#define NAND	7

struct COMPONENT {
	int id;
	int type;
	int value;
	int hist;
};

struct CONNECTION {
	int total;
	struct COMPONENT *device;
	struct COMPONENT **connect;
};

void gate(struct CONNECTION *joinList, int index){
        int i;
        for (i=0; i < joinList[index].total; ++i){
                if ((*(joinList[index].connect))[i].type == OUTPUT){
                        if ((*(joinList[index].connect))[i].hist == 0){
                                ((*joinList[index].connect))[i].hist = 1;
                                ((*joinList[index].connect))[i].value = 1;
                        }
                        continue;
                }
                else if ((*(joinList[index].connect))[i].type > OUTPUT){
                        struct COMPONENT *tmp = (*(joinList[index].connect)) + i;
                        if (tmp->hist == 0){
                                tmp->value = 1;
                                tmp->hist = 1;
                        }
                        else if (tmp->hist == 1){
                                tmp->value = 3;
                                tmp->hist = 3;
                                gate(joinList, tmp->id);
                        }
                        else if (tmp->hist == 3){
                                continue;
                        }
                }
        }
}

void loopinput(struct CONNECTION *joinList, int cinput){
	int i;
	for (i=0; i<cinput; ++i){
		if ((*(joinList[i].device)).type == INPUT && (*(joinList[i].device)).value == 1){
			int j;
			for (j=0; j < joinList[i].total; ++j){
				if ((*(joinList[i].connect))[j].type == OUTPUT){
					if ((*(joinList[i].connect))[j].hist == 0){
						((*joinList[i].connect))[j].hist = 1;
						((*joinList[i].connect))[j].value = 1;
					}
					continue;
				}
				else if ((*(joinList[i].connect))[j].type > OUTPUT){
					struct COMPONENT *tmp =  (*(joinList[i].connect)) + j;
					if (tmp->hist == 0){
						tmp->value = 1;
						tmp->hist = 1;
					}
					else if (tmp->hist == 1){
						tmp->value = 3;
						tmp->hist = 3;
						gate(joinList, tmp->id);
					}
					else if (tmp->hist == 3){
						continue;
					}
				}
			}
		}
	}
}

int main (){ /*
	struct COMPONENT comlist[10] =
	{
		{.type = INPUT, .value = 1, .hist = 1},
		{.type = INPUT, .value = 1, .hist = 1},
		{.type = INPUT, .value = 1, .hist = 1},
		{.type = OUTPUT, .value = 0, .hist = 0},
		{.type = OUTPUT, .value = 0, .hist = 0},
		{.type = OR, .value = 0, .hist = 0},
		{.type = AND, .value = 0, .hist = 0},
		{.type = XOR, .value = 0, .hist = 0},
		{.type = XOR, .value = 0, .hist = 0}
	};
	
	struct CONNECTION joinlist[8] = {0};
	joinList[0].total = 2;
	joinList[0].device = comlist
	so on...
	*/
	struct COMPONENT comList[8] =
	{
		{.id = 0, .type = INPUT, .value = 1, .hist = 1},
		{.id = 1, .type = INPUT, .value = 1, .hist = 1},
		{.id = 2, .type = INPUT, .value = 1, .hist = 1},
		{.id = 3, .type = INPUT, .value = 1, .hist = 1},
		{.id = 4, .type = AND, .value = 0, .hist = 0},
		{.id = 5, .type = AND, .value = 0, .hist = 0},
		{.id = 6, .type = AND, .value = 0, .hist = 0},
		{.id = 7, .type = OUTPUT, .value = 0, .hist = 0}
	};
	struct CONNECTION joinList[7];
	int i;
	struct COMPONENT *tmp1;
	struct COMPONENT *tmp2;
	struct COMPONENT *tmp3;
	struct COMPONENT *tmp4;
	struct COMPONENT *tmp5;
	struct COMPONENT *tmp6;
	struct COMPONENT *tmp7;
	for (i=0; i<7; ++i){
		joinList[i].total = 1;
		joinList[i].device = comList + i;
	}
	tmp1 = comList + 4;
	tmp2 = comList + 4;
	tmp3 = comList + 5;
	tmp4 = comList + 5;
	tmp5 = comList + 6;
	tmp6 = comList + 6;
	tmp7 = comList + 7;
	joinList[0].connect = &tmp1;
	joinList[1].connect = &tmp2;
	joinList[2].connect = &tmp3;
	joinList[3].connect = &tmp4;
	joinList[4].connect = &tmp5;
	joinList[5].connect = &tmp6;
	joinList[6].connect = &tmp7;
	loopinput(joinList, 4);
	printf("%d", comList[7].value);
	return 0;
}
