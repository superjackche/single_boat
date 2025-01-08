#include<stdio.h>
#include<stdlib.h>

typedef struct Time
{
    int        hour , minute , second ;
}TIME ;    // 时间结构，三个变量依次代表时、分、秒。

typedef struct student 
{
    int        id;        
    TIME    start , end ;
} STUDENT;    // 学生结构， 三个变量依次为学号，开始时间和结束时间

void Sort(STUDENT *p,int n);
STUDENT * Create( int size ) ;

int main()
{
    int        i , n ;
    STUDENT    *students ;     

    scanf("%d",&n);  
    students = Create( n ) ;
    
    if ( students != NULL )
    {
        for( i = 0 ; i < n ; i++ ) 
            scanf( "%d%d%d%d%d%d%d" , &students[i].id ,
             &students[i].start.hour , &students[i].start.minute , &students[i].start.second , 
             &students[i].end.hour , &students[i].end.minute , &students[i].end.second );
    
        Sort( students , n );
        for( i = 0 ; i < n ; i++ ) 
            printf("%d\n" , students[i].id);
            
        free( students ) ;
    }
    
    return 0;
}

STUDENT * Create( int size ) {
    STUDENT *students = (STUDENT*)malloc(size*sizeof(STUDENT));
    if (students != NULL) {
        return students;
    } else return NULL; 
}

int compare(const void *a, const void *b) {
    STUDENT *s1 = (STUDENT*) a;
    STUDENT *s2 = (STUDENT*) b;
    int sign1 = (s1->end.hour - s1->start.hour)*3600 + (s1->end.minute - s1->start.minute)*60 + (s1->end.second - s1->start.second);
    int sign2 = (s2->end.hour - s2->start.hour)*3600 + (s2->end.minute - s2->start.minute)*60 + (s2->end.second - s2->start.second);
    return sign2 - sign1;
}

void Sort(STUDENT *p,int n) {
    qsort(p, n, sizeof(STUDENT), compare);
}