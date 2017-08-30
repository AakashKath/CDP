#include <stdio.h>
#include <string.h>
#include <dirent.h>

void FilePresent(char**);
void FileAbsent(char**);
void FolderPresent(char**);

int main(int argc, char** argv){
	if(argv[2]!=NULL){
//		FolderPresent(argv);
		FilePresent(argv);
	}
	else{
		FileAbsent(argv);
	}
	return 0;
}

void FolderPresent(char** argv){
	struct dirent *entry;
	DIR *d=opendir(argv[2]);
	if(d==NULL){
		perror("opendir");
		return;
	}
	while((entry=readdir(d))!=NULL){
		printf("%s\n", entry->d_name);
		if(!strcmp(entry->d_name,"checker.txt")){
//			FilePresent(argv, entry->d_name);
		}
	}
	closedir(d);
}

void FilePresent(char** argv){
	int i=0, j=0, counter=0, lineCount=0;
	int searchLength=strlen(argv[1]);
	char c, lineKeeper[10000];
	FILE *fp;
	fp = fopen(argv[2], "r");
	while(1){
//		printf("Play with while\n");
		c=fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c=='\n'){
			if(counter==1){
				printf("%d. %s\n", lineCount+1, lineKeeper);
			}
			lineCount++;
			counter=0;
			strcpy(lineKeeper, "");
			i=0;
			j=0;
		}
		else{
			lineKeeper[j]=c;
				j++;
		}
		if(c==' '){
			i=0;
		}
		else if(c==argv[1][i]){
			i++;
		}
		else if(argv[1][i]=='?'){
			if(c==argv[1][i+1]){
				i++;
			}
			if(c!=' '){
				i++;
			}
		}
		else if(c!=argv[1][i]){
			i=0;
		}
		if(i==searchLength){
			counter=1;
		}
	}
	fclose(fp);
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
