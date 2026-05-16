#include "library_system.h"

// 清空输入缓冲区
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 安全的整数输入（处理输入错误）
int safeScanfInt(const char *prompt, int *value) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    if (scanf("%d", value) != 1) {
        printf("输入格式错误! 请输入数字。\n");
        clearInputBuffer();
        return 0; // 失败
    }
    clearInputBuffer();
    return 1; // 成功
}

// 全局变量
Book books[MAX_BOOKS];
User users[MAX_USERS];
BorrowRecord borrowRecords[MAX_BORROWS];
AccessLog accessLogs[MAX_ACCESS_LOGS];
BookCategory categories[MAX_CATEGORIES];
int bookCount = 0;
int userCount = 0;
int borrowCount = 0;
int accessLogCount = 0;
int categoryCount = 0;

// 初始化系统
void initSystem() {
    loadData();
}

// 保存数据到文件
void saveData() {
    // 保存图书数据
    FILE *fp = fopen("books.dat", "wb");
    if (fp) {
        fwrite(&bookCount, sizeof(int), 1, fp);
        fwrite(books, sizeof(Book), bookCount, fp);
        fclose(fp);
    }

    // 保存用户数据
    fp = fopen("users.dat", "wb");
    if (fp) {
        fwrite(&userCount, sizeof(int), 1, fp);
        fwrite(users, sizeof(User), userCount, fp);
        fclose(fp);
    }

    // 保存借阅记录
    fp = fopen("borrows.dat", "wb");
    if (fp) {
        fwrite(&borrowCount, sizeof(int), 1, fp);
        fwrite(borrowRecords, sizeof(BorrowRecord), borrowCount, fp);
        fclose(fp);
    }

    // 保存出入记录
    fp = fopen("access.dat", "wb");
    if (fp) {
        fwrite(&accessLogCount, sizeof(int), 1, fp);
        fwrite(accessLogs, sizeof(AccessLog), accessLogCount, fp);
        fclose(fp);
    }

    // 保存图书种类数据
    fp = fopen("categories.dat", "wb");
    if (fp) {
        fwrite(&categoryCount, sizeof(int), 1, fp);
        fwrite(categories, sizeof(BookCategory), categoryCount, fp);
        fclose(fp);
    }

    printf("\n数据保存成功!\n");
}

// 从文件加载数据
void loadData() {
    FILE *fp;

    // 加载图书数据
    fp = fopen("books.dat", "rb");
    if (fp) {
        fread(&bookCount, sizeof(int), 1, fp);
        fread(books, sizeof(Book), bookCount, fp);
        fclose(fp);
    }

    // 加载用户数据
    fp = fopen("users.dat", "rb");
    if (fp) {
        fread(&userCount, sizeof(int), 1, fp);
        fread(users, sizeof(User), userCount, fp);
        fclose(fp);
    }

    // 加载借阅记录
    fp = fopen("borrows.dat", "rb");
    if (fp) {
        fread(&borrowCount, sizeof(int), 1, fp);
        fread(borrowRecords, sizeof(BorrowRecord), borrowCount, fp);
        fclose(fp);
    }

    // 加载出入记录
    fp = fopen("access.dat", "rb");
    if (fp) {
        fread(&accessLogCount, sizeof(int), 1, fp);
        fread(accessLogs, sizeof(AccessLog), accessLogCount, fp);
        fclose(fp);
    }

    // 加载图书种类数据
    fp = fopen("categories.dat", "rb");
    if (fp) {
        fread(&categoryCount, sizeof(int), 1, fp);
        fread(categories, sizeof(BookCategory), categoryCount, fp);
        fclose(fp);
    }

    // 初始化默认种类(如果为空)
    if (categoryCount == 0) {
        strcpy(categories[0].name, "文学");
        strcpy(categories[1].name, "科技");
        strcpy(categories[2].name, "历史");
        strcpy(categories[3].name, "其他");
        categoryCount = 4;
    }
}

// 时间转字符串
char* timeToString(time_t t) {
    static char str[100];
    struct tm *tm_info = localtime(&t);
    strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", tm_info);
    return str;
}

// 根据ID查找图书
int findBookById(char* id) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// 根据ID查找用户
int findUserById(char* id) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// 添加图书
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("\n图书馆已满,无法添加更多图书!\n");
        return;
    }

    Book book;
    char input[MAX_STRING_LENGTH];
    int i;

    printf("\n--- 添加图书 ---\n");
    printf("提示: 输入 '%s' 表示该字段未知\n", UNKNOWN_SYMBOL);

    printf("请输入图书编号 : ");
    scanf("%s", input);
    if (strcmp(input, UNKNOWN_SYMBOL) == 0) {
        strcpy(book.id, UNKNOWN_SYMBOL);
    } else {
        if (findBookById(input) != -1) {
            printf("\n该图书编号已存在!\n");
            return;
        }
        strcpy(book.id, input);
    }

    printf("请输入书名 : ");
    scanf(" %[^\n]", input);
    if (strcmp(input, UNKNOWN_SYMBOL) == 0) {
        strcpy(book.title, UNKNOWN_SYMBOL);
    } else {
        strcpy(book.title, input);
    }

    printf("请输入作者 (输入 %s 表示未知): ", UNKNOWN_SYMBOL);
    scanf(" %[^\n]", input);
    if (strcmp(input, UNKNOWN_SYMBOL) == 0) {
        strcpy(book.author, UNKNOWN_SYMBOL);
    } else {
        strcpy(book.author, input);
    }

    printf("请输入出版社 (输入 %s 表示未知): ", UNKNOWN_SYMBOL);
    scanf(" %[^\n]", input);
    if (strcmp(input, UNKNOWN_SYMBOL) == 0) {
        strcpy(book.publisher, UNKNOWN_SYMBOL);
    } else {
        strcpy(book.publisher, input);
    }

    while (!safeScanfInt("请输入出版年份 (输入 %s 表示未知): ", UNKNOWN_SYMBOL, &book.year));

    printf("请输入价格 (输入 %s 表示未知): ", UNKNOWN_SYMBOL);
    scanf("%f", &book.price);
    clearInputBuffer();

    while (!safeScanfInt("请输入库存数量 : ", &book.stock));

    // 显示现有种类供选择
    printf("\n请选择图书种类:\n");
    for (i = 0; i < categoryCount; i++) {
        printf("%d. %s\n", i + 1, categories[i].name);
    }
    printf("%d. 自定义种类\n", categoryCount + 1);
    printf("请选择 (1-%d): ", categoryCount + 1);
    int categoryChoice;
    while (!safeScanfInt(NULL, &categoryChoice));

    if (categoryChoice == categoryCount + 1) {
        printf("请输入自定义种类名称: ");
        scanf(" %[^\n]", input);
        if (categoryCount < MAX_CATEGORIES) {
            strcpy(categories[categoryCount].name, input);
            book.category = categoryCount;
            categoryCount++;
            printf("已添加新种类: %s\n", input);
        } else {
            printf("种类数量已达上限!\n");
            book.category = 0;
        }
    } else if (categoryChoice >= 1 && categoryChoice <= categoryCount) {
        book.category = categoryChoice - 1;
    } else {
        book.category = 0;
    }

    books[bookCount++] = book;
    printf("\n图书添加成功!\n");
    saveData();
}

