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

bool is_figure(char c)
{
    return ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || (c == '6') || (c == '7') || (c == '8') || (c == '9'));
}
bool is_numeric(char c)
{
    return (is_figure(c) || (c == '-') || (c == '.'));
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
    char firstword[11];       // used to identify following numerical value(s)
    uint8_t ind_firstword = 0;
    bool read_int = false;
    bool read_array = false;
    bool read_word = false;
    char current_ch[10] = {0}; // currently read value (integer, float or word)
    uint8_t current_ind = 0;   // character index when reading word or number
    uint8_t array_ind = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if ((gonextline && (char)c != '\n') || (read_word && ((char)c == ' ' || (char)c == ':')))
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
            if (read_int)
            {
                current_ch[current_ind] = '\0';
                current_ind = 0;
                read_int = false;
                // TODO: attribute number to right value
                printf("[DEBUG] load_network(): read int: %s\n", current_ch);
            }
            if (read_word)
            {
                current_ch[current_ind] = '\0';
                current_ind = 0;
                read_word = false;
                // TODO: attribute word to right value
                printf("[DEBUG] load_network(): read word: %s\n", current_ch);
            }
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
            if (!strncmp(firstword, "Max", 4) || !strncmp(firstword, "Current", 8) || !strncmp(firstword, "Input", 5) || !strncmp(firstword, "Number", 7))
                read_int = true;
            else if (!strncmp(firstword, "weights", 9) || !strncmp(firstword, "biases", 7))
                read_array = true;
            else if (!strncmp(firstword, "Activation", 11))
                read_word = true;
        }

        else if ((read_int && is_figure((char)c)) || (read_array && is_numeric((char)c)))
        {
            current_ch[current_ind] = (char)c;
            current_ind++;
        }

        else if (read_array && (char)c == ',')
        {
            current_ch[current_ind] = '\0';
            current_ind = 0;
            // TODO: attribute word to right value
            printf("[DEBUG] load_network(): read array float: %s (index: %u)\n", current_ch, array_ind);
            array_ind++;
        }

        else if (read_array && (char)c == ']')
        {
            current_ch[current_ind] = '\0';
            current_ind = 0;
            read_array = false;
            // TODO: attribute word to right value
            printf("[DEBUG] load_network(): read array float: %s (index: %u)\n", current_ch, array_ind);
            array_ind = 0;
        }

        else if (read_word)
        {
            current_ch[current_ind] = (char)c;
            current_ind++;
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}