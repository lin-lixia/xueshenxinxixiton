#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#define MAX_STUDENTS 50	
#define FILENAME "students.dat"
#define MAX_USERS 20
#define USER_FILE "users.dat"


struct User{
	char username[20];
	char password[20];
};

struct Score{
	float english;
	float computer;
	float math;
}; 

struct Student{
	int id;
	char name[50];  
	struct Score score;
};


struct Student students[MAX_STUDENTS];
int count = 0;

struct User users[MAX_USERS];
int usercount = 0;

// 函数声明
void saveToFile();
void loadFromFile();
void saveUsersToFile();
void loadUsersFromFile();
void registerUser();
bool loginUser();
void adminMenu();
void showAdminMenu();
void addstudent();
void deletestudent();
void modifystudent();
void findstudent();
void showallstudent();
void statistics();
void showmenu();
void clearBuffer();

void welcomeScreen() {
    printf("\n================================\n");
    printf("    学生信息管理系统\n");
    printf("================================\n");
    printf("1. 注册\n");
    printf("2. 登录\n");
    printf("0. 退出\n");
    printf("================================\n");
    printf("请选择操作: ");
}

void registerUser() {
    if (usercount >= MAX_USERS) {
        printf("用户数量已达上限!\n");
        return;
    }
    
    printf("\n--- 用户注册 ---\n");
    printf("请输入用户名: ");
    scanf("%s", users[usercount].username);
    
    for (int i = 0; i < usercount; i++) {
        if (strcmp(users[i].username, users[usercount].username) == 0) {
            printf("用户名已存在!\n");
            return;
        }
    }

printf("请输入密码: ");
    scanf("%s", users[usercount].password);
    
    usercount++;
    saveUsersToFile();
    printf("注册成功! 请登录系统。\n");
}

bool loginUser() {
    char username[20];
    char password[20];
    
    printf("\n--- 用户登录 ---\n");
    printf("请输入用户名: ");
    scanf("%s", username);
    
    printf("请输入密码: ");
    scanf("%s", password);
    
    for (int i = 0; i < usercount; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0) {
            printf("\n登录成功! 欢迎 %s!\n", username);
            return true;
        }
    }
    
    printf("用户名或密码错误!\n");
    return false;
}


void showmenu(){
	printf("\n====学生信息管理系统====\n");
	printf("1.添加学生\n");
	printf("2.删除学生\n");
	printf("3.修改学生\n");
	printf("4.查找学生\n");
	printf("5.显示所有学生\n");
	printf("6.统计信息\n");
	printf("7. 保存数据\n");
	printf("0.退出系统\n");
    printf("==========================\n");
	printf("请选择操作:"); 
}

void addstudent(){
	if(count>=MAX_STUDENTS){
		printf("学生数量达到上限！\n");
		return;
	} 

    printf("输入学号：");
	scanf("%d", &students[count].id);
	printf("输入姓名:");
	scanf("%s", students[count].name); 
	printf("输入英语成绩：");
	scanf("%f", &students[count].score.english);
	printf("输入数学成绩："); 
	scanf("%f",&students[count].score.math);
	printf("输入计算机成绩：");
	scanf("%f",&students[count].score.computer);
	
    count++;
    printf("添加成功！");
}

 
void showallstudent(){
	if(count==0){
		printf("没有学生记录！\n");
		return;
	}
	
	printf("\n----所有学生信息----\n");
	printf("学号\t姓名\t英语\t数学\t计算机\n"); 
	printf("------------------------------\n");
	for(int i=0; i<count; i++){
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\n", 
		       students[i].id,
		       students[i].name,
		       students[i].score.english,
			   students[i].score.math,
			   students[i].score.computer);
	}
}

void findstudent(){
	int id;
    printf("\n----查找学生----\n");
    printf("请输入要查找学生的学号:");
    scanf("%d", &id);
    
    int found = 0;
	for(int i=0; i<count; i++){ 
		if(students[i].id == id){
			printf("\n找到学生信息：\n");
			printf("学号：%d\n", students[i].id);
			printf("姓名：%s\n", students[i].name);
			printf("英语成绩：%.2f\n", students[i].score.english);
			printf("数学成绩：%.2f\n", students[i].score.math);
			printf("计算机成绩：%.2f\n", students[i].score.computer);
			found = 1;
			
			float total=students[i].score.english+students[i].score.math+students[i].score.computer;
			float average=total/3.0;
			
			break;
		}
	}
	
	if(!found){
		printf("没有学号为%d的学生信息！\n", id);	
	}
}
        
void deletestudent(){
	int id; 
    printf("\n----删除学生----\n");
    printf("请输入要删除学号的学生：");
	scanf("%d", &id); 
		
	int found=0;
	for(int i=0; i<count; i++){
		if(students[i].id == id){
			for(int j=i; j<count-1; j++){
				students[j] = students[j+1];
			}
			count--;
			found=1;
			printf("删除成功！\n");
			break;
		}
	}
	if(!found){
		printf("未找到该学号为%d的学生\n", id);
	}
}        

