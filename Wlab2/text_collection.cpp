#include <text_collection.h>
#include <text.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

//Initialization constructor
stack_obj::stack_obj(text &stack_obj){
    set_object(stack_obj);
    set_previous(NULL);
};

stack_obj::stack_obj(stack_obj &other){
    text *text_1;
    text_1 = new text(other.get_object()) ;
    this->set_object(other.get_object());
    this->set_previous(other.get_previous());
};

//Setter for previous object
void stack_obj::set_previous(stack_obj *stack_obj){
    this->previous = stack_obj;
};

//Setter for text stack
void stack_obj::set_object(text &object){
    this->object = object;
};

//Getter for text stack
text &stack_obj::get_object(){
    return this->object;
};

stack_obj *stack_obj::get_previous() const{
    return this->previous;
};

//Def constructor
text_collection::text_collection(){
    last = NULL;
    first = NULL;
    size = 0;
};

//Copy constructor
text_collection::text_collection(text_collection &stack){
    this->last=NULL;
    this->first=NULL;
    this->set_size(0);
    if(stack.get_last()){
        stack_obj *object = stack.get_last();
        while(object->get_previous() != NULL){
            this->push_object(*object);
            object = object->get_previous();
        }
        this->push_object(*object);
    }
    //this->set_size(stack.get_size());
};

void text_collection::set_size(const size_t size){
    this->size = size;
};

void text_collection::set_last(stack_obj& object){
    this->last = &object;
};

void text_collection::set_first(stack_obj& object){
    this->first = &object;
};

int text_collection::get_size(){
    return this->size;
};

stack_obj *text_collection::get_last() const{
    if(this->last==NULL){
        cout << "Stack is empty" << endl;
        return NULL;
    }
    else
        return this->last;
};

stack_obj *text_collection::get_first() const{
    if(this->first==NULL){
        cout << "Stack is empty" << endl;
        return NULL;
    }
    else
        return this->first;
};

stack_obj *text_collection::get_by_index(int iterator){
    if(this->get_size()<=iterator){
        cout << "Iterartor out of stack size" << endl;
        exit(1);
    }
    else{
        stack_obj *object = this->get_last();
        int len = this->get_size()-iterator-1;
        for(int i=0;i<len;i++){
            object=object->get_previous();
        }
        return object;
    }
};

void text_collection::push_object(stack_obj& object){
    stack_obj *new_object;
    new_object= new stack_obj(object);
    new_object->set_object(object.get_object());
    if (this->size == 0){
        this->first = new_object;
    }
    new_object->set_previous(this->last);
    this->last = new_object;
    this->size++;
    cout << "Object with text: '" << this->last->get_object().get_text() << "' - added to the stack. Now it's length is: " << this->get_size() << endl;
};


//Add object stack_obj to end of stack and clear another stack
void text_collection::push_operation(stack_obj &object, text_collection &change){
    if(this==&change)
    {
        cout << "Please use different undo and change stacks." << endl;
        exit(1);
    }
    stack_obj *new_object;
    new_object= new stack_obj(object);
    new_object->set_object(object.get_object());
    //If stack is empty, first is first object
    if (this->size == 0)
        this->first = new_object;
    //Record previous value to last value
    new_object->set_previous(this->last);
    this->last = new_object;
    this->size++;
    cout << "Object with text: '" << this->last->get_object().get_text() << "' - added to the undo stack. Now it's length is: " << this->get_size() << endl;
    change.remove_all();
};


//Add text_collection обьект to stack
void text_collection::push_stack(text_collection& add_stack){
       stack_obj *last_object = add_stack.last;
       while(last_object->get_previous() != NULL){
           this->push_object(*last_object);
           last_object = last_object->get_previous();
       };
       this->push_object(*last_object);
};


//Remove stack_obj object from stack
stack_obj *text_collection::remove_last()
{
    if(this->get_size()==0){
        cout << "No more operations to undo" << endl;
        return NULL;
    }
    else{
        if(this->get_size()>1)
        {
            stack_obj *newLast = this->last->get_previous();
            stack_obj *del=this->get_last();
            this->last = newLast;
            this->size = this->size - 1;
            return del;
        }
        else//first is Null too
        {
            stack_obj *del=this->get_last();
            this->last = NULL;
            this->first = NULL;
            this->size = this->size - 1;
            return del;
        }
    }
}


//Remove last obj
void text_collection::remove(){
    stack_obj *delet = remove_last();
    delete delet;
}


//Cancel operation
void text_collection::undo(text_collection& stack_cmback)
{
    stack_obj *object = this->remove_last();
    if(object==NULL)
        cout << "Operation failed" << endl;
    else
    {
        cout << "Last object from stack with text: '" << object->get_object().get_text() << "' - deleted. Now it's length is: " << this->get_size() << " ." << endl;
        stack_cmback.push_object(*object);
    }
}



void text_collection::remove_all()
{
    if (this->size > 0){
        for(int i=this->get_size();i>0;i--){
            delete this->remove_last();
        }
        this->last = NULL;
        this->first = NULL;
    };
};


//Record to file
int text_collection::record_file(const string &fname)
{
    ofstream fout;
    fout.open(fname);

    for (int i = 0; i <int(this->size); i++)
    {
        text object = this->get_by_index(i)->get_object();
        fout <<  object.get_text() <<" " << object.get_pozition() << " " << object.get_type() << endl;
    }
    fout.close();
    return 0;
};


//Read from file
int text_collection::output_file(const string &fname)
{
    string textt;
    size_t poz;
    string type;

    //Open file
    ifstream file(fname);

    //Clear stack
    if(this->size>0)  this->remove_all();

    while(file >> textt >> poz >> type)
    {
        auto text_1 = new text(textt,poz,type);
        auto object = new stack_obj(*text_1);
        this->push_object(*object);
    }
    file.close();
    return 0;
};

//Checking of 2 stacks
bool text_collection::operator==(const text_collection& l)
{
    // Checker for size
    if(this->size != l.size)
        return false;

    stack_obj *t1, *t2;
    t1 = get_last();
    t2 = l.get_last();

    // Checker for data
    while(t1 != NULL)
    {
        if (t1->get_object().get_text() != t2->get_object().get_text() && t1->get_object().get_pozition() != t2->get_object().get_pozition() && t1->get_object().get_type() != t2->get_object().get_type())
            return false;
        t1 = t1->get_previous();
        t2 = t2->get_previous();
    }
    return true;
}


//Output stack
int show_stack_obj(text_collection& stack){
    int m = stack.get_size();
    stack_obj *object = stack.get_last();
    cout << "Number  " << "Type      " << "Text              " << "Substring" << endl;
    for (int i=0; i < m; i++){
        string type;
        if (object->get_object().get_type() == "insert")
            type = "Insert";
        else
            type = "Delete";
        cout << i+1 << ".      " << type << "    " << object->get_object().get_text() \
             << "             " << object->get_object().get_pozition() << endl;
        object = object->get_previous();
    };
    return 0;
};



