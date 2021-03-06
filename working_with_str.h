struct OptionDef
{
    const char* option_name;

    void (*func)();
};


void  my_puts   (char str[]);

char* my_strchr (char str[], char char_find);

int   my_strlen (const char str[]);

void  my_strcpy (char str_to[], const char str_from[]);

void  my_strNcpy(char str_to[], const char str_from[], int copy_length);

void  my_strCat (char str_first[], char str_last[]);

int   my_strcmp (char str_first[], char str_second[]);

char* my_fgets  (char *str, int num, FILE *file);

void process_arguments(int                    argc,       const char* argv[],
                       const struct OptionDef  Options[], int         options_range);

void print_help();

void start_unit_test();

void print_error();

void ASSERT(int error_id);

FILE* get_tests_file();

//--------Constants---------
const char default_file_name[] = "tests.txt";

const bool Debug = true;

const int  MAX_STR_SIZE = 1000;

const OptionDef Options[] = {
    {"--test", start_unit_test},
    {"-t",     start_unit_test},
    {"/t",     start_unit_test},

    {"--help", print_help},
    {"-h",     print_help},
    {"/h",     print_help}
};

const int  INF  = 100000000;

int        Line = -1;
//--------Constants---------


enum ERROR_CODES
{
    NULL_ARRAY = 1,
    TOO_BIG_NUMBER,
    UNEXPECTED_EOF,
    UNEXPECTED_ZERO,
    CURSED_FILE
};




