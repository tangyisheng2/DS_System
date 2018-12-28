#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define _CRT_SECURE_NO_WARNINGS

/*
struct file {
short level;	//����������
unsigned flags;	//�ļ�״̬��־
char fd;	//�ļ�������
unsigned char hold;	//��������С
short bsize;	//�ļ����������׵�ַ
unsigned char *buffer;	//ָ���ļ��������Ĺ���ָ��
unsigned char *curp;	//������Ϣ
unsigned istemp;
short token;
};
*/
struct node
{
	struct node *pre;	//ǰһ�ڵ�ָ����
	unsigned int code;	//���
	char name[50];	//����
	float price;	//�۸�
	unsigned long int barcode;	//������
	struct inport_date	//����
	{
		int month;	//��
		int day;	//��
	};
	int sales;	//����
	struct node *next;	//��һ�ڵ�ָ����
};	//����ڵ�ṹ

//Intail System
static int init_system();	//��ʼ��ϵͳ
int show_main_menu(struct node *head);	//��ӡ���˵�
static int init_list(struct node *head);	//��ʼ����
int init_array(struct node *head, struct node **node_array);	//��ʼ������

//BasicFunction
int edit_data(struct node *node);	//�޸ı�������
struct node *get_last_node(struct node *head);	//��ȡ����βָ��
int print_title();
int print_list(struct node *head);	//��ӡ����
int print_sorted_list(struct node *head);	//��ӡ������б�
int print_node(struct node *node_current);	//��ӡ�ڵ�
int check_file_empty(const char PATH[]);	//����ļ�Ϊ��
int get_len(struct node *head);	//��ȡ����
int relink_node(struct node **node_array, struct node *head, int len);	//������������

//Function
int add_node(struct node *head);	//��ӽڵ�
int print_list(struct node *head);	//��ӡ�б�
int search_list(struct node *head);	//����
int sort_list(struct node *head);	//��������
int insert_node(struct node *head);	//����ڵ�
int save(struct node *head, const char PATH[]);	//����
static int load(struct node *head, const char PATH[]);	//��ȡ
int easter_egg();




int main() {

	init_system();
	system("pause");
	return 0;
}

//Initialization
/*init_system����ʼ��ϵͳ
��������
����ֵ��(int)0-Success
*/
int init_system() {
	struct node *head = (struct node*)malloc(sizeof(struct node));
	system("cls");
	SetConsoleTitle("Super Market Management System.Powered By ��һ��");
	if (!check_file_empty("database.dat")) {	//����ļ�Ϊ�գ���ʼ��������
		init_list(head);
		save(head, "database.dat");
	}
	else
		load(head, "database.dat");
	show_main_menu(head);
	return 0;
}

/*show_main_menu����ʾ���˵�
������ͷ�ڵ�ָ��head
����ֵ��(int)0-Success
*/
int show_main_menu(struct node *head) {

	printf(
		"Welcome! Super Market Management System\n"
		"Powered by:��һ��\n\n"
		"--------------------------------------------------------\n"
		"Menu:\n"
		"Shortcut	Description\n"
		"1:		Add new node.\n"
		"2:		Print list.\n"
		"3:		Seach item in list.\n"
		"4:		Sort all items in list.\n"
		"5:		Insert item to list.\n"
		"6:		Save to file.\n"
		"0:		Quit System.\n"
		"--------------------------------------------------------\n"
	);
	int op = (int)NULL;
	scanf_s("%d", &op);
	switch (op)
	{
	case 1:add_node(head); break;
	case 2:print_list(head); break;
	case 3:search_list(head); break;
	case 4:sort_list(head); break;
	case 5:insert_node(head); break;
	case 6:save(head,"database.dat"); break;
	case 0:exit(0); break;
	default:
		show_main_menu(head);
		//printf("Invaild input.");

		//easter_egg;
		//init_system;
		break;
	}
	show_main_menu(head);
	//init_list(1, head);
	return 0;
}

/*init_list����ʼ����
������ͷ�ڵ�ָ��*head
����ֵ��(int)0-Success
*/
static int init_list(struct node *head) {	//n�ǳ�ʼ���Ľڵ�������*head��ͷ���
	int n;	//��ʼ��ʱ���������
	printf("Error 404: Database not found. Create a Database now\n"
		"Input the number of node:");
	scanf_s("%d", &n);
	printf("Intializing List...");
	struct node *node_current = head, *node_next = head;	//��������ָ�����ָ��ڵ�
	node_next = (struct node*)malloc(sizeof(struct node));	//���µ�����ڵ����ռ�
	node_next->pre = head;	//��һ���ڵ��pre��ָ��ͷ���
	head->next = node_next;	//ͷ�ڵ�next��ָ���һ���ڵ�
	printf("Input data:");
	for (int i = 1; i < n + 1; i++) {
		node_next->pre = node_current;	//node_next��pre��ָ��node_current�ڵ�
		edit_data(node_next);	//��data������������
		node_current = node_next;	//node_current�Ƶ�node_next�ڵ�
		node_next = (struct node*)malloc(sizeof(struct node));	//���µ�����ڵ����ռ�
		node_current->next = node_next;	//node_nextָ���µ�����ڵ�
	}
	node_current->next = NULL;	//�������
	return 0;
}