// 删除图书
void deleteBook() {
    char keyword[MAX_STRING_LENGTH];
    char confirm;

    printf("\n--- 删除图书 ---\n");

    // 第一步：查询流程
    printf("请输入书名或作者关键词进行搜索: ");
    scanf(" %[^\n]", keyword);

    // 搜索并显示匹配结果
    int indices[MAX_BOOKS];
    int foundCount = 0;

    printf("\n搜索结果:\n");
    printf("%-5s %-15s %-30s %-20s %-15s %-8s\n",
           "序号", "图书编号", "书名", "作者", "出版社", "库存");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL ||
            strstr(books[i].author, keyword) != NULL ||
            strstr(books[i].id, keyword) != NULL) {
            printf("%-5d %-15s %-30s %-20s %-15s %-8d\n",
                   foundCount + 1,
                   books[i].id, books[i].title, books[i].author,
                   books[i].publisher, books[i].stock);
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\n未找到匹配的图书!\n");
        return;
    }

    // 第二步：选择目标
    printf("\n共找到 %d 条记录, 请输入要删除的序号(1-%d): ", foundCount, foundCount);
    int selection;
    if (!safeScanfInt(NULL, &selection) || selection < 1 || selection > foundCount) {
        printf("\n无效的选择!\n");
        return;
    }

    int index = indices[selection - 1];
    Book *book = &books[index];

    // 显示将要删除的信息
    printf("\n========== 即将删除的图书 ==========\n");
    printf("图书编号: %s\n", book->id);
    printf("书名: %s\n", book->title);
    printf("作者: %s\n", book->author);
    printf("出版社: %s\n", book->publisher);
    printf("库存: %d\n", book->stock);
    printf("====================================\n");

    // 第三步：握手确认协议
    printf("\n⚠️ 警告: 此操作不可恢复!\n");
    printf("确认删除此图书? (输入 Y 确认, 其他键取消): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n删除操作已取消.\n");
        return;
    }

    // 检查是否有未归还的借阅记录
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].bookId, book->id) == 0 && borrowRecords[i].status == 0) {
            printf("\n该图书还有未归还的借阅记录,无法删除!\n");
            return;
        }
    }

    // 执行删除
    for (int i = index; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;

    printf("\n✓ 图书删除成功!\n");
    saveData();
}

// 修改图书
// 修改图书
void updateBook() {
    char id[BOOK_ID_LENGTH];
    printf("\n--- 修改图书 ---\n");
    printf("请输入要修改的图书编号: ");
    scanf("%s", id);

    int index = findBookById(id);
    if (index == -1) {
        printf("\n未找到该图书!\n");
        return;
    }

    Book *book = &books[index];
    int modified = 0;
    int choice;
    char input[MAX_STRING_LENGTH];

    while (1) {
        printf("\n当前图书信息:\n");
        printf("图书编号: %s\n", book->id);
        printf("1. 书名: %s\n", book->title);
        printf("2. 作者: %s\n", book->author);
        printf("3. 出版社: %s\n", book->publisher);
        printf("4. 出版年份: %d\n", book->year);
        printf("5. 价格: ¥%.2f\n", book->price);
        printf("6. 库存: %d\n", book->stock);
        printf("7. 分类: %d\n", book->category);
        printf("0. 返回\n");
        if (!safeScanfInt("请选择要修改的项: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 0: {
                char confirm;
                printf("确定保存并返回吗? (Y/N): ");
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y') {
                    if (modified) {
                        printf("\n图书修改成功!\n");
                        saveData();
                    } else {
                        printf("\n未做任何修改.\n");
                    }
                    return;
                }
                break;
            }
            case 1:
                printf("当前书名: %s\n", book->title);
                printf("请输入新书名(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(book->title, input);
                    modified = 1;
                }
                break;
            case 2:
                printf("当前作者: %s\n", book->author);
                printf("请输入新作者(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(book->author, input);
                    modified = 1;
                }
                break;
            case 3:
                printf("当前出版社: %s\n", book->publisher);
                printf("请输入新出版社(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(book->publisher, input);
                    modified = 1;
                }
                break;
            case 4: {
                printf("当前出版年份: %d\n", book->year);
                int newYear;
                if (safeScanfInt("请输入新出版年份(0表示未知): ", &newYear)) {
                    book->year = newYear;
                    modified = 1;
                }
                break;
            }
            case 5: {
                printf("当前价格: ¥%.2f\n", book->price);
                float newPrice;
                printf("请输入新价格: ");
                if (scanf("%f", &newPrice) == 1) {
                    book->price = newPrice;
                    modified = 1;
                } else {
                    printf("输入格式错误!\n");
                    clearInputBuffer();
                }
                break;
            }
            case 6: {
                printf("当前库存: %d\n", book->stock);
                int newStock;
                if (safeScanfInt("请输入新库存: ", &newStock)) {
                    book->stock = newStock;
                    modified = 1;
                }
                break;
            }
            case 7: {
                printf("当前分类: %d\n", book->category);
                int newCat;
                if (safeScanfInt("请输入新分类编号: ", &newCat)) {
                    book->category = newCat;
                    modified = 1;
                }
                break;
            }
            default:
                printf("\n无效选项!\n");
        }
    }
}

// 查找图书
void searchBook() {
    char keyword[MAX_STRING_LENGTH];
    printf("\n--- 查找图书 ---\n");
    printf("请输入书名或作者: ");
    scanf(" %[^\n]", keyword);

    printf("\n%-15s %-30s %-20s %-15s %-8s\n",
           "图书编号", "书名", "作者", "出版社", "库存");
    printf("------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL ||
            strstr(books[i].author, keyword) != NULL) {
            printf("%-15s %-30s %-20s %-15s %-8d\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].publisher, books[i].stock);
            found++;
        }
    }

    if (found == 0) {
        printf("\n未找到匹配的图书!\n");
    }
}

// 列出所有图书
void listBooks() {
    printf("\n--- 图书列表 ---\n");
    printf("共有 %d 本图书\n\n", bookCount);
    printf("%-15s %-30s %-20s %-15s %-8s %-6s %-10s\n",
           "图书编号", "书名", "作者", "出版社", "年份", "库存", "价格");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-15s %-30s %-20s %-15s %-8d %-6d ¥%-8.2f\n",
               books[i].id, books[i].title, books[i].author,
               books[i].publisher, books[i].year, books[i].stock, books[i].price);
    }
}

// 添加用户
void addUser() {
    if (userCount >= MAX_USERS) {
        printf("\n用户数量已达上限!\n");
        return;
    }

    User user;
    printf("\n--- 添加用户 ---\n");

    // 循环直到输入有效的ID
    while (1) {
        printf("请输入用户ID: ");
        scanf("%s", user.id);

        // 检查是否包含未知标记
        if (strchr(user.id, '#') != NULL) {
            printf("用户ID不允许使用 '#' 符号! 请重新输入。\n");
            continue;
        }

        if (findUserById(user.id) != -1) {
            printf("该用户ID已存在! 请重新输入。\n");
        } else {
            break; // ID有效，跳出循环
        }
    }

    printf("请输入学号(教师或其他可留空): ");
    scanf("%s", user.studentId);
    printf("请输入姓名: ");
    scanf(" %[^\n]", user.name);
    printf("请输入电话: ");
    scanf(" %[^\n]", user.phone);
    printf("请输入邮箱: ");
    scanf(" %[^\n]", user.email);
    while (!safeScanfInt("请输入用户类型(1-学生, 2-教师, 3-其他): ", &user.userType));

    users[userCount++] = user;
    printf("\n用户添加成功!\n");
    saveData();
}

