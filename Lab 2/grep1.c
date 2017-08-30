#include <stdio.h>
#include <string.h>
#include <dirent.h>

void FileSearch(char*, int, char**);
void FileAbsent(char*, int);
//void FilePresent(char*, int, char**);

int main(int argc, char** argv){
	int searchLength, i;
	searchLength = strlen(argv[1]);
	char userSearch[searchLength];
	for(i=0; i<searchLength; i++){
		userSearch[i]=argv[1][i];
	}
	if(argv[2]!=NULL){
		FileSearch(userSearch, searchLength, argv);
	}
	else{
		FileAbsent(userSearch, searchLength);
	}
	return 0;
}

/*void FilePresent(char* userSearch, int searchLength, char* argv[2]){
	struct dirent *entry;
	DIR *d=opendir(argv[2]);
	if(d==0){
		perror("opendir");
		return;
	}
	while((entry=readdir(d))!=0){
		FilePresent(userSearch, searchLength, entry->d_name);
	}
	closedir(d);
}*/

void FileSearch(char* userSearch, int searchLength, char* argv[2]){
	int i=0, j=0, counter=0, lineCount=0, numberofline=0;
	char c, lineKeeper[10000];
	FILE *fp;
	fp = fopen(argv[2], "r");
	while(1){
		c=fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c=='\n'){
			if(counter==1){
				printf("%d. %s\n\n", lineCount+1, lineKeeper);
				numberofline++;
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
		if(c==userSearch[i]){
//			if(c!=' '){
				i++;
//			}
		}
		else if(userSearch[i]=='?'){
			if(c==userSearch[i+1]){
				i++;
			}
			if(c!=' '){
				i++;
			}
		}
		else if(c!=userSearch[i]){
			i=0;
		}
		if(i==searchLength){
			counter=1;
		}
	}
	printf("%d", numberofline);
	fclose(fp);
}

void FileAbsent(char* userSearch, int searchLength){
	int i=0, length, j=0, counter=0;
	char ch, input[10000];
	while(ch!='\n'){
		ch=getchar();
		input[i]=ch;
		i++;
	}
	length=strlen(input);
	for(i=0; i<length; i++){
		if(input[i]==userSearch[j] || userSearch[j]=='?'){
			j++;
		}
		else if(input[i]!=userSearch[j]){
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
