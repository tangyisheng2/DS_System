#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define _CRT_SECURE_NO_WARNINGS

/*
struct file {
short level;	//缓冲区用量
unsigned flags;	//文件状态标志
char fd;	//文件描述符
unsigned char hold;	//缓冲区大小
short bsize;	//文件缓冲区的首地址
unsigned char *buffer;	//指向文件缓冲区的工作指针
unsigned char *curp;	//其他信息
unsigned istemp;
short token;
};
*/
struct node
{
	struct node *pre;	//前一节点指针域
	unsigned int code;	//编号
	char name[50];	//名字
	float price;	//价格
	unsigned long int barcode;	//条形码
	struct inport_date	//日期
	{
		int month;	//月
		int day;	//日
	};
	int sales;	//销量
	struct node *next;	//后一节点指针域
};	//定义节点结构

//Intail System
static int init_system();	//初始化系统
int show_main_menu(struct node *head);	//打印主菜单
static int init_list(struct node *head);	//初始链表
int init_array(struct node *head, struct node **node_array);	//初始化数组

//BasicFunction
int edit_data(struct node *node);	//修改表中数据
struct node *get_last_node(struct node *head);	//获取链表尾指针
int print_title();
int print_list(struct node *head);	//打印链表
int print_sorted_list(struct node *head);	//打印排序后列表
int print_node(struct node *node_current);	//打印节点
int check_file_empty(const char PATH[]);	//检查文件为空
int get_len(struct node *head);	//获取链表长
int relink_node(struct node **node_array, struct node *head, int len);	//重新连接链表

//Function
int add_node(struct node *head);	//添加节点
int print_list(struct node *head);	//打印列表
int search_list(struct node *head);	//搜索
int sort_list(struct node *head);	//链表排序
int insert_node(struct node *head);	//插入节点
int save(struct node *head, const char PATH[]);	//保存
static int load(struct node *head, const char PATH[]);	//读取
int easter_egg();




int main() {

	init_system();
	system("pause");
	return 0;
}

//Initialization
/*init_system：初始化系统
参数：无
返回值：(int)0-Success
*/
int init_system() {
	struct node *head = (struct node*)malloc(sizeof(struct node));
	system("cls");
	SetConsoleTitle("Super Market Management System.Powered By 唐一晟");
	if (!check_file_empty("database.dat")) {	//如果文件为空，初始化并保存
		init_list(head);
		save(head, "database.dat");
	}
	else
		load(head, "database.dat");
	show_main_menu(head);
	return 0;
}

