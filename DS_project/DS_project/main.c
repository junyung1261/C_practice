#include <stdio.h>
#include <string.h>

#define AUDIENCE_NUM 100
#define MOVIE_NUM 499
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

typedef struct actor {
	char *name;
	int avg_aud;
	int actor_count;
}actor;

typedef struct director {
	char *name;
	int dir_count;
}director;

typedef struct genre {
	char *name;
	int genre_count;

}genre;

typedef struct actor_heap{
	int capacity;
	int count;
	actor *actor;
}actor_heap;

typedef struct director_heap {
	int capacity;
	int count;
	director *director;
}director_heap;

typedef struct genre_heap {
	int capacity;
	int count;
	genre *genre;
}genre_heap;


typedef struct {
	int id;
	int visit[MOVIE_NUM];
	int view_count;
	actor_heap *pref_actor;
	genre_heap *pref_genre;
	director_heap *pref_diretor;
}audience;

movielist chart;
audience *test_aud[AUDIENCE_NUM];
actor *actors[2000];
genre *genres[20];
director *directors[MOVIE_NUM];

void parsing(char* str, int row) {
	int i = 0;
	char *token = NULL;
	char token2[100];
	movie *temp;
	movie *node = (movielist)malloc(sizeof(movie));

	node->name = (char*)malloc(sizeof(char) * 100);
	node->nation = (char*)malloc(sizeof(char) * 100);
	node->genre = (char**)malloc(sizeof(char*) * 3);
	node->director = (char*)malloc(sizeof(char) * 100);
	node->actors = (char**)malloc(sizeof(char*) * 10);
	for (int c = 0; c < 10; c++) {

		node->actors[c] = (char*)malloc(sizeof(char) * 100);
		node->actors[c] = NULL;
	}

	for (int j = 0; j < 3; j++) {
		node->genre[j] = NULL;
		node->actors[j] = NULL;
	}

	token = strtok(str, "\t");
	strcpy(node->name, token);

	token = strtok(NULL, "\t");
	node->audience = atoi(token);

	token = strtok(NULL, "\t");
	node->screen_num = atoi(token);

	token = strtok(NULL, "\t");
	strcpy(node->nation, token);

	token = strtok(NULL, "\t");
	strcpy(token2, token);

	token = strtok(NULL, "\t");
	strcpy(node->director, token);

	token = strtok(NULL, "|\r\n");

	while (token != NULL && i < 10) {
		node->actors[i] = (char*)malloc(sizeof(char) * 100);
		strcpy(node->actors[i], token);
		token = strtok(NULL, "|\r\n");
		i++;
	}

	i = 0;
	token = strtok(token2, "|");
	while (token != NULL && i < 3) {
		node->genre[i] = (char*)malloc(sizeof(char) * 100);
		strcpy(node->genre[i], token);
		token = strtok(NULL, "|");

		i++;
	}

	if (chart == NULL) {
		chart = node;
		node->nextmovie = NULL;
	}
	else {
		temp = chart;
		while (temp != NULL) {
			if (temp->nextmovie == NULL)
				break;
			temp = temp->nextmovie;
		}
		temp->nextmovie = node;
		node->nextmovie = NULL;
	}
}

