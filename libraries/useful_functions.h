

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
    typedef unsigned char bytes;


    namespace {
        // const std::string ansi_escape = "\033[";
        // "\033[<style>;<color>;<bkg>m<the_string>\033[0m"

        const int  NOT_IMPLEMENTEDYET = 5;
        const int UNSELECTED_ALGORITHM = 6;

        const char* merge_const = "merge";
        const char* select_const = "select";
        const char* insert_const = "insert";
        const char* bubble_const = "bubble";

        const char case_diff = 'a' - 'A';
        const char A = 'A', Z = 'Z', a = 'a', z = 'z', zero = '0', nine = '9';
        const char* esc_seq_start = "\033[";
        const char* esc_seq_end = "\033[0m";

        bool valid_color(short_int color) {
            return ((color >= (short_int) black_text) && (color <= (short_int) white_text));
        }

        bool valid_style(short_int style) {
            return (((style >= (short_int) no_effect_style) && (style <= (short_int) negative_1_style)) || (style == (short_int) negative_2_style));
        }

        bool valid_bkg(short_int bkg) {
            return ((bkg >= (short_int) black_background) && (bkg <= (short_int) default_background));
        }



        // sorting algorithms


        void swap(unsigned long* first, unsigned long* second) {
            unsigned long* temp = first;
            first = second;
            second = temp;
        }


        /**
         * @brief Implementation of Bubble sort.
         * 
         * @note Bubble sort is different from insertion sort in that it "bubbles" the largest or smallest
         * value to the end of the list being sorted and doesn't maintain an sorted section as it does so.
         * 
         * @note Bubble sort is different from selection sort in that "bubbles" the largest or smallest
         * value to the end of the list being sorted and doesn't maintain a sorted section in the same way as selection sort.
         * 
         * @note Bubble sort is unique compared to selection sort and insertion sort in that it "bubbles"
         * the largest or smallest value to the end of the list.
         * 
         * 
         * @param list `(unsigned long* array)` The list to be sorted.
         * 
         * @param length `(unsigned long int)` The length of the list to be sorted.
         * 
         * @param increasing `(bool)` A bool specifying whether the sorting algorithm should sort the data
         * in ascending or descending order.
         * 
         * 
         * @returns void.
        */
        void bubble_sort(unsigned long* list[], unsigned long length, bool increasing = true) {

            // algorithm from book:
            unsigned long first, second;
            for (first = length - 1; first > 1; first = first - 1) {
                for (second = 0; second < first; second = second + 1) {
                    if (((increasing) && (*list[first] > *list[first + 1])) || (!(increasing) && (*list[first] < *list[first + 1]))) {
                        swap(list[first], list[first + 1]);
                    }
                }
            }

            // from cs50 course
            // unsigned long index, swap_count = -1;
            // while (swap_count != 0) {
            //     swap_count = 0;
            //     for (index = 0; index < length - 2; index = index + 1) {
            //         if (((increasing) && (*list[index] > *list[index + 1])) || (!(increasing) && (*list[index] < *list[index + 1]))) {
            //             swap(list[index], list[index + 1]);
            //             swap_count = swap_count + 1;
            //         }
            //     }
            // }

            // both algorithms are the same. The only difference is whether the data being compared is shoulder to shoulder or arbitrarily apart from each other.

        }


        /**
         * @brief Implementation of insertion sort algorithm.
         * 
         * @note Insertion sort is different from bubble sort in that it maintains
         * a sorted and unsorted section of the list, and continually `inserts` data
         * from the unsorted section into the sorted section at the proper location in the sorted section.
         * 
         * 
         * @note Insertion sort is very similar to the selection sort algorithm in that
         * it maintains a sorted and unsorted section of the list and inserts data into the sorted
         * section at the proper location of the sorted list.
         * 
         * @param list `(unsigned long* array)` The list to be sorted.
         * 
         * @param length `(unsigned long int)` The length of the list to be sorted.
         * 
         * @param increasing `(bool)` A bool specifying whether the sorting algorithm should sort the data
         * in ascending or descending order.
         * 
         * @returns void
        */
        void insertion_sort(unsigned long* list[], unsigned long length, bool increasing = true) {
            unsigned long outer_lim, inner_lim, *temp;
            outer_lim = 1;
            for (outer_lim = 1; outer_lim < length; outer_lim = outer_lim + 1) {
                temp = list[outer_lim];
                inner_lim = outer_lim;
                while ((inner_lim > 0) && (((increasing) && (*list[inner_lim - 1] >= *list[inner_lim])) || (!(increasing) && (*list[inner_lim - 1] <= *list[inner_lim])))) {
                    list[inner_lim] = list[inner_lim - 1];
                    inner_lim = inner_lim - 1;
                }
                list[inner_lim] = temp;
            }
        }


        /**
         * @brief Implementation of selection_sort.
         * 
         * @note Selection sort is different from bubble sort in that it maintains
         * a sorted and unsorted section of the list, and continually `selecting` and adding the smallest piece 
         * of data (if sorting in increasing order), or the largest piece of data (if sorting 
         * in a decreasing order) to the end of the sorted list.
         * 
         * 
         * 
         * @param list `(unsigned long* array)` The list to be sorted.
         * 
         * @param length `(unsigned long int)` The length of the list to be sorted.
         * 
         * @param increasing `(bool)` A bool specifying whether the sorting algorithm should sort the data
         * in ascending or descending order.
         * 
         * @returns void
        */
        void selection_sort(unsigned long* list[], unsigned long length, bool increasing = true) {
            // find smallest unsorted element and add it to the end of the sorted list.
            unsigned long index, other_index, *temp;
            for (index = 0; index < length - 1; index = index + 1) {
                temp = list[index];
                for (other_index = index + 1; other_index < length; other_index = other_index + 1) {
                    if (((increasing) && (*list[other_index] < *temp)) || ((increasing) && (*list[other_index] > *temp))) {
                        swap(temp, list[other_index]);
                    }
                }
                list[index] = temp;
            }

        }

        //--------------------------------------Mergesort stuff. Needs to be tested--------------------------------------

        void merge(unsigned long* list[], unsigned long lower_limit, unsigned long mid_point, unsigned long upper_limit, unsigned long* new_list[], bool increasing = true) {
            unsigned long new_index = (mid_point - lower_limit) + (upper_limit - mid_point - 1);
            unsigned long lower_index = lower_limit, upper_index = mid_point + 1;
            while ((lower_index <= mid_point) && (upper_index <= upper_limit)) {
                if ((((*list[lower_index] <= *list[upper_index]) && (increasing))) || (!(increasing) && (*list[lower_index] >= *list[upper_index]))) {
                    new_list[new_index] = list[lower_index];
                    lower_index = lower_index + 1;
                }
                else {
                    new_list[new_index] = list[upper_index];
                    upper_index = upper_index + 1;
                }
                new_index = new_index + 1;
            }

            while (lower_index <= mid_point) {
                new_list[new_index] = list[lower_index];
                new_index = new_index + 1;
                lower_index = lower_index + 1;
            }


            while (upper_index <= upper_limit) {
                new_list[new_index] = list[upper_index];
                new_index = new_index + 1;
                upper_index = upper_index + 1;
            }


        }


        void rec_merge_sort(unsigned long* list[], unsigned long lower_limit, unsigned long upper_limit, unsigned long* new_list[]) {

            // base case. Nothing to sort here
            if (lower_limit == upper_limit) {
                return;
            }

            // otherwise there are at least 2 pieces of data to sort at index lower_limit and upper_limit which is at least lower_limit + 1
            unsigned long mid_point = (lower_limit + upper_limit) / 2;
            rec_merge_sort(list, lower_limit, mid_point, new_list);
            rec_merge_sort(list, mid_point + 1, upper_limit, new_list);
            merge(list, lower_limit, mid_point, upper_limit, new_list);
        }


        void merge_sort(unsigned long* list[], unsigned long length, bool increasing = true) {
            unsigned long* new_list[length];
            rec_merge_sort(list, 0, length - 1, new_list);
            list = new_list;
        }


        //--------------------------------------Mergesort stuff end. Needs to be tested-----------------------------------

    }



    // const char case_diff = 'a' - 'A';

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


    void sort_pointers(unsigned long* array[], unsigned long length, char* sort = (char *) "insert", bool increasing = true) {

        if (same_string(sort, (char *) merge_const)) {
            fprintf(stderr, "Not yet Implemented \n");
            exit(NOT_IMPLEMENTEDYET);
        }

        else if (same_string(sort, (char *) bubble_const)) {
            bubble_sort(array, length, increasing);
        }

        else if (same_string(sort, (char *) select_const)) {
            selection_sort(array, length, increasing);
        }

        else if (same_string(sort, (char *) insert_const)) {
            insertion_sort(array, length, increasing);
        }

        else {
            fprintf(stderr, "Unselected sorting algorithm.\n");
            exit(UNSELECTED_ALGORITHM);
        }

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