#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct e_node_tag
{
    int v;
    struct e_node_tag* next;
}e_node;
typedef struct v_node_tag
{
    int v;
    struct v_node_tag* down;
    e_node* next;
}v_node;

bool IfVertExist(v_node** root, int v)
{
    bool ret_val=0;
    v_node* ptr=*root;
    if(ptr!=NULL)
    {
        while(ptr!=NULL&&ret_val==0)
        {
            if(ptr->v==v)
            {
                ret_val=1;
            }
            else
            {
                ptr=ptr->down;
            }
        }
        *root=ptr;
    }
    return ret_val;
}

v_node* InsertAdjList(v_node* root, int v1, int v2)
{
    v_node* ptr=root;
    if(ptr==NULL)
    {
        v_node* vnptr=(v_node*)malloc(sizeof(v_node));
        vnptr->v=v1;
        e_node* enptr=(e_node*)malloc(sizeof(e_node));
        enptr->v=v2;
        enptr->next=NULL;
        vnptr->next=enptr;
        v_node* vnptr2=(v_node*)malloc(sizeof(v_node));
        vnptr2->v=v2;
        vnptr2->down=NULL;
        vnptr2->next=NULL;
        vnptr->down=vnptr2;
        root=vnptr;
    }
    else
    {
        v_node* lptr=root;
        if(IfVertExist(&lptr,v1))
        {
            e_node* enptr=(e_node*)malloc(sizeof(e_node));
            enptr->v=v2;
            enptr->next=lptr->next;
            lptr->next=enptr;
            lptr=root;
            if(!(IfVertExist(&lptr,v2)))
            {
                v_node* vnptr=(v_node*)malloc(sizeof(v_node));
                vnptr->v=v2;
                vnptr->next=NULL;
                vnptr->down=ptr->down;
                ptr->down=vnptr;
            }
        }
        else
        {
            v_node* vnptr=(v_node*)malloc(sizeof(v_node));
            vnptr->v=v1;
            vnptr->down=ptr->down;
            ptr->down=vnptr;
            e_node* enptr=(e_node*)malloc(sizeof(e_node));
            enptr->v=v2;
            enptr->next=NULL;
            vnptr->next=enptr;
            lptr=root;
            if(!(IfVertExist(&lptr,v2)))
            {
                v_node* vnptr2=(v_node*)malloc(sizeof(v_node));
                vnptr2->v=v2;
                vnptr2->next=NULL;
                vnptr2->down=ptr->down;
                ptr->down=vnptr2;
            }
        }
    }
    return root;
}

v_node* InitAdjList(v_node* root)
{
    v_node* ptr=root;
    int v1, v2;
    FILE* fptr=fopen("data.txt","r");
    fseek(fptr,0,SEEK_END);
    unsigned int len=ftell(fptr);
    if(len>0)
    {
        rewind(fptr);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d",&v1);
            fscanf(fptr,"%d",&v2);
            //printf("\nv1: %d\n",v1);
            //printf("\nv2: %d\n",v2);
            ptr=InsertAdjList(ptr,v1,v2);
        }
    }
    fclose(fptr);
    return ptr;
}

void PrintAdjList(v_node* root)
{
    v_node* vptr=root;
    e_node* eptr;
    if(vptr!=NULL)
    {
        for(vptr=root;vptr!=NULL;vptr=vptr->down)
        {
            printf("\n%d : ",vptr->v);
            for(eptr=vptr->next;eptr!=NULL;eptr=eptr->next)
            {
                printf("%d, ",eptr->v);
            }
        }
    }
}

void main()
{
    v_node* root=NULL;
    root=InitAdjList(root);
    PrintAdjList(root);
}
