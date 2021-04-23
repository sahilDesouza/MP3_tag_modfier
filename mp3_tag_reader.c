/*
Description :  This is an example program that shows how to extract bytes of data and modify the MP3 file.
	       Title, Albumn, Artist, Year, Comment and Genre.
Project name: mp3_tag_reader_editor
Author: Sahil Desouza
Date : 21/08/2020

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creating structure
typedef struct _Mp3Info
{
	//char arrays initialised
	char id3_tag[100];
	char title_p[100];
	char artist_p[100];
	char album_p[100];
	char year_p[100];
	char genre_p[100];
	char comment_p[100];

	//size int values initilised
	int size_title_p;
	int size_artist_p;
	int size_album_p;
	int size_year_p;
	int size_genre_p;
	int size_comment_p;

	//file pointer
	FILE *fp;
	
} Mp3Info;

void titleInfo(Mp3Info *);
void artistInfo(Mp3Info *);
void albumInfo(Mp3Info *);
void yearInfo(Mp3Info *);
void commentInfo(Mp3Info *);
void genreInfo(Mp3Info *);

int main(int argc, char **argv) 
{
	Mp3Info mp3Info;
	int i;
	//inititalising the size variables in the structure to 0
	mp3Info.size_title_p = 0;
	mp3Info.size_artist_p = 0;
	mp3Info.size_album_p = 0;
	mp3Info.size_year_p = 0;
	mp3Info.size_genre_p = 0;
	mp3Info.size_comment_p = 0;
		
	//if only 1 argument passed then ERROR
        if(argc == 1)
        {
		printf("ERROR: ./mp3_tag_reader.out: Invalid Arguments\n");
            	printf("USAGE: ./mp3_tag_reader.out: -h for help\n");
            	return 0;

        }
	//if -h is passed as one of the CLA
	//-h is for help displace various commands need to view or edit the mp3 file
        if (!strcmp(argv[1], "-h"))
        {
		printf("Help Menu for the MP3 TAG Reader and Editor\n\n");
            	printf("For viewing the tags-   ./mp3_tag_reader -v <.mp3 file name> \n\n");
            	printf("For editing the tags-   ./mp3_tag_reader -e <.mp3 file name>  <tag>  <Modified file name> \n\n");;
            	printf("\n\tModifier\tFunction\n");
           	printf("\t-t\t        Title Tag\n");
            	printf("\t-a\t        Artist Tag\n");
            	printf("\t-A\t        Album Tag\n");
            	printf("\t-y\t        Year Tag\n");
            	printf("\t-c\t        Comment Tag\n");
            	printf("\t-g\t        Genre Tag\n");
            	exit(EXIT_SUCCESS);
        }
	
   	//Opening the file and it is in read mode for viewing it and checking if it is opened
	mp3Info.fp = fopen(argv[2], "r");
	//Condition to check if file passed through CLA exists or not
      	if (!mp3Info.fp)
        {
		printf("Couldnt open file %s\n", argv[2]);
            	exit(EXIT_FAILURE);
        }
	
	//calling functions to get the desired data
	titleInfo(&mp3Info);
	artistInfo(&mp3Info);
	albumInfo(&mp3Info);
	yearInfo(&mp3Info);
	genreInfo(&mp3Info);
	commentInfo(&mp3Info);
	
	//-v for viewing the details of the audio file
    	if (!strcmp(argv[1], "-v"))
      	{
		//seek set to 0 inorder to get ID3 TAG
		fseek(mp3Info.fp, 0, SEEK_SET);
		fread(mp3Info.id3_tag, 3, 1, mp3Info.fp);
		//printf("%s\n", id3_tag);

	      	if (strncmp(mp3Info.id3_tag, "ID3", 3))
        	{
            		printf("File \"%s\" doesn't have an ID3 tag\n\n", argv[i]);
        	}
            	else
            	{					
			//Printing the obtained data
			printf("\nMP3 TAG Reader And Editor\n");
			printf("-------------------------\n\n");
			printf("Version ID\t:\t2.3\n");

			printf("Title\t\t:\t%-s\nArtist\t\t:\t%s\n", mp3Info.title_p, mp3Info.artist_p);
			printf("Album\t\t:\t%-s\nYear\t\t:\t%s\n", mp3Info.album_p, mp3Info.year_p);
			printf("Comment\t\t:\t%-30s\nGenre\t\t:\t%s\n\n", mp3Info.comment_p, mp3Info.genre_p);

			//close the file
			fclose(mp3Info.fp);
			return 0;
      		}
		/* end of viewing part */
		    
	}
	
	/* Code for the editing part */
	if (!strcmp(argv[1], "-e"))
	{
		//initialising char arrays
    		char title[100];
    		char *p;
    		char artist[100];
    		char album[100];
    		char year[100];
    		char comment[100];
    		char genre[100];
   		FILE *fp2 = fopen(argv[2], "r+");

      		if (!fp2)
        	{
            		printf("Couldn't open file %s\n", argv[2]);
            		exit(EXIT_FAILURE);
        	}
		
     		/* Read from 21th bytes of the file, if we can */
		if (fseek(fp2, 21, SEEK_SET))
        	{
            		printf("Couldn't jump/read in file %s\n", argv[2]);
            		exit(EXIT_FAILURE);
        	}
        	for (i = 1; i < argc; i++)
        	{
			//TITLE modification
            		if (!strcmp(argv[i], "-t"))
                  	{
				//4th argument contains the new file details
				//store the base address of that string in a char ptr
                    		p = (argv[4]);
                    		for(i = 0; i < strlen(p); i++)
                    		{
                         		title[i] = p[i];
                    		}
                    		title[i] = '\0';
                    		fwrite(title, mp3Info.size_title_p - 1, 1, fp2);
                    		printf("Title Modification done\n");
                    		return 0;
                    	}
			//ARTIST modification
            		if (!strcmp(argv[i], "-a"))
                	{
                    		fseek(fp2, 57, SEEK_CUR);
                    		p = (argv[4]);
                    		for(i = 0; i < strlen(p); i++)
                    		{
                         		artist[i] = p[i];
                    		}
                    		artist[i] = '\0';
                    		fwrite(artist, mp3Info.size_artist_p - 1, 1, fp2);
                    		printf("Artist Modification done\n");
                    		return 0;
                	}
			//ALBUMN modification
        		if (!strcmp(argv[i], "-A"))
                	{
                   		fseek(fp2, 100, SEEK_CUR);
                    		p = (argv[4]);
                    		for(i = 0; i < strlen(p); i++)
				{
                         		album[i] = p[i];
				}
                    		album[i] = '\0';
                    		fwrite(album, mp3Info.size_album_p - 1, 1, fp2);
                    		printf("Album Modification done\n");
                    		return 0;
                	}
			//YEAR modification
            		if (!strcmp(argv[i], "-y"))
                	{
                      		fseek(fp2, 119, SEEK_CUR);
                    		p = (argv[4]);
                    		for(i=0; i < strlen(p); i++)
                    		{
                         		year[i] = p[i];
                    		}
                    		year[i] = '\0';
                    		fwrite(year, mp3Info.size_year_p - 1, 1, fp2);
                    		printf("Year Modification done\n");
                    		return 0;
                	}
			//COMMENT modification
            		if (!strcmp(argv[i], "-c"))
                	{
                    		fseek(fp2, 179, SEEK_CUR);
                    		p = (argv[4]);
                    		for(i = 0 ;i < strlen(p); i++)
                    		{
                         		comment[i] = p[i];
                    		}
                    		comment[i] = '\0';
                    		fwrite(comment, mp3Info.size_comment_p - 5, 1, fp2);
                    		printf("Comment Modification done\n");
                    		return 0;
                	}
			//GENRE modification
            		if (!strcmp(argv[i], "-g"))
            		{
                    		fseek(fp2, 134,SEEK_CUR);
                    		p=(argv[4]);
                    		for(i=0; i<strlen(p); i++)
                    		{
                        		genre[i] = p[i];
                    		}
                    		genre[i] = '\0';
                    		fwrite(genre, mp3Info.size_genre_p - 1, 1, fp2);
                    		printf("Genre Modification done\n");
                    		return 0;
            		}

        	}
		//close the file
		fclose(fp2);
	}
	return 0;
}
void titleInfo(Mp3Info *mp3Info)
{
	//TITLE
	//seek from 14th byte
	fseek(mp3Info->fp, 14, SEEK_SET);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->title_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_title_p += mp3Info->title_p[i];
	}
	//skip 3 bytes which are flags
	fseek(mp3Info->fp, 3, SEEK_CUR);
	fread(mp3Info->title_p, mp3Info->size_title_p - 1, 1, mp3Info->fp);

}
void artistInfo(Mp3Info *mp3Info)
{
	//ARTIST
	//move 4 bytes from the current position
	//skiping the tag
	fseek(mp3Info->fp, 4, SEEK_CUR);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->artist_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_artist_p += mp3Info->artist_p[i];
	}
	//printf("%d\n", size);
	//moving 3 bytes from current position to skip the flags
	fseek(mp3Info->fp, 3, SEEK_CUR);
	fread(mp3Info->artist_p, mp3Info->size_artist_p - 1, 1, mp3Info->fp);

}
void albumInfo(Mp3Info *mp3Info)
{
	//ALBUM
	//move 4 bytes from the current position
	//skiping the tag
	fseek(mp3Info->fp, 4, SEEK_CUR);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->album_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_album_p += mp3Info->album_p[i];
	}
	//skip 3 bytes which are flags
	fseek(mp3Info->fp, 3, SEEK_CUR);
	fread(mp3Info->album_p, mp3Info->size_album_p - 1, 1, mp3Info->fp);

}
void yearInfo(Mp3Info *mp3Info)
{
	//YEAR
	//skiping the tag
	fseek(mp3Info->fp, 4, SEEK_CUR);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->year_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_year_p += mp3Info->year_p[i];
	}
	//skip 3 bytes which are flags
	fseek(mp3Info->fp, 3, SEEK_CUR);
	fread(mp3Info->year_p, mp3Info->size_year_p - 1, 1, mp3Info->fp);

}
void genreInfo(Mp3Info *mp3Info)
{
	//GENRE
	//skiping the tag
	fseek(mp3Info->fp, 4, SEEK_CUR);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->genre_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_genre_p += mp3Info->genre_p[i];
	}
	//skip 3 bytes which are flags
	fseek(mp3Info->fp, 3, SEEK_CUR);
	fread(mp3Info->genre_p, mp3Info->size_genre_p - 1, 1, mp3Info->fp);
	//printf("%s\n", genre_p);

}
void commentInfo(Mp3Info *mp3Info)
{
	//COMMENT
	//skiping the tag
	fseek(mp3Info->fp, 4, SEEK_CUR);
	//read the 4 bytes which contains size of the string
	fread(mp3Info->comment_p, 4, 1, mp3Info->fp);
	for (int i = 0; i < 4; i++)
	{
		mp3Info->size_comment_p += mp3Info->comment_p[i];
	}
	//printf("%d\n", size_comment_p);
	fseek(mp3Info->fp, 7, SEEK_CUR);
	fread(mp3Info->comment_p, mp3Info->size_comment_p - 5, 1, mp3Info->fp);
	//printf("%s\n", comment_p);
}