// 删除用户
void deleteUser() {
    char keyword[MAX_STRING_LENGTH];
    char confirm;

    printf("\n--- 删除用户 ---\n");

    // 第一步：查询流程
    printf("请输入姓名、电话或学号进行搜索: ");
    scanf(" %[^\n]", keyword);

    // 搜索并显示匹配结果
    int indices[MAX_USERS];
    int foundCount = 0;

    printf("\n搜索结果:\n");
    printf("%-5s %-15s %-20s %-20s %-20s %-10s\n",
           "序号", "用户ID", "学号", "姓名", "电话", "类型");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, keyword) != NULL ||
            strstr(users[i].phone, keyword) != NULL ||
            strstr(users[i].studentId, keyword) != NULL ||
            strstr(users[i].id, keyword) != NULL) {
            char typeStr[20];
            if (users[i].userType == 1) strcpy(typeStr, "学生");
            else if (users[i].userType == 2) strcpy(typeStr, "教师");
            else strcpy(typeStr, "其他");

            printf("%-5d %-15s %-20s %-20s %-20s %-10s\n",
                   foundCount + 1,
                   users[i].id, users[i].studentId, users[i].name,
                   users[i].phone, typeStr);
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\n未找到匹配的用户!\n");
        return;
    }

    // 第二步：选择目标
    printf("\n共找到 %d 条记录, 请输入要删除的序号(1-%d): ", foundCount, foundCount);
    int selection;
    if (!safeScanfInt(NULL, &selection) || selection < 1 || selection > foundCount) {
        printf("\n无效的选择!\n");
        return;
    }

    int index = indices[selection - 1];
    User *user = &users[index];

    // 显示将要删除的信息
    printf("\n========== 即将删除的用户 ==========\n");
    printf("用户ID: %s\n", user->id);
    printf("学号: %s\n", user->studentId);
    printf("姓名: %s\n", user->name);
    printf("电话: %s\n", user->phone);
    printf("邮箱: %s\n", user->email);
    printf("类型: %s\n", user->userType == 1 ? "学生" : (user->userType == 2 ? "教师" : "其他"));
    printf("====================================\n");

    // 第三步：握手确认协议
    printf("\n⚠️ 警告: 此操作不可恢复!\n");
    printf("确认删除此用户? (输入 Y 确认, 其他键取消): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n删除操作已取消.\n");
        return;
    }

    // 检查是否有未归还的借阅记录
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].userId, user->id) == 0 && borrowRecords[i].status == 0) {
            printf("\n该用户还有未归还的图书,无法删除!\n");
            return;
        }
    }

    // 执行删除
    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    printf("\n✓ 用户删除成功!\n");
    saveData();
}

// 修改用户
// 修改用户
void updateUser() {
    char id[USER_ID_LENGTH];
    printf("\n--- 修改用户 ---\n");
    printf("请输入要修改的用户ID: ");
    scanf("%s", id);

    int index = findUserById(id);
    if (index == -1) {
        printf("\n未找到该用户!\n");
        return;
    }

    User *user = &users[index];
    int modified = 0;
    int choice;
    char input[MAX_STRING_LENGTH];

    while (1) {
        char typeStr[20];
        if (user->userType == 1) strcpy(typeStr, "学生");
        else if (user->userType == 2) strcpy(typeStr, "教师");
        else strcpy(typeStr, "其他");

        printf("\n当前用户信息:\n");
        printf("用户ID: %s\n", user->id);
        printf("1. 姓名: %s\n", user->name);
        printf("2. 电话: %s\n", user->phone);
        printf("3. 邮箱: %s\n", user->email);
        printf("4. 用户类型: %s\n", typeStr);
        printf("0. 返回\n");
        if (!safeScanfInt("请选择要修改的项: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 0: {
                char confirm;
                printf("确定保存并返回吗? (Y/N): ");
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y') {
                    if (modified) {
                        printf("\n用户修改成功!\n");
                        saveData();
                    } else {
                        printf("\n未做任何修改.\n");
                    }
                    return;
                }
                break;
            }
            case 1:
                printf("当前姓名: %s\n", user->name);
                printf("请输入新姓名(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->name, input);
                    modified = 1;
                }
                break;
            case 2:
                printf("当前电话: %s\n", user->phone);
                printf("请输入新电话(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->phone, input);
                    modified = 1;
                }
                break;
            case 3:
                printf("当前邮箱: %s\n", user->email);
                printf("请输入新邮箱(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->email, input);
                    modified = 1;
                }
                break;
            case 4: {
                printf("当前用户类型: %s\n", typeStr);
                int newType;
                if (safeScanfInt("请输入新用户类型(1-学生, 2-教师, 3-其他): ", &newType)) {
                    if (newType >= 1 && newType <= 3) {
                        user->userType = newType;
                        modified = 1;
                    } else {
                        printf("无效的用户类型!\n");
                    }
                }
                break;
            }
            default:
                printf("\n无效选项!\n");
        }
    }
}

// 查找用户
void searchUser() {
    char keyword[MAX_STRING_LENGTH];
    printf("\n--- 查找用户 ---\n");
    printf("请输入姓名、电话或学号: ");
    scanf(" %[^\n]", keyword);

    printf("\n%-15s %-20s %-20s %-20s %-20s %-10s\n",
           "用户ID", "学号", "姓名", "电话", "邮箱", "类型");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, keyword) != NULL ||
            strstr(users[i].phone, keyword) != NULL ||
            strstr(users[i].studentId, keyword) != NULL) {
            char typeStr[20];
            if (users[i].userType == 1) strcpy(typeStr, "学生");
            else if (users[i].userType == 2) strcpy(typeStr, "教师");
            else strcpy(typeStr, "其他");

            printf("%-15s %-20s %-20s %-20s %-20s %-10s\n",
                   users[i].id, users[i].studentId, users[i].name, users[i].phone,
                   users[i].email, typeStr);
            found++;
        }
    }

    if (found == 0) {
        printf("\n未找到匹配的用户!\n");
    }
}