/*show_main_menu：显示主菜单
参数：头节点指针head
返回值：(int)0-Success
*/
int show_main_menu(struct node *head) {

	printf(
		"Welcome! Super Market Management System\n"
		"Powered by:唐一晟\n\n"
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

/*init_list：初始链表
参数：头节点指针*head
返回值：(int)0-Success
*/
static int init_list(struct node *head) {	//n是初始化的节点数量，*head是头结点
	int n;	//初始化时数组的数量
	printf("Error 404: Database not found. Create a Database now\n"
		"Input the number of node:");
	scanf_s("%d", &n);
	printf("Intializing List...");
	struct node *node_current = head, *node_next = head;	//声明两个指针变量指向节点
	node_next = (struct node*)malloc(sizeof(struct node));	//给新的链表节点分配空间
	node_next->pre = head;	//第一个节点的pre域指向头结点
	head->next = node_next;	//头节点next域指向第一个节点
	printf("Input data:");
	for (int i = 1; i < n + 1; i++) {
		node_next->pre = node_current;	//node_next的pre域指向node_current节点
		edit_data(node_next);	//向data域中输入数据
		node_current = node_next;	//node_current移到node_next节点
		node_next = (struct node*)malloc(sizeof(struct node));	//给新的链表节点分配空间
		node_current->next = node_next;	//node_next指向新的链表节点
	}
	node_current->next = NULL;	//链表结束
	return 0;
}

/*init_array：初始化排序数组
参数：
*head 头节点
**node_array 存放节点的数组
返回值：0-Success
*/
int init_array(struct node *head, struct node **node_array) {

	struct node *node_current = head->next;
	int len = get_len(head);
	for (int i = 0; i < len; i++) {
		node_array[i] = node_current;
		node_current = node_current->next;
		//printf("%x，", (int)&node_current);
		///For Debug
	}
	return 0;
}

//Basic Function
/*edit_data：编辑节点数据
参数：节点指针*node
返回值：(int)0-Success
*/
int edit_data(struct node *node) {
	printf("\nInput Code:");
	scanf_s("%d", &(node->code));
	printf("\nInput Name:");
	//fflush(stdin);	//消去scanf的回车
	getchar();
	char buffer[50];
	gets_s(buffer,50);
	//node->name = _strdup(buffer);	//ref:https://blog.csdn.net/u013485792/article/details/52807056
		//scanf_s("%s", node->name,50);
	strcpy_s(node->name, 50, buffer);
	printf("\nInput price:￥:");
	scanf_s("%f", &(node->price));
	printf("\nInput Barcode:");
	scanf_s("%d", &(node->barcode));
	printf("\nInput Date(MM/DD):");
	scanf_s("%d/%d", &(node->month), &(node->day));
	printf("\nInput Sales:");
	scanf_s("%d", &(node->sales));
	return 0;
}

/*get_last_node：获取链表尾节点
参数：链表头指针*head
返回值：（指针）*node_current
*/
struct node *get_last_node(struct node *head) {
	struct node *node_current = head, *node_next = head, *node_last = NULL;
	node_next = node_current->next;	//node_next右移到链表第一个元素
	while (node_next->next != NULL)	//遍历数组，把node_next移到链表末位，node_current移到n-1位
	{
		node_current = node_next;
		node_next = node_next->next;
	}
	node_current = node_next;	//把node_current移到末位
	return node_current;
}

/*print_title：打印表标题
参数：无
*/
int print_title() {
	printf("Code\tName\tPrice\tBarcode\tDate(MM/DD)\tSales\n");	//打印表头，Tab分隔
	return 0;
}


/*print_list：打印链表
参数：链表头结点指针*head
返回值：(int)0-Success
*/
int print_list(struct node *head) {
	struct node *node_current = head->next;
	/*do
	{
	printf("%d\t%s\t%.2f\t%d\t%d/%d\t%d\n", node_current->code, node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);	//打印后续节点
	node_current = node_current->next;
	} while (node_current->next != NULL);
	Original Ver*/
	print_title();	//打印表头，tab分隔
	for (int i = 0; i<get_len(head); i++) {
		print_node(node_current);
		node_current = node_current->next;
	}
	system("pause");
	system("cls");
	return 0;
}

/*print_sorted_list：打印链表
参数：链表头结点指针*head
返回值：(int)0-Success
*/
/*int print_sorted_list(struct node **node_array,struct node *head) {
print_title();	//打印表头，tab分隔
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

/*print_node：打印节点
参数：要打印的节点的指针*node_current
*/
int print_node(struct node *node_current) {
	printf("%d\t%s\t%.2f\t%d\t%2d/%2d\t%d\n", node_current->code, node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);
	return 0;
}


/*check_file_empty：检测文件是否为空
参数：文件路径const char PATH[]
返回值：空-(int)0
非空-(int)1
*/
int check_file_empty(const char PATH[]) {
	FILE *fp;
	errno_t err;
	int ch;
	err = fopen_s(&fp, PATH, "rb");
	if (fp)
		ch = fgetc(fp);	//增加检测fp是否为空,防止报错
	else
		return 0;
	fclose(fp);
	if (ch == EOF)	//如果文件内为空
		return 0;
	else
		return 1;
}

/*get_len：获得数组长度
参数：头节点指针*head
返回值：链表长度(int)n
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

/*relink_node：重新连接结构体指针数组中的指针域
参数：
结构体数组指针**node_array
头节点，连接数组第一个节点*head
返回值：(int)0-Success
*/
int relink_node(struct node **node_array,struct node *head,int len) {
	int i;
	head->next = node_array[0];
	node_array[0]->pre = head;
	for (i = 0; i < len - 1; i++) {
		node_array[i]->next = node_array[i + 1];
		node_array[i + 1]->pre = node_array[i];
	}
	node_array[i]->next = NULL;	//链表结束
	return 0;
}



//Function
/*add_node：添加节点
参数：链表头指针*head
返回值：(int)0-Success
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






/*search_list：搜索数组
参数：
*head 头节点
返回值：(int)0-Success
*/
int search_list(struct node *head) {
	system("cls");
	struct node *node_current = head->next, *node_next = head->next;
	printf("Please select the column you want to search:\n"	//按字段搜索
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
	case 1:	//搜索Code字段
		printf(
			"Searching by Code...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//打印表头，tab分隔
		/*
		do
		{
			if (node_current->code == Target) {	//如果node_current的值=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		} while (node_current->next != 0);*/
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->code == Target) {	//如果node_current的值=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		}
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 2:	//搜索Name字段
		printf(
			"Searching by Name...\n"
			"Please input target:"
		);
		getchar();	//除去回车符
		char Name_Target[50];;	//定义单独字符目标（因为数据类型不同）
		gets_s(Name_Target,50);
		print_title();	//打印表头，tab分隔
		for (int i = 0; i < get_len(head); i++) {
			if (!strcmp(node_current->name, Name_Target)) {	//如果node_current的值=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 3:	//搜索Price字段
		printf(
			"Searching by Price...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//打印表头，tab分隔
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->price == Target) {	//如果node_current的值=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 4:	//搜索Barcode字段
		printf(
			"Searching by Barcode...\n"
			"Please input target:"
		);
		scanf_s("%d", &Target);
		print_title();	//打印表头，tab分隔
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->barcode == Target) {	//如果node_current的值=Target
				print_node(node_current);
			}
			node_current = node_current->next;
		};
		system("pause");
		system("cls");
		search_list(head);
		break;
	case 5:	//搜索销量字段（模糊搜索）
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
		print_title();	//打印表头，tab分隔
		for (int i = 0; i < get_len(head); i++) {
			if (node_current->sales <= Target_MAX && node_current->sales>=Target_MIN) {	//如果node_current的值位于设定的区间内
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

/*sort_list：排序链表
参数：*head 头节点
返回值：(int)0-Success
*/
int sort_list(struct node *head) {
	system("cls");
	struct node *node_current = head, *node_next = head;
	int len = get_len(head);	//获取链表长
	struct node **node_array = (struct node**)malloc(sizeof(struct node*)*len);	//建立数组
	init_array(head, node_array);	//初始化数组
	printf("Please select the column you want to search:\n"	//按字段搜索
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
	int min,  i, j;	//初始化排序所需变量
	struct node *node_tmp;
	switch (Column)
	{
	case 1:
		printf("Sorting by Code\n");
		for (i = 0; i < len; i++) {//对数组内元素冒泡排序
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->code > node_array[j]->code) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//重新连接指针域
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	
	case 2:
		printf("Sorting by Name\n");
		for (i = 0; i < len - 1; i++) {//对数组内元素冒泡排序
			min = i;
			for (j = min+1; j < len; j++) {
				if (strcmp(node_array[min]->name, node_array[j]->name)>0) {	//Debug
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//重新连接指针域
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	case 3:
		printf("Sorting by Price\n");
		for (i = 0; i < len - 1; i++) {//对数组内元素冒泡排序
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->price > node_array[j]->price) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//重新连接指针域
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	
	case 4:
		printf("Sorting by Barcode\n");
		for (i = 0; i < len - 1; i++) {//对数组内元素冒泡排序
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->barcode > node_array[j]->barcode) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//重新连接指针域
		print_sorted_list(head);
		system("pause");
		system("cls");
		//save
		break;
	case 5:
		printf("Sorting by Sales");
		for (i = 0; i < len - 1; i++) {//对数组内元素冒泡排序
			min = i;
			for (j = min+1; j < len; j++) {
				if (node_array[min]->sales > node_array[j]->sales) {
					node_tmp = node_array[min];
					node_array[min] = node_array[j];
					node_array[j] = node_tmp;
				}
			}
		}
		relink_node(node_array, head, len);	//重新连接指针域
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

/*insert_node：插入节点
参数：
*head 头节点
*/
int insert_node(struct node *head) {
	int n;
	printf("Inserting node:\n"
	"Please input the node you want to insert:");
	scanf_s("%d", &n);
	struct node *node_insert = (struct node*)malloc(sizeof(struct node));
	//scanf_s("%d", &node_insert->data);	//输入要插入的节点的数据
	edit_data(node_insert);
	struct node *node_current = head, *node_next = head;

	for (int i = 0; i < n ; i++) {	//遍历链表，寻找插入点
		node_next = node_current->next;
		node_current = node_next;
		if (!node_current->next)	//链表结束，在数组末尾插入
			break;
	}
	if (!node_current->next) {	//链表结束，在数组末尾插入
		node_current->next = node_insert;
		node_insert->pre = node_current;
		node_insert->next = NULL;
		return 0;
	}
	node_next = node_current->next;	//移位，准备插入数据
	node_insert->pre = node_current;	//插入数据
	node_insert->next = node_next;
	node_current->next = node_insert;
	node_next->pre = node_insert;
	return 0;
}

/*save：保存节点
参数：头节点*head
文件名(const char) "Filename"
返回值：(int)0-Success
*/
int save(struct node *head, const char PATH[]) {
	struct node *node_current = head->next;
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, PATH, "w+");
	print_title();	//打印表头，tab分隔
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

/*load：载入节点
参数：头节点*head
文件名(const char) "Filename"
返回值：(int)0-Success
*/
int load(struct node *head, const char PATH[]) {
	printf("Found Database.\n"
		"Loading...\n");
	struct node *node_current = head, *node_read;	//node_read指向读出来的结构体
	FILE *fp;	//打开文件基本操作
	errno_t err;
	err = fopen_s(&fp, PATH, "r");
	print_title();	//打印表头，tab分隔
	while (1)
	{
		
		node_read = (struct node *)malloc(sizeof(struct node));
		fread(node_read, sizeof(struct node), 1, fp);
		
		node_current->next = node_read;
		node_read->pre = node_current;
		node_current = node_current->next;	//连接链表指针域
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
///修改




/*
int fprint_node(FILE *fp,struct node *node_current) {
fprintf(fp,"%d\t%s\t%d\t%d\t%d/%d\t%d\n", node_current->code, (char*)node_current->name, node_current->price, node_current->barcode, node_current->month, node_current->day, node_current->sales);
return 0;
}
*/