/*init_array����ʼ����������
������
*head ͷ�ڵ�
**node_array ��Žڵ������
����ֵ��0-Success
*/
int init_array(struct node *head, struct node **node_array) {

	struct node *node_current = head->next;
	int len = get_len(head);
	for (int i = 0; i < len; i++) {
		node_array[i] = node_current;
		node_current = node_current->next;
		//printf("%x��", (int)&node_current);
		///For Debug
	}
	return 0;
}

//Basic Function
/*edit_data���༭�ڵ�����
�������ڵ�ָ��*node
����ֵ��(int)0-Success
*/
int edit_data(struct node *node) {
	printf("\nInput Code:");
	scanf_s("%d", &(node->code));
	printf("\nInput Name:");
	//fflush(stdin);	//��ȥscanf�Ļس�
	getchar();
	char buffer[50];
	gets_s(buffer,50);
	//node->name = _strdup(buffer);	//ref:https://blog.csdn.net/u013485792/article/details/52807056
		//scanf_s("%s", node->name,50);
	strcpy_s(node->name, 50, buffer);
	printf("\nInput price:��:");
	scanf_s("%f", &(node->price));
	printf("\nInput Barcode:");
	scanf_s("%d", &(node->barcode));
	printf("\nInput Date(MM/DD):");
	scanf_s("%d/%d", &(node->month), &(node->day));
	printf("\nInput Sales:");
	scanf_s("%d", &(node->sales));
	return 0;
}

/*get_last_node����ȡ����β�ڵ�
����������ͷָ��*head
����ֵ����ָ�룩*node_current
*/
struct node *get_last_node(struct node *head) {
	struct node *node_current = head, *node_next = head, *node_last = NULL;
	node_next = node_current->next;	//node_next���Ƶ������һ��Ԫ��
	while (node_next->next != NULL)	//�������飬��node_next�Ƶ�����ĩλ��node_current�Ƶ�n-1λ
	{
		node_current = node_next;
		node_next = node_next->next;
	}
	node_current = node_next;	//��node_current�Ƶ�ĩλ
	return node_current;
}

/*print_title����ӡ�����
��������
*/
int print_title() {
	printf("Code\tName\tPrice\tBarcode\tDate(MM/DD)\tSales\n");	//��ӡ��ͷ��Tab�ָ�
	return 0;
}


/*print_list����ӡ����
����������ͷ���ָ��*head
����ֵ��(int)0-Success
*/
int print_list(struct node *head) {
	struct node *node_current = head->next;
	/*do
	{
	printf("%d\t%s\t%.2f\t%d\t%d/%d\t%d\n", node_current->code, node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);	//��ӡ�����ڵ�
	node_current = node_current->next;
	} while (node_current->next != NULL);
	Original Ver*/
	print_title();	//��ӡ��ͷ��tab�ָ�
	for (int i = 0; i<get_len(head); i++) {
		print_node(node_current);
		node_current = node_current->next;
	}
	system("pause");
	system("cls");
	return 0;
}

/*print_sorted_list����ӡ����
����������ͷ���ָ��*head
����ֵ��(int)0-Success
*/
/*int print_sorted_list(struct node **node_array,struct node *head) {
print_title();	//��ӡ��ͷ��tab�ָ�
for (int i = 0; i<get_len(head)+1; i++) {
print_node(node_array[i]);
}
system("pause");
system("cls");
return 0;
}*/
int print_sorted_list(struct node *head) {
	print_title();
	struct node *node_current = head->next;
	for (int i = 0; i < get_len(head); i++) {
		print_node(node_current);
		node_current = node_current->next;
	}
	return 0;
}

/*print_node����ӡ�ڵ�
������Ҫ��ӡ�Ľڵ��ָ��*node_current
*/
int print_node(struct node *node_current) {
	printf("%d\t%s\t%.2f\t%d\t%2d/%2d\t%d\n", node_current->code, node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);
	return 0;
}


/*check_file_empty������ļ��Ƿ�Ϊ��
�������ļ�·��const char PATH[]
����ֵ����-(int)0
�ǿ�-(int)1
*/
int check_file_empty(const char PATH[]) {
	FILE *fp;
	errno_t err;
	int ch;
	err = fopen_s(&fp, PATH, "rb");
	if (fp)
		ch = fgetc(fp);	//���Ӽ��fp�Ƿ�Ϊ��,��ֹ����
	else
		return 0;
	fclose(fp);
	if (ch == EOF)	//����ļ���Ϊ��
		return 0;
	else
		return 1;
}

