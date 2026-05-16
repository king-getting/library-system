#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 1000
#define MAX_USERS 500
#define MAX_BORROWS 1000
#define MAX_ACCESS_LOGS 2000
#define MAX_BOOK_ENTRIES 5000
#define MAX_STRING_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_CATEGORIES 100
#define BOOK_ID_LENGTH 20
#define USER_ID_LENGTH 20
#define STUDENT_ID_LENGTH 20
#define UNKNOWN_SYMBOL "#"  // 未知字段标记符号

// 图书结构体
typedef struct {
    char id[BOOK_ID_LENGTH];        // 图书编号
    char title[MAX_STRING_LENGTH];   // 书名
    char author[MAX_STRING_LENGTH];  // 作者
    char publisher[MAX_STRING_LENGTH]; // 出版社
    int year;                        // 出版年份
    float price;                     // 价格
    int stock;                       // 库存数量
    int category;                    // 分类: 1-文学, 2-科技, 3-历史, 4-其他
} Book;

// 用户结构体
typedef struct {
    char id[USER_ID_LENGTH];         // 用户ID
    char studentId[STUDENT_ID_LENGTH]; // 学号(学生专用)
    char name[MAX_STRING_LENGTH];    // 姓名
    char phone[MAX_STRING_LENGTH];   // 电话
    char email[MAX_STRING_LENGTH];   // 邮箱
    int userType;                    // 用户类型: 1-学生, 2-教师, 3-其他
    int grade;                       // 年级(学生专用, 如2024表示2024级)
} User;

// 借阅记录结构体
typedef struct {
    char bookId[BOOK_ID_LENGTH];    // 图书编号
    char userId[USER_ID_LENGTH];     // 用户ID
    time_t borrowDate;              // 借阅时间
    time_t dueDate;                  // 应还时间
    time_t returnDate;               // 实际还书时间
    int status;                     // 状态: 0-已借出, 1-已归还
} BorrowRecord;

// 出入登记记录结构体
typedef struct {
    char userId[USER_ID_LENGTH];    // 用户ID
    time_t enterTime;               // 进入时间
    time_t leaveTime;               // 离开时间
    int status;                     // 状态: 0-已进入, 1-已离开
} AccessLog;

// 图书入库记录结构体
typedef struct {
    char bookId[BOOK_ID_LENGTH];       // 图书编号
    char title[MAX_STRING_LENGTH];     // 书名
    int quantity;                      // 入库数量
    time_t entryDate;                  // 入库时间
} BookEntryRecord;

// 图书种类结构体
typedef struct {
    char name[MAX_CATEGORY_LENGTH];    // 种类名称
    int bookCount;                     // 该种类的图书数量
} BookCategory;

// 全局变量
extern Book books[MAX_BOOKS];
extern User users[MAX_USERS];
extern BorrowRecord borrowRecords[MAX_BORROWS];
extern AccessLog accessLogs[MAX_ACCESS_LOGS];
extern BookEntryRecord bookEntryRecords[MAX_BOOK_ENTRIES];
extern BookCategory categories[MAX_CATEGORIES];
extern int bookCount;
extern int userCount;
extern int borrowCount;
extern int accessLogCount;
extern int bookEntryCount;
extern int categoryCount;

// 函数声明
void initSystem();
void saveData();
void loadData();
void clearInputBuffer();
int safeScanfInt(const char *prompt, int *value);

// 图书管理
void addBook();
void deleteBook();
void updateBook();
void searchBook();
void listBooks();
void addCategory();
void deleteCategory();
void listCategories();

// 用户管理
void addUser();
void deleteUser();
void updateUser();
void searchUser();
void listUsers();

// 学生账号管理
void addStudent();
void deleteStudent();
void updateStudent();
void searchStudentByNumber();
void listStudents();

// 教师账号管理
void addTeacher();
void deleteTeacher();
void updateTeacher();
void searchTeacherById();
void listTeachers();

// 借阅管理
void borrowBook();
void returnBook();
void viewBorrowRecords();
void checkOverdue();

// 出入登记
void enterLibrary();
void leaveLibrary();
void viewAccessLogs();
void viewAccessLogsByStudentId();
void viewAccessLogsByTeacherId();

// 入库记录管理
void viewBookEntryRecords();
void viewBookBorrowHistory();

// 辅助函数
void printMenu();
char* timeToString(time_t t);
int findBookById(char* id);
int findUserById(char* id);
int findUserByStudentId(char* studentId);

#endif
