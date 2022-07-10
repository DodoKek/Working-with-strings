//#define NDEBUG 1

#include <txlib.h>
#include <stdio.h>
#include <assert.h>
#include "working_with_str.h"
#include <algorithm>
#include <string.h>

void ASSERT(int error_id)
{
    switch (error_id)
    {
        case NULL_ARRAY:
            printf("Error while working with the array, error_id = %d.\n", NULL_ARRAY);

        case TOO_BIG_NUMBER:
            printf("Pathetic attempt to work with digit, greater than allowed, error_id = %d.\n", TOO_BIG_NUMBER);

        case UNEXPECTED_EOF:
            printf("Pathetic attempt to call function with EOF while working with file, error_id = %d.\n", UNEXPECTED_EOF);

        case CURSED_FILE:
            printf("Error while reading the file, error_id = %d.\n", CURSED_FILE);

        case UNEXPECTED_ZERO:
            printf("Function does not expect the number to be zero.\n", UNEXPECTED_ZERO);

        default:
            printf("Something scary happened, error_id = %d.\n", error_id);

    }

    printf("Was triggered by function call in line %d. \n", Line);
}


int my_strlen(const char str[])
{
    if (!(str != NULL)) ASSERT(NULL_ARRAY);

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

    for (int i = 0; str_from[i-1] != '\0'; i++)
    {
        str_to[i] = str_from[i];
    }

}


void  my_puts(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        putchar(str[i]);
    }

    putchar('\n');
}


char* my_strchr(char str[], char char_find)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == char_find) return str + i;
    }

    return nullptr;
}


void  my_strNcpy(char str_to[], const char str_from[], int copy_length)
{
    for (int i = 0; i < copy_length || str_from[i-1] != '\0'; i++)
    {
        str_to[i]   = str_from[i];
    }

    for (int i = copy_length; str_from[i-1] != '\0'; i++)
    {
        str_to[i]   = '\0';
    }
}


void my_strCat (char str_first[], char str_last[])
{
    int str_first_len = my_strlen(str_first);

    for (int i = str_first_len; str_last[i-1] != '\0'; i++)
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
    if(!(num < INF)) assert(num < INF);

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


//Line_debug_tracking

#define LocSet        Line = __LINE__

#define de_my_strlen  LocSet, my_strlen
#define de_my_strcpy  LocSet, my_strcpy
#define de_my_puts    LocSet, my_puts
#define de_my_fgets   LocSet, my_fgets

//Line_debug_tracking


int main(int argc, const char* argv[])
{
    assert(argc > 0 && argv != NULL);

    char str1[] = "abcd";
    char str2[] = "abcde";

    process_arguments(argc, argv, Options, sizeof(Options) / sizeof(Options[0]));

    //printf("%d\n", TOO_BIG_NUMBER);

    de_my_strlen(NULL);


}
