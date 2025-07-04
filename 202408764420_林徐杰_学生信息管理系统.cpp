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

// ��������
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
    printf("    ѧ����Ϣ����ϵͳ\n");
    printf("================================\n");
    printf("1. ע��\n");
    printf("2. ��¼\n");
    printf("0. �˳�\n");
    printf("================================\n");
    printf("��ѡ�����: ");
}

void registerUser() {
    if (usercount >= MAX_USERS) {
        printf("�û������Ѵ�����!\n");
        return;
    }
    
    printf("\n--- �û�ע�� ---\n");
    printf("�������û���: ");
    scanf("%s", users[usercount].username);
    
    for (int i = 0; i < usercount; i++) {
        if (strcmp(users[i].username, users[usercount].username) == 0) {
            printf("�û����Ѵ���!\n");
            return;
        }
    }

printf("����������: ");
    scanf("%s", users[usercount].password);
    
    usercount++;
    saveUsersToFile();
    printf("ע��ɹ�! ���¼ϵͳ��\n");
}

bool loginUser() {
    char username[20];
    char password[20];
    
    printf("\n--- �û���¼ ---\n");
    printf("�������û���: ");
    scanf("%s", username);
    
    printf("����������: ");
    scanf("%s", password);
    
    for (int i = 0; i < usercount; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0) {
            printf("\n��¼�ɹ�! ��ӭ %s!\n", username);
            return true;
        }
    }
    
    printf("�û������������!\n");
    return false;
}


void showmenu(){
	printf("\n====ѧ����Ϣ����ϵͳ====\n");
	printf("1.���ѧ��\n");
	printf("2.ɾ��ѧ��\n");
	printf("3.�޸�ѧ��\n");
	printf("4.����ѧ��\n");
	printf("5.��ʾ����ѧ��\n");
	printf("6.ͳ����Ϣ\n");
	printf("7. ��������\n");
	printf("0.�˳�ϵͳ\n");
    printf("==========================\n");
	printf("��ѡ�����:"); 
}

void addstudent(){
	if(count>=MAX_STUDENTS){
		printf("ѧ�������ﵽ���ޣ�\n");
		return;
	} 

    printf("����ѧ�ţ�");
	scanf("%d", &students[count].id);
	printf("��������:");
	scanf("%s", students[count].name); 
	printf("����Ӣ��ɼ���");
	scanf("%f", &students[count].score.english);
	printf("������ѧ�ɼ���"); 
	scanf("%f",&students[count].score.math);
	printf("���������ɼ���");
	scanf("%f",&students[count].score.computer);
	
    count++;
    printf("��ӳɹ���");
}

 
void showallstudent(){
	if(count==0){
		printf("û��ѧ����¼��\n");
		return;
	}
	
	printf("\n----����ѧ����Ϣ----\n");
	printf("ѧ��\t����\tӢ��\t��ѧ\t�����\n"); 
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
    printf("\n----����ѧ��----\n");
    printf("������Ҫ����ѧ����ѧ��:");
    scanf("%d", &id);
    
    int found = 0;
	for(int i=0; i<count; i++){ 
		if(students[i].id == id){
			printf("\n�ҵ�ѧ����Ϣ��\n");
			printf("ѧ�ţ�%d\n", students[i].id);
			printf("������%s\n", students[i].name);
			printf("Ӣ��ɼ���%.2f\n", students[i].score.english);
			printf("��ѧ�ɼ���%.2f\n", students[i].score.math);
			printf("������ɼ���%.2f\n", students[i].score.computer);
			found = 1;
			
			float total=students[i].score.english+students[i].score.math+students[i].score.computer;
			float average=total/3.0;
			
			break;
		}
	}
	
	if(!found){
		printf("û��ѧ��Ϊ%d��ѧ����Ϣ��\n", id);	
	}
}
        
