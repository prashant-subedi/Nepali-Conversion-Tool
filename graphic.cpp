#include<gtk/gtk.h>
#include<iostream>
#include"FiletoFile.h"
#include"unicode2preeti.h"
#include "preeti2unicode.h"
#include<string.h>
using namespace std;
GtkTextBuffer *buffer1,*buffer2;
GtkWidget *picker,*picker1;
static gboolean activate(GtkWidget*refresh,GdkEvent*event,gpointer data) // for clearing the text buffer
{
 GtkTextIter iter,start,end;
	if (buffer1 != NULL)
	{
		gtk_text_buffer_get_start_iter (buffer1,&start);
        gtk_text_buffer_get_end_iter (buffer1,&end);
        gtk_text_buffer_delete (buffer1,&start,&end);
	}
	if (buffer2 != NULL)
	{
        gtk_text_buffer_get_start_iter (buffer2,&start);
        gtk_text_buffer_get_end_iter (buffer2,&end);
        gtk_text_buffer_delete (buffer2,&start,&end);
	}

}
static gboolean activate1(GtkWidget*help,GdkEvent*event,gpointer data) //another callback for help

{

	GtkWidget *window,*label;
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_default_size(GTK_WINDOW(window),400,400);
		label=gtk_label_new("we will write when we finish it");


		gtk_container_add(GTK_CONTAINER(window),label);

		gtk_widget_show_all(window);

}

static gboolean activate2(GtkWidget*about,GdkEvent*event,gpointer data)  //another one for about
{

	GtkWidget *window,*label;
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_default_size(GTK_WINDOW(window),400,400);

		label=gtk_label_new("we are about");


		gtk_container_add(GTK_CONTAINER(window),label);

		gtk_widget_show_all(window);

}

static gboolean activate3(GtkWidget*homepage,GdkEvent*event,gpointer data)  //another one for homepage
{
    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,999,580);
	gtk_window_set_title(GTK_WINDOW(window),"Unicode Layout");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    image = gtk_image_new_from_file("image.png");
    gtk_layout_put(GTK_LAYOUT(layout), image,0,0);

    gtk_widget_show_all(window);

}
static gboolean clicked8(GtkWidget*button4,GdkEvent*event,gpointer data)  //another one for Preeti to uni
{
	char *raw_filename;
	raw_filename=gtk_file_chooser_get_uri((GtkFileChooser*)picker1);
	if (raw_filename==NULL)//To avoid segmentation fault
	{
			GtkWidget *window,*label;
            window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_widget_set_size_request(window,300,200);
			gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
            gtk_window_set_title(GTK_WINDOW(window),"ERROR!!!");
            label=gtk_label_new("Please Select A DOCX File First!");
            gtk_container_add(GTK_CONTAINER(window),label);
            gtk_widget_show_all(window);
	}
	else
	{	char *string_slicer;
		string_slicer=(raw_filename+7);
		std::string temp=string_slicer;
		std::string filename="";
		std::string check_string;
		std::cout<<temp;
		for(int i=0;i<(temp.length());i++)
		{
			if(i<(temp.length()-2))
			{
				check_string+=temp[i];
				check_string+=temp[i+1];
				check_string+=temp[i+2];
			}
			if(check_string=="%20")
			{
				filename+=" ";
				i+=2;
			}
			else
			{
				filename+=temp[i];
			}
			check_string="";
		}
		convert_File_Unicode(filename);
	}
}
static gboolean clicked9(GtkWidget *button4,GdkEvent*event,gpointer data)  //another one for uni to Preeti
{

GtkWidget *window,*label;
window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window),400,400);

label=gtk_label_new("convert Preeti to Unicode");


gtk_container_add(GTK_CONTAINER(window),label);

gtk_widget_show_all(window);

}
static gboolean clicked7(GtkWidget*button5,GdkEvent*event,gpointer data)  //another one for output folder
{

GtkWidget *window,*label;
window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window),400,400);

label=gtk_label_new("output folder");


gtk_container_add(GTK_CONTAINER(window),label);

gtk_widget_show_all(window);

}





static gboolean activate4(GtkWidget*skin,GdkEvent*event,gpointer data)  //another one ???
{

GtkWidget *window,*label;
window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window),400,400);

label=gtk_label_new("to change the color");


gtk_container_add(GTK_CONTAINER(window),label);

gtk_widget_show_all(window);

}

