// compatible  // type,variable

// node check_sym(string,size)	//
// ret_compatible(func_node,node)
patchtype(type,list of nodes) check if already there in sym tab, if not insert
struct node
{
    char name[50];
    
    enum type t;        /* array / var*/
    enum ele_type et;
    int ptr_depth;
    
    int valid;          /* whether this entry is deleted or not*/
    int scope;
    int *dim_ptr;
    
    struct node *next;

    int *a[2];
    int **a;

    *a
};


/*
insert_func_entry
check_func_proto($1,$2,$4.list_var)
check_param_match($$,$2);
check_func_exists($1.name); 
add_params_to_sym($4.list_var);


delete_entries(cur_scope);
patch_type($1,$2);
check_sym_tab(strdup(yytext),0);
compatible($3,$5);
ret_compatible(cur_func,$2);
comp_binopt_type($1,AND_AND,$3);
comp_opt_type(PLUS,$2);		//unary


*/






struct func_node{
    char name[50];
    
    enum ele_type return_type;
    int ptr_depth;

    int valid;

    struct node *param_list;
    int num_params;

    struct func_node *next;
};

void insert_symb_table(struct node* var)
{
	if var == NULL
		return ;
	
	var->valid = 1;
	var->next = symb_table;
	symb_table = var;
}

void add_params_to_sym(struct node *param_list)
{
	while(param_list!=NULL)
	{
		param_list->scope = 1;

		if(exists_in_scope(*param_list)){
			printf("Parameter already defined\n");
		}else{
			insert_symb_table(param_list);
		}

		param_list = param_list->next;
	}
}

void check_distinct(struct node *attrs)
{
	struct node *n1 = attrs;
	struct node *n2;

	while(n1!=NULL)
	{
		n2 = n1->next;
		while(n2!=NULL)
		{
			if(strcmp(n1->name,n2->name) == 0)
			{
				printf("Same variables names not allowed %s \n",n1->name);
			}

			n2 = n2->next;
		}
		n1 = n1->next;
	}
}

void insert_func_entry(struct node type,struct node id,struct list_attr attrs)
{
	if(get_func_entry(id.name) != NULL)
	{
		printf("Function already declared\n");
		return;
	}

	struct func_node *n = (struct func_node *)malloc(sizeof(struct func_node));
	n->name = id.name;
	n->return_type = type.et;
	n->ptr_depth = type.ptr_depth;
	n->valid = 0;

	check_distinct(attrs.list_var);
	n->param_list = attrs.list_var;
	n->num_params = attrs.size;

	n->next = func_table;
	func_table = n;
}

struct func_node check_func_exists(char *name)
{
	struct func_node ret_node;

	struct func_node *tmp = get_func_entry(name);
	
	if(tmp == NULL){
		ret_node.et = ERROR;
		ret_node.valid = 0;
	}
	else
		ret_node = *tmp;

	return ret_node;
}	

struct func_node* get_func_entry(char *name)
{
	struct func_node *act_func = func_table;

	while(act_func!=NULL)
	{
		if(strcmp(act_func->name,name)==0)
			return act_func;
		act_func = act_func->next;
	}

	return NULL; 
}


int check_func_proto(struct node type,struct node id,struct list_attr attrs)
{
	struct func_node *act_func = get_func_entry(id.name);

	if(act_func == NULL){
		printf("Function prototype not declared\n");		
		return 0;
	}

	if(act_func->return_type == type.et 
		&& act_func->ptr_depth == type.ptr_depth 
		&& match_node_list(attrs->list_var,act_func->param_list))
	{
		return 1;
	}

	return 0;
}

int check_param_match(struct func_node func,struct list_attr attrs)
{
	int ret_val = match_node_list(func->param_list,attrs->list_var);

	if(ret_val == 0)
		printf("Parameters mismatch for the Function %s\n",func->name);

	return ret_val;
}

int match_node_list(struct node *list_var,struct node *param_list)
{

	while(list_var!=NULL && param_list!=NULL)
	{
		if(!match_node(list_var,param_list))
		{
			printf("variable mismatch : %s %s\n",list_var->name,param_list->name);
		}
		list_var = list_var -> next;
		param_list = param_list->next;
	}

	if(list_var == NULL && param_list == NULL){
		act_func->valid == 1; 
		return 1;
	}else{
		printf("Number of var mismatch");
	}

	return 0;
}


int match_node(struct node *n1,struct node *n2)
{
    return  n1->valid == n2->valid && n1->size == n2->size && n1->ptr_depth == n2->ptr_depth \
    			&& n1->ele_type == n2->ele_type && strcmp(n1->name,n2->name) == 0;
}












struct func_node{
	char name[50];
	enum ele_type return_type;
	int valid;
	struct list *param_list;
	int num_params;

	struct func_node *next;
};
struct func_node *func_table;

enum ele_type {INTEGER,REAL,CHAR_T};
enum type {SIMPLE,ARRAY};

struct symb_node
{
	char name[50];
	enum type t;		/* array / var*/
	enum ele_type et;
	int valid;			/* whether this entry is deleted or not*/
	int scope;
	int ptr_depth;
	struct symb_node **points_to;
	int *dim_ptr;
	struct symb_node *next;
};

struct symb_node *symb_table;

int main(){
	int a[20];
	int d=2;
	int i;
	for ( i = 0; i < 20; ++i)
	{
		a[i]  =i*i;
	}
	int b=2;
	int aa = b==5;
	printf("%d\n",aa );
}