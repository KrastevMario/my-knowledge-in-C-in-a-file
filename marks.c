/*
Requisiti dell'esercizio:
1. fare una struct con delle materie e voti [Subject ---- mark]
2. fare la average di ogni mark [Subject ---- mark ---- average]
3. cercare la Subject con la average piu alta [Subject ---- mark ---- average >>> (alla fine) stampa Maxaverage
4. ordinare le materie dalla Subject piu alta a quella piu bassa [Subject ---- mark ---- average]
5. modificare un mark [decidi la Subject e modifica il mark che c'e in quella posizione]
6. salvare e caricare da un file record compreso il numero di materie presenti nella tabella
*/

/*
Program requirements:
1. Use the struct to create subjects with marks
2. Calculate the average for each mark
3. Get the subject with the highest average
4. Modify a mark
5. Write and Read from a file.
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define true 1
#define false 0

#define NV 20
#define NM 10
#define FILENAME "dati.txt"

// definisco la struct || declaring the struct
typedef struct Subject {
	char name[4]; 
	float mark[NV]; 
	float average; 
	int nMarks;
} Subject;

int nSubject = 0;

//  le funzioni  || the functions
void readData(Subject *);
int readLine(FILE*, char*, int);
void printData(Subject*);
float averageM(Subject m);
int caricaBuffer(char buffer[20][10]);
int rline(FILE *fd, char *str, int n);
int maxaverage(Subject m[NM]);

// il main(le funzioni che devi eseguire appena il programma fa lo start)
void main(){
	FILE *save = fopen(FILENAME, "r");
	
	Subject subjects[NM];
	readData(subjects);
	maxaverage(subjects);
    //modificamark(subjects);

	printf("\n");
	
	printData(subjects);

	fclose(save);
}

// leggi i dati dal file || read some data from file
void readData(Subject m[NM]){
	char dati[20][10];
	int righe = caricaBuffer(dati);
	char name[4], name1[4];
	char nameDati[4];
	float markDati;
	float mark;
	int fnd;
	sscanf(dati[0], "%s %f", name, &mark);
	strcpy(m[0].name, name);
	for(int i = 0; i < righe; i++){
		fnd = false;
		sscanf(dati[i], "%s %f", name, &mark);
		for(int j = 0; j < i; j++){
			sscanf(dati[j], "%s %f", name1, &mark);
			if(!strcmp(name1, name)){
				fnd = true;
				break;
			}
		}
		if(!fnd){
			strcpy(m[nSubject].name, name);
			nSubject++;
		}
	}
	for(int i = 0; i < nSubject; i++) m[i].nMarks = 0;

	for(int i = 0; i < nSubject; i++){
		for(int j = 0; j < righe; j++){
			sscanf(dati[j], "%s %f", nameDati, &markDati);
		//	printf("\n\n\t\t%4.2f\n", markDati);
			if(!strcmp(m[i].name, nameDati)){
				m[i].mark[m[i].nMarks] = markDati;
				m[i].nMarks++;
			}
		}		
		
	}

}

//leggi riga || read a line
int readLine(FILE *f, char* str, int size){
	char c;
	for(int i = 0; (c = getc(f)) != '\n' && i < size && !feof(f); i++){
		 str[i] = c;
	}
	return true;
}

//average di ogni Subject || the average of each subject
float averageM(Subject m){
	float num = 0;
	//m.average = 0.0;
	for(int i = 0; i < m.nMarks; i++){
		num += m.mark[i];
	}
	m.average = (num/m.nMarks);
	//printf("\n\taverage calcolata\n");
	return m.average;
}
//catrico la memoria || loading the memory
int caricaBuffer(char buffer[20][10]){
	FILE *fp = fopen(FILENAME, "r");
	fseek(fp, 0, SEEK_SET);
	int i;
	if(fp){
		printf("\n\tFile Aperto!\n");
		for(i = 0; !feof(fp); i++){
			rline(fp, buffer[i], 10);
		//	printf("\n%s", buffer[i]);
		}
	}
	else{
		printf("\n\tFile 'dati.txt' inesistente!\n");
		return 0;
	}
	fclose(fp);
	return (i-1);
}

//stampa tutti i dati || print all data (info)
void printData(Subject Subject[NM]) {
	for(int i = 0; i < nSubject; i++){
		printf("\n %s | ", Subject[i].name);
		for(int j = 0; j < Subject[i].nMarks; j++)
			printf(" %4.2f ", Subject[i].mark[j]);
		printf("  average:  %4.2f", averageM(Subject[i]));
		//printf("MAXaverage : %d" , maxaverage(Subject));
		printf("\n");
	}
}

//reading the lines
int rline(FILE *fd, char *str, int n) {
  int i, m = 0, c;
  int size = 1024;
  char buffer[size];
  char *b = buffer;

  while((c = getc(fd)) != EOF && c != '\n' && m < size) buffer[m++] = c;

  for (i=0; i<m && i<n; i++) str[i] = buffer[i];
  str[i] = '\0';

  return m;
}

/* 									|| 	Questa e la average massima 	|| Max average
int maxaverage(Subject m[NM]){
	int max = m[0].average;
	for(int i = 0; i < nSubject; i++){
		if (m[i].average > max){
			max = m[i].average;
		}
	}
	return max;
}
*/

//modifica un mark || modify a mark
void modificamark(Subject m, int cellamark, int mark){
	m.mark[cellamark] = mark;
}


    





