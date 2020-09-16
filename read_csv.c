# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
//# include <stdarg.h>
# define Maxrow 25
# define Maxcol 12
# define len 300  //把待处理元素总数量宏定义

/*自定义排序比较算法*/
double in[100];
int cmp_double(const void* _a , const void* _b) //参数格式固定
{
    double* a = (double*)_a;    //强制类型转换
    double* b = (double*)_b;
    return *a > *b ? 1 : -1; //特别注意
}

/*自定义中位数函数*/
double get_mid(double a[],int size)
{
  int i,j;
  double t;
  double mid;
  for (i=0;i<size-1;i++)//i为排序的趟数
  {
    for(j=0;j<size-i-1;j++)//j为第i趟需比较的次数
    {
      if(a[j]>a[j+1])
      {
        t=a[j];
        a[j]=a[j+1];
        a[j+1]=t;
      }
    }
  }
  if(size%2==0)//判断元素个数是否为偶数
  {
    mid=(a[size/2]+a[size/2-1])/2;
    printf("raw数组偶数的中位数是:%lf\n",mid);
  }
  else
    mid=a[(size-1)/2];
  return mid;
}

/*自定义规定阈值的最小值函数*/
double get_min(double a[],int size,double rate )
{
  int num;
  num = floor(size*rate);
  printf("%d\n",num);
  double min = a[num];
  //double max = a[size-num];
  return min;
}

/*自定义规定阈值的最大值函数*/
double get_max(double a[],int size,double rate )
{
  int num;
  num = floor(size*rate);
  //double min = a[num];
  double max = a[size-num];
  printf("%d\n",size - num);
  return max;
}

/*自定义均值与方差求解函数*/
void get_mv(double a[],int size,double *aver,double *vari,double *std)
{
  int i;
  double *p,aver2;
  *aver =0.0;
  for(p=a+(size-1);p>=a;--p)
  {
    *aver+=*p;
    aver2+=(*p)*(*p);
  }
  *aver/=size;
  aver2/=size;
  *vari=aver2-(*aver)*(*aver);
  *std=sqrt(*vari);
}

int main()
{
  //读入数据得到一个raw数组
  FILE *fp = NULL;
	char *line,*record;
	char buffer[1024];
  double raw[Maxrow*Maxcol];
	if ((fp = fopen("fake0828_test_0.1_80120.csv", "at+")) != NULL)
	{
		fseek(fp, 0, 0);  //每个英文字符大小为1
		char delims[] = ",";
		char *result = NULL;
		int i = 0;
		while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续
		{
			record = strtok(line, ",");
			while (record != NULL)//读取每一行的数据
			{
				if (strcmp(record, "Ps:") == 0)//当读取到Ps那一行时，不再继续读取
					return 0;
				//printf("%s ", record);//将读取到的每一个数据打印出来
        raw[i] = atof(record);
        i++;
        //printf("%lf ", raw[i]);//将读取到的每一个数据打印出来
				record = strtok(NULL, ",");
			}
		}
    fclose(fp);
		fp = NULL;
	}
  //特征提取都是基于一个一维raw数组进行
  //排序
  int i;
  qsort(raw,Maxrow*Maxcol,sizeof(double),cmp_double);//调用qsort排序
  for(i=0;i<Maxrow*Maxcol;i++)//输出排序后的数组
  {
    //printf("%lf\n",raw[i]);
    printf("%d ——> %lf\n",i,raw[i]);
  }
  //取规定阈值的最值
  int size = sizeof(raw)/sizeof(raw[0]);
  double min = get_min(raw,size,0.1);
  double max = get_max(raw,size,0.1);
  printf("raw数组的min是:%lf\nraw数组的max是::%lf\n",min,max);
  //取中位数
  //int size = sizeof(raw)/sizeof(raw[0]);
  printf("元素数量：%d\n",size);
  printf("raw数组中的中位数是:%lf\n",get_mid(raw,size));
  //求均值和方差
  double mean,var,std;
  get_mv(raw,size,&mean,&var,&std);
  printf("raw数组的均值是：%lf\n",mean);
  printf("raw数组的方差是：%lf\n",var);
  printf("raw数组的标准差是：%lf\n",std);
  return 0;
}