void deletestudent(){
	int id; 
    printf("\n----ɾ��ѧ��----\n");
    printf("������Ҫɾ��ѧ�ŵ�ѧ����");
	scanf("%d", &id); 
		
	int found=0;
	for(int i=0; i<count; i++){
		if(students[i].id == id){
			for(int j=i; j<count-1; j++){
				students[j] = students[j+1];
			}
			count--;
			found=1;
			printf("ɾ���ɹ���\n");
			break;
		}
	}
	if(!found){
		printf("δ�ҵ���ѧ��Ϊ%d��ѧ��\n", id);
	}
}        

void modifystudent(){
	int id;
	printf("\n----�޸�ѧ����Ϣ----\n");
	printf("������Ҫ�޸ĵ�ѧ�ţ�");
	scanf("%d", &id);
	for(int i=0; i<count; i++){
		if(students[i].id == id){
			printf("�ҵ�ѧ����Ϣ:\n");
			printf("ѧ�ţ�%d\n", students[i].id);
			printf("������%s\n", students[i].name);
			printf("Ӣ��ɼ���%.2f\n", students[i].score.english);
			printf("��ѧ�ɼ���%.2f\n", students[i].score.math);
			printf("������ɼ���%.2f\n", students[i].score.computer);
			
			printf("\n��������������");
			scanf("%s", students[i].name); 
			printf("��������Ӣ��ɼ���");
			scanf("%.2f", &students[i].score.english);
			printf("����������ѧ�ɼ���");
			scanf("%.2f", &students[i].score.math);
			printf("�������¼�����ɼ���");
			scanf("%.2f", &students[i].score.computer);
			
			printf("�޸ĳɹ���\n");
			return; 
		}
	}
	printf("δ�ҵ���ѧ��Ϊ%d��ѧ��\n", id);
}

void statistics(){
	printf("\n----ͳ����Ϣ----\n");
	printf("ѧ��������%d\n", count);
	
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
		
	printf("Ӣ��ƽ���ɼ���%.2f\n",englishsum/count);
	printf("Ӣ����߷֣�%.2f\n",englishmax); 
	printf("Ӣ����ͷ֣�%.2f\n",englishmin);
	
	printf("��ѧƽ���ɼ���%.2f\n",mathsum/count);
	printf("��ѧ��߷֣�%.2f\n",mathmax); 
	printf("��ѧ��ͷ֣�%.2f\n",mathmin);
	
	printf("�����ƽ���ɼ���%.2f\n",computersum/count);
	printf("�������߷֣�%.2f\n",computermax); 
	printf("�������ͷ֣�%.2f\n",computermin);	
}       

// �������ݵ��ļ�
void saveToFile() {
    FILE *file = fopen(FILENAME, "wb"); 
    if (file == NULL) {
        printf("�޷��������ݵ��ļ�!\n");
        return;
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), count, file);
    
    fclose(file);
    printf("ѧ�������ѱ��浽 %s\n", FILENAME);
}

// ���ļ���������
void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb"); 
    if (file == NULL) {
        printf("δ�ҵ������ļ������������ļ���\n");
        return;
    }
    
    fread(&count, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), count, file);
    fclose(file);
    printf("�Ѵ� %s ����ѧ������\n", FILENAME);
}

// �����û����ݵ��ļ�
void saveUsersToFile() {
    FILE *file = fopen(USER_FILE, "wb");
    if (file == NULL) {
        printf("�޷������û�����!\n");
        return;
    }

    // ��д���û�����
    fwrite(&usercount, sizeof(int), 1, file);

    // д�������û�����
    fwrite(users, sizeof(struct User), usercount, file);

    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen(USER_FILE, "rb");
    if (file == NULL) {
        printf("δ�ҵ��û������ļ������������ļ���\n");
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
                printf("\n���ص�¼����...\n");
                return;
            default:
                printf("��Чѡ�����������룡\n");
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
        printf("�Ѵ���Ĭ�Ϲ���Ա�˻�: �û���=0000, ����=0000\n");
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
                printf("\n��лʹ��ѧ������ϵͳ���ټ�!\n");
                return 0;
            default:
                printf("��Ч��ѡ������������!\n");
        }
    }
}   
  

