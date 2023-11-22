

#define useful_functions_h "useful_functions.h"





namespace useful_functions {


    // TEXT COLORS
    #define black_text 30
    #define red_text 31
    #define green_text 32
    #define yellow_text 33
    #define blue_text 34
    #define purple_text 35
    #define cyan_text 36
    #define white_text 37




    // TEXT STYLE
    #define no_effect_style 0
    #define bold_style 1
    #define underline_style 2
    #define negative_1_style 3
    #define negative_2_style 5




    // BACKGROUND COLOR
    #define black_background 40
    #define red_background 41
    #define green_background 42
    #define yellow_background 43
    #define blue_background 44
    #define purple_background 45
    #define cyan_background 46
    #define white_background 47
    #define default_background 49

    typedef unsigned short int short_int;

    // const std::string ansi_escape = "\033[";
    // "\033[<style>;<color>;<bkg>m<the_string>\033[0m"


    const char case_diff = 'a' - 'A';

    template <typename data_> data_ absolute(data_ value) {
        return ((value < 0) ? (data_) (value * -1) : (data_) value);
    }

    template<typename data_> data_* absolute(data_* value) {
        if (*value < 0) {
            *value = (data_) (*value * -1);
        }
        return value;
    }

    template <typename data_> data_ max(data_ a, data_ b, bool abs) {
        if (abs) {
            if (a == b) {
                return a;
            }
            return (absolute(a) >= absolute(b)) ? a : b;
        }
        return (a >= b) ? a : b;
    }

    template <typename data_> data_* max(data_* a, data_* b, bool abs) {
        if (abs) {
            if (*a == *b) {
                return a;
            }
            return (absolute(*a) >= absolute(*b)) ? a : b;
        }
        return (*a >= *b) ? a : b;
    }

    template <typename data_> data_* max(unsigned int len, data_* arr[], bool abs = false) {
        unsigned int index;
        data_* the_answer = arr[0];
        for (index = 1; index < len; index = index + 1) {
            the_answer = max(arr[index], the_answer, abs);
        }
        return the_answer;
    }

    template <typename data_> data_ min(data_ a, data_ b, bool abs) {
        if (abs) {
            if (a == b) {
                return a;
            }
            return (absolute(a) <= absolute(b)) ? a : b;
        }
        return (a <= b) ? a : b;
    }

    template <typename data_> data_* min(data_* a, data_* b, bool abs) {
        if (abs) {
            if (*a == *b) {
                return a;
            }
            return (absolute(*a) <= absolute(*b)) ? a : b;
        }
        return (*a <= *b) ? a : b;
    }

    template <typename data_> data_* min(unsigned int len, data_* arr[], bool abs = false) {
        unsigned int index;
        data_* the_answer = arr[0];
        for (index = 1; index < len; index = index + 1) {
            the_answer = min(the_answer, arr[index], abs);
        }
        return the_answer;
    }

    template<typename data_ = signed long> data_ difference(data_ first, data_ second, bool abs = false) {
        // data_ the_answer;
        // if (abs) {
        //     the_answer = useful_functions::max<data_>(first, second, abs) - useful_functions::min<data_>(first, second, abs);
        // }
        // else {
        //     the_answer = first - second;
        // }
        // return the_answer;
        if (abs) {
            return max<data_>(absolute(first), absolute(second), abs) - min<data_>(absolute(first), absolute(second), abs);
        }

        return max<data_>(first, second, abs) - min<data_>(first, second, abs);

    }

    bool is_caps(char c) {
        return ((c >= 'A') && (c <= 'Z')) ? true : false;
    }

    bool is_lower(char c) {
        return ((c >= 'a') && (c <= 'z')) ? true : false;
    }

    bool is_letter(char c) {
        return ((is_caps(c)) || (is_lower(c))) ? true : false;
    }

    bool is_number(char c) {
        return ((c >= '0') && (c <= '9')) ? true : false;
    }

    char to_caps(char c) {
        return ((is_letter(c)) && (is_lower(c))) ? (c - case_diff) : c;
    }