/*get_len��������鳤��
������ͷ�ڵ�ָ��*head
����ֵ��������(int)n
*/
int get_len(struct node *head) {
	struct node *node_current = head;
	int n = 0;
	while (node_current->next)
	{
		n++;
		node_current = node_current->next;
	}
	return n;
}

/*relink_node���������ӽṹ��ָ�������е�ָ����
������
�ṹ������ָ��**node_array
ͷ�ڵ㣬���������һ���ڵ�*head
����ֵ��(int)0-Success
*/
int relink_node(struct node **node_array,struct node *head,int len) {
	int i;
	head->next = node_array[0];
	node_array[0]->pre = head;
	for (i = 0; i < len - 1; i++) {
		node_array[i]->next = node_array[i + 1];
		node_array[i + 1]->pre = node_array[i];
	}
	node_array[i]->next = NULL;	//�������
	return 0;
}



//Function
/*add_node����ӽڵ�
����������ͷָ��*head
����ֵ��(int)0-Success
*/
int add_node(struct node *head) {
	struct node *node_current = get_last_node(head), *node_next = get_last_node(head);
	node_next = (struct node*)malloc(sizeof(struct node));
	node_current->next = node_next;
	node_next->pre = node_current;
	node_next->next = NULL;
	edit_data(node_next);
	save(head, "Database.dat");
	//system("pause");
	system("cls");
	return 0;
}