static gboolean clicked(GtkWidget*button7,GdkEvent*event,gpointer data)  //  converting unicode to Preeti direct
{
GtkWidget *window,*label;
GtkTextIter iter,start,end;

if (buffer2 != NULL)
	{
        gtk_text_buffer_get_start_iter (buffer2,&start);
        gtk_text_buffer_get_end_iter (buffer2,&end);
        gtk_text_buffer_delete (buffer2,&start,&end);
	}
gtk_text_buffer_get_start_iter(buffer1,&start);
gtk_text_buffer_get_end_iter(buffer1,&end);
char *text;
text=gtk_text_buffer_get_text(buffer1,&start,&end,FALSE);
//If you get a problem in this part...consult Code-er
char *result;
std::string converted;
converted=unicode_Converter_Direct(text);
result=new char[converted.length()+1];
int i;
for(i=0;i<converted.length();i++)
{
	result[i]=converted[i];
}
result[i]='\0';
/**
  *The above lines are to convert the string(object) into null terminating string(array of char)
  */
text=result;
//upto here...Now its Graphic' fault
gtk_text_buffer_get_iter_at_offset(buffer2, &iter,10);
gtk_text_buffer_insert(buffer2,&iter,text,-1);
//Again..Prashant
	delete[] result;
//And here is where it ends.

}

static gboolean clicked1(GtkWidget*button8,GdkEvent*event,gpointer data) // for PREETI to unicode direct
{
GtkWidget *window,*label;
GtkTextIter iter,start,end;

if (buffer1 != NULL)
	{
        gtk_text_buffer_get_start_iter (buffer1,&start);
        gtk_text_buffer_get_end_iter (buffer1,&end);
        gtk_text_buffer_delete (buffer1,&start,&end);
	}
gtk_text_buffer_get_start_iter(buffer2,&start);
gtk_text_buffer_get_end_iter(buffer2,&end);
char *text;
text=gtk_text_buffer_get_text(buffer2,&start,&end,FALSE);

//If you get a problem in this part...consult Code-er
char *result;
std::string converted;
converted=preeti_Converter(text);
result=new char[converted.length()+1];
int i;
for(i=0;i<converted.length();i++)
{
	result[i]=converted[i];
}
result[i]='\0';

  //The above lines are to convert the string(object) into null terminating string(array of char)

text=result;
//upto here...Now its Graphic' fault
gtk_text_buffer_get_iter_at_offset(buffer1, &iter,10);
gtk_text_buffer_insert(buffer1,&iter,text,-1);
//Again..Coding
	delete[] result;
//And here is where it ends.

}



