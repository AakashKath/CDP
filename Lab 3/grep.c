#include <stdio.h>
#include <string.h>
#include <dirent.h>

void FilePresent(char**, char*);
void FileAbsent(char**);
void FolderPresent(char**);

int linec=0;

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
	struct dirent *entry;
	DIR *d=opendir(argv[2]);
	if(d==NULL){
		perror("opendir");
		return;
	}
	while((entry=readdir(d))!=NULL){
		if(!strcmp(entry->d_name,".") || !(strcmp(entry->d_name, ".."))){
			continue;
		}
		else{
			FilePresent(argv, entry->d_name);
			printf(".\n.\n.\n%d", linec);
			linec=0;
		}
	}
	closedir(d);
}

void FilePresent(char** argv, char* entry){
	int i=0, j=0, counter=0, lineCount=0;
	int searchLength=strlen(argv[1]);
	char c, *lineKeeper;
	FILE *fp;
	printf("\n\n%s\n\n", entry);
	fp = fopen(entry, "r");
	while(1){
		c=fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c=='\n'){
			if(counter==1){
				printf("%d. %s\n", lineCount+1, lineKeeper);
				linec++;
			}
			lineCount++;
			counter=0;
			memset(lineKeeper, ' ', j*sizeof(char));
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
