#include"stud_struct.h"


void info() {
    printf("\n\n############### For run program ###############\n\n");
    printf("call help  :  <-h> or <--help> (1 arg)\n");
    printf("clear file :  <-c> or <--clear> (1 arg) <file name> (2 arg with or without format)\n");
    printf("write data :  <-w> or <--write> (1 arg) <file name> (2 arg with or without format)\n");
    printf("start calc :  <-s> or <--start> (1 arg) <file name> (2 arg with or without format)\n");
    printf("\n\n\n\n");
    printf("Format input data:\n");
    printf("    [Surname F.M.], [sex], [number group]\n");
    printf("        Surname F.M.  - this surname, forename, middle (with two points and space!)\n");
    printf("        sex  - one char\n");
    printf("        number group  - only integers\n");
    printf("        all separate follow char: ',' \n\n");
    printf("then enter the ratings with a space\n");
    printf("numbers in the range 0...999\n");
    printf("to complete the entry - two clicks 'enter' key\n\n\n");
}

void preparation_file(char *file_name) {
    char format_file[] = ".txt";
    int count_str = 0, count_substr = 0;
    bool flag;
    while(file_name[count_str] != '\0')
        count_str++;
    while(format_file[count_substr] != '\0')
        count_substr++;
    for(int i = 0; i <= (count_str - count_substr); i++) {
        for(int j = i; j < i + count_substr; j++) {
            flag = true;
            if(file_name[j] != format_file[j - i]) {
                flag = false;
                break;
            }
        }
        if(flag == true)
            break;
    }
    if(flag == false)
        file_name = strcat(file_name, ".txt");
}

struct marks* write_marks(struct student *s_in) {
    struct marks *m_in = (marks*)malloc(sizeof(marks) + sizeof(int));
    m_in->id = s_in->id;
    int two_consec_mark = 0, i = 0, bit = 0;
    char ch_mark, num_mark[3];
    bool empty_row_mark = true;
    printf("enter marks (with space and range 0...999):   ");
    while (ch_mark != EOF) {
        ch_mark = getchar();
        if(ch_mark == 0x0A && empty_row_mark == true) {
            two_consec_mark++;
            if(two_consec_mark == 2)
                break;
            empty_row_mark = true;
        } else if((ch_mark - '0') >= 0 && (ch_mark - '0') <= 9 && bit < 3) {
            num_mark[bit] = ch_mark;
            bit++;
            two_consec_mark = 0;
            empty_row_mark = false;
        } else if((ch_mark == 0x20 || ch_mark == 0x0A) && empty_row_mark == false) {
            i++;
            m_in->mark_arr = (int*)realloc(m_in->mark_arr, sizeof(int) * i * 2);
            sscanf(num_mark, "%d", (m_in->mark_arr + i));
            for(int j = 0; j < sizeof(num_mark); j++)
                num_mark[j] = ' ';
            bit = 0;
            empty_row_mark = (ch_mark == 0x0A) ? true : false;
        } else {
            printf("\ninvalided inputs marks\n");
            return NULL;
        }
    }
    printf("\nsave marks\n");
    return m_in;
};

void write_input(char *file_name) {
    FILE *f = fopen(file_name, "at+");
    fprintf(f, "id,surname,F.M.,sex,group,marks\n");
    (f == NULL) ? printf("cannot open file") : printf("open file for recard\nWrite as form '<surname> <initials> <sex> <num group>'\n\n");
    int two_consec = 0, num_word = 0, count_record = 0;
    char ch;
    bool empty_row = true;
    student *s_in = (student*)malloc(sizeof(student) + 33 * sizeof(char) + sizeof(int));
    printf("input data:   ");
    do {
        ch = getchar();
        if(ch == 0x0A && empty_row == false) {
            s_in->id = count_record;
            count_record++;
            printf("\n             gen. id  surname F.M.   sex   group\n");
            printf("you entered: %d       %s %s    %s    %s\n\n", s_in->id, s_in->surname, s_in->initials, s_in->sex, s_in->num_group);
            struct marks *m_in = write_marks(s_in);
            fprintf(f, "%d,%s,%s,%s,%s", s_in->id, s_in->surname, s_in->initials, s_in->sex, s_in->num_group);
            for(int i = 0; i < sizeof(m_in->mark_arr); i++) {
                fprintf(f, ",%d", m_in->mark_arr[i]);
                m_in->mark_arr[i] = ' ';
            }
            fprintf(f, "\n");
            num_word = 0;
            empty_row = true;
            two_consec++;
            s_in = (student*)malloc(sizeof(student) + 33 * sizeof(char) + sizeof(int));
            free(s_in);
            free(m_in);
            printf("\ninput data or for save tap 'enter' (%d/2):   ", two_consec);
        } else if(ch == 0x0A && empty_row == true) {
            two_consec++;
            printf("for save tap 'enter' (%d/2)\n", two_consec);
            empty_row = true;
        } else {
            if(ch == 0x20) {
                num_word++;
            } else if(strcmp(&ch, ",") != 0) {
                switch(num_word) {
                case 0:
                    strncat(s_in->surname, &ch, 1);
                    break;
                case 1:
                    strncat(s_in->initials, &ch, 1);
                    break;
                case 2:
                    strncat(s_in->sex, &ch, 1);
                    break;
                case 3:
                    strncat(s_in->num_group, &ch, 1);
                    break;
                default:
                    fclose(f);
                }
            }
            two_consec = 0;
            empty_row = false;
        }
    } while(two_consec != 2);
    fclose(f);
}

int main(int argc, char* argv[]) {
    if(argc < 2 || (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))) {
        info();
    } else if(argc == 3 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0)) {
        preparation_file(argv[2]);
        FILE *f = fopen(argv[2], "w");
        fclose(f);
    } else if(argc == 3 && (strcmp(argv[1], "-w") == 0 || strcmp(argv[1], "--write") == 0)) {
        preparation_file(argv[2]);
        write_input(argv[2]);
    } else if(argc == 3 && (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--start") == 0)) {
        preparation_file(argv[2]);
        start_calc(argv[2]);
    } else {
        printf("specify input line\n");
        return 1;
    }
    return 0;
}
