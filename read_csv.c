# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
//# include <stdarg.h>
# define Maxrow 25
# define Maxcol 12
# define len 300  //�Ѵ�����Ԫ���������궨��

/*�Զ�������Ƚ��㷨*/
double in[100];
int cmp_double(const void* _a , const void* _b) //������ʽ�̶�
{
    double* a = (double*)_a;    //ǿ������ת��
    double* b = (double*)_b;
    return *a > *b ? 1 : -1; //�ر�ע��
}

/*�Զ�����λ������*/
double get_mid(double a[],int size)
{
  int i,j;
  double t;
  double mid;
  for (i=0;i<size-1;i++)//iΪ���������
  {
    for(j=0;j<size-i-1;j++)//jΪ��i����ȽϵĴ���
    {
      if(a[j]>a[j+1])
      {
        t=a[j];
        a[j]=a[j+1];
        a[j+1]=t;
      }
    }
  }
  if(size%2==0)//�ж�Ԫ�ظ����Ƿ�Ϊż��
  {
    mid=(a[size/2]+a[size/2-1])/2;
    printf("raw����ż������λ����:%lf\n",mid);
  }
  else
    mid=a[(size-1)/2];
  return mid;
}

/*�Զ���涨��ֵ����Сֵ����*/
double get_min(double a[],int size,double rate )
{
  int num;
  num = floor(size*rate);
  printf("%d\n",num);
  double min = a[num];
  //double max = a[size-num];
  return min;
}

/*�Զ���涨��ֵ�����ֵ����*/
double get_max(double a[],int size,double rate )
{
  int num;
  num = floor(size*rate);
  //double min = a[num];
  double max = a[size-num];
  printf("%d\n",size - num);
  return max;
}

/*�Զ����ֵ�뷽����⺯��*/
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
  //�������ݵõ�һ��raw����
  FILE *fp = NULL;
	char *line,*record;
	char buffer[1024];
  double raw[Maxrow*Maxcol];
	if ((fp = fopen("fake0828_test_0.1_80120.csv", "at+")) != NULL)
	{
		fseek(fp, 0, 0);  //ÿ��Ӣ���ַ���СΪ1
		char delims[] = ",";
		char *result = NULL;
		int i = 0;
		while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//��û�ж�ȡ���ļ�ĩβʱѭ������
		{
			record = strtok(line, ",");
			while (record != NULL)//��ȡÿһ�е�����
			{
				if (strcmp(record, "Ps:") == 0)//����ȡ��Ps��һ��ʱ�����ټ�����ȡ
					return 0;
				//printf("%s ", record);//����ȡ����ÿһ�����ݴ�ӡ����
        raw[i] = atof(record);
        i++;
        //printf("%lf ", raw[i]);//����ȡ����ÿһ�����ݴ�ӡ����
				record = strtok(NULL, ",");
			}
		}
    fclose(fp);
		fp = NULL;
	}
  //������ȡ���ǻ���һ��һάraw�������
  //����
  int i;
  qsort(raw,Maxrow*Maxcol,sizeof(double),cmp_double);//����qsort����
  for(i=0;i<Maxrow*Maxcol;i++)//�������������
  {
    //printf("%lf\n",raw[i]);
    printf("%d ����> %lf\n",i,raw[i]);
  }
  //ȡ�涨��ֵ����ֵ
  int size = sizeof(raw)/sizeof(raw[0]);
  double min = get_min(raw,size,0.1);
  double max = get_max(raw,size,0.1);
  printf("raw�����min��:%lf\nraw�����max��::%lf\n",min,max);
  //ȡ��λ��
  //int size = sizeof(raw)/sizeof(raw[0]);
  printf("Ԫ��������%d\n",size);
  printf("raw�����е���λ����:%lf\n",get_mid(raw,size));
  //���ֵ�ͷ���
  double mean,var,std;
  get_mv(raw,size,&mean,&var,&std);
  printf("raw����ľ�ֵ�ǣ�%lf\n",mean);
  printf("raw����ķ����ǣ�%lf\n",var);
  printf("raw����ı�׼���ǣ�%lf\n",std);
  return 0;
}
