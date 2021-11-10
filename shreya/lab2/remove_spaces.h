

void removeSpaces()
{
    //changes : 1. check for proper termination of comment lines
    // 2. do not remove any spaces or anything inside literals
    FILE *fa, *fb;
    int ca, cb;
    fa = fopen("input.c", "r");
    char buffer[1048];
    buffer[0] = '\0';
    int i = 0,linecount=0;
    int commentClosed=1;
    //bool commentClosed = false;
    if (fa == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    fb = fopen("spaces_output.c", "w+");
    ca = getc(fa);
    while (ca != EOF)
    {
        //to handle literals
        if (ca == '"')
        {
            putc(ca, fb);
            ca = getc(fa);
            while (ca != '"')
            {
                putc(ca, fb);
                ca = getc(fa);
            }
            putc(ca, fb);
        }
        if (ca == ' ')
        {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }
        //also handle if comment not closed by storing everythin in buffer
        if (ca == '/')
        {
            linecount=0;
            i = 0;
            buffer[i++] = ca;
            cb = getc(fa);
            buffer[i++] = cb;
            if (cb == '/')
            {
                while (ca != '\n')
                {
                    ca = getc(fa);
                    buffer[i++] = ca;
                    if (ca == EOF)
                    { // IE COMMENT DID NOT TERMINATE
                        for (int j = 0; j < i; j++)
                        {
                            putc(buffer[j], fb);
                        }
                        break;
                    }
                }
                if(ca =='\n')
                    putc('\n',fb);
                
            }
            else if (cb == '*')
            {
                do
                {
                    while (ca != '*')
                    {
                        ca = getc(fa);
                        buffer[i++] = ca;
                        if(ca =='\n')
                            linecount++;
                        if (ca == EOF)
                        { // IE COMMENT DID NOT TERMINATE
                            // for (int j = 0; j < i; j++)
                            // {
                            //     putc(buffer[j], fb);
                            // }
                            commentClosed=0;
                            break;
                        }
                    }
                    
                    if (!commentClosed)
                    { // IE COMMENT DID NOT TERMINATE
                        
                        break;
                    }
                    ca = getc(fa);
                    buffer[i++] = ca;
                    if(ca=='\n')
                        linecount++;
                    if(ca == EOF){
                        commentClosed=0;
                        break;
                    }
                    
                } while (ca != '/');
            }
            if(!commentClosed){
                for (int j = 0; j < i; j++)
                 {
                    putc(buffer[j], fb);
                 }
            }
            for(int i=0;i<linecount;i++){
                putc('\n',fb);
            }
            // else
            // {
            //     putc(ca, fb);
            //     putc(cb, fb);
            // }
        }
        else
            putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
}