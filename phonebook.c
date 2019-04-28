#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
 struct phonebook
 {
     char name[100];
     char email[100];
     char ph_no[11];
 };
 int add_contact(struct phonebook *abc,char * name,char * email,char * phone);
 int edit(struct phonebook *abc, char * new_name,char * new_email,char * new_phone);
 int del(int index,int index_serached,struct phonebook abc[]);
 int search(char * name,struct phonebook abc[]);
 int find_empty_index(struct phonebook abc[]);
 int print_contacts(struct phonebook abc[]);
 int save_contact_to_file(struct phonebook abc[],int find_empty_index);
 int read_from_file(struct phonebook p[]);

 int main()
{
    int user_choice,k;
    char name[100],name2[100],email[100],new_name[100],new_email[100],phone[11],new_phone[11];
    struct phonebook p[100];
    int search_index,index_searched, for_index = 0, last_index =0;
    system("cls");

    char s[100]="Welcome to Phonebook management system. . . ";
    printf("                                    ");
    for(int z=0;z<44;z++)
    {
        printf("%c",s[z]);
        Sleep(40);

    }
    Sleep(500);
    for(int z=0;z<44;z++)
    {printf("\b\b");Sleep(40);printf(" ");}
    system("cls");
    for(k=0;k<10;k++)
    {
     p[k].name[0]=0;
     p[k].email[0]=0;
     p[k].ph_no[0]=0;
    }
    FILE *f1;
    f1=fopen("user.abc","r");
    if(f1==NULL)
    {
        char pass[100],pass1[100];
        printf("You are a new New User\nPlease create a new password\n");
        do{
                printf("Enter new password : ");
        gets(pass);
        system("cls");
        printf("Confirm new password : ");
        gets(pass1);
        if(strcmp(pass,pass1)!=0)
            printf("Password mismatch\n");
        }while(strcmp(pass,pass1)!=0);
        if(strcmp(pass,pass1)==0)
        {
            fclose(f1);
            f1=fopen("user.abc","w+");
            fputs(pass,f1);
        }
        fclose(f1);

    }
    else
    {
        printf("You are a existing user\n");
        char pass[100],pass1[100];
        int t=0;
        fgets(pass,100,f1);
        do{
        printf("Enter password : ");
        gets(pass1);
        system("cls");t++;
        if(strcmp(pass,pass1)!=0)
        {
            printf("Authention error!!\n");
            if(t<3)
                printf("\nTry again!!\n\n");
            else
            {printf("\nTerminating program\n\n");return 0;}
        }
        }while(strcmp(pass,pass1)!=0);
    }
    system("cls");
    read_from_file(p);
    while(1)
    {
	printf("Enter anyone of the following options \n 1:Add a contact\n 2:Edit a contact\n 3:Delete a contact\n 4:Print Contacts\n 5.Search\n 6.Exit\n");

	char ch,q[100];
	int check,in;
	user_choice=getch()-48;
	system("cls");
	switch(user_choice)
	{
	    case 1:printf("Enter the name \n");
		   gets(name);
		   do{
		   printf("Enter the email \n");
		   gets(email);
		   check=checke(email);
		   if(check==0)
            printf("\n!!!Invalid Email!!!\n\n");
		   }while(check==0);
		   do{printf("Enter the phone number \n");
		   gets(phone);
		   check=checkph(phone);
		   if(check==0)
            printf("\n!!!Invalid Phone Number!!!\n\n");
		   }while(check==0);
		   index_searched=find_empty_index(p);
		   printf("\nAdding contact to index : %d\n",index_searched);
		   add_contact(&p[index_searched],name,email,phone);
		   save_contact_to_file(p,index_searched);
		       break;
	    case 2:printf("Enter the contact to be edited \n");
		       gets(name);
		       index_searched=find_empty_index(p);
		       search_index = search(name,p);
		       if(search_index>=0){
		       printf("contact found at: %d \n",search_index);
		       printf("\nWhat would you like to edit in this contact :\n  1.Name\n  2.Email\n  3.Phone number\n  4.All information\n\n");
		       in=getch()-48;
		       switch(in){
		           case 4 :
		       printf("Enter the new name \n");
		       gets(new_name);
		       do{printf("Enter the new email \n");
		       gets(new_email);check=checke(new_email);
		   if(check==0)
            printf("\n!!!Invalid Email!!!\n\n");
		   }while(check==0);
		       do{printf("Enter the new phone \n");
		       gets(new_phone);
		          check=checkph(new_phone);
		   if(check==0)
            printf("\n!!!Invalid Phone Number!!!\n\n");
		   }while(check==0);
		       edit(&p[search_index],new_name,new_email,new_phone);
		       save_contact_to_file(p,index_searched);
		       printf("\nContact Updated\n\n");
		       break;
                   case 1:
                    printf("Enter the new name \n");
		       gets(new_name);
		       edit(&p[search_index],new_name,p[search_index].email,p[search_index].ph_no);
		       save_contact_to_file(p,index_searched);
		       printf("\nName Updated\n\n");
		       break;
                   case 2:
                    do{printf("Enter the new email \n");
		       gets(new_email);check=checke(new_email);
		   if(check==0)
            printf("\n!!!Invalid Email!!!\n\n");
		   }while(check==0);
		   edit(&p[search_index],p[search_index].name,new_email,p[search_index].ph_no);
		       save_contact_to_file(p,index_searched);
		       printf("\nEmail Updated\n\n");
		       break;
                   case 3:
                    do{printf("Enter the new phone \n");
		       gets(new_phone);
		          check=checkph(new_phone);
		   if(check==0)
            printf("\n!!!Invalid Phone Number!!!\n\n");
		   }while(check==0);
		   edit(&p[search_index],p[search_index].name,p[search_index].email,new_phone);
		       save_contact_to_file(p,index_searched);
		       printf("\nPhone Number Updated\n\n");
		       break;
		       default : printf("\n!!!Invalid Option!!!\n\n");
		       break;
		       }}
		       break;
	    case 3:printf("Enter the contact to be deleted \n");
		       gets(name2);
		       search_index = search(name2,p);
		       if(search_index>=0){
		       index_searched=find_empty_index(p);
		       del(search_index,index_searched,p);
		       index_searched=find_empty_index(p);
		       save_contact_to_file(p,index_searched);
		       printf("\n!!!Contact Deleted!!!\n\n");
		       }
		       break;
	    case 6:
		       break;
		case 4:
			 last_index = find_empty_index(p);

		      for(for_index = 0; for_index < last_index ; for_index++)
		      {
			printf("Contact %d : \n", for_index);
			printf ("Name : %s\n", p[for_index].name);
			printf ("Email : %s\n", p[for_index].email);
			printf ("Phone Number : %s\n", p[for_index].ph_no);
		      }

		      break;
        case 5 :

            printf("Enter the starting characters of contact name or email id : ");
            gets(q);
            find(q,p);
            break;
	    default: printf("Enter any valid option\n");
		    break;

	}
	if(user_choice==6)
	 break;
	 printf("Press any key to continue.......");
	 getch();
    system("cls");
    }
    fflush(stdin);
    return 0;

}

