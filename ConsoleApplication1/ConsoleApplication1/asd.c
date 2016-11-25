#include <stdio.h>

#define AUDIENCE_NUM 100
#define MOVIE_NUM 100
#define POPULATION 70000



typedef struct movie* movielist;

typedef struct {
	char* name;
	int audience;
	int screen_num;
	char* nation;
	char** genre;
	char* director;
	char** actors;
	movielist nextmovie;

}movie;



typedef struct {
	char *name;
	int avg_aud;
	int actor_count;

}actor;

typedef struct {
	char *name;
	int dir_count;

}director;

typedef struct {
	char *name;
	int genre_count;

}genre;



typedef struct {

	int capacity;
	int count;
	actor *actor;


}actor_heap;

typedef struct {

	int capacity;
	int count;
	actor *director;

}director_heap;

typedef struct {

	int capacity;
	int count;
	actor *genre;

}genre_heap;


typedef struct {
	int id;
	int visit[MOVIE_NUM];
	int view_count;

	actor_heap *pref_actor;
	genre_heap *pref_genre;
	director_heap *pref_diretor;
}audience;




movie *chart[MOVIE_NUM];
audience *test_aud[AUDIENCE_NUM];
actor *actors[500];
genre *genres[20];
director *directors[MOVIE_NUM];

void parsing(char* str, int row) {

	int i = 0;


	char *token = NULL;
	char token2[100];


	token = strtok(str, "\t");
	strcpy(chart[row]->name, token);

	token = strtok(NULL, "\t");
	chart[row]->audience = atoi(token);

	token = strtok(NULL, "\t");
	chart[row]->screen_num = atoi(token);

	token = strtok(NULL, "\t");
	strcpy(chart[row]->nation, token);

	token = strtok(NULL, "\t");
	strcpy(token2, token);

	token = strtok(NULL, "\t");
	strcpy(chart[row]->director, token);

	token = strtok(NULL, "\n|");
	while (token != NULL && i < 3) {


		strcpy(chart[row]->actors[i], token);


		i++;
		token = strtok(NULL, "\n|");
	}

	i = 0;
	token = strtok(token2, "\n|");
	while (token != NULL && i < 3) {

		chart[row]->genre[i] = (char*)malloc(sizeof(char) * 100);
		strcpy(chart[row]->genre[i], token);
		token = strtok(NULL, "\n|");

		i++;
	}

}



void makeStruct(movie *chart) {
	int k = 0;
	int j = 0;
	for (int i = 0; i < 3; i++) {
		j = 0;
		while (chart->actors[i] != NULL) {
			if (actors[j]->name == NULL) {

				actors[j]->name = (char*)malloc(sizeof(char) * 100);
				strcpy(actors[j]->name, chart->actors[i]);
				actors[j]->actor_count++;
				actors[j]->avg_aud += chart->audience;

				break;
			}
			else if (strcmp(actors[j]->name, chart->actors[i])) {

				actors[j]->actor_count++;
				actors[j]->avg_aud += chart->audience;
				break;
			}

			else j++;
		}


	}
	/*
	for (int i = 0; i < sizeof(genre) / sizeof(char); i++) {
	int j = 0;
	int k = 0;
	while (1) {
	if (genres[j++]->name == genre[i]) {
	genres[k++]->genre_count++;

	break;
	}
	else {
	genres[k]->name = genre[i];
	genres[k++]->genre_count++;

	}

	}

	}

	int j = 0;
	int k = 0;
	while (1) {
	if (directors[j++]->name == director) {
	directors[k++]->dir_count++;

	break;
	}
	else {
	directors[k]->name = director;
	directors[k++]->dir_count++;

	}

	}*/



}


void makeVisit() {                        //각 사람별로 모든 영화에 대해 관객수에 따라 영화를 볼것인지 아닌지 선택

	srand(time(NULL));

	int percent = 0;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < MOVIE_NUM; j++) {
			percent = chart[j]->audience / POPULATION;      // 관객수를 POPULATION으로 나누어 확률(0~100사이)를 구함
			test_aud[i]->visit[j] = (rand() % 101 < percent) ? 1 : 0;
			if (test_aud[i]->visit[j]) {
				test_aud[i]->view_count++;
				//makeStruct(chart[j]);

			}

		}
	}

}

actor_heap* creatActorHeap() {
	int capacity = 300;
	actor_heap *heap = (actor_heap*)malloc(sizeof(actor_heap));
	heap->capacity = capacity;
	heap->actor = (actor*)malloc(sizeof(actor)*capacity);



	return heap;
}


void initializse() {                     // 구조체 배열(chart, test_aud 초기화);

	for (int i = 0; i < MOVIE_NUM; i++) {

		chart[i] = (movie*)malloc(sizeof(movie));
		chart[i]->name = (char*)malloc(sizeof(char) * 100);
		chart[i]->nation = (char*)malloc(sizeof(char) * 100);
		chart[i]->genre = (char**)malloc(sizeof(char*));

		chart[i]->director = (char*)malloc(sizeof(char) * 100);
		chart[i]->actors = (char**)malloc(sizeof(char*) * 3);
		for (int j = 0; j < 3; j++) {
			chart[i]->actors[j] = (char*)malloc(sizeof(char) * 100);
			chart[i]->actors[j] = NULL;

		}

	}

	for (int i = 0; i < AUDIENCE_NUM; i++) {
		test_aud[i] = (audience*)malloc(sizeof(audience));
		test_aud[i]->view_count = 0;
		test_aud[i]->id = i;
	}

	for (int i = 0; i < 500; i++) {
		actors[i] = (actor_heap*)malloc(sizeof(actor_heap));
		actors[i]->name = NULL;
		actors[i]->actor_count = 0;
		actors[i]->avg_aud = 0;
	}

}

void main() {

	initializse();


	FILE* fp = fopen("test.txt", "rb");
	char buff[1000];
	//fread(buff, 1, sizeof(buff), fp);



	int i = 0;
	while (!feof(fp) && i< MOVIE_NUM)
	{


		if (buff != NULL)
		{
			fgets(buff, 1000, fp);
			parsing(buff, i++);

		}

	}

	fclose(fp);

	for (i = 0; i < MOVIE_NUM; i++) {
		//printf("%s         %d   %d   %s   %s   %s   %s\n", chart[i]->name, chart[i]->audience, chart[i]->screen_num, chart[i]->nation, chart[i]->genre[0], chart[i]->director, chart[i]->actors[0]);
		for (int j = 0; j<3; j++)printf("%s\n", chart[i]->actors[j]);

	}

	i = 0;

	//makeVisit();

	/*while (actors[i]->name != NULL) {
	printf("%s\n", actors[i++]->name);


	}*/
}