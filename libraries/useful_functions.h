








namespace useful_functions {


    // TEXT COLORS
    #define black_txt 30
    #define red_txt 31
    #define green_txt 32
    #define yellow_txt 33
    #define blue_txt 34
    #define purple_txt 35
    #define cyan_txt 36
    #define white_txt 37






    // TEXT STYLE
    #define no_style 0
    #define bold_style 1
    #define uline_style 2
    #define neg_1_style 3
    #define neg_2_style 5




    // BACKGROUND COLOR
    #define black_bkg 40
    #define red_bkg 41
    #define green_bkg 42
    #define yellow_bkg 43
    #define blue_bkg 44
    #define purple_bkg 45
    #define cyan_bkg 46
    #define white_bkg 47
    #define default_bkg 49



    typedef unsigned short int us;
    typedef unsigned char bytes;



    namespace {

        /* 
            Using escape sequence to print colors
            esc_start<style>;<color>;<bkg>m<the_string>esc_stop
         */


        const char* esc_start = "\033[";
        const char* esc_stop = "\033[m";
        


        const char* merge_const = "merge";
        const char* select_const = "select";
        const char* insert_const = "insert";
        const char* bubble_const = "bubble";


        const char case_diff = 'a' - 'A';
        const char A = 'A', Z = 'Z', a = 'a', z = 'z', zero = '0', nine = '9';

        bool valid_text_color(us color) {
            return ((color) >= (us) black_txt) && (color <= (us) white_txt);
        }

        bool valid_style(us color) {
            return (color >= (us) no_style) && (color <= (us) neg_1_style) || (color == (us) neg_2_style);
        }

        bool valid_bkg_color(us color) {
            return (color >= (us) black_bkg) && (color <= (us) default_bkg);
        }

        template <typename data_> void swap(data_& first, data_& second) {
            data_ temp = first;
            first = second;
            second = first;
        }

    }




    /*=====================================useful functions accessible===============================*/




    template <typename data_> data_ absolute(data_ val) {
        return (val < 0) ? val * -1 : val;
    }

    
    template <typename data_> data_ max_data(data_ first, data_ second) {
        return (first >= second) ? first : second;
    }


    template <typename data_> data_ min_data(data_ first, data_ second) {
        return (first <= second) ? first : second;
    }

    template <typename data_> unsigned long max_in_list(data_ list[], unsigned long length) {
        unsigned long the_answer = 0, index;
        for (index = 0; index < length; index = index + 1) {
            the_answer = (max_data(list[index], list[the_answer]) == list[index]) ? index : the_answer;
        }
        return the_answer;
    }

    template <typename data_> unsigned long min_in_list(data_ list[], unsigned long length) {
        unsigned long the_answer = 0, index;
        for (index = 0; index < length; index = index + 1) {
            the_answer = (min_data(list[index], list[the_answer]) == list[index]) ? index : the_answer;
        }
        return the_answer;
    }

    template <typename data_> unsigned long max_data_ptr(data_* list[], unsigned long length) {
        unsigned long the_answer = 0, index;
        for (index = 0; index < length; index = index + 1) {
            the_answer = (max_data(*list[index], *list[the_answer]) == *list[index]) ? index : the_answer;
        }
        return the_answer;
    }

    template <typename data_> unsigned long min_data_ptr(data_* list[], unsigned long length) {
        unsigned long the_answer = 0, index;
        for (index = 0; index < length; index = index + 1) {
            the_answer = (min_data(*list[index], *list[the_answer]) == *list[index]) ? index : the_answer;
        }
        return the_answer;
    }

}