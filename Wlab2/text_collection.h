#ifndef stack_obj_H
#define stack_obj_H
#include <text.h>
#include <fstream>
#include <stdio.h>

class stack_obj
{
private:
    stack_obj *previous;
    text object;
public:

    stack_obj(text& object);
    stack_obj(stack_obj &object);

    void set_previous(stack_obj *stack_obj);
    void set_object(text& object);

    text& get_object();
    stack_obj *get_previous() const;
};

class text_collection{
private:
    stack_obj *last, *first;
    size_t size;
    stack_obj *remove_last();
public:

    text_collection();
    text_collection(text_collection& stack_obj);//copy constructor

    void set_size(const size_t size);
    void set_last(stack_obj& object);
    void set_first(stack_obj& object);

    int get_size();
    stack_obj *get_last() const;
    stack_obj *get_first() const;
    stack_obj *get_by_index(int iterator);

    void push_stack(text_collection& add_stack);
    void push_operation(stack_obj& object, text_collection& change);
    void push_object(stack_obj& object);
    void undo(text_collection& stack_cmback);
    void remove();
    void remove_all();

    int record_file(const string &name);
    int output_file(const string &name);

    bool operator == (const text_collection&);
};

int show_stack_obj(text_collection& stack_obj);


#endif