// 列出所有用户
void listUsers() {
    printf("\n========== 用户列表 ==========\n");

    // 统计各类用户数量
    int teacherCount = 0, studentCount = 0, otherCount = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2) teacherCount++;
        else if (users[i].userType == 1) studentCount++;
        else otherCount++;
    }

    // 先显示教师
    printf("\n【教师】共 %d 人\n", teacherCount);
    printf("%-15s %-20s %-20s %-20s %-20s\n",
           "用户ID", "工号", "姓名", "电话", "邮箱");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2) {
            printf("%-15s %-20s %-20s %-20s %-20s\n",
                   users[i].id, users[i].studentId, users[i].name,
                   users[i].phone, users[i].email);
        }
    }

    // 再显示学生
    printf("\n【学生】共 %d 人\n", studentCount);
    printf("%-15s %-20s %-20s %-20s %-20s %-10s\n",
           "用户ID", "学号", "姓名", "电话", "邮箱", "年级");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 1) {
            printf("%-15s %-20s %-20s %-20s %-20s %-10s\n",
                   users[i].id, users[i].studentId, users[i].name,
                   users[i].phone, users[i].email, users[i].grade);
        }
    }

    // 最后显示其他用户
    if (otherCount > 0) {
        printf("\n【其他】共 %d 人\n", otherCount);
        printf("%-15s %-20s %-20s %-20s %-20s\n",
               "用户ID", "工号/学号", "姓名", "电话", "邮箱");
        printf("----------------------------------------------------------------------------------------\n");

        for (int i = 0; i < userCount; i++) {
            if (users[i].userType != 1 && users[i].userType != 2) {
                printf("%-15s %-20s %-20s %-20s %-20s\n",
                       users[i].id, users[i].studentId, users[i].name,
                       users[i].phone, users[i].email);
            }
        }
    }

    printf("\n总计: %d 个用户\n", userCount);
}

// 借阅图书
void borrowBook() {
    char userId[USER_ID_LENGTH], bookId[BOOK_ID_LENGTH];

    printf("\n--- 借阅图书 ---\n");
    printf("请输入用户ID: ");
    scanf("%s", userId);

    int userIndex = findUserById(userId);
    if (userIndex == -1) {
        printf("\n用户不存在!\n");
        return;
    }

    printf("请输入图书编号: ");
    scanf("%s", bookId);

    int bookIndex = findBookById(bookId);
    if (bookIndex == -1) {
        printf("\n图书不存在!\n");
        return;
    }

    if (books[bookIndex].stock <= 0) {
        printf("\n该图书库存不足!\n");
        return;
    }

    // 检查是否已经借阅且未归还
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].userId, userId) == 0 &&
            strcmp(borrowRecords[i].bookId, bookId) == 0 &&
            borrowRecords[i].status == 0) {
            printf("\n该用户已经借阅了这本书且未归还!\n");
            return;
        }
    }

    // 创建借阅记录
    BorrowRecord record;
    strcpy(record.bookId, bookId);
    strcpy(record.userId, userId);
    record.borrowDate = time(NULL);
    record.dueDate = record.borrowDate + 30 * 24 * 60 * 60; // 30天后到期
    record.returnDate = 0;
    record.status = 0; // 已借出

    borrowRecords[borrowCount++] = record;
    books[bookIndex].stock--;

    printf("\n借阅成功!\n");
    printf("借阅时间: %s\n", timeToString(record.borrowDate));
    printf("应还时间: %s\n", timeToString(record.dueDate));
    saveData();
}

// 归还图书
void returnBook() {
    char userId[USER_ID_LENGTH], bookId[BOOK_ID_LENGTH];

    printf("\n--- 归还图书 ---\n");
    printf("请输入用户ID: ");
    scanf("%s", userId);

    printf("请输入图书编号: ");
    scanf("%s", bookId);

    // 查找借阅记录
    int found = -1;
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].userId, userId) == 0 &&
            strcmp(borrowRecords[i].bookId, bookId) == 0 &&
            borrowRecords[i].status == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\n未找到借阅记录!\n");
        return;
    }

    borrowRecords[found].returnDate = time(NULL);
    borrowRecords[found].status = 1; // 已归还

    // 增加库存
    int bookIndex = findBookById(bookId);
    if (bookIndex != -1) {
        books[bookIndex].stock++;
    }

    printf("\n归还成功!\n");
    printf("归还时间: %s\n", timeToString(borrowRecords[found].returnDate));

    // 检查是否逾期
    if (borrowRecords[found].returnDate > borrowRecords[found].dueDate) {
        int overdueDays = (borrowRecords[found].returnDate - borrowRecords[found].dueDate) / (24 * 60 * 60);
        printf("警告: 已逾期 %d 天!\n", overdueDays);
    }

    saveData();
}

// 查看借阅记录
void viewBorrowRecords() {
    printf("\n--- 借阅记录 ---\n");
    printf("%-15s %-15s %-25s %-25s %-25s %-10s\n",
           "图书编号", "用户ID", "借阅时间", "应还时间", "归还时间", "状态");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < borrowCount; i++) {
        char* statusStr = borrowRecords[i].status == 0 ? "借出中" : "已归还";
        char* returnTime = borrowRecords[i].status == 0 ? "-" : timeToString(borrowRecords[i].returnDate);

        printf("%-15s %-15s %-25s %-25s %-25s %-10s\n",
               borrowRecords[i].bookId,
               borrowRecords[i].userId,
               timeToString(borrowRecords[i].borrowDate),
               timeToString(borrowRecords[i].dueDate),
               returnTime,
               statusStr);
    }
}

// 检查逾期记录
void checkOverdue() {
    time_t now = time(NULL);
    printf("\n--- 逾期记录 ---\n");
    printf("%-15s %-15s %-25s %-25s %-10s\n",
           "图书编号", "用户ID", "借阅时间", "应还时间", "逾期天数");
    printf("------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].status == 0 && now > borrowRecords[i].dueDate) {
            int overdueDays = (now - borrowRecords[i].dueDate) / (24 * 60 * 60);
            printf("%-15s %-15s %-25s %-25s %-10d天\n",
                   borrowRecords[i].bookId,
                   borrowRecords[i].userId,
                   timeToString(borrowRecords[i].borrowDate),
                   timeToString(borrowRecords[i].dueDate),
                   overdueDays);
            found++;
        }
    }

    if (found == 0) {
        printf("\n暂无逾期记录!\n");
    }
}

// 进入图书馆(登记进入)
void enterLibrary() {
    if (accessLogCount >= MAX_ACCESS_LOGS) {
        printf("\n出入记录已满!\n");
        return;
    }

    char userId[USER_ID_LENGTH];
    printf("\n--- 进入登记 ---\n");
    printf("请输入用户ID: ");
    scanf("%s", userId);

    int userIndex = findUserById(userId);
    if (userIndex == -1) {
        printf("\n用户不存在!\n");
        return;
    }

    // 检查是否有未离开的记录
    for (int i = 0; i < accessLogCount; i++) {
        if (strcmp(accessLogs[i].userId, userId) == 0 && accessLogs[i].status == 0) {
            printf("\n该用户已进入图书馆,尚未离开!\n");
            printf("进入时间: %s\n", timeToString(accessLogs[i].enterTime));
            return;
        }
    }

    // 创建进入记录
    AccessLog log;
    strcpy(log.userId, userId);
    log.enterTime = time(NULL);
    log.leaveTime = 0;
    log.status = 0; // 已进入

    accessLogs[accessLogCount++] = log;

    printf("\n进入登记成功!\n");
    printf("用户: %s\n", users[userIndex].name);
    printf("进入时间: %s\n", timeToString(log.enterTime));
    saveData();
}

