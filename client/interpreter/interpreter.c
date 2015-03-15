#include <stdio.h>
#include <err.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "interp.h"
void rmStr(const char *str1,const char *str2)
{
        while (( str1 = strstr(str1,str2)))
        {
                memmove(str1, str1 + strlen(str2),1 + strlen(str1 + strlen(str2)));
        }
}
char *bChar(char *str1,char rmChar)
{
        for (int i = 0;i < strlen(str1) - 1;i++)
        {
                if(str1[i] == rmChar)
                {
                        int l = strlen(str1) - i;
                       	char *nchar = (char*)malloc(l);
			strcpy(nchar,str1 + i + 1);
			return nchar;
                }
        }
}
char *aChar(char *str1, char rmChar)
{
	int cancpy = 1;
	char *buff = malloc(80);
	for (int i = 0; i < strlen(str1) - 1;i++)
	{

		if(str1[i - 1] == rmChar)
		{
			cancpy = 0;
		}
		if (cancpy == 1)
		{
			strcpy(buff,&str1[i]);
		}
		
	}
	char *dup = malloc(1024);
	strcpy(dup,str1);
	rmStr(dup,buff);
	return dup;
}
static void ufunc(GtkWidget *w,gpointer p,char *line)
{
        char *func = bChar(line,',');
        system(func);
}
static gboolean delete_event(GtkWidget *w,GdkEvent *e,gpointer p)
{
        return FALSE;
}
static void destroy(GtkWidget *w, gpointer p)
{
        gtk_main_quit();
}
int interpret(char *line)
{
	if(strncmp(line,"button ",6) == 0)
	{
		return BUTTON;
	}
	else if(strncmp(line,"win",3) ==0)
	{
		return WIN;
	}
	else if (strncmp(line,"rbutton",7) == 0)
	{
		return RBUTTON;
	}
	else if(strncmp(line,"label",5) == 0)
	{
		return LABEL;
	}
	else
	{
		printf("Failed to interpret code!\n");
	}
}

char *button(char *name,int x, int y)
{
        char *a = malloc (1025);
        char *b = malloc(3);
        char *c = malloc(3);
        sprintf(b,"%d",x);
        sprintf(c,"%d",y);
        strcpy(a,name);
        strcat(a,",");
        strcat(a,b);
        strcat(a,",");
        strcat(a,c);
        strcat(a,";");
        return a;
}

int main(int a, char *b[])
{
        char *binfo = malloc(1024);
	if (a < 2)
	{
		printf("Syntax: ./{INTP_EXEC} PATH_TO_FILE\n");
		return -1;
	}
	else
	{
		FILE *f = fopen(b[1],"r");
		ssize_t r;
		size_t len = 0;
		char line[1024];
		if(f == NULL)
		{
			printf("Error 1: No such file!\n");
			return -1;
			exit(EXIT_FAILURE);
		}
		int b_win_init = 0;
		int buttons = 0;
		while (fgets(line,sizeof(line),f))
		{
			//sscanf(line,"%ld");
			//printf("%s",line);
			int a = interpret(line);
			if(a == WIN)
			{
				b_win_init += 1;
			}
			else if (a == BUTTON)
			{
				buttons+=1;
				char *one = aChar(line,',');
				char *linedup = malloc(80);
				strcpy(linedup,line);
				char *onedup = malloc(80);
				strcpy(onedup,one);
				strcat(onedup,",");
				rmStr(linedup,onedup);
				char *name = aChar(linedup,',');
				strcpy(binfo,name);
				char *x1 = bChar(line,',');
				char *x2 = bChar(x1,',');
				char *xc = aChar(x2,',');
				char *y1 = bChar(line,',');
				char *y2 = bChar(y1,',');
				char *yc = bChar(y2,',');
				int x = atoi(xc);
				int y = atoi(yc);
				strcpy(binfo,button(name,x,y));
				//strcat(binfo,button(name,x,y));
				//printf("%s\n",button(name,x,y));
			}
		}
		fclose(f);
		GtkWidget *win;
		GtkWidget *eventbox;
		GtkWidget *button1;
		GtkWidget *button2;
		GtkWidget *button3;
		GtkWidget *button4;
		GtkWidget *fixed;
		GtkWidget *box;
		gtk_init(&a,&b);
		fixed = gtk_fixed_new();
		eventbox = gtk_event_box_new();
		//gtk_container_add(GTK_CONTAINER(win),eventbox);
		if(b_win_init >= 1)
		{
			win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			//gtk_container_add(GTK_CONTAINER(win),eventbox);
			box = gtk_hbox_new(FALSE,0);
				char *name = aChar(binfo,',');
				int x;
				int y;
				char *x1 = bChar(binfo,',');
				char *x2 = aChar(x1,',');
				x = atoi(x2);
			//	printf("%d\n",x);
				char *y1 = bChar(binfo,',');
				char *y2 = bChar(y1,',');
				//char *y3 = bChar(binfo,',');
				rmStr(y2,";");
				y = atoi(y2);
				gtk_container_add(GTK_CONTAINER(win),box);
			//	printf("%d\n",y);
				for (int i = 0; i < buttons;i++)
				  {
				    button1 = gtk_button_new_with_label(name);
				   
					gtk_box_pack_start(GTK_BOX(box),button1,TRUE,TRUE,0);
					gtk_widget_show(button1);
				  }
				//gtk_widget_set_usize(button1,x,y);
			//	gtk_container_add(GTK_WINDOW(eventbox),button1);
				//gtk_container_add(GTK_WINDOW(win),box1);
				//gtk_fixed_put(GTK_FIXED(fixed),button1,0,0);
				//gtk_widget_set_size_request(button1,x,y);
				if(strcmp(b[2],"--debug") == 0)
				  {
				    printf("%s\n",binfo);
				  }
				gtk_widget_show(win);
				gtk_widget_show(box);
				gtk_widget_show(button1);
				gtk_main();
		       
		}
		else
		{
			printf("Window not initialised\n");
		}
	}
}
