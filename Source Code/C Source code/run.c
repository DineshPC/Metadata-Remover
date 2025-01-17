
/* Metadata Removal Tool v3.5.0 for windows. Compile using gcc c complier mingw only*/
//[ THIS IS A STABLE RELEASE]

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

char  file[80],vfile[80],fil[50],vfil[50];

//Function For pausing program temporarily to display message.
void pause()
    {
      printf("\n");
      system(" pause");
      printf("\n");
    }

//Function to check if output file is generated when expected and throw errors when necessary.
void checker()
    {
        int check=0;
        char eff[80];
        memcpy(eff,"exiftool ",10);eff[9]='\0';
        strcat(eff,file);
        strcat(eff,">output.txt");

    check=system(eff);
    if(check!=0)
    {
        printf("\n\nOutput.txt couldnot be created!\nmaybe exiftool is missing or u don't have user permissions or\nSomething went wrong like you entering a non image file!");
        system("start https://exiftool.org");
        pause();
        exit(0);
    }
    }

//Function to check if output file is generated when expected and throw errors when necessary for videos.
void vchecker()
    {
        int check=0;
        char eff[200] , fvfile[50];
        strcpy(fvfile,"Videos\\final_");
        strcat(fvfile,vfil);
        memcpy(eff,"exiftool ",10);eff[9]='\0';
        strcat(eff,fvfile);
        strcat(eff,">video_output_metadata.txt");
    check=system(eff);
    if(check!=0)
    {
        printf("\n\nOutput.txt couldnot be created!\nmaybe exiftool is missing or u don't have user permissions or\nSomething went wrong like you entering a non image file!");
        system("start https://exiftool.org");
        pause();
        exit(0);
    }
    }

//Function to get input from user.
void input()
    {
      system("cls");
        printf("\n\t|---------Image Sanitisation Tool ---------|\n");
        printf("\n\n Enter Image name:");
        scanf("%30s",fil);
        memcpy(file,"Images\\",8);file[8]='\0';
        strcat(file,fil);
    }

bool endswith(const char str1[] , const char str2[] )
    {
        int i = 0;
        int j = 0;
        int str1_length = strlen(str1);
        int str2_length = strlen(str2);
        if(str1_length > str2_length)
        {
            for(i = str2_length-1,j=str1_length-1; i>=0;--j,--i)
                {
                if(tolower(str1[j])!= tolower(str2[i]))
                {
                    return false;
                }
                }
            return true;
        }
        return false;

    }

//Function to sanitize the image selected using exiftool.
void sanitize()
    {
      int check=0;
	  int file_length = 0;
	  int visit = 0;
      char eff[80];
	  char tmp[80];
	  file_length = strlen(file);

      if( endswith(file,"tiff") || endswith(file,"tif"))
		 {
			 memcpy(tmp,"exiftool -all= -CommonIFD0= ",28);tmp[28] = '\0';
			 strcat(tmp,file);
			 check=system(tmp);
			 visit = 1;
		 }

	  else if(visit == 0){
             memcpy(eff,"exiftool ",10);eff[9]='\0';
             strcat(eff,file);
             strcat(eff," -all=");
             check=system(eff);
	  }
    if(check!=0)
    {
        printf("\n\nImage Sanitization failed maybe exiftool is missing!\nor Something went wrong like you entering a non image file!");
        system("start https://exiftool.org");
        pause();
        exit(0);
    }

    }

//Function to generate and check generation of input log.
void ichecker()
    {
    int check=0;
    char eff[80];
    memcpy(eff,"exiftool ",10);eff[9]='\0';
    strcat(eff,file);
    strcat(eff,">input.txt");
    check=system(eff);
    if(check!=0)
    {
        printf("\n\nInput log couldnot be created \nmaybe exiftool is missing! or u don't have enough access permission!\n\nSomething went wrong like you entering a non image file!\n\n");
        system("start https://exiftool.org");
        pause();
        exit(0);
    }
    }


    //Function to generate and check generation of input log for videos.
void ivchecker()
    {
    int check=0;
    char eff[200];
    memcpy(eff,"exiftool ",10);eff[9]='\0';
    strcat(eff,vfile);
    strcat(eff,">video_input_metadata.txt");
    check=system(eff);
    if(check!=0)
    {
        printf("\n\nInput log couldnot be created \nmaybe exiftool is missing! or u don't have enough access permission!\n\nSomething went wrong like you entering a non image file!\n\n");
        system("start https://exiftool.org");
        pause();
        exit(0);
    }
    }

