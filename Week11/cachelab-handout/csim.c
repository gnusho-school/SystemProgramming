//2016024893
#include "cachelab.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "getopt.h"
#include "unistd.h"
#include "math.h"

struct line{
	int valid;
	unsigned long int tag;
	unsigned long int byte;
	int used;
};


int main(int argc, char ** argv)
{

	int v=-1,s=-1,e=-1,b=-1;
	char *trace_file="none";
	int opt;
	while((opt=getopt(argc, argv, "vs:E:b:t:"))!=-1)
	{
		switch(opt)
		{
			case 'v': v=1;break;
			case 's': s=atoi(optarg);break;
			case 'E': e=atoi(optarg);break;
			case 'b': b=atoi(optarg);break;
			case 't': trace_file=optarg;break;

			default: return 0;
		}
	}

	//printf("%d %d %d %d\n", v,s,e,b);

	int set=pow(2,s);

	struct line **cache;
	cache=(struct line**)malloc(sizeof(struct line*)*set);
	for(int i=0;i<set;i++)
		cache[i]=(struct line*)malloc(sizeof(struct line)*e);
	for(int i=0;i<set;i++)
	{	
		for(int j=0;j<e;j++)
		{
			cache[i][j].valid=0;
			cache[i][j].used=0;
			cache[i][j].tag=0;
			cache[i][j].byte=0;
		}
	}
	set--;

	FILE *trace;
	trace=fopen(trace_file,"r");
	int hit_cnt=0,miss_cnt=0,evic_cnt=0;
	char order;
	unsigned long int memory;
	int bytes;

	int turn=0;
	while(fscanf(trace," %c %lx,%d", &order, &memory, &bytes)>0)
	{
		if(order=='I') continue;
		if(v) printf("%c %lx %d ", order,memory,bytes);
		unsigned long int tags=memory>>(b+s);
		unsigned long int sets=(memory>>b)&set;
		
		int find=0,evic=0,empty=-1,last=-1,mini=1e9;
		for(int i=0;i<e;i++)
		{
			if(cache[sets][i].valid==1)
			{
				if(cache[sets][i].tag==tags)
				{
					find=1;
					cache[sets][i].used=turn;
					break;
				}
				else if(mini>cache[sets][i].used)
				{
					mini=cache[sets][i].used;
					last=i;
				}
			}
			else if(empty<0) empty=i;
		}
		char* sign;
		if(find==0&&empty>=0)
		{
			cache[sets][empty].valid=1;
			cache[sets][empty].tag=tags;
			cache[sets][empty].used=turn;
			//miss=1;
		}

		else if(find==0&&empty<0)
		{
			cache[sets][last].valid=1;
			cache[sets][last].tag=tags;
			cache[sets][last].used=turn;
			evic=1;
		}

		if(find) 
		{
			sign="hit";
			hit_cnt++;
		}
		else if(evic) 
		{
			sign="miss evic";
			miss_cnt++;
			evic_cnt++;
		}
		else 
		{
			sign="miss";
			miss_cnt++;
		}

		if(order=='M')
		{
			hit_cnt++;			
		}

		if(v) printf("%s\n", sign);
		turn++;
	}


    printSummary(hit_cnt, miss_cnt, evic_cnt);

    fclose(trace);

    //for(int i=0;i<set+1;i++) free(cache[i]);
    //free(cache);
    return 0;
}
