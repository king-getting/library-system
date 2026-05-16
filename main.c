#include "library_system.h"

int main() {
    int choice, subChoice;
    char input[100];

    // 初始化系统
    initSystem();

    printf("\n========================================\n");
    printf("欢迎使用图书馆管理系统!\n");
    printf("========================================\n");

    while (1) {
        printMenu();
        if (!safeScanfInt(NULL, &choice)) {
            continue;
        }

        switch (choice) {
            case 0:
                printf("\n感谢使用,再见!\n");
                saveData();
                return 0;

            case 1: // 图书管理
                printf("\n--- 图书管理 ---\n");
                printf("1. 添加图书  2. 删除图书  3. 修改图书  4. 查找图书  5. 列出所有图书  6. 添加种类  7. 删除种类  8. 列出种类  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: addBook(); break;
                    case 2: deleteBook(); break;
                    case 3: updateBook(); break;
                    case 4: searchBook(); break;
                    case 5: listBooks(); break;
                    case 6: addCategory(); break;
                    case 7: deleteCategory(); break;
                    case 8: listCategories(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            case 2: // 用户管理
                printf("\n--- 用户管理 ---\n");
                printf("1. 添加用户  2. 删除用户  3. 修改用户  4. 查找用户  5. 列出所有用户  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: addUser(); break;
                    case 2: deleteUser(); break;
                    case 3: updateUser(); break;
                    case 4: searchUser(); break;
                    case 5: listUsers(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            case 3: // 学生账号管理
                printf("\n--- 学生账号管理 ---\n");
                printf("1. 添加学生  2. 删除学生  3. 修改学生信息  4. 按学号查询  5. 列出所有学生  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: addStudent(); break;
                    case 2: deleteStudent(); break;
                    case 3: updateStudent(); break;
                    case 4: searchStudentByNumber(); break;
                    case 5: listStudents(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            case 4: // 教师账号管理
                printf("\n--- 教师账号管理 ---\n");
                printf("1. 添加教师  2. 删除教师  3. 修改教师信息  4. 按工号查询  5. 列出所有教师  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: addTeacher(); break;
                    case 2: deleteTeacher(); break;
                    case 3: updateTeacher(); break;
                    case 4: searchTeacherById(); break;
                    case 5: listTeachers(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            case 5: // 借阅管理
                printf("\n--- 借阅管理 ---\n");
                printf("1. 借阅图书  2. 归还图书  3. 查看借阅记录  4. 检查逾期记录  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: borrowBook(); break;
                    case 2: returnBook(); break;
                    case 3: viewBorrowRecords(); break;
                    case 4: checkOverdue(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            case 6: // 出入登记
                printf("\n--- 出入登记 ---\n");
                printf("1. 进入登记  2. 离开登记  3. 查看出入记录  4. 按学号查看  5. 按工号查看  0. 返回\n");
                if (!safeScanfInt("请选择: ", &subChoice)) {
                    break;
                }

                switch (subChoice) {
                    case 1: enterLibrary(); break;
                    case 2: leaveLibrary(); break;
                    case 3: viewAccessLogs(); break;
                    case 4: viewAccessLogsByStudentId(); break;
                    case 5: viewAccessLogsByTeacherId(); break;
                    case 0: break;
                    default: printf("\n无效选项!\n");
                }
                break;

            default:
                printf("\n无效选项,请重新选择!\n");
        }

        // 询问是否继续
        printf("\n按回车键继续...");
        getchar();
    }

    return 0;
}