// 离开图书馆(登记离开)
void leaveLibrary() {
    char userId[USER_ID_LENGTH];
    printf("\n--- 离开登记 ---\n");
    printf("请输入用户ID: ");
    scanf("%s", userId);

    int userIndex = findUserById(userId);
    if (userIndex == -1) {
        printf("\n用户不存在!\n");
        return;
    }

    // 查找进入记录
    int found = -1;
    for (int i = accessLogCount - 1; i >= 0; i--) {
        if (strcmp(accessLogs[i].userId, userId) == 0 && accessLogs[i].status == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\n未找到该用户的进入记录!\n");
        return;
    }

    accessLogs[found].leaveTime = time(NULL);
    accessLogs[found].status = 1; // 已离开

    time_t duration = accessLogs[found].leaveTime - accessLogs[found].enterTime;
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    printf("\n离开登记成功!\n");
    printf("用户: %s\n", users[userIndex].name);
    printf("进入时间: %s\n", timeToString(accessLogs[found].enterTime));
    printf("离开时间: %s\n", timeToString(accessLogs[found].leaveTime));
    printf("停留时长: %d小时%d分%d秒\n", hours, minutes, seconds);
    saveData();
}

// 查看出入记录
void viewAccessLogs() {
    printf("\n--- 出入记录 ---\n");
    printf("%-15s %-20s %-20s %-25s %-25s %-10s\n",
           "用户ID", "学号", "姓名", "进入时间", "离开时间", "状态");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < accessLogCount; i++) {
        int userIndex = findUserById(accessLogs[i].userId);
        char* userName = userIndex != -1 ? users[userIndex].name : "未知";
        char* studentId = userIndex != -1 ? users[userIndex].studentId : "-";
        char* leaveTime = accessLogs[i].status == 1 ? timeToString(accessLogs[i].leaveTime) : "尚未离开";
        char* statusStr = accessLogs[i].status == 0 ? "在馆中" : "已离开";

        printf("%-15s %-20s %-20s %-25s %-25s %-10s\n",
               accessLogs[i].userId,
               studentId,
               userName,
               timeToString(accessLogs[i].enterTime),
               leaveTime,
               statusStr);
    }
}

// 打印菜单
void printMenu() {
    printf("\n");
    printf("========================================\n");
    printf("        图书馆管理系统\n");
    printf("========================================\n");
    printf("  1. 图书管理\n");
    printf("     1.1 添加图书\n");
    printf("     1.2 删除图书\n");
    printf("     1.3 修改图书\n");
    printf("     1.4 查找图书\n");
    printf("     1.5 列出所有图书\n");
    printf("\n");
    printf("  2. 用户管理\n");
    printf("     2.1 添加用户\n");
    printf("     2.2 删除用户\n");
    printf("     2.3 修改用户\n");
    printf("     2.4 查找用户\n");
    printf("     2.5 列出所有用户\n");
    printf("\n");
    printf("  3. 学生账号管理\n");
    printf("     3.1 添加学生\n");
    printf("     3.2 删除学生\n");
    printf("     3.3 修改学生信息\n");
    printf("     3.4 按学号查询\n");
    printf("     3.5 列出所有学生\n");
    printf("\n");
    printf("  4. 教师账号管理\n");
    printf("     4.1 添加教师\n");
    printf("     4.2 删除教师\n");
    printf("     4.3 修改教师信息\n");
    printf("     4.4 按工号查询\n");
    printf("     4.5 列出所有教师\n");
    printf("\n");
    printf("  5. 借阅管理\n");
    printf("     5.1 借阅图书\n");
    printf("     5.2 归还图书\n");
    printf("     5.3 查看借阅记录\n");
    printf("     5.4 检查逾期记录\n");
    printf("\n");
    printf("  6. 出入登记\n");
    printf("     6.1 进入登记\n");
    printf("     6.2 离开登记\n");
    printf("     6.3 查看出入记录\n");
    printf("     6.4 按学号查看出入记录\n");
    printf("     6.5 按工号查看出入记录\n");
    printf("\n");
    printf("  0. 退出系统\n");
    printf("========================================\n");
    printf("请输入选项: ");
}

// 根据学号查找用户
int findUserByStudentId(char* studentId) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].studentId, studentId) == 0) {
            return i;
        }
    }
    return -1;
}

// 添加学生
void addStudent() {
    if (userCount >= MAX_USERS) {
        printf("\n用户数量已达上限!\n");
        return;
    }

    User user;
    printf("\n--- 添加学生 ---\n");

    // 循环直到输入有效的学号
    while (1) {
        printf("请输入学号: ");
        scanf("%s", user.studentId);

        // 检查是否包含未知标记
        if (strchr(user.studentId, '#') != NULL) {
            printf("学号不允许使用 '#' 符号! 请重新输入。\n");
            continue;
        }

        if (findUserByStudentId(user.studentId) != -1) {
            printf("该学号已存在! 请重新输入。\n");
        } else {
            break; // 学号有效，跳出循环
        }
    }

    // 自动生成用户ID
    sprintf(user.id, "S%04d", userCount + 1);

    printf("请输入姓名: ");
    scanf(" %[^\n]", user.name);
    printf("请输入电话: ");
    scanf(" %[^\n]", user.phone);
    printf("请输入邮箱: ");
    scanf(" %[^\n]", user.email);

    // 年级选择
    printf("\n请选择年级:\n");
    printf("1. 2020级\n");
    printf("2. 2021级\n");
    printf("3. 2022级\n");
    printf("4. 2023级\n");
    printf("5. 2024级\n");
    printf("6. 2025级\n");
    printf("7. 2026级\n");
    printf("8. 其他年级\n");
    int gradeChoice;
    while (!safeScanfInt("请选择 (1-8): ", &gradeChoice));

    switch (gradeChoice) {
        case 1: user.grade = 2020; break;
        case 2: user.grade = 2021; break;
        case 3: user.grade = 2022; break;
        case 4: user.grade = 2023; break;
        case 5: user.grade = 2024; break;
        case 6: user.grade = 2025; break;
        case 7: user.grade = 2026; break;
        case 8:
            while (!safeScanfInt("请输入年级 (如2027): ", &user.grade));
            break;
        default:
            user.grade = 2025; // 默认2025级
            break;
    }

    user.userType = 1; // 学生

    users[userCount++] = user;
    printf("\n学生添加成功!\n");
    printf("用户ID: %s\n", user.id);
    printf("学号: %s\n", user.studentId);
    printf("年级: %d级\n", user.grade);
    saveData();
}

