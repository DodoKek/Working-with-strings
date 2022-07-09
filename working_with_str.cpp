//#define NDEBUG 1

#include <txlib.h>
#include <stdio.h>
#include <assert.h>
#include "working_with_str.h"

//Line_debug_tracking

#define LocSet        Line = __LINE__

#define de_my_strlen  LocSet; my_strlen
#define de_my_strcpy  LocSet; my_strcpy
#define de_my_puts    LocSet; my_puts
#define de_my_fgets   LocSet; my_fgets

//Line_debug_tracking


int x = 1, 2, 3, 4, x, x+1, x-1, rand(), y, 0? 0? 0 : 1 : 0;


int len = de_my_strlen ("abc");

int len = LocSet, my_strlen ("abc");

void ASSERT(int error_id)
{
    switch (error_id)
    {
        case NULL_ARRAY:
            printf("Error while working with the array. \n");

        case TOO_BIG_NUMBER:
            printf("Pathetic attempt to work with digit, greater than allowed \n");

        case UNEXPECTED_EOF:
            printf("Pathetic attempt to call function with EOF while working with file. \n");

        case CURSED_FILE:
            printf("Error while reading the file." "\n");

        case UNEXPECTED_ZERO:
            printf("Function does not expect the number to be zero. \n");

        default:
            printf("Something scary happened, error_id = %d.\n", error_id);

    }

    printf("Was triggered by function call in line %d. \n", Line);
}


int my_strlen(const char str[])
{
    assert(str != NULL);

    if (str == NULL) ASSERT(NULL_ARRAY);

    for (int i = 0; ; i++)
    {
        if (str[i] == '\0')
        {
            return i;
        }
    }
}


void my_strcpy(char str_to[], const char str_from[])
{
    if (!str_to)   ASSERT(NULL_ARRAY);
    if (!str_from) ASSERT(NULL_ARRAY);

    int str_len = my_strlen(str_from);

    for (int i = 0; str_from[i]; i++)
    {
        str_to[i] = str_from[i];
    }

    str_to[str_len] = '\0';
}


void  my_puts(char str[])
{
    int str_len = my_strlen(str);

    for (int i = 0; i < str_len; i++)
    {
        putchar(str[i]);
    }

    putchar('\n');
}


char* my_strchr(char str[], char char_find)
{
    int str_len = my_strlen(str);

    for (int i = 0; i < str_len; i++)
    {
        if (str[i] == char_find) return str + i;
    }

    return nullptr;
}


void  my_strNcpy(char str_to[], const char str_from[], int copy_length)
{
    int str_from_len = my_strlen(str_from);

    int final_indx = std::min(str_from_len, copy_length);

    for (int i = 0; i < final_indx; i++)
    {
        str_to[i] = str_from[i];
    }

    for (int i = final_indx; i <= str_from_len; i++)
    {
        str_to[i] = '\0';
    }
}


void my_strCat (char str_first[], char str_last[])
{
    int str_first_len = my_strlen(str_first);
    int str_last_len  = my_strlen(str_last);

    for (int i = str_first_len; i < str_first_len + str_last_len; i++)
    {
        str_first[i] = str_last[i-str_first_len];
    }

}


int my_strcmp(char str_first[], char str_second[])
{

    for (int i = 0;;i++)
    {
        assert(i < strlen(str_first) && i < strlen(str_second));

        if (str_first[i] < str_second[i]) return -1;

        if (str_first[i] > str_second[i]) return 1;

        if (str_first[i] == '\0' && str_second[i] == '\0') break;
    }

    return 0;

}


char* my_fgets(char *str, int num, FILE *file)
{
    if(num > INF)
    {
        assert(num < INF);
        print_error();
    }

    if (file == NULL) return nullptr;

    int sym = -1;

    for (int i = 0; i < num - 1; i++)
    {
        sym = fgetc(file);

        switch(sym)
        {
            case EOF:
            {
                if (i == 0) return nullptr;
                else
                {
                    str[i] = '\0';
                    return str;
                }
            }
            case '\n':
            {
                str[i] = '\n';
                str[i+1] = '\0';
                return str;
            }
            default:
            {
                str[i] = sym;
            }
        }


    }
    str[num-1] = '\0';
    return str;
}


void process_arguments(int                    argc,      const char* argv[],
                       const struct OptionDef Options[], int         options_range)
{
    assert(argc > 0 && argv != NULL && Options != NULL && options_range < INF);

    int count_processed_options = 0;

    for (int i = 0; i < argc; i++)
    {
        for(int j = 0; j < options_range; j++)
        {
            if (strcmp(argv[i], Options[j].option_name) == 0)
            {
                Options[j].func();
                count_processed_options++;
            }
        }
    }

    if (count_processed_options != argc - 1)
    {
        printf("��������� ��������� ������� �����������.\n");
    }
}


void print_help()
{
    printf("�������� ��� ������������ ���������... �� � ��� �����!\n");

    char help_src[] = "chrome C:\\Users\\User\\Desktop\\Lessons\\Square_equasion\\html\\index.html";

    system(help_src);
}


void start_unit_test()
{
    FILE *tests_file = get_tests_file();

    if (tests_file == NULL)
    {
        printf("Failed to open the file \n");
        getchar();

        return;
    }

    int num_of_test = 1;

    while (true)
    {
        int check_EOF = 1;
        char test_str_1[MAX_STR_SIZE] = "";
        char test_str_2[MAX_STR_SIZE] = "";

        my_fgets(test_str_1, INF + 10, tests_file);
        my_fgets(test_str_2, MAX_STR_SIZE, tests_file);

        //my_puts(test_str_1); //Testing puts
        my_puts(test_str_1);
        my_puts(test_str_2);

        num_of_test++;
        if (fgets("", MAX_STR_SIZE, tests_file) == NULL) break;
    }

    fclose(tests_file);
}


FILE* get_tests_file()
{
    char file_name[] = {};

    char is_default[] = "def";

    printf("Enter file name. Enter def to keep tests.txt\n");

    scanf("%s", file_name);

    assert(file_name[0] != '\0');

    if (strcmp(file_name, is_default) == 0)
    {
        printf("Default name\n");
        return fopen(default_file_name, "r");
    }
    else
    {
        return fopen(file_name, "r");
    }

    printf("File name %s\n", file_name);
}


void print_error()
{
//    printf("������ ���� ������� ��� ������ ������� � ������ %d", Line_debug);
}


int main(int argc, const char* argv[])
{
    assert(argc > 0 && argv != NULL);

    char str1[] = "abcd";
    char str2[] = "abcde";

    process_arguments(argc, argv, Options, sizeof(Options) / sizeof(Options[0]));

    de_my_strlen(NULL);

}