void modifystudent(){
	int id;
	printf("\n----修改学生信息----\n");
	printf("请输入要修改的学号：");
	scanf("%d", &id);
	for(int i=0; i<count; i++){
		if(students[i].id == id){
			printf("找到学生信息:\n");
			printf("学号：%d\n", students[i].id);
			printf("姓名：%s\n", students[i].name);
			printf("英语成绩：%.2f\n", students[i].score.english);
			printf("数学成绩：%.2f\n", students[i].score.math);
			printf("计算机成绩：%.2f\n", students[i].score.computer);
			
			printf("\n请输入新姓名：");
			scanf("%s", students[i].name); 
			printf("请输入新英语成绩：");
			scanf("%.2f", &students[i].score.english);
			printf("请输入新数学成绩：");
			scanf("%.2f", &students[i].score.math);
			printf("请输入新计算机成绩：");
			scanf("%.2f", &students[i].score.computer);
			
			printf("修改成功！\n");
			return; 
		}
	}
	printf("未找到该学号为%d的学生\n", id);
}

void statistics(){
	printf("\n----统计信息----\n");
	printf("学生总数：%d\n", count);
	
	if(count == 0) return;
		
	float englishsum = 0;
	float englishmax = students[0].score.english;
	float englishmin = students[0].score.english;
	
	float mathsum = 0;
	float mathmax = students[0].score.math;
	float mathmin = students[0].score.math;
	
	float computersum = 0;
	float computermax = students[0].score.computer;
	float computermin = students[0].score.computer;
		
	for (int i=0; i<count; i++){
		englishsum += students[i].score.english;
		if(students[i].score.english > englishmax)
			englishmax = students[i].score.english;
		if(students[i].score.english < englishmin)
			englishmin = students[i].score.english;
			
		mathsum += students[i].score.math;
		if(students[i].score.math > mathmax)
			mathmax = students[i].score.math;
		if(students[i].score.math < mathmin)
			mathmin = students[i].score.math;
			
	    computersum += students[i].score.computer;
		if(students[i].score.computer > computermax)
			computermax = students[i].score.computer;
		if(students[i].score.computer < computermin)
			computermin = students[i].score.computer;
	}
		
	printf("英语平均成绩：%.2f\n",englishsum/count);
	printf("英语最高分：%.2f\n",englishmax); 
	printf("英语最低分：%.2f\n",englishmin);
	
	printf("数学平均成绩：%.2f\n",mathsum/count);
	printf("数学最高分：%.2f\n",mathmax); 
	printf("数学最低分：%.2f\n",mathmin);
	
	printf("计算机平均成绩：%.2f\n",computersum/count);
	printf("计算机最高分：%.2f\n",computermax); 
	printf("计算机最低分：%.2f\n",computermin);	
}       

// 保存数据到文件
void saveToFile() {
    FILE *file = fopen(FILENAME, "wb"); 
    if (file == NULL) {
        printf("无法保存数据到文件!\n");
        return;
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), count, file);
    
    fclose(file);
    printf("学生数据已保存到 %s\n", FILENAME);
}

// 从文件加载数据
void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb"); 
    if (file == NULL) {
        printf("未找到数据文件，将创建新文件。\n");
        return;
    }
    
    fread(&count, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), count, file);
    fclose(file);
    printf("已从 %s 加载学生数据\n", FILENAME);
}

// 保存用户数据到文件
void saveUsersToFile() {
    FILE *file = fopen(USER_FILE, "wb");
    if (file == NULL) {
        printf("无法保存用户数据!\n");
        return;
    }

    // 先写入用户数量
    fwrite(&usercount, sizeof(int), 1, file);

    // 写入所有用户数据
    fwrite(users, sizeof(struct User), usercount, file);

    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen(USER_FILE, "rb");
    if (file == NULL) {
        printf("未找到用户数据文件，将创建新文件。\n");
        return;
    }
    fread(&usercount, sizeof(int), 1, file);
    fread(users, sizeof(struct User), usercount, file);
    fclose(file);
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void adminMenu() {
    int menuChoice;
    while (1) {
        showmenu();
        scanf("%d", &menuChoice);
        clearBuffer();  

        switch (menuChoice) {
            case 1:
                addstudent();
                break;
            case 2:
                deletestudent();
                break;
            case 3:
                modifystudent();
                break;
            case 4:
                findstudent();
                break;
            case 5:
                showallstudent();
                break;
            case 6:
                statistics();
                break;
            case 7:
                saveToFile();
                break;
            case 0:
                saveToFile();  
                printf("\n返回登录界面...\n");
                return;
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
}
   

int main() {
    loadUsersFromFile();
    loadFromFile();

    if (usercount == 0) {
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        usercount = 1;
        saveUsersToFile();
        printf("已创建默认管理员账户: 用户名=0000, 密码=0000\n");
    }

    int choice;
    while (1) {
        welcomeScreen();
        scanf("%d", &choice);
        clearBuffer();  

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    adminMenu();  
                }
                break;
            case 0:
                printf("\n感谢使用学生管理系统，再见!\n");
                return 0;
            default:
                printf("无效的选择，请重新输入!\n");
        }
    }
}   
  