void makeStruct(movie *chart) { /// 차트랑 visit을 비교해서 ->
	int k = 0;
	int j = 0;
	for (int i = 0; i < 10; i++) {
		j = 0;
		while (chart->actors[i] != NULL) {
			if (actors[j]->name == NULL) {

				actors[j]->name = (char*)malloc(sizeof(char) * 100);
				strcpy(actors[j]->name, chart->actors[i]);
				actors[j]->actor_count++;
				actors[j++]->avg_aud += chart->audience;

				break;
			}
			else if (!strcmp(actors[j]->name, chart->actors[i])) {

				actors[j]->actor_count++;
				actors[j++]->avg_aud += chart->audience;
				break;
			}

			else j++;
		}


	}

	for (int i = 0; i < 3; i++) {
		j = 0;
		while (chart->genre[i] != NULL) {
			if (genres[j]->name == NULL) {

				genres[j]->name = (char*)malloc(sizeof(char) * 100);
				strcpy(genres[j]->name, chart->genre[i]);
				genres[j]->genre_count++;


				break;
			}
			else if (!strcmp(genres[j]->name, chart->genre[i])) {

				genres[j]->genre_count++;

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
	movie* temp;

	temp = chart;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < MOVIE_NUM; j++) {
			percent = temp->audience / POPULATION;      // 관객수를 POPULATION으로 나누어 확률(0~100사이)를 구함
			test_aud[i]->visit[j] = 1;
			if (test_aud[i]->visit[j]) {
				test_aud[i]->view_count++;
				makeStruct(temp);
			}
			temp = temp->nextmovie;
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


void init_List() {                     // 구조체 배열(chart, test_aud 초기화);

	chart = (movielist)malloc(sizeof(movie));
	chart = NULL;


	for (int i = 0; i < AUDIENCE_NUM; i++) {
		test_aud[i] = (audience*)malloc(sizeof(audience));
		test_aud[i]->view_count = 0;
		test_aud[i]->id = i;
	}

	for (int i = 0; i < 2000; i++) {
		actors[i] = (actor_heap*)malloc(sizeof(actor_heap));
		actors[i]->name = NULL;
		actors[i]->actor_count = 0;
		actors[i]->avg_aud = 0;
	}
	for (int i = 0; i < 20; i++) {
		genres[i] = (genre_heap*)malloc(sizeof(genre_heap));
		genres[i]->name = NULL;
		genres[i]->genre_count = 0;

	}

}



genre_heap* createGenreHeap(int size) {

	int capacity = 200;
	struct genre_heap* heap = (genre_heap*)malloc(sizeof(genre_heap));
	heap->capacity = size;
	heap->count = 0;
	heap->genre = (genre*)malloc(sizeof(genre)*size);
	
	return heap;

}


int get_parent(genre_heap* heap, int index) {
	if (index <= 0 || index >= heap->capacity) return -1;

	return (index - 1) / 2;

}

int get_leftChild(genre_heap* heap, int index) {
	if (index < 0 || ((index * 2) + 1) >= heap->count) {
		return -1;

	}
	return (index * 2) + 1;

}

int get_rightChild(genre_heap* heap, int index) {
	if (index < 0 || ((index * 2) + 2) >= heap->count) {
		return -1;

	}
	return (index * 2) + 2;

}
void precolateUp(genre_heap* heap, int childIndex) {
	int parentIndex = get_parent(heap, childIndex);
	if (heap->genre[parentIndex].genre_count < heap->genre[childIndex].genre_count && parentIndex >= 0) {
		genre temp = heap->genre[parentIndex];
		heap->genre[parentIndex] = heap->genre[childIndex];
		heap->genre[childIndex] = temp;

		precolateUp(heap, parentIndex);


	}
	

}


void insertHeap(genre_heap* heap, genre data) {
	heap->genre[heap->count] = data;
	precolateUp(heap, heap->count);
	heap->count++;


}

void precolateDown(genre_heap* heap, int parentIndex) {
	if (heap->count <= 1) return;

	else {
		int left = get_leftChild(heap, parentIndex);
		int right = get_rightChild(heap, parentIndex);

		if (left == -1 && right == -1) return;

		int max = 0;
		if (heap->genre[left].genre_count > heap->genre[parentIndex].genre_count && left != -1) {
			max = left;

		}
		else { max = parentIndex; }
		if (heap->genre[right].genre_count > heap->genre[max].genre_count && right != -1) {
			max = right;

		}

		if (max == left || max == right) {
			genre temp = heap->genre[parentIndex];
			heap->genre[parentIndex] = heap->genre[max];
			heap->genre[max] = temp;
			precolateDown(heap, max);

		}

	}

}


genre deletHeap(genre_heap* heap) {
	if (heap->count == 0) return;

	genre del_data = heap->genre[0];
	if (heap->genre[heap->count - 1].genre_count != -1) {
		heap->genre[0] = heap->genre[heap->count - 1];
		heap->genre[heap->count - 1].genre_count = -1;

	}
	heap->count--;

	precolateDown(heap, 0);
	return del_data;
}



void main() {

	init_List();


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
		//for(int j =0; j<3; j++)if(chart[i]->actors[j]!=NULL)printf("%s\n", chart[i]->actors[j]);

	}

	i = 0;

	makeVisit();

	genre_heap* heap = createGenreHeap(20);

	for (i = 0; i < 20; i++) {

		insertHeap(heap, *genres[i]);

	}
	for (i = 0; i < 20; i++){
		printf("%s - %d\n", deletHeap(heap).name, deletHeap(heap).genre_count); }
	/*while (genres[i]->name != NULL) {

	printf("%s -%d\n", genres[i]->name, genres[i]->genre_count);
	i++;
	}

	while (actors[i]->name != NULL) {
	printf("%s -%d\n", actors[i]->name, actors[i]->avg_aud);
	i++;
	}*/

}