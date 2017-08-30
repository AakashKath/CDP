#include <stdio.h>
#include <string.h>

void FilePresent(char*, int, char**);
void FileAbsent(char*, int);

int main(int argc, char** argv){
	int searchLength, i;
	searchLength = strlen(argv[1]);
	char userSearch[searchLength];
	for(i=0; i<searchLength; i++){
		userSearch[i]=argv[1][i];
	}
	if(argv[2]!=NULL){
		FilePresent(userSearch, searchLength, argv);
	}
	else{
		FileAbsent(userSearch, searchLength);
	}
	return 0;
}

void FilePresent(char* userSearch, int searchLength, char* argv[2]){
	int i=0, j=0, counter=0, lineCount=0;
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
		if(c==userSearch[i]){
			i++;
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
		if(input[i]==userSearch[j]){
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