    char to_lower(char c) {
        return ((is_letter(c)) && (is_caps(c))) ? (c + case_diff) : c;
    }

    unsigned long string_length(char* the_string) {
        unsigned long the_answer;
        for (the_answer = 0; the_string[the_answer] != '\0'; the_answer = the_answer + 1) {}
        return the_answer;
    }

    bool same_char(char first, char second, bool ignore_case = true) {
        if (ignore_case) {
            // std::cout << "\t\tto_caps(first) : " << to_caps(first) << ", to_caps(second) : " << to_caps(second) << std::endl;
            // std::cout << "\t\t\tabout to return " << std::to_string((to_caps(first) == to_caps(second)) ? true : false) << std::endl;
            return (to_caps(first) == to_caps(second)) ? true : false;
        }
        return (first == second) ? true : false;
    }

    bool same_string(char* first, char* second, bool ignore_case = true) {
        unsigned long index;
        for (index = 0; first[index] != '\0' && second[index] != '\0'; index = index + 1) {
            if (!same_char(first[index], second[index], ignore_case)) {
                // std::cout << "\t\"" << first[index] << "\", and \"" << second[index] << "\" are different" << std::endl;
                return false;
            }
            // std::cout << "Continuing...";
        }
        return ((first[index] == second[index]) && (first[index] == '\0')) ? true : false;
    }

    bool valid_color(short_int color) {
        return ((color >= (short_int) black_text) && (color <= (short_int) white_text));
    }

    bool valid_style(short_int style) {
        return (((style >= (short_int) no_effect_style) && (style <= (short_int) negative_1_style)) || (style == (short_int) negative_2_style));
    }

    bool valid_bkg(short_int bkg) {
        return ((bkg >= (short_int) black_background) && (bkg <= (short_int) default_background));
    }

    std::string get_styled_string(std::string the_string, short_int style = (short_int) no_effect_style, short_int color = (short_int) black_text, short_int bkg = (short_int) default_background) {
        style = (valid_style((short_int) style)) ? (short_int) style : (short_int) no_effect_style;
        color = (valid_color((short_int) color)) ? (short_int) color : (short_int) black_text;
        bkg = (valid_bkg((short_int) bkg)) ? (short_int) bkg : (short_int) default_background;
        return "\033[" + std::to_string(int(style)) + ";" + std::to_string(int(color)) + ";" + std::to_string(int(bkg)) + "m" + the_string + "\033[0m";
    }

    std::string to_std_string(char* the_string) {
        std::string the_answer = "";
        unsigned long index;
        for (index = 0; the_string[index] != '\0'; index = index + 1) {
            the_answer = the_answer + std::to_string(the_string[index]);
        }
        return the_answer;
    }

    signed long index_of(std::string to_search, char to_find) {
        signed long index;
        for (index = 0; index < to_search.length(); index = index + 1) {
            if (same_char(to_search[index], to_find)) {
                return index;
            }
        }
        return -1;
    }

    char* new_char_ptr(char* the_string) {
        unsigned long index;
        char* the_answer = (char*) malloc(sizeof(char) * string_length(the_string));
        for (index = 0; the_string[index] != '\0'; index = index + 1) {
            the_answer[index] = the_string[index];
        }
        the_answer[index] = '\0';
        return the_answer;
    }

    unsigned int str_to_uint(std::string num) {
        unsigned int the_answer = 0, index;
        for (index = num.length() -1 ; index >= 0; index = index - 1) {
            the_answer = the_answer + (((unsigned int) (num[index] - '0')) * (index + 1));
        }
        return the_answer;
    }

    signed int str_to_int(std::string num) {
        signed int the_answer = 0, index;
        for (index = num.length() - 1; index >= 0; index = index - 1) {
            if (index == 0 && num[index] == '-') {
                the_answer = the_answer * -1;
                break;
            }
            the_answer = the_answer + (((signed int) (num[index] - '0')) * (index + 1));
        }
        return the_answer;
    }

}