int main(int argc,char *argv[])
{
        gtk_init(&argc,&argv); //initializing the two arguments
        GtkWidget *window;
        GtkWidget *menubar,*homemenu,*home,*refresh,*exit;
        GtkWidget *skin,*settingmenu,*color;
        GtkWidget *helpmenu,*help,*help1,*about,*homepage;
        GtkWidget *box,*button1,*label,*label1,*label2,*label5;
        GtkWidget *box1,*button2,*scroll,*scroll1;
        GtkWidget *box2,*label3,*button3,*button4;
        GtkWidget *box3,*label4,*button5,*label6,*button7,*label7,*box4,*label11;
        GtkWidget *box5,*button6,*label8,*box6,*box7,*label12,*button8;
        GtkWidget *label9,*label10,*view,*view1;
        PangoFontDescription *font_desc;



      /*
      //creating gtk objects
      GtkWidget *window;
      GtkWidget *menubar,*homemenu,*home,*refresh,*exit;    //for home menu
      GtkWidget *skinmenu,*skin;							//for skin menu
      GtkWidget *helpmenu,*help,*help1,*about,*homepage;	//for help menu
      GtkWidget *box,*box1,*box2,*box3,*box4,*box5,*box6;	//for boxes
      GtkWidget *label,*label1,*label2,*label3,*label4,*label5,*label6,*label7,*label8,*label9,*label10,*label11;	//for labels
      GtkWidget *button,*button1,*button2,*button3,*button4,*button5,*button6,*button7;	//for buttons
      GtkWidget *picker,*picker1;	//for file chooser dialouge
      GtkWidget *view,*view1;		//creating text area
      PangoFontDescription *font_desc;	//for changing the font of text area

      */













        GtkTextIter iter,start,end;

        //creating window
        window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window),800,550);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window),20);
        gtk_window_set_title(GTK_WINDOW(window),"Nepali Conversion Tool");
        g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

	//creating menusbar for home

	menubar=gtk_menu_bar_new();
	homemenu=gtk_menu_new();
	home=gtk_menu_item_new_with_label("Home");
	refresh=gtk_menu_item_new_with_label("Refresh");
	exit=gtk_menu_item_new_with_label("Exit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(home),homemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(homemenu),refresh);
	gtk_menu_shell_append(GTK_MENU_SHELL(homemenu),exit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),home);

	//setting menu

	settingmenu=gtk_menu_new();
	skin=gtk_menu_item_new_with_label("preferences");
	color=gtk_menu_item_new_with_label("color");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(skin),settingmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingmenu),color);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),skin);


	//creating menusbar for help

	helpmenu=gtk_menu_new();
	help=gtk_menu_item_new_with_label("Help");
	help1=gtk_menu_item_new_with_label("help");
	about=gtk_menu_item_new_with_label("About");
	homepage=gtk_menu_item_new_with_label("Homepage");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help),helpmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu),help1);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu),about);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu),homepage);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),help);


	box=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);        //creating vertical box

	label=gtk_label_new("WELCOME!!!   Nepali Conversion Tool\n\n");
	gtk_widget_set_size_request(label,30,10);
	gtk_misc_set_alignment (GTK_MISC (label),0.5, 1);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);

	label1=gtk_label_new("File Convert\n");
	gtk_widget_set_size_request(label,30,10);
	gtk_misc_set_alignment (GTK_MISC (label1),-1, 1);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box),label1,FALSE,FALSE,0);

	//box1 and box2 for the file convert

	box1=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,30);
	gtk_container_add(GTK_CONTAINER(box),box1);

	label2=gtk_label_new("1.Unicode to Preeti\t\t");
	gtk_misc_set_alignment (GTK_MISC (label2),0.01, 0.001);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box1),label2,FALSE,FALSE,0);


	label9=gtk_label_new("choose unicode file:");
	gtk_box_pack_start(GTK_BOX(box1),label9,FALSE,FALSE,0);


	button1=gtk_label_new("Choose Unicode File\t\t");
        picker1 = gtk_file_chooser_button_new ("Pick a File",GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_container_add(GTK_CONTAINER(picker1),button1);
	gtk_box_pack_start(GTK_BOX(box1),picker1,30,30,0);


	button2=gtk_button_new_with_label("\tconvert\t");
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(clicked8),NULL);	//for the preeti to unicode
	gtk_box_pack_start(GTK_BOX(box1),button2,0,0,2);

	//box2
	box2=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,30);
	gtk_container_add(GTK_CONTAINER(box),box2);

	label3=gtk_label_new("2.Preeti to Unicode\t\t  ");
	gtk_misc_set_alignment (GTK_MISC (label3),0.01, 0.001);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box2),label3,FALSE,FALSE,0);

	label10=gtk_label_new(" Choose Preeti file:");
	gtk_box_pack_start(GTK_BOX(box2),label10,FALSE,FALSE,0);

	button3=gtk_button_new_with_label("Choose Preeti File\t\t");
	picker = gtk_file_chooser_button_new ("Pick a File",GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_container_add(GTK_CONTAINER(picker),button3);
	gtk_box_pack_start(GTK_BOX(box2),picker,30,30,0);

	button4=gtk_button_new_with_label("\tconvert\t");
	g_signal_connect(G_OBJECT(button4),"clicked",G_CALLBACK(clicked9),NULL);	//for the preeti to unicode
	gtk_box_pack_start(GTK_BOX(box2),button4,0,0,2);

	//box3
	box3=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,100);
	gtk_container_add(GTK_CONTAINER(box),box3);

	label4=gtk_label_new("     \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          ");
	gtk_misc_set_alignment (GTK_MISC (label4),0.01, 0.001);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box3),label4,FALSE,FALSE,0);

	button5=gtk_button_new_with_label("\tOutput Folder\t");	////for output folder
	g_signal_connect(G_OBJECT(button5),"clicked",G_CALLBACK(clicked7),NULL);
	gtk_box_pack_start(GTK_BOX(box3),button5,0,0,2);

	label5=gtk_label_new("Text Convert\n\n");
	gtk_misc_set_alignment (GTK_MISC (label5),-1,1);   //for making an allignment
	gtk_widget_set_size_request(label5,30,10);
	gtk_box_pack_start(GTK_BOX(box),label5,FALSE,FALSE,0);

	//box4
	box4=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,400);
	gtk_container_add(GTK_CONTAINER(box),box4);

	label6=gtk_label_new("\t\t\t\t\t\tUNICODE");
	gtk_misc_set_alignment (GTK_MISC (label6),FALSE,1);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box4),label6,FALSE,FALSE,0);

	label7=gtk_label_new("PREETI\t\t");
	gtk_misc_set_alignment (GTK_MISC (label7),FALSE,1);   //for making an allignment
	gtk_box_pack_start(GTK_BOX(box4),label7,TRUE,FALSE,40);

	//box5
	box5=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,150);
	gtk_container_add(GTK_CONTAINER(box),box5);

	scroll=gtk_scrolled_window_new(0,0);
	gtk_widget_set_size_request(scroll,100,300);
	view=gtk_text_view_new();

	gtk_container_set_border_width(GTK_CONTAINER(view),5);


	buffer1=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

	gtk_text_buffer_create_tag(buffer1,"gap","pixels_above_lines",30,NULL);
	gtk_text_buffer_create_tag(buffer1,"lmarg","left_margin",5,NULL);

	gtk_text_buffer_get_iter_at_offset(buffer1, &iter,10);
	gtk_text_buffer_insert(buffer1,&iter,"type here in unicode",-1);




	gtk_container_add(GTK_CONTAINER(scroll),view);
	gtk_box_pack_start(GTK_BOX(box5),scroll,TRUE,TRUE,10);


	scroll1=gtk_scrolled_window_new(0,0);
	gtk_widget_set_size_request(scroll1,100,300);
	view1=gtk_text_view_new();


	gtk_container_set_border_width(GTK_CONTAINER(view1),5);


	buffer2=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1));

	font_desc = pango_font_description_from_string ("Preeti 15");

	gtk_widget_override_font (view1, font_desc);

	pango_font_description_free (font_desc);






	gtk_text_buffer_create_tag(buffer2,"gap","pixels_above_lines",30,NULL);
	gtk_text_buffer_create_tag(buffer2,"lmarg","left_margin",5,NULL);
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter,10);

	gtk_text_buffer_insert(buffer2,&iter,"ofxf n]V‍g'xf]; ",-1);
	gtk_container_add(GTK_CONTAINER(scroll1),view1);
	gtk_box_pack_start(GTK_BOX(box5),scroll1,TRUE,TRUE,10);


	//box6
	box6=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	gtk_container_add(GTK_CONTAINER(box),box6);

	label11=gtk_label_new(" \t\t\t\t         ");

	gtk_box_pack_start(GTK_BOX(box6),label11,FALSE,FALSE,0);




	button7=gtk_button_new_with_label("\t\t\tconvert from unicode to preeti\t\t\t");
	gtk_box_pack_start(GTK_BOX(box6),button7,FALSE,FALSE,300);
	g_signal_connect(G_OBJECT(button7),"clicked",G_CALLBACK(clicked),NULL);

	button6=gtk_button_new_with_label("\t\tclose\t\t");
	gtk_box_pack_start(GTK_BOX(box6),button6,0,0,0);
	//box7
	box7=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	gtk_container_add(GTK_CONTAINER(box),box7);

	label12=gtk_label_new(" \t\t\t\t         ");

	gtk_box_pack_start(GTK_BOX(box7),label12,FALSE,FALSE,0);
	button8=gtk_button_new_with_label("\t\t\tconvert from preeti to unicode\t\t\t");
	gtk_box_pack_start(GTK_BOX(box7),button8,FALSE,FALSE,300);
	g_signal_connect(G_OBJECT(button8),"clicked",G_CALLBACK(clicked1),NULL);







	g_signal_connect(button6,"clicked",G_CALLBACK(gtk_main_quit),window);






	gtk_box_pack_start(GTK_BOX(box),menubar,FALSE,FALSE,20);
	g_signal_connect(G_OBJECT(color),"activate",G_CALLBACK(activate4),NULL);
	g_signal_connect(G_OBJECT(exit),"activate",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(G_OBJECT(refresh),"activate",G_CALLBACK(activate),NULL);
	g_signal_connect(G_OBJECT(help1),"activate",G_CALLBACK(activate1),NULL);
	g_signal_connect(G_OBJECT(about),"activate",G_CALLBACK(activate2),NULL);
	g_signal_connect(G_OBJECT(homepage),"activate",G_CALLBACK(activate3),NULL);


	gtk_container_add(GTK_CONTAINER(window),box);
	//making all widgets visible
	gtk_widget_show_all(window);
	gtk_main(); //running main loop
	return 0;
        }
