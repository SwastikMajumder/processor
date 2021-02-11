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

void gate(struct CONNECTION *joinList, int state, int index){
        int i;
	struct COMPONENT *tmp;
        for (i=0; i < joinList[index].total; ++i){
		if (state == 1){
	                if ((*(joinList[index].connect))[i].type == OUTPUT){
       	                	if ((*(joinList[index].connect))[i].hist == 0){
       	                        	((*joinList[index].connect))[i].hist = 1;
       	                        	((*joinList[index].connect))[i].value = 1;
					//if (index == 3) printf("b");
       	                 	}
       	         	}
       	         	else if ((*(joinList[index].connect))[i].type > OUTPUT){
                        	tmp = *(joinList[index].connect + i);
                       		switch (tmp->type){
                                	case OR:
                                        	if (tmp->hist == 0 || tmp->hist == 1){
                                                	tmp->hist = 2;
							//if (index == 5) printf("a");
                                                	gate(joinList, 1, tmp->id);
                                        	}
						break;
                                	case AND:
                                       		if (tmp->hist == 0){
                                                	tmp->hist = 1;
                                        	}
                                        	else if (tmp->hist == 1){
                                               		tmp->hist = 2;
                                                	gate(joinList, 1, tmp->id);
                                        	}
                                        	break;
                                	case XOR:
                                        	if (tmp->hist == 0){
                                                	tmp->value = 1;
                                                	tmp->hist = 1;
                                        	}
                                        	else if (tmp->hist == 1){
                                                	tmp->hist = 2;
                                                        if (tmp->value == 0){
                                                                gate(joinList, 1, tmp->id);
                                                        } else {
                                                                gate(joinList, 0, tmp->id);
                                                        }
                                                }
                                                break;
                                }
			}
		} else {
			//if (index == 6 && i==1) printf("g");
			tmp = *(joinList[index].connect + i);
			//printf("%d", tmp->type);
                        switch (tmp->type){
                                case OR:
                                        if (tmp->hist == 0){
                                                tmp->hist = 1;
                                        }
                                        else if (tmp->hist == 1){
                                                tmp->hist = 2;
                                                gate(joinList, 0, tmp->id);
					} else {
						//if (index == 4) printf("e");
					}
					break;
                                case AND:
                                        if (tmp->hist == 0 || tmp->hist == 1){
                                                tmp->hist = 2;
						//if (index == 6) printf("d");
                                                gate(joinList, 0, tmp->id);
						//if (index == 6) printf("f");
                                        }
                                        break;
                                case XOR:
					//if(index == 6 && i==1) printf("h");
                                        if (tmp->hist == 0){
                                                tmp->hist = 1;
                                                tmp->value = 0;
                                        }
                                        else if (tmp->hist == 1){
                                                tmp->hist = 2;
                                        	if (tmp->value == 0){
                                                        gate(joinList, 0, tmp->id);                                                                                    } else {
                                                	gate(joinList, 1, tmp->id);
                                                }
                                        }
                                        break;
                        }
                }

        }
}

