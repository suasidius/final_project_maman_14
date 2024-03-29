#include "first_scan.h"
#include "macro_deploy.h"


int SetNext(ptSymbol* head, char* command, int from, int length, int adress, short type)
{
    ptSymbol pt;
    if (*head)
    {
        pt = *head;
        while (pt->next)
        {
            pt = pt->next;
        }
        pt->next = (ptSymbol)malloc(sizeof(nodeSymbol));
        pt = pt->next;
    }
    else
    {
        *head = (ptSymbol)malloc(sizeof(nodeSymbol));
        pt = *head;
    }
    if (pt && (pt->name = (char*)malloc((length + 1) * sizeof(char))))
    {
        pt->next = NULL;
        pt->name = strncpy(pt->name, command + from, length);
        pt->name[length] = '\0';
        pt->adress = adress;
        pt->type = type;
    }
    else
    {
        return -2;
    }
    return 1;
}

int checkExist(ptSymbol head, char* name)
{
    while (head)
    {
        if (strcmp(head->name, name) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

ptSymbol GetIfExist(ptSymbol head, char* name)
{
    while (head)
    {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

int isSYEmpty(ptSymbol head)
{
    return (head) ? 0 : 1;
}

ptSymbol getNextSY(ptSymbol* head)
{
    ptSymbol p;
    if (!isSYEmpty(*head))
    {
        p = *head;
        *head = (*head)->next;
        return p;
    }
    return NULL;
}

void DeleteSymbols(ptSymbol* head)
{
    ptSymbol pt, next;
    if (!isSYEmpty(*head))
    {
        pt = *head;
        while (pt)
        {
            next = pt->next;
            free(pt->name);
            free(pt);
            pt = next;
        }
        *head = NULL;
    }
}

int addSymbols(ptSymbol* head, char* command, int from)
{
    int start, end, count = 0;
    while (isTextLeft(command, from) && from >= 0)
    {
        start = jumpSpace(command, from);
        end = endOfText(command, start);
        if (end > -1)
        {
            if (SetNext(head, command, start, end - start, 0, 2) < 0)
                return -2;
            count++;
            from = jumpBreak(command, end);
            if ((from == -1 && isTextLeft(command, end)) || (from != -1 && !isTextLeft(command, from)))
                return -3;
        }
        else
        {
            return -1;
        }
    }
    return count;
}

void upgreadeSymbols(ptSymbol head, int IC)
{
    while (head)
    {
        if (head->type <= 1)
            head->adress += IC;
        head = head->next;
    }
}


node_t* first_scan(node_t* input_node_head) {
    int IC = 100;
    int DC = 0;
    int symbol_flag = 0;
    char* ptr;
    node_t* symbolnode;
    node_t* symbol_head = NULL;
    printf("input_node_head: %d\n", IC);
    /* Rewind input list */
    while (input_node_head->next != NULL) {
        input_node_head = input_node_head->next;
    }


    while (input_node_head->prev != NULL) {
        //printf("IC: %d\n", IC);
        input_node_head = input_node_head->prev;

        ptr = input_node_head->arr;
        if (strstr(ptr, ";") != NULL) {
            //printf("comment found, ptr: %c\n", *ptr);
            IC--;


        }
        else if (strstr(ptr, ":") != NULL) {


            symbol_flag = 1;

            //is it allready in the list?
            //is it .struct , .string or .data?

            ptr = input_node_head->arr;
            char c = *ptr;
            //printf("Label found In: %sand c = %c\n", ptr, *ptr);
            symbolnode = create_new_node(IC);
            symbolnode->next = symbol_head;
            if (symbol_head != NULL)
                symbol_head->prev = symbolnode;


            int running_counter;
            for (running_counter = 0;c != LABEL_DELIM; running_counter++) {
                //printf("%c", c);
                c = (char)*(ptr++);


                symbolnode->arr[running_counter] = c;
                if (c == SPACE)
                    running_counter--;



            }
            symbolnode->arr[running_counter - 1] = '\0';
            symbol_head = symbolnode;
            printf("IC: %d LABEL: <%s> next is %s\n", symbolnode->value, symbolnode->arr, symbolnode->next->arr);
        }


        //printf("ptr location is: %s\n", ptr);


        // define 
        //TODO check for labels serch for ":" and return "label exist"
        // if ":" exist => set label exist to "1"
        // return the pointer to start of the line
        //jumpspace || 
        //while isalphanumeric || isnumber  copy char to struct_symbl.label_name 


        //TODO create node 


        //if exist, return to the start of the line, skip spaces and copy the labal name

        //store the label name with the counter in the simbol stack


        //after symbol table is created

        //check for "."

        /*Lada:first check
            -loop that goes over each line at file
            -operands: ץ raise notice for a symbol, number of line
            A check if there’s no empty spots or next line.
            - -good line: finds num of the first char after space (the number of the char in the line)
            - -Find number of the last char in the word
            - -A check if there’s a really a label(:)
            - -Pointer to the begging of the label+ length of the label to check if it’s length ok
            - -A check if there’s something after the label (needs to be else error)
            - -Checks if after label comes directive + is valid and existent directive
            - If a struct -add the label to the list (set next) short type for struct=1 (others 0)
            - -Now adding the data after string ,data ,or struct directive to data list and returns the index after this data
            - -Checks if there’s something left in the. Line (not supposed to be
            - -Check if directive is .extern
            - -Moves index after the” .extern” and adds data(label) to the list
            - -If there’s no directive, checks if there’s previous label- if no then adds label to list
            - -Than looks if there’s an order and returns number of order
            - -Checks and returns how many location spots the order needs
            - -Updating the location spots in IC
            - -In the end of the file- command that updating all labels address */
        IC++;
    }
    printf("symbole list:\n");


    if (symbol_flag == 1) {
        //printlist(symbol_head);
        printf("head is  null? %p\n", symbol_head);
        return symbol_head;
    }
    else {
        printf("head is %p\n", symbol_head);
        return NULL;
    }
}


