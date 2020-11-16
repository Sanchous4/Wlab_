#include <iostream>
#include <assert.h>
#include <text_collection.h>
#include <text.h>
#include <fstream>
#include <stdio.h>


using namespace std;

int main()
{
    //Class text
     text test_txt("first_word", 2, "insert" );
     assert(test_txt.get_text() == "first_word");
     assert(test_txt.get_pozition() == 2);
     assert(test_txt.get_type() == "insert");

     stack_obj test_stack_obj(test_txt);

     // Default constructors
     text_collection text_cl_test;
     assert(text_cl_test.get_last()==NULL);
     assert(text_cl_test.get_first()==NULL);
     assert(text_cl_test.get_size()==0);

     // Remove and add
     assert(text_cl_test.get_size() == 0);
     text_cl_test.push_object(test_stack_obj);
     assert(text_cl_test.get_size() == 1);
     text_cl_test.remove();
     assert(text_cl_test.get_size() == 0);

     text_cl_test.push_object(test_stack_obj);
     text_cl_test.push_object(test_stack_obj);

     //Copy constructors and remove all
     text_collection stack2(text_cl_test);
     assert(text_cl_test == stack2);
     assert(text_cl_test.get_size() == 2);
     stack2.remove_all();
     bool check = text_cl_test == stack2;
     assert(check==false);
     assert(stack2.get_size() == 0);

     //Show stack_obj
     assert(show_stack_obj(text_cl_test) == 0);


     //Record and read file
     assert(text_cl_test.record_file("1.txt") == 0);
     text_collection text_cl_test_out;
     assert(text_cl_test_out.output_file("1.txt") == 0);
     show_stack_obj(text_cl_test_out);

     assert(text_cl_test == text_cl_test_out);

    return 0;
}