/*search_list����������
������
*head ͷ�ڵ�
����ֵ��(int)0-Success
*/
int search_list(struct node *head) {
	system("cls");
	struct node *node_current = head->next, *node_next = head->next;
	printf("Please select the column you want to search:\n"	//���ֶ�����
		"--------------------------------------------------------\n"
		"Shortcut		Description\n"
		"1.		Search by Code\n"
		"2.		Search by Name\n"
		"3.		Search by Price\n"
		"4.		Search by Barcode\n"
		"5.		Search by Sales\n"
		"0.		Exit\n"
		"--------------------------------------------------------\n");
	int Column = 0, Target = 0;
	scanf_s("%d", &Column);
	switch (Column)
	{
	case 1:	//����Code�ֶ�
		printf(
			"Searching by Code...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//��ӡ��ͷ��tab�ָ�
		/*
		do
		{
			if (node_current->code == Target) {	//���node_current��ֵ=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		} while (node_current->next != 0);*/
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->code == Target) {	//���node_current��ֵ=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		}
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 2:	//����Name�ֶ�
		printf(
			"Searching by Name...\n"
			"Please input target:"
		);
		getchar();	//��ȥ�س���
		char Name_Target[50];;	//���嵥���ַ�Ŀ�꣨��Ϊ�������Ͳ�ͬ��
		gets_s(Name_Target,50);
		print_title();	//��ӡ��ͷ��tab�ָ�
		for (int i = 0; i < get_len(head); i++) {
			if (!strcmp(node_current->name, Name_Target)) {	//���node_current��ֵ=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 3:	//����Price�ֶ�
		printf(
			"Searching by Price...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//��ӡ��ͷ��tab�ָ�
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->price == Target) {	//���node_current��ֵ=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 4:	//����Barcode�ֶ�
		printf(
			"Searching by Barcode...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//��ӡ��ͷ��tab�ָ�
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->barcode == Target) {	//���node_current��ֵ=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 5:	//���������ֶΣ�ģ��������
		printf(
			"Searching by Sales...\n"
			"Please input the minimum target:"
		);
		int Target_MIN, Target_MAX;
		scanf_s("%d", &Target_MIN);
		printf("\nPlease input the maximun target:");
		scanf_s("%d", &Target_MAX);
		if (Target_MIN > Target_MAX) {
			printf("Invalid Target.\n");
			break;
		}
		print_title();	//��ӡ��ͷ��tab�ָ�
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->sales <= Target_MAX && node_current->sales>=Target_MIN) {	//���node_current��ֵλ���趨��������
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 0:
		system("cls");
		show_main_menu(head);
	default:
		system("cls");
		search_list(head);
		break;
	}
	return 0;
}

/*sort_list����������
������*head ͷ�ڵ�
����ֵ��(int)0-Success
*/
int sort_list(struct node *head) {
	system("cls");
	struct node *node_current = head, *node_next = head;
	int len = get_len(head);	//��ȡ����
	struct node **node_array = (struct node**)malloc(sizeof(struct node*)*len);	//��������
	init_array(head, node_array);	//��ʼ������
	printf("Please select the column you want to search:\n"	//���ֶ�����
		"--------------------------------------------------------\n"
		"Shortcut		Description\n"
		"1.		Sort by Code\n"
		"2.		Sort by Name\n"
		"3.		Sort by Price\n"
		"4.		Sort by Barcode\n"
		"5.		Sort by Sales\n"
		"0.		Exit\n"
		"--------------------------------------------------------\n");
	int Column = 0, Target = 0;
	scanf_s("%d", &Column);
	int min,  i, j;	//��ʼ�������������
	struct node *node_tmp;
	switch (Column)
	{
	case 1:
		printf("Sorting by Code\n");
		for (i = 0; i < len; i++) {//��������Ԫ��ð������
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->code > node_array[j]->code) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//��������ָ����
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	
	case 2:
		printf("Sorting by Name\n");
		for (i = 0; i < len - 1; i++) {//��������Ԫ��ð������
			min = i;
			for (j = min+1; j < len; j++) {
				if (strcmp(node_array[min]->name, node_array[j]->name)>0) {	//Debug
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//��������ָ����
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	case 3:
		printf("Sorting by Price\n");
		for (i = 0; i < len - 1; i++) {//��������Ԫ��ð������
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->price > node_array[j]->price) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//��������ָ����
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	
	case 4:
		printf("Sorting by Barcode\n");
		for (i = 0; i < len - 1; i++) {//��������Ԫ��ð������
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->barcode > node_array[j]->barcode) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//��������ָ����
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	case 5:
		printf("Sorting by Sales");
		for (i = 0; i < len - 1; i++) {//��������Ԫ��ð������
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->sales > node_array[j]->sales) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//��������ָ����
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	case 0:
		system("cls");
		show_main_menu(head);
		break;
	default:
		printf("Error,exiting");
		Sleep(3000);
		system("cls");

		sort_list(head);
		break;
	}

	//sort_list(head);
	return 0;
}

/*insert_node������ڵ�
������
*head ͷ�ڵ�
*/
int insert_node(struct node *head) {
	int n;
	printf("Inserting node:\n"
	"Please input the node you want to insert:");
	scanf_s("%d", &n);
	struct node *node_insert = (struct node*)malloc(sizeof(struct node));
	//scanf_s("%d", &node_insert->data);	//����Ҫ����Ľڵ������
	edit_data(node_insert);
	struct node *node_current = head, *node_next = head;

	for (int i = 0; i < n ; i++) {	//��������Ѱ�Ҳ����
		node_next = node_current->next;
		node_current = node_next;
		if (!node_current->next)	//���������������ĩβ����
			break;
	}
	if (!node_current->next) {	//���������������ĩβ����
		node_current->next = node_insert;
		node_insert->pre = node_current;
		node_insert->next = NULL;
		return 0;
	}
	node_next = node_current->next;	//��λ��׼����������
	node_insert->pre = node_current;	//��������
	node_insert->next = node_next;
	node_current->next = node_insert;
	node_next->pre = node_insert;
	return 0;
}

/*save������ڵ�
������ͷ�ڵ�*head
�ļ���(const char) "Filename"
����ֵ��(int)0-Success
*/
int save(struct node *head, const char PATH[]) {
	struct node *node_current = head->next;
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, PATH, "w+");
	print_title();	//��ӡ��ͷ��tab�ָ�
	for (int i = 0; i < get_len(head); i++) {
		print_node(node_current);
		fwrite(node_current, sizeof(struct node), 1, fp);
		node_current = node_current->next;
	}
	fclose(fp);
	printf("Changes Saved.");
	system("pause");
	system("cls");
	show_main_menu(head);
	return 0;
}

/*load������ڵ�
������ͷ�ڵ�*head
�ļ���(const char) "Filename"
����ֵ��(int)0-Success
*/
int load(struct node *head, const char PATH[]) {
	printf("Found Database.\n"
		"Loading...\n");
	struct node *node_current = head, *node_read;	//node_readָ��������Ľṹ��
	FILE *fp;	//���ļ���������
	errno_t err;
	err = fopen_s(&fp, PATH, "r");
	print_title();	//��ӡ��ͷ��tab�ָ�
	while (1)
	{
		
		node_read = (struct node *)malloc(sizeof(struct node));
		fread(node_read, sizeof(struct node), 1, fp);
		
		node_current->next = node_read;
		node_read->pre = node_current;
		node_current = node_current->next;	//��������ָ����
		//node_current->name=_strdup(node_read->name);
		

		print_node(node_current);
		if (node_current->next == NULL)
			break;
	};
	Sleep(3000);
	system("cls");
	fclose(fp);
	return 0;
}


int easter_egg() {
	printf(
		"Invalid Operation.\n"
	);
	return 0;
}
///�޸�




/*
int fprint_node(FILE *fp,struct node *node_current) {
fprintf(fp,"%d\t%s\t%d\t%d\t%d/%d\t%d\n", node_current->code, (char*)node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);
return 0;
}
*/
