/*
	ID: 2015 556 032
		Cemsina Güzel
		Visual Studio 2015 - Console Application
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NPOP 50
#define ITER 200
#define NSIZE 11
#define CHANGE 10
#define MAX 90
#define MIN 65
int actual_size;
int FindCount(char s[]) {
	for (int i = 0; i < NSIZE; i++) if (s[i] == '\0') return i;
	s[NSIZE - 1] = '\0'; return NSIZE - 1;
}
int isInArray(int s[], int x, int _count) {
	for (int i = 0; i < _count; i++) if (s[i] == x) return 1;
	return 0;
}
void ToUppercase(char s[]) {
	for (int i = 0; i < actual_size; i++) if (s[i] >= 97 && s[i] <= 122) s[i] -= 32;
}
int total_function(char s[],char word[]) {
	int sum = 0;
	for (int i = 0; i < actual_size; i++) sum += abs(cost_function(s[i],word[i]));
	return sum;
}
int GetRandomValue(int from, int to) {
	return from + rand() % (to - from + 1);
}
void GenerateRandomString(char s[]) {
	for (int i = 0; i < actual_size; i++) {
		s[i] = GetRandomValue(65, 90);
	}
	if (actual_size < NSIZE) s[actual_size] = '\0';
}
int WhichCharsChange(int change_aim, int changeList[]) {
	int noList[CHANGE];
	for (int i = 0; i < actual_size; i++) noList[i] = i;
	int added = 0;
	while (added < change_aim) {
		int randomlySelected = GetRandomValue(0, actual_size - 1);
		if (!isInArray(changeList, randomlySelected, added)) {
			changeList[added] = randomlySelected;
			added++;
		}
	}
}
int cost_function(int a, int b) {
	return a - b;
}
int sort(int s[],int _count) {
	int isChanged=1,temp=0;
	while (isChanged) {
		isChanged = 0;
		for (int i = 0; i < _count-1; i++) {
			if (s[i] > s[i + 1]) {
				temp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = temp;
				isChanged = 1;
			}
		}
	}
}
int _ceil(double x) {
	int y = (int)x;
	return (y == x) ? y : y + 1;
}
void change_to_words_function(char s[]) {
	int change_aim = GetRandomValue(0, actual_size);
	int change_aim_list[CHANGE];
	WhichCharsChange(change_aim, change_aim_list);
	for (int i = 0; i < change_aim; i++) {
		int randomadd = GetRandomValue(0, 10);
		s[change_aim_list[i]] = (s[change_aim_list[i]] + randomadd > 90) ? s[change_aim_list[i]] : s[change_aim_list[i]] + randomadd;
	}
}
int CloneArray(char from[],char to[]) {
	for (int i = 0; i < NSIZE; i++) to[i] = from[i];
}
int main() {
	srand(time(NULL));
	char word[11];
	char popword[NPOP][11];
	char newpopword[NPOP][11];
	int fitness[NPOP];
	char newone[11];
	char newtwo[11];
	char newthree[11];
	char newfour[11];
	printf("Enter a word (max. 10 characters) : ");
	scanf("%s", word);
	actual_size = FindCount(word);
	ToUppercase(word);
	for (int i = 0; i < NPOP; i++) GenerateRandomString(popword[i]);
	int goal = 0;
	for (int i = 0; i < actual_size; i++) goal += word[i];
	int loop = 1;
	while (loop <= ITER) {
		for (int i = 0; i < NPOP; i++) fitness[i] = total_function(popword[i], word);
		for (int i = 0; i < NPOP; i++) {
			int randomnumbers[4];
			int added = 0;
			while (added < 4) {
				int num = GetRandomValue(0, NPOP-1);
				if (!isInArray(randomnumbers,num,4)) {
					randomnumbers[added] = num;
					added++;
				}
			}
			int fitnessrandom[4];
			for (int j = 0; j < 4; j++) fitnessrandom[j] = fitness[randomnumbers[j]];
			sort(fitnessrandom,4);
			int smalls[2];
			for (int j = 0; j < 4; j++) {
				if (fitness[randomnumbers[j]] == fitnessrandom[0]) smalls[0] = randomnumbers[j];
				if (fitness[randomnumbers[j]] == fitnessrandom[1]) smalls[1] = randomnumbers[j];
			}
			int cross = _ceil((double)actual_size/2);
			for (int j = 0; j < actual_size; j++) {
				newone[j] = popword[smalls[(j < cross) ? 0 : 1]][j];
				newtwo[j] = popword[smalls[(j < cross) ? 1 : 0]][j];
				newthree[j] = popword[smalls[(j < actual_size - cross) ? 0 : 1]][(j + cross>=actual_size) ? j-cross+1 : j + cross];
				newfour[j] = popword[smalls[(j < actual_size - cross) ? 1 : 0]][(j + cross >= actual_size) ? j - cross + 1 : j + cross];
			}
			newone[actual_size] = '\0';
			newtwo[actual_size] = '\0';
			newthree[actual_size] = '\0';
			newfour[actual_size] = '\0';
			int costnewone = total_function(newone,word);
			int costnewtwo = total_function(newtwo, word);
			int costnewthree = total_function(newthree, word);
			int costnewfour = total_function(newfour, word);
			int costs[] = { costnewone ,costnewtwo ,costnewthree ,costnewfour };
			sort(costs,4);
			if (costs[0] == costnewone) {
				change_to_words_function(newone);
				CloneArray(newone, newpopword[i]);
			}
			else if (costs[0] == costnewtwo) {
				change_to_words_function(newtwo);
				CloneArray(newtwo, newpopword[i]);
			}
			else if (costs[0] == costnewthree) {
				change_to_words_function(newthree);
				CloneArray(newthree, newpopword[i]);
			}
			else if (costs[0] == costnewfour) {
				change_to_words_function(newfour);
				CloneArray(newfour, newpopword[i]);
			}
		}
		for (int i = 0; i < NPOP; i++) CloneArray(newpopword[i], popword[i]);
		loop++;
	}
	for (int i = 0; i < NPOP; i++) fitness[i] = total_function(popword[i], word);
	int smallest = 0;
	for (int i = 0; i < NPOP; i++) if (fitness[i] < fitness[smallest]) smallest = i;
	printf("%s", popword[smallest]);
	getchar();
	getchar();
	return 0;
}
