#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100
#define MAX_SIZE 50

typedef struct {
	char data[MAX_STACK_SIZE];
	int top;
}StackType;

// 스택 초기화
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검사
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, char item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

//삭제함수
char pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return '\0';
	}

	else return s->data[(s->top--)];
}

// 피크함수
char peek(StackType* s)
{
	return s->data[s->top];
}

// 대문자 > 소문자, 특수기호 뺀 후 스택에 저장
void savestack(StackType* s, char word[MAX_SIZE])
{
	int len = strlen(word);

	for (int i = 0; i < len; i++)
	{
		if ('a' <= word[i] && word[i] <= 'z') {
			push(s, word[i]);
		}
		else if ('A' <= word[i] && word[i] <= 'Z') {
			push(s, word[i] - ('A' - 'a'));
		}
	}
}

// 회문 확인 함수
void check(char* word, char* reverse)
{
	int len = strlen(word);
	int i;

	// word 배열을 reverse 배열에 복사
	for (i = 0; i < len; i++)
	{
		reverse[i] = word[i];
	}
	reverse[len] = '\0'; // 마지막에 널문자 입력

	// reverse 배열을 뒤집음
	int start = 0;
	int end = len - 1;
	while (start < end)
	{
		char temp = reverse[start];
		reverse[start] = reverse[end];
		reverse[end] = temp;

		start++;
		end--;
	}

	// word 배열과 reverse 배열을 비교하여 회문인지 확인
	if (strcmp(word, reverse) == 0) {
		printf("회문입니다.\n");
	}
	else {
		printf("회문이 아닙니다.\n");
	}
}


int main()
{
	do {
		int num = 0;
		char enter[MAX_SIZE]; // 입력 받은 문자 저장
		char word[MAX_SIZE]; // 변환된 단어 저장
		char reverse[MAX_SIZE]; // 변환된 단어 반대로 저장

		StackType s; // 입력 받은 문자에서 소문자 변환 및 특수기호 제외 저장하는 스택
		init_stack(&s);

		printf("문자열을 입력하세요 : ");
		scanf_s("%[^\n]s", enter, MAX_SIZE); // enter나오기 전까지 모든 값 저장

		// word 배열 초기화
		for (int i = 0; i < MAX_SIZE; i++) {
			word[i] = 0;
		}

		// reverse 배열 초기화
		for (int i = 0; i < MAX_SIZE; i++) {
			reverse[i] = 0;
		}

		// 대문자->소문자, 특수기호 제거하는 함수
		savestack(&s, enter);

		while (!is_empty(&s))
		{
			char popped = pop(&s);
			word[num] = popped;
			num++;
		}
		word[num] = '\0'; // 마지막에 널문자 입력

		// 회문 판별 함수
		check(word, reverse);

		printf("계속 하시겠습니까? (yes/no) ");
		char answer[4];
		scanf_s("%3s", answer, 4);
		if (strcmp(answer, "no") == 0) {
			break;
		}
		getchar(); // 버퍼에 남은 개행문자 처리
	} while (1);

	return 0;
}