int add_contact (struct phonebook *contact,char * name,char * email,char * phone)
{
    strcpy(contact->name, name);
    strcpy(contact->email, email);
    strcpy(contact->ph_no, phone);

    return 1;
}

 int edit (struct phonebook *contact, char * new_name,char * new_email,char * new_phone)
 {
     strcpy(contact->name,new_name);
     strcpy(contact->email,new_email);
     strcpy(contact->ph_no, new_phone);
     return 1;
 }

 int del (int index,int index_searched,struct phonebook p[])
{
    int l;
    for(l=index;l<index_searched;l++)
    {
    strcpy(p[l].name,p[l+1].name);
    strcpy(p[l].email,p[l+1].email);
    strcpy(p[l].ph_no,p[l+1].ph_no);
    }
    return 1;
}

 int search (char * name,struct phonebook p[])
 {
   int search,f=0;
   for(search=0;search<100;search++)
   {
    if(strcmp(p[search].name,name)==0)
    {
     f=1;
     break;
    }
   }
    if(f==0)
    {
    printf("Entered name not found\n");
    return -1;
     }
    return search;
}
int find_empty_index(struct phonebook p[])
{
    int i=-1;
    for(i=0;i<100;i++)
    {
	if(p[i].name[0]== 0)
	{
	 return i;
	}
    }

    return -1;
}
void find(char ch[],struct phonebook p[])
{
    system("cls");
    int i,len=find_empty_index(p),f=0;
    printf("Found contacts whose name starts with %s are :\n\n",ch);
    for(i=0;i<len;i++)
    {
        if(match(ch,p[i].name))
        {
            printf("Contact %d : \n", i);
			printf ("Name : %s\n", p[i].name);
			printf ("Email : %s\n", p[i].email);
			printf ("Phone Number : %s\n\n", p[i].ph_no);
			f=1;
        }
    }
    if(f==0)
        printf("No contacts found\n");
    f=0;
    printf("\n\n\nFound contacts whose email starts with %s are :\n\n",ch);
    for(i=0;i<len;i++)
    {
        if(match(ch,p[i].email))
        {
            printf("Contact %d : \n", i);
			printf ("Name : %s\n", p[i].name);
			printf ("Email : %s\n", p[i].email);
			printf ("Phone Number : %s\n\n", p[i].ph_no);
			f=1;
        }
    }
    if(f==0)
        printf("No contacts found\n");
}
int save_contact_to_file(struct phonebook p[],int find_empty_index)
{
 FILE *contacts;
 int a;
 char phone[11],concat[100];
 concat[0] = 0;
 contacts=fopen("phone.txt","w+");
 for(a=0;a<=find_empty_index;a++)
 {

   strcat(concat,p[a].name);
   strcat(concat,"\n");
   strcat(concat,p[a].email);
   strcat(concat,"\n");
   strcat(concat,p[a].ph_no);
   strcat(concat,"\n");
  // concat = strcat(p[a].name,",",p[a].email,",",phone,"\n");

   fputs(concat,contacts);
   concat[0]=0;
  }
  fclose(contacts);
  return -1;
 }
 int read_from_file(struct phonebook p[])
 {
  FILE *f1;
  char *output,*token,line[100];
  int j=-1,phno;
    const char s[2]=",";
    f1=fopen("phone.txt","r");
    if(f1==NULL)
     {

      return -1;
     }
    while(1)
    {
     output = fgets(line,100,f1);
      if(output==NULL)
      break;
      j++;
      output[strlen(output)-1]='\0';
      strcpy(p[j].name,output);
      output = fgets(line,100,f1);
     output[strlen(output)-1]='\0';
      strcpy(p[j].email,output);
      output = fgets(line,100,f1);output[strlen(output)-1]='\0';
      strcpy(p[j].ph_no,output);
    }
    fclose(f1);
  return -1;
 }
 int checke(char s[])
 {
     int l=strlen(s),a=0,i;
     for(i=0;i<l;i++)
     {
         if((s[i]=='.')&&(a==1))
            return 1 ;
         if(s[i]=='@')
            a=1;
     }
     return 0;

 }
int checkph(char s[])
{
    int l=strlen(s);
    if(l!=10)
        return 0;
    int i;
    for(i=0;i<l;i++)
    {
        if(isdigit(s[i])==0)
            return 0;

    }
    return 1;
}
int match(char a[],char b[])
{
    int l=strlen(a),i;
    if(l>(strlen(b)))
        return 0;
    for(i=0;i<l;i++)
        if(a[i]!=b[i])
        return 0;
    return 1;
}
