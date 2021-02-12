#include <stdio.h>
#include <stdlib.h>

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

int find(char *code, int location, char c){
	for(;code[location]!='\0';++location){
		if (code[location] == c){
			return location;
		}
	}
	return -1;
}

int findLetter(char *code, int location){
	for(;code[location]!='\0';++location){
		if (code[location] <= 'Z' && code[location] >= 'A'){
			return location;
		}
	}
	return -1;
}

int findnumber(char *code, int location){
	for(;code[location]!='\0';++location){
		if (code[location] <= '9' && code[location] >= '1'){
			return location;
		}
	}
	return -1;
}

void first(char *code, int *input, int *or, int *and, int *xor, int *output){
	int location = 0;
	*input = 0;
	*or = 0;
	*and = 0;
	*xor = 0;
	*output = 0;
	while (1){
		location = findLetter(code, location);
		if (location == -1) return;
		switch (code[location]){
			case 'I':
				(*input)++;
				break;
			case 'O':
				if (code[location + 1] == 'R'){
					(*or)++;
				}
				else if (code[location + 1] == 'U'){
					(*output)++;
				}
				break;
			case 'A':
				(*and)++;
				break;
			case 'X':
				(*xor)++;
				break;
		}
		location = find(code, location, '}');
	}
}
	

int compile(char *code, struct CONNECTION *joinList, struct COMPONENT *comList, struct COMPONENT **tmp,
		int *ora, int *ol){
	int location = 0;
	int cindex = 0;
	int jindex = 0;
	int tmpindex = 0;
	char c;
	int input, or, and, xor, output;
	//How many gates
	first(code, &input, &or, &and, &xor, ol);
	*ora = input + or + and + xor;
	while(1){
		joinList[cindex].connect = tmp + tmpindex;
		//Find a letter
		location = findLetter(code, location);
		//Set id
		comList[cindex].id = cindex;
		//Hist is always zero initally
		comList[cindex].hist = 0;
		//Set the device incrementally
		joinList[cindex].device = comList + cindex;
		//If the word is I
		if (code[location] == 'I'){
			comList[cindex].type = INPUT;
			//Skip the word input
			location = find(code, location, ':');
			//Skip the input number
			location = find(code, ++location, ':');
			//Check on or off
			location += 2;
			if (code[location] == 'N'){
				comList[cindex].value = 1;
			}
			else if (code[location] == 'F'){
				comList[cindex].value = 0;
			}
			if (cindex == 0) printf("a");
			if (cindex == 1) printf("d");
			if (cindex == 2) printf("g");
		}
		//If or or output
		else if (code[location] == 'O'){
			//or
			if (code[location + 1] == 'R'){
				comList[cindex].type = OR;
			}
			//output
			else if (code[location + 1] == 'U'){
				comList[cindex].type = OUTPUT;
			}
		}
		//If and
		else if (code[location] == 'A'){
			comList[cindex].type = AND;
		}
		//If xor
		else if (code[location] == 'X'){
			comList[cindex].type = XOR;
		}
		//If it was not input
		if (comList[cindex].type != INPUT){
			//Value will be zero
			comList[cindex].value = 0;
		}
		//Go to the inside connection
		location = find(code, location, '{');
		//If it is output the last set of device
		if (code[location + 1] == '}'){
			location = findLetter(code, location);
			if (location == -1) return input; //No letter means finish
			++cindex; //Go to next device
			continue;
		}
		//Number of connection for the given device
		joinList[cindex].total = 0;
		
		//Iterate until we reach the end bracket
		for(++location;code[location] != '}';++location){
			//If a letter
			if (code[location] <= 'Z' && code[location] >= 'A'){
				//Put the device address on the connection
				tmp[tmpindex] = comList;
				//If it is or or output
				if (code[location] == 'O'){
					//If or
					if (code[location + 1] == 'R'){
						//Change device location
						tmp[tmpindex] += input;
					}
					//If output
					else if (code[location + 1] == 'U'){
						//CHange device location
						tmp[tmpindex] += input + or + and + xor;
					}
				}
				//If and
				else if (code[location] == 'A'){
					if (cindex == 0) printf("b");
					if (cindex == 1) printf("e");
					tmp[tmpindex] += input + or;
				}
				//If xor
				else if (code[location] == 'X'){
					if (cindex == 0) printf("c");
					tmp[tmpindex] += input + or + and;
				}
				if (cindex == 1 && tmpindex == 2) printf("f");
				//End the sequence
				location = find(code, location, ':');
				//Which numberth device
				tmp[tmpindex] += code[location + 1] - '1';
				if (cindex == 2 && tmpindex == 4)
					printf("%d", code[location + 1] - '1' + input + or);
				if (cindex == 2 && tmpindex == 5)
					printf("%d", input + or + and + code[location + 1] - '1');
				++tmpindex;
				(joinList[cindex].total)++;
			}
		}
		++cindex;
	}
	return input;

}

int main (){
	FILE *file;
	int location=0;
	char *code = (char *) calloc(1000, sizeof(char));
	char c;
	file = fopen("0003.prcsr", "r");
	while (1){
		c = (char)fgetc(file);
		if (feof(file)) break;
		printf("%c", c);
		code[location++] = c;
	}
	code[location] = '\0';
	fclose(file);
	struct COMPONENT comList[100] = {0};
	struct CONNECTION joinList[100] = {0};
	struct COMPONENT *tmp[100] = {0};
	int or, ol;
	int x = compile(code, joinList, comList, tmp, &or, &ol);
	printf("%d\n", comList[3].type);
	loopinput(joinList, x);
	/*
	struct COMPONENT comList[10] =
	{
		{.id = 0, .type = INPUT, .value = 1, .hist = 0},
		{.id = 1, .type = INPUT, .value = 1, .hist = 0},
		{.id = 2, .type = INPUT, .value = 1, .hist = 0},
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
	loopinput(joinList, 3);*/
	int i;
	for(i=0; i<ol; ++i){
		printf("%d", comList[or + i].value);
	}
	//printf("%d %d", comList[8].value, comList[9].value);
	return 0;
}
