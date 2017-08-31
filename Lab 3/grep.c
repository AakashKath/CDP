#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void FileAbsent(char**);
void FolderPresent(char**);
void FilePresent(char*, char*);
int matchFound(char*, char*);

int main(int argc, char** argv){
	if(argv[2]!=NULL){
		FolderPresent(argv);
	}
	else{
		FileAbsent(argv);
	}
	return 0;
}

void FolderPresent(char** argv){
	DIR *d=opendir(argv[2]);	
	FILE *fp;
	struct dirent *entry;
	char c;
	int row, lineCount=0;
	if(d==NULL){
		printf("Unable to locate directory!\n");
		return;
	}
	int fileCount = 1;
	while((entry = readdir(d)) != NULL){
		char filename[30];
		strcpy(filename,argv[2]);
		strcat(filename,"/");	
		strcat(filename,entry->d_name);
		printf("\nFile %d : %s\n",fileCount,entry->d_name);
		fileCount++;
		FilePresent(filename, argv[1]);
	}
}

void FilePresent(char filename[], char argv[1]){
	FILE *fp;
	int lineCount=0, row, charCount;
	char c, *line = (char*)malloc(200*sizeof(char));
	fp=fopen(filename,"r");
	row=1;
	while((c=fgetc(fp)) != EOF){
		if(c=='\n'){
			row++;
		}
	}
	fclose(fp);
	fp = fopen(filename,"r");
	for(int i=1;i<row;i++){
		charCount = 0;
		for(c=fgetc(fp);c!='\n';c=fgetc(fp)){
			line[charCount] = c;
			charCount++;
		}
		if(matchFound(argv,line)){
			lineCount++;
			printf("%d.\t%s\n",i,line);
		}
		memset(line,'\0',200*sizeof(char));
	}
	fclose(fp);
	printf(".\n.\n.\nMatched lines:%d\n",lineCount);
}

int matchFound(char pattern[], char line[]){
	int i,k,counter = 0;
	for(i=0;i<strlen(line);i++){
		if(line[i] == pattern[0]){
			counter = 1;
			for(k=1;pattern[k] != '\0';k++){
				if(pattern[k] == '?'){
					if( (line[i+1]<48 || line[i+1]>57) && (line[i+1]<97 || line[i+1]>122) ){
						counter = 0;
						break;
					}
					if(line[i+2] == pattern[k+1] || line[i+1] == pattern[k+1]){
						counter = 1;
						break;
					}
				}
				else if(line[i+k] != pattern[k]){
					counter = 0;
					break;
				}
			}
		}
		if(counter == 1){
			return 1;
		}
	}
	return 0;
}

void FileAbsent(char** argv){
	int i=0, length, j=0, counter=0;
	int searchLength=strlen(argv[1]);
	char ch, input[10000];
	while(ch!='\n'){
		ch=getchar();
		input[i]=ch;
		i++;
	}
	length=strlen(input);
	for(i=0; i<length; i++){
		if(input[i]==' '){
			j=0;
		}
		else if(input[i]==argv[1][j]){
			j++;
		}
		else if(argv[1][j]=='?'){
			if(input[i]==argv[1][j+1]){
				j++;
			}
			if(input[i]!=' '){
				j++;
			}
		}
		else if(input[i]!=argv[1][j]){
			j=0;
		}
		if(j==searchLength){
			counter=1;
		}
		if(input[i]=='\n' && counter==1){
			printf("%s", input);
		}
	}
}