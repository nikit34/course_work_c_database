#include"stud_struct.h"


void info() {
    printf("\n\n############### For run program ###############\n\n");
    printf("call help  :  <-h> or <--help> (1 arg)\n");
    printf("clear file :  <-c> or <--clear> (1 arg) <file name> (2 arg with or without format)\n");
    printf("write data :  <file name> (1 arg with or without format)\n");
    printf("\n\n\n\n");
    printf("Format input data:\n");
    printf("    [Surname F.M.], [sex], [number group]\n");
    printf("        Surname F.M.  - this surname, forename, middle (with two points and space!)\n");
    printf("        sex  - one char\n");
    printf("        number group  - only integers\n");
    printf("        all separate follow char: ',' \n\n\n");
}

void preparation_file(char *file_name) {
    char format_file[4] = ".txt";
    int count_str = 0, count_substr = 0;
    bool flag;
    while(file_name[count_str] != '\0')
        count_str++;
    while(format_file[count_substr] != '\0')
        count_substr++;
    for(int i = 0; i <= count_str - count_substr; i++) {
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

void write_input(char *file_name) {
    FILE *f = fopen(file_name, "at+");
    (f == NULL) ? printf("cannot open file") : printf("open file for recard\nWrite as form '<surname> <initials> <sex> <num group>'\n\n");
    int two_consecutive = 0, num_word = 0;
    char ch;
    student *s_in = (student*)malloc(sizeof(student) + 40 * sizeof(char));
    do {
        ch = getchar();
        if(ch == 0x0A) {
            printf("you entered: %s - %s - %s - %s\n\n", s_in->surname, s_in->initials, s_in->sex, s_in->num_group);
            fprintf(f, "%s%s%s%s\n", s_in->surname, s_in->initials, s_in->sex, s_in->num_group);
            num_word = 0;
            two_consecutive++;
            s_in = (student*)malloc(sizeof(student) + 40 * sizeof(char));
        } else {
            if(ch == 0x20) {
                num_word++;
            } else {
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
            two_consecutive = 0;
        }
    } while(two_consecutive != 2);
    fclose(f);
}

int main(int argc, char* argv[]) {
    if(argc < 2 || (argc == 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")))) {
        info();
    } else if(argc == 3 && (strcmp(argv[1], "-c") || strcmp(argv[1], "--clear"))) {
        preparation_file(argv[2]);
        FILE *f = fopen(argv[2], "w");
        fclose(f);
    } else if(argc == 2 || (argc == 3 && (strcmp(argv[1], "-w") || strcmp(argv[1], "--write")))) {
        preparation_file(argv[1]);
        write_input(argv[1]);
    } else {
        printf("specify input line\n");
        return 1;
    }
    return 0;
}