// 删除学生(按学号)
void deleteStudent() {
    char keyword[STUDENT_ID_LENGTH];
    char confirm;

    printf("\n--- 删除学生 ---\n");

    // 第一步：查询流程
    printf("请输入学号或姓名进行搜索: ");
    scanf(" %[^\n]", keyword);

    // 搜索并显示匹配的学生结果
    int indices[MAX_USERS];
    int foundCount = 0;

    printf("\n搜索结果:\n");
    printf("%-5s %-15s %-20s %-20s %-15s %-20s %-10s\n",
           "序号", "用户ID", "学号", "姓名", "年级", "电话", "类型");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 1 && (
            strstr(users[i].studentId, keyword) != NULL ||
            strstr(users[i].name, keyword) != NULL ||
            strstr(users[i].id, keyword) != NULL)) {

            printf("%-5d %-15s %-20s %-20s %-15d级 %-20s %-10s\n",
                   foundCount + 1,
                   users[i].id, users[i].studentId, users[i].name,
                   users[i].grade, users[i].phone, "学生");
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\n未找到匹配的学生!\n");
        return;
    }

    // 第二步：选择目标
    printf("\n共找到 %d 条记录, 请输入要删除的序号(1-%d): ", foundCount, foundCount);
    int selection;
    if (!safeScanfInt(NULL, &selection) || selection < 1 || selection > foundCount) {
        printf("\n无效的选择!\n");
        return;
    }

    int index = indices[selection - 1];
    User *user = &users[index];

    // 显示将要删除的信息
    printf("\n========== 即将删除的学生 ==========\n");
    printf("用户ID: %s\n", user->id);
    printf("学号: %s\n", user->studentId);
    printf("姓名: %s\n", user->name);
    printf("年级: %d级\n", user->grade);
    printf("电话: %s\n", user->phone);
    printf("邮箱: %s\n", user->email);
    printf("====================================\n");

    // 第三步：握手确认协议
    printf("\n⚠️ 警告: 此操作不可恢复!\n");
    printf("确认删除此学生? (输入 Y 确认, 其他键取消): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n删除操作已取消.\n");
        return;
    }

    // 检查是否有未归还的借阅记录
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].userId, user->id) == 0 && borrowRecords[i].status == 0) {
            printf("\n该学生还有未归还的图书,无法删除!\n");
            return;
        }
    }

    // 执行删除
    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    printf("\n✓ 学生删除成功!\n");
    saveData();
}

// 修改学生信息(按学号)
// 修改学生信息
void updateStudent() {
    char studentId[STUDENT_ID_LENGTH];
    printf("\n--- 修改学生信息 ---\n");
    printf("请输入学号: ");
    scanf("%s", studentId);

    int index = findUserByStudentId(studentId);
    if (index == -1) {
        printf("\n未找到该学号的学生!\n");
        return;
    }

    User *user = &users[index];
    int modified = 0;
    int choice;
    char input[MAX_STRING_LENGTH];

    while (1) {
        printf("\n当前学生信息:\n");
        printf("用户ID: %s\n", user->id);
        printf("学号: %s\n", user->studentId);
        printf("1. 姓名: %s\n", user->name);
        printf("2. 年级: %d级\n", user->grade);
        printf("3. 电话: %s\n", user->phone);
        printf("4. 邮箱: %s\n", user->email);
        printf("0. 返回\n");
        if (!safeScanfInt("请选择要修改的项: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 0: {
                char confirm;
                printf("确定保存并返回吗? (Y/N): ");
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y') {
                    if (modified) {
                        printf("\n学生信息修改成功!\n");
                        saveData();
                    } else {
                        printf("\n未做任何修改.\n");
                    }
                    return;
                }
                break;
            }
            case 1:
                printf("当前姓名: %s\n", user->name);
                printf("请输入新姓名(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->name, input);
                    modified = 1;
                }
                break;
            case 2: {
                printf("当前年级: %d级\n", user->grade);
                int gradeChoice;
                if (safeScanfInt("请选择新年级 (1-2020级, 2-2021级, 3-2022级, 4-2023级, 5-2024级, 6-2025级, 7-2026级, 0-不修改): ", &gradeChoice)) {
                    if (gradeChoice >= 1 && gradeChoice <= 7) {
                        int grades[] = {2020, 2021, 2022, 2023, 2024, 2025, 2026};
                        user->grade = grades[gradeChoice - 1];
                        modified = 1;
                    }
                }
                break;
            }
            case 3:
                printf("当前电话: %s\n", user->phone);
                printf("请输入新电话(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->phone, input);
                    modified = 1;
                }
                break;
            case 4:
                printf("当前邮箱: %s\n", user->email);
                printf("请输入新邮箱(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->email, input);
                    modified = 1;
                }
                break;
            default:
                printf("\n无效选项!\n");
        }
    }
}

// 按学号查询学生信息
void searchStudentByNumber() {
    char studentId[STUDENT_ID_LENGTH];
    printf("\n--- 按学号查询 ---\n");
    printf("请输入学号: ");
    scanf("%s", studentId);

    int index = findUserByStudentId(studentId);
    if (index == -1) {
        printf("\n未找到该学号的学生!\n");
        return;
    }

    User *user = &users[index];
    printf("\n学生信息:\n");
    printf("----------------------------------------\n");
    printf("用户ID: %s\n", user->id);
    printf("学号: %s\n", user->studentId);
    printf("姓名: %s\n", user->name);
    printf("年级: %d级\n", user->grade);
    printf("电话: %s\n", user->phone);
    printf("邮箱: %s\n", user->email);
    printf("用户类型: 学生\n");

    // 查询该学生的进出记录
    printf("\n进出记录:\n");
    printf("%-20s %-25s %-25s %-10s %-15s\n",
           "学号", "进入时间", "离开时间", "状态", "停留时长");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < accessLogCount; i++) {
        int userIndex = findUserById(accessLogs[i].userId);
        if (userIndex != -1 && strcmp(users[userIndex].studentId, studentId) == 0) {
            char* leaveTime = accessLogs[i].status == 1 ? timeToString(accessLogs[i].leaveTime) : "尚未离开";
            char* statusStr = accessLogs[i].status == 0 ? "在馆中" : "已离开";

            printf("%-20s %-25s %-25s %-10s",
                   studentId,
                   timeToString(accessLogs[i].enterTime),
                   leaveTime,
                   statusStr);

            if (accessLogs[i].status == 1) {
                time_t duration = accessLogs[i].leaveTime - accessLogs[i].enterTime;
                int hours = duration / 3600;
                int minutes = (duration % 3600) / 60;
                int seconds = duration % 60;
                printf("%d小时%d分%d秒", hours, minutes, seconds);
            } else {
                printf("%-15s", "-");
            }
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        printf("暂无进出记录\n");
    }
}

// 列出所有学生
void listStudents() {
    int studentCount = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 1) {
            studentCount++;
        }
    }

    printf("\n--- 学生列表 ---\n");
    printf("共有 %d 个学生\n\n", studentCount);

    if (studentCount == 0) {
        printf("暂无学生记录\n");
        return;
    }

    printf("%-15s %-20s %-20s %-15s %-20s %-10s %-10s\n",
           "用户ID", "学号", "姓名", "年级", "电话", "邮箱", "类型");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 1) {
            printf("%-15s %-20s %-20s %-15d级 %-20s %-10s\n",
                   users[i].id,
                   users[i].studentId,
                   users[i].name,
                   users[i].grade,
                   users[i].phone,
                   "学生");
        }
    }
}