//Function to add support for * wildcards.
void detect()
    {
        FILE *f;
        char d;
        int flag=0,len=0,i=0;
        int file_length = strlen(file);
        for( i=0;i<file_length;i++)
        {
            if((file[i]=='.')&&(i>0))
            {
                if(file[i-1]=='*')
                {
                    if(((file_length-i)==4)||((file_length-i)==5))
                    {
                        flag=1;
                    }
                }
            }
        }
        if(flag==0){
        f=fopen(file,"r");
        if(f==NULL)
        {
            printf("\n\nERROR:FILE NOT FOUND!\n\n");
            pause();
            exit(0);
        }
        fclose(f);
    }}

//Function to check if image file was cleaned successfully by comparing size of input log and output log files generated by exiftool.
void compare()
    {
        FILE *a,*b;
        int w1=0,w2=0;
        a=fopen("input.txt","r");
        b=fopen("output.txt","r");
        if((a==NULL)||(b==NULL))
        {
            printf("\n\nEither input.txt or output.txt not found!\n");
            pause();
            exit(0);
        }
        fseek(a,0,SEEK_END);
        fseek(b,0,SEEK_END);
        w1=ftell(a);
        w2=ftell(b);
        if(w1==w2)
        {
            printf("\n\nNo Significant change!\n");
        }
        else if(w1>w2)
        {
            printf("\n\nMetadata Cleaned Successfully!\n");
        }
        else
        {
            printf("\n\nCleaning done with errors!\n");
        }
fclose(a);fclose(b);
    }

void run() // combine all functions .
    {
        input();
        detect();
        ichecker();
        sanitize();
        checker();
        compare();
        pause();
    }

void vinput()
{
    /* Gets input ( filename ) for removal  of metadata from videos*/
    system("cls");
    printf("\n\t |----- Video sanitisation tool -----|\n");
    printf("\n\n Enter Video name:");
    scanf("%30s",vfil);
        memcpy(vfile,"Videos\\",8);vfile[8]='\0';
        strcat(vfile,vfil);
}

void vdetect()
    {
        /* Detects if video file is present or not.*/
        FILE *f;
        f=fopen(vfile,"r");
        if(f==NULL)
        {
            printf("\n\nERROR:FILE NOT FOUND!");
            fclose(f);
            pause();
            exit(1);
        }
        fclose(f);
    }

void vtool()
{
    /*Detects ffmpeg in default installation of this software.*/
    FILE *f;
    f=fopen("ffmpeg.exe","r");
    if(f==NULL)
    {
        printf("\n\n Critical Error: FFMPEG.EXE NOT FOUND!");
        printf("\n\n<------ Video Sanitization Failed! ----->\n");
        printf("\n\n");
        system("timeout 10");
        system("cls");
        fclose(f);
        exit(1);
    }
    fclose(f);

}

void vsanitise()
{
    /* Actual metadata removal process happens here.*/
    int status=0;
    char buffer[1000];char fvfile[50];
    strcpy(fvfile,"Videos\\final_");
    strcat(fvfile,vfil);
    memcpy(buffer,"ffmpeg -i ",11);buffer[10]='\0';
    strcat(buffer,vfile);
    strcat(buffer," -map_metadata -1 -c:v copy -c:a copy ");
    strcat(buffer,fvfile);
    status=system(buffer);
    if(status!=0)
    {
        printf("\n\n :(  <---Video Sanitization Failed!--->");
    }

}

void qrun()
{
    /* Responsible for combining all video management functions.*/
    vtool();
    vinput();
    vdetect();
    ivchecker();
    vsanitise();
    vchecker();
    pause();
}

void menu()
{
    int raw=0,backdoor=0;
    printf("\n\t|----- Menu -----|\n\n");
    printf("\n 1)Sanitize images using exiftool\n");
    printf(" 2)Sanitize video files using ffmpeg\n");
    while(1)
    {
     printf("\n Enter Your choice( 1 or 2):");
     backdoor=scanf("%d",&raw);
     if(backdoor==1)
        break;
    }
    if (raw==1)
    {
        run();
    }
    else if(raw==2)
    {
        qrun();
        pause();
    }
    else
    {
        pause();
        exit(0);
    }
}

void main()
    {
        system("title Metadata Removal Tool v3.5.0");
        menu();
    }

