#include <text.h>
#include <string>

using namespace std;

text::text(string text, size_t pozition, string value) {
    this->str = text;
    size_t len = text.length();
    //Pozition !> length
    if (len > pozition)
        this->pozition = pozition;
    else
        this->pozition = 0;
    if (value == "delete")
        this->type = false;
    else
        this->type = true;

}

text::text(const text& i) {
    this->str = i.str;
    this->pozition = i.pozition;
    this->type = i.type;
}

text::text() {
    this->str = "";
    this->pozition = 0;
    this->type = true;
}

const string& text::get_text()
{
    return this->str;
}

int text::get_pozition() const
{
    return this->pozition;
}

const string text::get_type()
{
    if (this->type == true)
        return "insert";
    else
    {
        if (this->type == false)
            return "delete";
        else
            return "none";
    }
}


void text::set_text(string value)
{
    this->str = value;
}

void text::set_type(string value)
{
    if (value == "insert")
        this->type = true;
    else
        if (value == "delete")
            this->type = false;
}

void text::set_pozition(size_t value)
{
    size_t text_len = this->str.length();
    if (value >= 0 && text_len > value)
        this->pozition = value;
    else
        this->pozition = 0;

}


