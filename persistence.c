#include "persistence.h"
#include "nnc_utils.h"

int persist_network(network *nk, char *fp)
{
    FILE *f = fopen(fp, "w");
    if (f == NULL)
    {
        fprintf(stderr, "[ERROR] persist_network(): Could not open %s (in write mode)\n", fp);
        return EXIT_FAILURE;
    }
    print_network(f, nk);
    printf("[INFO] persist(): Network persisted in %s\n", fp);
    fclose(f);
    return EXIT_SUCCESS;
}

int load_network(char *fp)
{
    FILE *f = fopen(fp, "r");
    if (f == NULL)
    {
        fprintf(stderr, "[ERROR] load_network(): Could not open %s (in read mode)\n", fp);
        return EXIT_FAILURE;
    }

    int c;
    bool preq;         // previous character was '='
    uint8_t neq = 0;   // number of previous eq signs
    int cur_stage = 0; // current stage
    bool gonextline = false;
    bool is_firstword = true; // is first word in line?
    char firstword[11];
    char word[9];
    uint8_t ind_firstword = 0;
    bool read_int = false;
    bool read_array = false;
    bool read_word = false;
    while ((c = fgetc(f)) != EOF)
    {
        if (gonextline && (char)c != '\n')
            continue;

        else if ((char)c == '\n')
        {
            gonextline = false;
            is_firstword = true;
            if (preq)
            {
                cur_stage = neq;
                preq = false;
            }
            if (neq > 0)
                neq = 0;
            continue;
        }

        else if ((char)c == '=' && (firstword || preq))
        {
            neq++;
            if (!preq)
                preq = true;
        }

        else if (preq && (char)c != '=')
        {
            cur_stage = neq;
            neq = 0;
            preq = false;
            gonextline = true;
        }

        else if (is_firstword && (char)c != ' ' && (char)c != ':')
        {
            firstword[ind_firstword] = (char)c;
            ind_firstword++;
        }

        else if (is_firstword && ((char)c == ' ' || (char)c == ':'))
        {
            is_firstword = false;
            firstword[ind_firstword] = '\0';
            ind_firstword = 0;
            printf("[DEBUG] load_network(): cur_stage=%i, firstword: %s\n", cur_stage, firstword);
            // TODO: handle depending on cur_stage and firstword
            if (!strncpm(firstword, "Max", 4) || !strncpm(firstword, "Current", 8) || !strncpm(firstword, "Input", 5) || !strncpm(firstword, "Number", 7))
                read_int = true;
            else if (!strncpm(firstword, "weights", 9) || !strncpm(firstword, "biases", 7))
                read_array = true;
            else if (!strncpm(firstword, "Activation", 11))
                read_word = true
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}