// 按学号查看出入记录
void viewAccessLogsByStudentId() {
    char studentId[STUDENT_ID_LENGTH];
    printf("\n--- 按学号查看出入记录 ---\n");
    printf("请输入学号: ");
    scanf("%s", studentId);

    int studentIndex = findUserByStudentId(studentId);
    if (studentIndex == -1) {
        printf("\n未找到该学号的学生!\n");
        return;
    }

    // 显示基本信息
    printf("\n该用户为: %s (%s)\n", users[studentIndex].name, 
           users[studentIndex].userType == 1 ? "学生" : "教师");
    
    // 查询该用户的进出记录
    printf("\n进出记录:\n");
    printf("%-20s %-25s %-25s %-10s %-15s\n",
           users[studentIndex].userType == 1 ? "学号" : "工号", 
           "进入时间", "离开时间", "状态", "停留时长");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < accessLogCount; i++) {
        int userIndex = findUserById(accessLogs[i].userId);
        if (userIndex != -1 && strcmp(users[userIndex].studentId, studentId) == 0) {
            char* leaveTime = accessLogs[i].status == 1 ? timeToString(accessLogs[i].leaveTime) : "尚未离开";
            char* statusStr = accessLogs[i].status == 0 ? "在馆中" : "已离开";

            printf("%-20s %-25s %-25s %-10s",
                   studentId,
                   timeToString(accessLogs[i].enterTime),
                   leaveTime,
                   statusStr);

            if (accessLogs[i].status == 1) {
                time_t duration = accessLogs[i].leaveTime - accessLogs[i].enterTime;
                int hours = duration / 3600;
                int minutes = (duration % 3600) / 60;
                int seconds = duration % 60;
                printf("%d小时%d分%d秒", hours, minutes, seconds);
            }
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        printf("暂无进出记录\n");
    }
}

// ==================== 教师账号管理 ====================

// 查找教师(按工号)
int findTeacherById(char* teacherId) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2 && strcmp(users[i].studentId, teacherId) == 0) {
            return i;
        }
    }
    return -1;
}

// 添加教师
void addTeacher() {
    if (userCount >= MAX_USERS) {
        printf("\n用户数量已达上限!\n");
        return;
    }

    User user;
    printf("\n--- 添加教师 ---\n");

    // 循环直到输入有效的工号
    while (1) {
        printf("请输入工号: ");
        scanf("%s", user.studentId);

        // 检查是否包含未知标记
        if (strchr(user.studentId, '#') != NULL) {
            printf("工号不允许使用 '#' 符号! 请重新输入。\n");
            continue;
        }

        if (findTeacherById(user.studentId) != -1) {
            printf("该工号已存在! 请重新输入。\n");
        } else {
            break; // 工号有效，跳出循环
        }
    }

    // 自动生成用户ID
    sprintf(user.id, "T%04d", userCount + 1);

    printf("请输入姓名: ");
    scanf(" %[^\n]", user.name);
    printf("请输入电话: ");
    scanf(" %[^\n]", user.phone);
    printf("请输入邮箱: ");
    scanf(" %[^\n]", user.email);
    user.userType = 2; // 教师

    users[userCount++] = user;
    printf("\n教师添加成功!\n");
    printf("用户ID: %s\n", user.id);
    printf("工号: %s\n", user.studentId);
    saveData();
}

// 删除教师(按工号)
void deleteTeacher() {
    char keyword[STUDENT_ID_LENGTH];
    char confirm;

    printf("\n--- 删除教师 ---\n");

    // 第一步：查询流程
    printf("请输入工号或姓名进行搜索: ");
    scanf(" %[^\n]", keyword);

    // 搜索并显示匹配的教师结果
    int indices[MAX_USERS];
    int foundCount = 0;

    printf("\n搜索结果:\n");
    printf("%-5s %-15s %-20s %-20s %-20s %-10s\n",
           "序号", "用户ID", "工号", "姓名", "电话", "类型");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2 && (
            strstr(users[i].studentId, keyword) != NULL ||
            strstr(users[i].name, keyword) != NULL ||
            strstr(users[i].id, keyword) != NULL)) {

            printf("%-5d %-15s %-20s %-20s %-20s %-10s\n",
                   foundCount + 1,
                   users[i].id, users[i].studentId, users[i].name,
                   users[i].phone, "教师");
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\n未找到匹配的教师!\n");
        return;
    }

    // 第二步：选择目标
    printf("\n共找到 %d 条记录, 请输入要删除的序号(1-%d): ", foundCount, foundCount);
    int selection;
    if (!safeScanfInt(NULL, &selection) || selection < 1 || selection > foundCount) {
        printf("\n无效的选择!\n");
        return;
    }

    int index = indices[selection - 1];
    User *user = &users[index];

    // 显示将要删除的信息
    printf("\n========== 即将删除的教师 ==========\n");
    printf("用户ID: %s\n", user->id);
    printf("工号: %s\n", user->studentId);
    printf("姓名: %s\n", user->name);
    printf("电话: %s\n", user->phone);
    printf("邮箱: %s\n", user->email);
    printf("====================================\n");

    // 第三步：握手确认协议
    printf("\n⚠️ 警告: 此操作不可恢复!\n");
    printf("确认删除此教师? (输入 Y 确认, 其他键取消): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n删除操作已取消.\n");
        return;
    }

    // 检查是否有未归还的借阅记录
    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrowRecords[i].userId, user->id) == 0 && borrowRecords[i].status == 0) {
            printf("\n该教师还有未归还的图书,无法删除!\n");
            return;
        }
    }

    // 执行删除
    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    printf("\n✓ 教师删除成功!\n");
    saveData();
}

// 修改教师信息(按工号)
// 修改教师信息
void updateTeacher() {
    char teacherId[STUDENT_ID_LENGTH];
    printf("\n--- 修改教师信息 ---\n");
    printf("请输入工号: ");
    scanf("%s", teacherId);

    int index = findTeacherById(teacherId);
    if (index == -1) {
        printf("\n未找到该工号的教师!\n");
        return;
    }

    User *user = &users[index];
    int modified = 0;
    int choice;
    char input[MAX_STRING_LENGTH];

    while (1) {
        printf("\n当前教师信息:\n");
        printf("用户ID: %s\n", user->id);
        printf("工号: %s\n", user->studentId);
        printf("1. 姓名: %s\n", user->name);
        printf("2. 电话: %s\n", user->phone);
        printf("3. 邮箱: %s\n", user->email);
        printf("0. 返回\n");
        if (!safeScanfInt("请选择要修改的项: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 0: {
                char confirm;
                printf("确定保存并返回吗? (Y/N): ");
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y') {
                    if (modified) {
                        printf("\n教师信息修改成功!\n");
                        saveData();
                    } else {
                        printf("\n未做任何修改.\n");
                    }
                    return;
                }
                break;
            }
            case 1:
                printf("当前姓名: %s\n", user->name);
                printf("请输入新姓名(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->name, input);
                    modified = 1;
                }
                break;
            case 2:
                printf("当前电话: %s\n", user->phone);
                printf("请输入新电话(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->phone, input);
                    modified = 1;
                }
                break;
            case 3:
                printf("当前邮箱: %s\n", user->email);
                printf("请输入新邮箱(直接回车不修改): ");
                scanf(" %[^\n]", input);
                if (strlen(input) > 0) {
                    strcpy(user->email, input);
                    modified = 1;
                }
                break;
            default:
                printf("\n无效选项!\n");
        }
    }
}

