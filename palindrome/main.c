#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100
#define MAX_SIZE 50

typedef struct {
	char data[MAX_STACK_SIZE];
	int top;
}StackType;

// ���� �ʱ�ȭ
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� �˻�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� �˻�
int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, char item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

//�����Լ�
char pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return '\0';
	}

	else return s->data[(s->top--)];
}

// ��ũ�Լ�
char peek(StackType* s)
{
	return s->data[s->top];
}

// �빮�� > �ҹ���, Ư����ȣ �� �� ���ÿ� ����
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

// ȸ�� Ȯ�� �Լ�
void check(char* word, char* reverse)
{
	int len = strlen(word);
	int i;

	// word �迭�� reverse �迭�� ����
	for (i = 0; i < len; i++)
	{
		reverse[i] = word[i];
	}
	reverse[len] = '\0'; // �������� �ι��� �Է�

	// reverse �迭�� ������
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

	// word �迭�� reverse �迭�� ���Ͽ� ȸ������ Ȯ��
	if (strcmp(word, reverse) == 0) {
		printf("ȸ���Դϴ�.\n");
	}
	else {
		printf("ȸ���� �ƴմϴ�.\n");
	}
}


int main()
{
	do {
		int num = 0;
		char enter[MAX_SIZE]; // �Է� ���� ���� ����
		char word[MAX_SIZE]; // ��ȯ�� �ܾ� ����
		char reverse[MAX_SIZE]; // ��ȯ�� �ܾ� �ݴ�� ����

		StackType s; // �Է� ���� ���ڿ��� �ҹ��� ��ȯ �� Ư����ȣ ���� �����ϴ� ����
		init_stack(&s);

		printf("���ڿ��� �Է��ϼ��� : ");
		scanf_s("%[^\n]s", enter, MAX_SIZE); // enter������ ������ ��� �� ����

		// word �迭 �ʱ�ȭ
		for (int i = 0; i < MAX_SIZE; i++) {
			word[i] = 0;
		}

		// reverse �迭 �ʱ�ȭ
		for (int i = 0; i < MAX_SIZE; i++) {
			reverse[i] = 0;
		}

		// �빮��->�ҹ���, Ư����ȣ �����ϴ� �Լ�
		savestack(&s, enter);

		while (!is_empty(&s))
		{
			char popped = pop(&s);
			word[num] = popped;
			num++;
		}
		word[num] = '\0'; // �������� �ι��� �Է�

		// ȸ�� �Ǻ� �Լ�
		check(word, reverse);

		printf("��� �Ͻðڽ��ϱ�? (yes/no) ");
		char answer[4];
		scanf_s("%3s", answer, 4);
		if (strcmp(answer, "no") == 0) {
			break;
		}
		getchar(); // ���ۿ� ���� ���๮�� ó��
	} while (1);

	return 0;
}