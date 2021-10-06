#include <stdio.h>
#include <string.h>

void onlyIdentifierKept(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void symbolTableGenerate(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void numberedIdentifierKept(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int sl = 0;
char table[50][50][50];

void InsertSlNoInTable(int i, int j, int sl){                         //sl no converted into string and put into table
    int x = sl;
    int count = 0;

    while(sl != 0){
        sl = sl / 10;
        count++;
    }

    int k;
    for(k = count-1; k >= 0; k--){
        table[i][j][k] = (x % 10) + 48;
        x = x / 10;
    }
    table[i][j][count]  = '\0';
}

void InsertStringInTable(int i, int j, char* str2){              //strings are put into table
    int k;
    for(k = 0;k<strlen(str2);k++){
        table[i][j][k] = str2[k];
    }
    table[i][j][k]  = '\0';
}

void Insert(int sl, char* name, char* idtype, char* dataType, char* scope){
    InsertSlNoInTable(sl,0,sl+1);
    InsertStringInTable(sl,1,name);
    InsertStringInTable(sl,2,idtype);
    InsertStringInTable(sl,3,dataType);
    InsertStringInTable(sl,4,scope);
}

void UpdateScope(char* str1, char* str2, char* scope)
{
    int i;
    int a = Search(str1,scope);
    int b = Search(str2,scope);

    if(a==-1)
        a = Search(str1,"global");

    if(b==-1)
        b = Search(str2,"global");


    if(a!=-1){
        for(i = 0; table[b][5][i] != '\0'; i++){   //updating scope if str1 not global
            table[a][5][i] = table[b][5][i];
        }
        table[a][5][i]  = '\0';
    }

}

void UpdateId(char str1[], char str2[], char scope[]){
    int a = Search(str1,scope);
    int k;
    if(a!=-1){
        for(k = 0;k<strlen(str2);k++){    //updating id type
            table[a][2][k] = str2[k];
        }
        table[a][2][k]  = '\0';
    }
}

void Delete(char* str){
    int i;
    for(i = 0;i<50;i++){
        str[i] = '\0';
    }
}

int Search(char* str, char* scope){
   int i,k;
   char str2[50], str3[50];

   for(i = 0; i < sl; i++){
       Delete(str2);
       Delete(str3);

       for(k = 0; table[i][1][k] != '\0'; k++){ //id name
           str2[k] =  table[i][1][k];
       }

       for(k = 0;table[i][4][k]!='\0';k++){     //data type
           str3[k] =  table[i][4][k];
       }

       if(strcmp(str,str2) == 0 && strcmp(scope,str3) == 0)
           return i;
   }
   return -1;
}

void DisplayTable()
{
    int i,j;
    printf("\t\t\t\t\tSymbol Table\t\t\n\n");
    printf("Sl.No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    printf("\n");
    for(i = 0;i<sl;i++)
    {
        int bl = 0;
        int k;
        char s[50];
        Delete(s);
        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;
            printf("%s\t\t",table[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void printTableInFile(FILE *target)
{
    int i,j;
    fputs("Sl.No.\t\tName\tId Type\t\t\tData Type\t\t\tScope\t\t\tValue", target);
    fputs("\n", target);
    for(i = 0;i<sl;i++){
        int bl = 0;
        int k;
        char s[50];
        Delete(s);
        for(k = 0;table[i][2][k]!='\0';k++){
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++){
            if(bl==1 && j==5)
                continue;
            fputs(table[i][j], target);
            fputs("\t\t\t", target);
        }
        fputs("\n", target);
    }
}



void CopyIdToArray(char* str1, char* str2){
    int i, j;
    Delete(str1);

    for(i = 3,j = 0;i<strlen(str2);i++,j++){
        str1[j] = str2[i];
    }
}

void CopyStringToArray(char* str1, char* str2){
    int i;
    Delete(str1);

    for(i = 0; i < strlen(str2); i++){
        str1[i] = str2[i];
    }
}

int isDataType(char str1[]){
    int n = 5;
    char str2[5][20] = {"int","float","double","char", "void"};
    int i;
    for(i = 0;i<n;i++){
        if(strcmp(str1,str2[i])==0)
            return 1;
    }
    return 0;
}

int isNumerical(char *lex){
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) {
        s=1; i++;
    }
    else if(lex[i]=='.') {
        s=2;
        i++;
    }
    else
        s=0;
    l=strlen(lex);
    if(s==1){
        for(;i<l;i++){
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.') {
                s=2;
                i++;
                break;
            }
            else {
                s=0;
                break;
            }
        }
    }
    if(s==2){
        if(isdigit(lex[i])) {
            s=3; i++;
        }
        else
            s=0;
    }
    if(s==3){
        for(;i<l;i++) {
            if(isdigit(lex[i]))
                s=3;
            else {
                s=0;
                break;
            }
        }
    }
    if(s==3){
        s=1;
    }
    return s;
}




int main(){
    char c;
    char sourceFileName[30] = "Asm3_Input.txt";
    char targetFileName1[30] = "Asm3_O1.txt";
    char targetFileName2[30] = "Asm3_T2.txt";
    char targetFileName3[30] = "Asm3_O2.txt";
    FILE *source, *target;
    // step 1
    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName1, "w");
    onlyIdentifierKept(source, target, sourceFileName, targetFileName1);

     fclose(source);
    fclose(target);
    target = fopen (targetFileName1,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
    printf("\n\n\n");



    // step 2
    source = fopen(targetFileName1, "r");
    target = fopen(targetFileName2, "w");
    symbolTableGenerate(source, target, sourceFileName, targetFileName1);

    // 4
    source = fopen(targetFileName1, "r");
    target = fopen(targetFileName3, "w");
    numberedIdentifierKept(source, target, sourceFileName, targetFileName1);


    remove(targetFileName2);

    fclose(source);
    fclose(target);

    printf("\n\nAfter the identifiers are numbered : \n\n");

    target = fopen (targetFileName3,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
    printf("\n\n\n");

}

// step 1
void onlyIdentifierKept(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int bracketStarting = 0;

    if(source == NULL || target == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        fputc(' ',target);
        while( (c = fgetc(source)) != EOF){
            if(bracketStarting == 0 && c == '['){
                bracketStarting = 1;
                fputc('[',target);
                continue;
            }
            if(bracketStarting == 1){
                if(c == 'i'){
                    c = fgetc(source);
                    if(c == 'd'){
                        fputs("id ",target);
                        continue;
                    }
                }
                else if(c == ' '){                  //token checking complete
                    bracketStarting = 0;
                    continue;
                }
            }
            else{
                fputc(c,target);
            }
        }
    }
    fclose(source);
    fclose(target);
}


// step 2
void symbolTableGenerate(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    int count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100];
    char previous[100], temp[100];                //previous = "=", "return", any Id
    CopyStringToArray(scope,"global");      //In the beginning, default scope is global

    while( (c = fgetc(source)) != EOF){
        int i = 0;
        if(c=='['){                         //retrieving each token inside [] brackets and storing in str[] array
            while(1){
                c = fgetc(source);
                if(c==']')
                    break;
                str[i] = c;
                i++;
            }

            if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3){
               CopyIdToArray(temp,str);

               if(Search(temp,scope) == -1 && strcmp(previous,"=")!=0 ){       //id is not present in the table
                   Insert(sl,temp,"var",dataType, scope);                   //id type is variable
                   sl++;
               }
               else{                                                    //id is already present in the table
                   if(strcmp(previous,"=") == 0){
                      UpdateScope(name,temp,scope);
                   }
                   else if(strcmp(previous,"return") == 0){
                      UpdateScope(scope,temp,scope);
                   }
               }
               CopyIdToArray(name,str);
            }
            else if(isDataType(str)){
               CopyStringToArray(dataType,str);
            }
            else if(isNumerical(str)){
               if(strcmp(previous, "=") == 0){                  //if previously = is stored then scope will be previous id
                   if(Search(name, scope) != -1){
                       InsertStringInTable(Search(name,scope), 5, str);     //5th column is scope
                   }
                   else if(Search(name,"global") != -1 ){       //if previously "global" is stored then scope will be previous "global"
                       InsertStringInTable(Search(name,"global"), 5, str);
                   }
               }

               else if(strcmp(previous,"return") == 0){         //if previously "return" is stored then scope will be previous "global"
                   if(Search(scope,"global") != -1)
                       InsertStringInTable(Search(scope,"global"), 5, str);
               }
               CopyStringToArray(value,str);
            }
            else if(strlen(str)==1){
                if(str[0]=='('){
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3) {     //if previously a id is got
                        if(count==0){
                            CopyStringToArray(scope,name);
                            UpdateId(name,"func","global");             //function
                        }
                    }
                }
                else if(str[0]=='{'){
                    count++;
                }
                else if(str[0]=='}'){       //after closing bracket, scope will be global
                    count--;

                    if(count==0){
                        CopyStringToArray(scope,"global");
                    }
                }
            }
            CopyStringToArray(previous,str);                //will store previous string token
        }
        else{
            Delete(str);
            i = 0;
        }
    }
    DisplayTable();
    printTableInFile(target);
    fclose(source);
    fclose(target);
}


//step4
void numberedIdentifierKept(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    int i, count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100];
    char previous[100], temp[100];

    while( (c = fgetc(source)) != EOF){
        if(c=='['){                              //retrieving each token inside [] brackets and storing in str[] array
            while(1){
                c = fgetc(source);
                if(c==']')
                    break;
                str[i] = c; i++;
            }
            if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3){
                Delete(temp);
                CopyIdToArray(temp,str);
                fputs("[id",target);

                if(Search(temp,scope) != -1){                //get serial no of the id and print
                    fprintf(target," %d", Search(temp,scope) + 1);
                }
                else{
                    fprintf(target," %d", Search(temp,"global") + 1);
                }

                fputc(']',target);
                CopyIdToArray(name,str);
            }

            else if(strlen(str)==1){
                if(str[0]=='('){
                    //for maintaining scope
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3){     //if previously a id is got
                        if(count==0){
                            CopyStringToArray(scope,name);
                        }
                    }
                }
                else if(str[0]=='{'){
                    count++;
                }
                else if(str[0]=='}'){       //after closing bracket, scope will be global
                    count--;
                    if(count==0){
                        CopyStringToArray(scope,"global");
                    }
                }
                fputc('[',target);
                fputc(str[0],target);
                fputc(']',target);
            }
            else{
                fputc('[',target);
                fputs(str, target);
                fputc(']',target);
            }
            CopyStringToArray(previous,str);
        }
        else{
            fputc(c,target);
            Delete(str);
            i = 0;
        }
    }
}
