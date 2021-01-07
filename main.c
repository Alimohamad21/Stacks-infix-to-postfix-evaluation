#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
#include <math.h>
typedef union
{
    float fData;
    char  cData;
} Item;


typedef struct
{
    int top;
    Item items[MAXSIZE];
} Stack;

Stack* initialize();
int isEmpty(Stack *s);
Item top(Stack *s);
Item pop(Stack *s);
void push(Stack *s,Item x);
void infixToPostfix(char* infix, char* postfix);
float evaluatePostfix(char* postfix);
void replaceNewLineBySpace(char *s);
int pcheck(char a,char b);

int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result:%.2f\n\n", result);
        strcpy(infixExpr,"");
        strcpy(postfixExpr,"");
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
Stack* initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=-1;
    return s;

}
int isEmpty(Stack *s)
{
    if(s->top==-1)
        return 1;
    return 0;
}
Item  top(Stack *s)
{
    if(isEmpty(s))
        exit(0);
    return s->items[s->top];
}

Item pop(Stack *s)
{
    if(isEmpty(s))
        exit(0);
    return s->items[s->top--];
}
void push(Stack *s,Item x)
{
    if(s->top>=MAXSIZE-1)
        return;
    s->items[++s->top]=x;
}
void infixToPostfix(char* infix, char* postfix)
{
    Stack *s=initialize();
    char operator[2];
    operator[1]='\0';
    Item c;
    char *token=malloc(10);
    token=strtok(infix," ");
    while(token!=NULL)
    {
        if(token[0]=='('  )
        {
            c.cData=token[0];
            push(s,c);
        }
        else if(token[0]==')')
        {
            while(!isEmpty(s) && top(s).cData!='(')
            {
                operator[0]=pop(s).cData;
                strcat(postfix,operator);
                strcat(postfix," ");
            }
            pop(s); //to get rid of opening bracket
        }
        else if(token[0]=='+'||(token[0]=='-'&& !atof(token)) || token[0]=='*' || token[0]=='/' || token[0]=='^' )
        {
            while(!isEmpty(s) && top(s).cData!='('&& pcheck(top(s).cData,token[0]))
            {
                operator[0]=pop(s).cData;
                strcat(postfix,operator);
                strcat(postfix," ");
            }
            c.cData=token[0];
            push(s,c);
        }
        else
        {
            strcat(postfix,token);
            strcat(postfix," ");
        }
        token=strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        operator[0]=pop(s).cData;
        strcat(postfix,operator);
        strcat(postfix," ");
    }


}
float evaluatePostfix(char* postfix)
{
    char *token=malloc(10);
    Item pushed,x,y,result;
    Stack *s=initialize();
    token=strtok(postfix," ");
    while(token!=NULL)
    {
        if ( token[0]=='+'||(token[0]=='-'&& !atof(token)) || token[0]=='*' || token[0]=='/' || token[0]=='^')
        {
            y.fData=pop(s).fData;
            x.fData=pop(s).fData;
            if(token[0]=='+')
                result.fData=x.fData+y.fData;
            else if(token[0]=='*')
                result.fData=x.fData*y.fData;
            else if(token[0]=='-')
                result.fData=x.fData-y.fData;
            else if(token[0]=='/')
                result.fData=x.fData/y.fData;
            else if(token[0]=='^')
                result.fData=pow(x.fData,y.fData);
            push(s,result);
        }
        else
        {
            pushed.fData=atof(token);
            push(s,pushed);
        }
        token=strtok(NULL," ");
    }
    return top(s).fData;
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int pcheck(char a,char b)
{
    if(a=='+' || a=='-')
        a=1;
    else if(a=='/' || a=='*')
        a=2;
    else if(a=='^')
        a=3;
    if(b=='+' || b=='-')
        b=1;
    else if(b=='/' || b=='*')
        b=2;
    else if(a=='^')
        b=3;
    if(a==b)
    {
        if(a=='^')
            return 0;
        return 1;
    }
    return a>b?1:0;
}







