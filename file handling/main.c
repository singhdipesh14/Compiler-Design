#include <stdio.h>
#include <stdlib.h>

int main()
{
 FILE *finp;
 finp = fopen("input.txt", "r");
 if (finp == NULL)
 {
		printf("Cannot find the file, exiting ...");
		return 0;
 }
 FILE *fout;
 fout = fopen("output.txt", "w+");
 if (fout == NULL)
 {
		printf("Cannot find the file, exiting ...");
		return 0;
 }
 int cntLines = 0, cntChars = 0;
 char c = fgetc(finp);
 fseek(finp, 0L, SEEK_END);
 long sz = ftell(finp);
 fseek(finp, 0L, SEEK_SET);
 while (c != EOF)
 {
		if (c == '\n')
		{
			cntLines++;
		}
		cntChars++;
		fputc(c, fout);
		c = fgetc(finp);
 }
 printf("Done, size: %ld bytes, lines: %d, characters: %d", sz, cntLines, cntChars);
 fclose(finp);
 fclose(fout);
 return 0;
}