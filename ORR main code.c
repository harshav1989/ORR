#include<stdio.h>  
int main()  
{  
    int tot_cat=4;
    int ii,jj,fi,fj;
    int scale;
    int inp_at, inp_bt, swap_at, swap_bt;
    int cat,i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[4][10], bt[4][10], temp[4][10],cat_cnt[4],cat_i[4]; 
    cat_cnt[0]=cat_cnt[1]=cat_cnt[2]=cat_cnt[3]=0;
    cat_i[0]=cat_i[1]=cat_i[2]=cat_i[3]=0;
    float avg_wt, avg_tat;  
    printf(" Total number of process in the system: ");  
    scanf("%d", &NOP);  
    y = NOP;  
  
for(i=0; i<NOP; i++)  
{  
printf("\n Enter the Category, Arrival and Burst time of the Process[%d]\n", i+1);  
printf(" Process Category is: \t");
scanf("%d", &cat);  
printf(" Arrival time is: \t");
scanf("%d", &at[cat][cat_cnt[cat]]); 
printf(" \nBurst time is: \t"); 
scanf("%d", &bt[cat][cat_cnt[cat]]); 
temp[cat][cat_cnt[cat]] = bt[cat][cat_cnt[cat]]; 
cat_cnt[cat]=cat_cnt[cat]+1;  
}  
printf("\n** UnSorted Queue - Process as arrived : ");
for(ii=0;ii<tot_cat;ii++)
{ 
    printf("\nA-Queue %d Count %d : ",ii,cat_cnt[ii]);
    printf("\nArrival : ");
	for(jj=0;jj<cat_cnt[ii];jj++)
	{
		printf("%3d ",at[ii][jj]);
	}
	printf("\nBurst   : ");
	for(jj=0;jj<cat_cnt[ii];jj++)
	{
		printf("%3d ",bt[ii][jj]);
	}
}
for (i=0; i<tot_cat; i++)
{
	for (fi = 0; fi < cat_cnt[i]; fi++) 
    {
        for (fj = fi+1; fj < cat_cnt[i]; fj++)
        {
            if (bt[i][fi] > bt[i][fj]) 
            {
                swap_bt =  bt[i][fi];
                bt[i][fi] = bt[i][fj];
                bt[i][fj] = swap_bt;
                swap_bt =  temp[i][fi];
                temp[i][fi] = temp[i][fj];
                temp[i][fj] = swap_bt;
                swap_at =  at[i][fi];
                at[i][fi] = at[i][fj];
                at[i][fj] = swap_at;
            }
        }
	}
}
printf("\n** Sorted Queue to get Shortest Job First (SJF) : ");
for(ii=0;ii<tot_cat;ii++)
{ 
    printf("\nS-Queue %d Count %d : ",ii,cat_cnt[ii]);
    printf("\nArrival : ");
	for(jj=0;jj<cat_cnt[ii];jj++)
	{
		printf("%3d ",at[ii][jj]);
	}
	printf("\nBurst   : ");
		for(jj=0;jj<cat_cnt[ii];jj++)
	{
		printf("%3d ",bt[ii][jj]);
	}

}
printf("\nEnter the Time Quantum for the process: \t");  
scanf("%d", &quant);  
printf("\n Process No \t\t Burst Time \t TAT \t\t Waiting Time\n");  
cat=0;
sum=0;
scale=1;
for(sum=0; y!=0; )  
{  
    if(cat_cnt[cat]==0) 
    {
    	cat=cat+1;
    	if (cat==tot_cat) cat=0; 
    	continue;
	}
	if(at[cat][cat_i[cat]] > sum)
	{
		cat_i[cat]=cat_i[cat]+1;
		if(cat_i[cat]==cat_cnt[cat]) cat_i[cat]=0;
    	cat=cat+1;
    	if (cat==tot_cat) cat=0; 
    	continue;
	}
    if (cat==1) scale = 3; // SYSTEM USER QUEUE 1 - RR - 3 x TIME QUANTUM
    if (cat==2) scale = 2;// USER APPL I QUEUE 2 - RR - 2 x TIME QUANTUM
    if (cat==3) scale = 1;// USER APPL II QUEUE 3 - RR - 1 x TIME QUANTUM
    if (cat==0 && temp[cat][cat_i[cat]] > 0) // ROOT USER QUEUE 0 - FCFS - TIME QUANTUM = BURST TIME
    {
    	sum = sum + temp[cat][cat_i[cat]];
    	temp[cat][cat_i[cat]] = 0;
    	count=1;
	}
	else
	{
		if((temp[cat][cat_i[cat]] <= scale*quant || temp[cat][cat_i[cat]] <= (int)(scale*quant*1.25)) && temp[cat][cat_i[cat]] > 0) 
		{  
	    	sum = sum + temp[cat][cat_i[cat]];
	    	temp[cat][cat_i[cat]] = 0; 
	    	count=1;
		}     
	    else if(temp[cat][cat_i[cat]] > 0)  
	    {  
	        printf("CS.Proc No[Q%d-N%d] \t\t QT-%d\t\t LT-%d\t\t BT-%d\n", cat,cat_i[cat], scale*quant,temp[cat][cat_i[cat]],bt[cat][cat_i[cat]]);  
			temp[cat][cat_i[cat]] = temp[cat][cat_i[cat]] - scale*quant;
	        sum = sum + scale*quant;
	        
	    }  
	}
    if(temp[cat][cat_i[cat]]==0 && count==1)
    {  
        y--;
        printf("Proc No[Q%d-N%d] \t\t %d\t\t %d\t\t %d\n", cat,cat_i[cat], bt[cat][cat_i[cat]], sum-at[cat][cat_i[cat]], sum-at[cat][cat_i[cat]]-bt[cat][cat_i[cat]]);  
        wt = wt+sum-at[cat][cat_i[cat]]-bt[cat][cat_i[cat]]; 
		tat = tat+sum-at[cat][cat_i[cat]];
        count =0;     
    } 
    cat_i[cat]=cat_i[cat]+1;
    if(cat_i[cat]==cat_cnt[cat]) cat_i[cat]=0;
	cat=cat+1; 
	if (cat==tot_cat) cat=0;
}    
avg_wt = wt * 1.0/NOP;  
avg_tat = tat * 1.0/NOP;  
printf("\n Average Turn Around Time: \t%f", avg_tat);  
printf("\n Average Waiting Time: \t%f", avg_wt);  
}  
