#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
void main(void){
    FILE *fp;//声明文件指针.
    char fname[30]="test_";//文件名字符串.
    int i,M,x,y,k,*p,*ptmp;
    printf("Type i(1<i<32) & m(1<<i >= M)...\n");
    while(1){//2^i应大于等于M,否则无法工作.
        scanf("%d%d",&i,&M);
        if(1<<i >= M) break;
        printf("Error! redo...\n");
    }
    p=(int *)malloc(sizeof(int)*M);//根据需求大小申请空间.
    ptmp=(int *)malloc(sizeof(int)*(y=1<<i));//这个空间用于实现不重复.
    if(p==NULL || ptmp==NULL){//若申请空间失败则返回系统.
        printf("Application memory failure...\n");
        exit(0);
    }
    srand((unsigned)time(NULL));//初始化随机发生器.
    for(x=0;x<y;ptmp[x]=1+x++);//初始化随机空间.
    for(x=0;x<M;x++,y--){//产生M个范围在1~2^i之间的不重复随机数存于p空间.
        p[x]=ptmp[k=rand()%y];
        ptmp[k]=ptmp[y-1];
    }
    strcat(strcat(fname,itoa(i,(char *)ptmp,10)),"_");//生成文件名.
    strcat(strcat(fname,itoa(M,(char *)ptmp,10)),".txt");
    free(ptmp);//释放临时空间.
    for(x=0;x<M;x++){//用选择法排序.
        for(k=x,y=k+1;y<M;y++)
            if(p[k]>p[y]) k=y;
        if(k>x){
            y=p[k];
            p[k]=p[x];
            p[x]=y;
        }
    }
    if((fp=fopen(fname,"w"))==NULL){//创建文件.
        printf("Create file failure...\n");
        exit(0);
    }
    fprintf(fp,"%s %d\n%s %d\n",".i",i,".M",M);//写文件头.
    for(x=0;x<M;fprintf(fp,"%d ",p[x++]));//将排序后的数据写入文件.
    free(p);//释放工作空间.
    fclose(fp);
}