void loopinput(struct CONNECTION *joinList, int cinput){
	int i, j;
	struct COMPONENT *tmp;
	for (i=0; i<cinput; ++i){
		if ((*(joinList[i].device)).value == 1){
			for (j=0; j < joinList[i].total; ++j){
				if ((*(joinList[i].connect))[j].type == OUTPUT){
					if ((*(joinList[i].connect))[j].hist == 0){
						((*joinList[i].connect))[j].hist = 1;
						((*joinList[i].connect))[j].value = 1;
					}
					continue;
				}
				else if ((*(joinList[i].connect))[j].type > OUTPUT){
					tmp = *(joinList[i].connect + j);
					switch (tmp->type){
						case OR:
							if (tmp->hist == 0 || tmp->hist == 1){
								tmp->hist = 2;
								gate(joinList, 1, tmp->id);
							}
							break;

						case AND:
							if (tmp->hist == 0){
								tmp->hist = 1;
							}
							else if (tmp->hist == 1){
								tmp->hist = 2;
								gate(joinList, 1, tmp->id);
							}
							break;
						case XOR:
							if (tmp->hist == 0){
								tmp->value = 1;
								tmp->hist = 1;
							}
							else if (tmp->hist == 1){
								tmp->hist = 2;
								if (tmp->value == 0){
									gate(joinList, 1, tmp->id);
								} else {
									//if (i == 1 && j == 1) printf("c");
									gate(joinList, 0, tmp->id);
								}
							}
							break;
					}
				}

			}
		} else {
			for (j=0; j < joinList[i].total; ++j){
				tmp = *(joinList[i].connect + j);
				switch (tmp->type){
					case OR:
						if (tmp->hist == 0){
							tmp->hist = 1;
						}
						else if (tmp->hist == 1){
							tmp->hist = 2;
							gate(joinList, 0, tmp->id);
						}
						break;
					case AND:
						if (tmp->hist == 0 || tmp->hist == 1){
							tmp->hist = 2;
							gate(joinList, 0, tmp->id);
						}
						break;
					case XOR:
						if (tmp->hist == 0){
							tmp->hist = 1;
							tmp->value = 0;
						}
						else if (tmp->hist == 1){
							tmp->hist = 2;
							if (tmp->value == 0){
								gate(joinList, 0, tmp->id);
							} else {
								gate(joinList, 1, tmp->id);
							}
						}
						break;
				}
			}
		}
	}
}

int main (){
	struct COMPONENT comList[10] =
	{
		{.id = 0, .type = INPUT, .value = 1, .hist = 1},
		{.id = 1, .type = INPUT, .value = 1, .hist = 1},
		{.id = 2, .type = INPUT, .value = 1, .hist = 1},
		{.id = 3, .type = OR, .value = 0, .hist = 0},
		{.id = 4, .type = AND, .value = 0, .hist = 0},
		{.id = 5, .type = AND, .value = 0, .hist = 0},
		{.id = 6, .type = XOR, .value = 0, .hist = 0},
		{.id = 7, .type = XOR, .value = 0, .hist = 0},
		{.id = 8, .type = OUTPUT, .value = 0, .hist = 0},
                {.id = 9, .type = OUTPUT, .value = 0, .hist = 0},
	};
	
	struct CONNECTION joinList[8] = {0};
	struct COMPONENT *tmp1[2];
	struct COMPONENT *tmp2[2];
	struct COMPONENT *tmp3[2];
	struct COMPONENT *tmp4;
	struct COMPONENT *tmp5;
	struct COMPONENT *tmp6;
	struct COMPONENT *tmp7[2];
	struct COMPONENT *tmp8;
	int i;
	for (i=0; i<8; ++i){
		joinList[i].total = 1;
		joinList[i].device = comList + i;
	}
	joinList[0].total = 2;
	joinList[1].total = 2;
	joinList[2].total = 2;
	joinList[6].total = 2;
	tmp1[0] = comList + 5;
	tmp1[1] = comList + 6;
	tmp2[0] = comList + 5;
	tmp2[1] = comList + 6;
	tmp3[0] = comList + 4;
	tmp3[1] = comList + 7;
	tmp4 = comList + 9;
	tmp5 = comList + 3;
	tmp6 = comList + 3;
	tmp7[0] = comList + 4;
	tmp7[1] = comList + 7;
	tmp8 = comList + 8;
	joinList[0].connect = tmp1;
	joinList[1].connect = tmp2;
	joinList[2].connect = tmp3;
	joinList[3].connect = &tmp4;
	joinList[4].connect = &tmp5;
	joinList[5].connect = &tmp6;
	joinList[6].connect = tmp7;
	joinList[7].connect = &tmp8;
	loopinput(joinList, 3);
	printf("%d %d", comList[8].value, comList[9].value);
	return 0;
}
