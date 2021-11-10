#ifndef _REMOVE_H
#define _REMOVE_H
void prep()
{
    removeSpaces();
    FILE *finp = fopen("spaces_output.c", "r");
    FILE *fout = fopen("prep_output.c", "w+");
    char c = 0;
    char buffer[100];
    buffer[0] = '\0';
    int i = 0;
    char *includeStr = "include", *defineStr = "define", *intStr = "int";
    int intFlag = 0;
    while (c != EOF)
    {
        c = fgetc(finp);
        if (c == '#' && intFlag == 0)
        {
            while (c != ' ')
            {
                c = fgetc(finp);
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            if (strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL)
            {
                while (c != '\n')
                {
                    c = fgetc(finp); //removing from output file
                }
                if (c != EOF)
                    fputc('\n', fout);
            }
            else
            {
                if (c != EOF)
                    fputc('#', fout);
                for (int j = 0; j < i; j++)
                {
                    if (c != EOF)
                        fputc(buffer[j], fout);
                }
                while (c != '\n')
                {
                    c = fgetc(finp);
                    if (c != EOF)
                        fputc(c, fout);
                }
                if (c != EOF)
                    fputc('\n', fout);
            }
            i = 0;
            buffer[0] = '\0';
        }
        else
        {
            if (intFlag == 0)
            {
                buffer[i++] = c;
                buffer[i] = '\0';
                if (strstr(buffer, intStr) != NULL)
                {
                    intFlag = 1; // ie we have reached main function now or a global declaration
                }
            }
            if (c == ' ' || c == '\n')
            {
                buffer[0] = '\0';
                i = 0;
            }
            if (c != EOF)
                fputc(c, fout);
        }
    }
    fputc('$', fout);
    fclose(finp);
    fclose(fout);
    return;
}
#endif