// 按工号查询教师信息
void searchTeacherById() {
    char teacherId[STUDENT_ID_LENGTH];
    printf("\n--- 按工号查询 ---\n");
    printf("请输入工号: ");
    scanf("%s", teacherId);

    int index = findTeacherById(teacherId);
    if (index == -1) {
        printf("\n未找到该工号的教师!\n");
        return;
    }

    User *user = &users[index];
    printf("\n教师信息:\n");
    printf("----------------------------------------\n");
    printf("用户ID: %s\n", user->id);
    printf("工号: %s\n", user->studentId);
    printf("姓名: %s\n", user->name);
    printf("电话: %s\n", user->phone);
    printf("邮箱: %s\n", user->email);
    printf("用户类型: 教师\n");

    // 查询该教师的进出记录
    printf("\n进出记录:\n");
    printf("%-20s %-25s %-25s %-10s %-15s\n",
           "工号", "进入时间", "离开时间", "状态", "停留时长");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < accessLogCount; i++) {
        int userIndex = findUserById(accessLogs[i].userId);
        if (userIndex != -1 && strcmp(users[userIndex].studentId, teacherId) == 0) {
            char* leaveTime = accessLogs[i].status == 1 ? timeToString(accessLogs[i].leaveTime) : "尚未离开";
            char* statusStr = accessLogs[i].status == 0 ? "在馆中" : "已离开";

            printf("%-20s %-25s %-25s %-10s",
                   teacherId,
                   timeToString(accessLogs[i].enterTime),
                   leaveTime,
                   statusStr);

            if (accessLogs[i].status == 1) {
                time_t duration = accessLogs[i].leaveTime - accessLogs[i].enterTime;
                int hours = duration / 3600;
                int minutes = (duration % 3600) / 60;
                int seconds = duration % 60;
                printf("%d小时%d分%d秒", hours, minutes, seconds);
            }
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        printf("暂无进出记录\n");
    }
}

// 列出所有教师
void listTeachers() {
    printf("\n--- 教师列表 ---\n");
    
    int teacherCount = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2) {
            teacherCount++;
        }
    }
    printf("共有 %d 位教师\n\n", teacherCount);
    
    if (teacherCount == 0) {
        printf("暂无教师记录\n");
        return;
    }
    
    printf("%-15s %-20s %-20s %-20s %-20s %-10s\n",
           "用户ID", "工号", "姓名", "电话", "邮箱", "类型");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (users[i].userType == 2) {
            printf("%-15s %-20s %-20s %-20s %-20s %-10s\n",
                   users[i].id,
                   users[i].studentId,
                   users[i].name,
                   users[i].phone,
                   users[i].email,
                   "教师");
        }
    }
}

// ==================== 教师出入记录查看 ====================

void viewAccessLogsByTeacherId() {
    char teacherId[STUDENT_ID_LENGTH];
    printf("\n--- 按工号查看教师出入记录 ---\n");
    printf("请输入工号: ");
    scanf("%s", teacherId);

    int teacherIndex = findTeacherById(teacherId);
    if (teacherIndex == -1) {
        printf("\n未找到该工号的教师!\n");
        return;
    }

    // 显示基本信息
    printf("\n该用户为: %s (教师)\n", users[teacherIndex].name);

    // 查询该用户的进出记录
    printf("\n进出记录:\n");
    printf("%-20s %-25s %-25s %-10s %-15s\n",
           "工号", "进入时间", "离开时间", "状态", "停留时长");
    printf("----------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < accessLogCount; i++) {
        int userIndex = findUserById(accessLogs[i].userId);
        if (userIndex != -1 && strcmp(users[userIndex].studentId, teacherId) == 0) {
            char* leaveTime = accessLogs[i].status == 1 ? timeToString(accessLogs[i].leaveTime) : "尚未离开";
            char* statusStr = accessLogs[i].status == 0 ? "在馆中" : "已离开";

            printf("%-20s %-25s %-25s %-10s",
                   teacherId,
                   timeToString(accessLogs[i].enterTime),
                   leaveTime,
                   statusStr);

            if (accessLogs[i].status == 1) {
                time_t duration = accessLogs[i].leaveTime - accessLogs[i].enterTime;
                int hours = duration / 3600;
                int minutes = (duration % 3600) / 60;
                int seconds = duration % 60;
                printf("%d小时%d分%d秒", hours, minutes, seconds);
            }
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        printf("暂无进出记录\n");
    }
}

// ==================== 图书种类管理 ====================

// 添加图书种类
void addCategory() {
    if (categoryCount >= MAX_CATEGORIES) {
        printf("\n种类数量已达上限!\n");
        return;
    }

    char name[MAX_CATEGORY_LENGTH];
    printf("\n--- 添加图书种类 ---\n");
    printf("请输入种类名称: ");
    scanf(" %[^\n]", name);

    // 检查是否已存在
    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i].name, name) == 0) {
            printf("\n该种类已存在!\n");
            return;
        }
    }

    strcpy(categories[categoryCount].name, name);
    categories[categoryCount].bookCount = 0;
    categoryCount++;

    printf("\n种类 '%s' 添加成功!\n", name);
    saveData();
}

// 删除图书种类
void deleteCategory() {
    char confirm;
    char keyword[MAX_CATEGORY_LENGTH];

    printf("\n--- 删除图书种类 ---\n");

    if (categoryCount == 0) {
        printf("\n暂无种类记录!\n");
        return;
    }

    // 第一步：查询流程
    printf("请输入种类名称进行搜索: ");
    scanf(" %[^\n]", keyword);

    // 搜索并显示匹配的种类
    int indices[MAX_CATEGORIES];
    int foundCount = 0;

    printf("\n搜索结果:\n");
    printf("%-5s %-30s\n", "序号", "种类名称");
    printf("--------------------------------\n");

    for (int i = 0; i < categoryCount; i++) {
        if (strstr(categories[i].name, keyword) != NULL) {
            printf("%-5d %-30s\n", foundCount + 1, categories[i].name);
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\n未找到匹配的种类!\n");
        return;
    }

    // 第二步：选择目标
    printf("\n共找到 %d 条记录, 请输入要删除的序号(1-%d): ", foundCount, foundCount);
    int selection;
    if (!safeScanfInt(NULL, &selection) || selection < 1 || selection > foundCount) {
        printf("\n无效的选择!\n");
        return;
    }

    int index = indices[selection - 1];

    // 显示将要删除的信息
    printf("\n========== 即将删除的种类 ==========\n");
    printf("种类名称: %s\n", categories[index].name);
    printf("====================================\n");

    // 第三步：握手确认协议
    printf("\n⚠️ 警告: 此操作不可恢复!\n");
    printf("确认删除此种类? (输入 Y 确认, 其他键取消): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n删除操作已取消.\n");
        return;
    }

    // 执行删除
    for (int i = index; i < categoryCount - 1; i++) {
        categories[i] = categories[i + 1];
    }
    categoryCount--;

    printf("\n✓ 种类删除成功!\n");
    saveData();
}

// 列出所有图书种类
void listCategories() {
    printf("\n--- 图书种类列表 ---\n");
    printf("共有 %d 个种类\n\n", categoryCount);

    if (categoryCount == 0) {
        printf("暂无种类记录\n");
        return;
    }

    printf("%-5s %-30s\n", "序号", "种类名称");
    printf("--------------------------------\n");

    for (int i = 0; i < categoryCount; i++) {
        printf("%-5d %-30s\n", i + 1, categories[i].name);
    }
}
