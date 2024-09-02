#include "s21_sprintf.h"

#include <stdarg.h>
#include <ctype.h>
#include <string.h>

int s21_sprintf(char *str, const char *format,...) {
    va_list arguments;
    va_start(arguments, format);
    char *src = str;
    char *str_start = str;

    while (*format) {
        if (*format == '%') {
            format++;

            Spec specs = {0};
            
            format = specs_define(&specs, format); // на этом этапе считываем все спецификаторы перег спецификатором-буквой
            format = width_precicion_define(format, &specs, arguments);
            format = length_define(format, &specs);

            specs.specifier = *format;

            char buffer_str[BUFFER_SIZE] = {'\0'};
            processing(&specs, buffer_str, arguments);
            for (int i = 0; buffer_str[i];i++, str++)
                *str = buffer_str[i];
            
            if (specs.specifier == 'n'){
                int *ret = va_arg(arguments, int *);
                *ret = str-str_start;
            }
        } else {
            *str++ = *format; // Просто копируем символ, если он не является %
        }
        format++;
    }

    *str = '\0'; // Завершаем строку нулевым символом
    va_end(arguments);
    return (str - src); // Возвращаем длину результата
}

const char *specs_define(Spec *specs, const char *format){ // определяем спецификаторы пред 
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '0' || *format == '#'){
        switch (*format){
            case '-':  specs->minus = true ; break;
            case '+': specs->plus = true; break;
            case ' ': specs->space = true;break;
            case '0': specs->zero = true;break;
            case '#': specs->hash = true;break;
            default: break;
        }
        format++;
    }   
    return format;
}

const char *width_precicion_define(const char *format, Spec *specs, va_list arguments){
    // width definition 
    if (*format == '*'){
        format++;
        specs->width = va_arg(arguments, int);
    } else if (*format >= '0' && *format <= '9'){ // is digit?
        char buffer[BUFFER_SIZE] = {'\0'};
        for (int i = 0; *format >= '0' && *format <= '9'; format++, i++)
            buffer[i] = *format;
        specs->width = array_to_int(buffer);
    }
    // precision definition 
    if (*format == '.'){
        specs->is_precision_set = true;
        format++;
    }

    if (*format == '*'){
        format++;
        specs->precision = va_arg(arguments, int);
    }
    if (*format >= '0' && *format <= '9'){
        char buffer_2[BUFFER_SIZE] = {'\0'};
        for (int i = 0; *format >= '0' && *format <= '9'; format++, i++)
            buffer_2[i] = *format;
        specs->precision = array_to_int(buffer_2); 
    }
    return format;
}



int array_to_int(char *buffer){
    int result = 0;
    int multiplier = 1;

    for (int i = s21_strlen(buffer)-1; i >= 0 ; i--){ 
        if (buffer[i] == '-') break;
        if (buffer[i] == '.'){
            result = 0;
            multiplier =1;
            continue;
        }
        result += (buffer[i] - '0') * multiplier; 
        multiplier *= 10; 
    }
    if (buffer[0] == '-') result *=-1;
    return result;
}


const char *length_define(const char *format, Spec *specs){
    switch(*format){
        case 'h': specs -> length = 'h'; format++; break; // short int
        case 'l': specs -> length = 'l'; format++; break; // long int
        case 'L':specs -> length = 'L'; format++; break; // long double
    }
    return format;
}

void processing(Spec *specs, char *buffer_str, va_list arguments){
    switch (specs->specifier){
        case 'd': 
        case 'i': integer_strategy(&(*specs), buffer_str, arguments); break;
        case 'u': unsigned_strategy(&(*specs), buffer_str, arguments); break;
        case 'o': octal_strategy(&(*specs), buffer_str, arguments); break;
        case 'x':
        case 'X': hex_strategy(&(*specs), buffer_str, arguments); break;
        case '%': *buffer_str = '%'; break;
        case 'c': char_strategy(&(*specs), buffer_str, arguments); break;
        case 's': string_strategy(&(*specs), buffer_str, arguments); break;
        case 'p': pointer_strategy(&(*specs), buffer_str, arguments); break;
        case 'f': float_strategy(&(*specs), buffer_str, arguments); break;
        case 'e':
        case 'E': mantiss_strategy(&(*specs), buffer_str, arguments); break;
        case 'g':
        case 'G': gG_strategy(&(*specs), buffer_str, arguments); break;
    
    }
    
    
}

void integer_strategy(Spec *specs, char *buffer_str, va_list arguments){
    long value = va_arg(arguments, long);
    if ((specs->length == 'h')){
            short int new_value = (short int)value; 
            integer_to_char_array(new_value, buffer_str); 
    }else if(specs->length == 'l' ){
        
            long int new_value = (long int)value; 
            integer_to_char_array(new_value, buffer_str); 
    }else{
            int new_value = value; 
            integer_to_char_array(new_value, buffer_str);       
    }
    
    precision_processing(&(*specs), buffer_str);
    flags_processing(&(*specs), buffer_str);
    

}

void integer_to_char_array(long num, char *buff){
    int i = 0;
    int minus_flag = 0;
    if (num<0){
        minus_flag=1;
        num = -num;
        buff[i] = '-';
        i++;
        while(num!=0){
            int dig = num %10;
            buff[i] = dig + '0';
            i++;
            num /=10;
    }
    }
    else if(num == 0){
        buff[i] = '0';
        i++;
    }
    else {
        while(num!=0){
        int dig = num %10;
        buff[i] = dig + '0';
        i++;
        num /=10;
        }
    }
    buff[i] = '\0';
    // reverse
    int end = s21_strlen(buff)-1;
    int start = 0;
    if (minus_flag) start+=1;
    while(start<end){
        char temp = buff[start];
        buff[start] = buff[end];
        buff[end] = temp;
        start++;
        end--;
    }
}

void precision_processing(Spec *specs, char *buffer_str){
    char tmp_buff[BUFFER_SIZE] = {'\0'};
    
    if ((specs->specifier == 'd') || (specs->specifier == 'i') || (specs->specifier == 'o') ||
     (specs->specifier == 'u') || (specs->specifier == 'x') || (specs->specifier == 'X')){
            if (s21_strlen(buffer_str)>=1){
                
                if (specs->precision == 0 && specs->is_precision_set == 1 && *buffer_str == '0'){                   
                    *buffer_str ='\0';
                }
                else if (specs->precision != 0 && specs->is_precision_set == 1 && *buffer_str == '0'){
                    for (int i = 0; i<specs->precision-1;i++)
                        tmp_buff[i] = '0';
                    
                    s21_strncat(tmp_buff, buffer_str, s21_strlen(tmp_buff)); //!
                    s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); //!
                    clean_buffer(tmp_buff);                  
                }
                else if(specs ->precision >= 0){
                    
                    int j =0;
                    for (int i = s21_strlen(buffer_str); i<specs->precision;i++)
                        tmp_buff[j++] = '0';
                    s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); //!
                    s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff));// !
                    clean_buffer(tmp_buff);
                }
            
        }
    }
    
}

void flags_processing(Spec *specs, char *buffer_str){
    char tmp_buff[BUFFER_SIZE] = {'\0'};
    
    if (specs->space && buffer_str[0] != '-'){
        tmp_buff[0] = ' ';
        s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); // !
        s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); // !
        clean_buffer(tmp_buff);
    }

    if (specs->plus && array_to_int(buffer_str) > 0 &&!specs->minus){ 
        
        tmp_buff[0] = '+';
        s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str));
        s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); // !
        clean_buffer(tmp_buff);
       
    }
    if (specs->width > (int)s21_strlen(buffer_str) && !(specs->minus)){ // !
        char tmp_tmp_buff[1000] ={'\0'};
        int initial_len = (int)s21_strlen(buffer_str); 
        for (int i = (int)s21_strlen(tmp_tmp_buff); i<specs->width- initial_len; i++){
        
            if (!specs->zero)
                tmp_tmp_buff[i] = ' ';
            else
                tmp_tmp_buff[i] = '0';
        }
        
        s21_strncat(tmp_tmp_buff, buffer_str, s21_strlen(buffer_str)); //!
        s21_strncpy(buffer_str, tmp_tmp_buff, s21_strlen(tmp_tmp_buff)); //!
        clean_buffer(tmp_tmp_buff);
    }
    else if (specs->width > (int)s21_strlen(buffer_str) && specs->minus && !specs->plus){ //!
        
        s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); // !
        for (int i = (int)s21_strlen(buffer_str); i<specs->width; i++) //!
            tmp_buff[i] = ' ';
        s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); // !
        clean_buffer(tmp_buff);
    
    }
    else if(specs->minus && specs->plus){ //!
    
        int flag_plus = 0;
        if(!flag_plus){
            tmp_buff[0] = '+';
            flag_plus++;
        }
        s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); // !
        s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); // !
        for (int i = (int)s21_strlen(buffer_str); i<specs->width; i++) //!
            buffer_str[i] = ' ';
        clean_buffer(tmp_buff);
    }
    if (specs->hash == 1 && (specs->specifier=='x' || specs->specifier=='X' || specs->specifier=='o')){
        
        tmp_buff[0] = '0';
        
        if (specs->specifier == 'x') tmp_buff[1] = 'x';
        if (specs->specifier == 'X') tmp_buff[1] = 'X';
        s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); // !
        s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); //!
        clean_buffer(tmp_buff);
    }
    
}

void clean_buffer(char *buffer){
    for(long unsigned int i = 0; i < sizeof(buffer); i++){
        buffer[i] = '\0';
    }
}

void unsigned_strategy(Spec *specs, char *buffer_str, va_list arguments){
    unsigned long val = va_arg(arguments, unsigned long);
    switch(specs->length){
        case 'h':
            val = (short unsigned int)val;break;
        case 'l':
            val = (long unsigned int)val;break;
        
    }
    unsigned_to_array(val, buffer_str, 10);
    precision_processing(&(*specs), buffer_str);
    flags_processing(&(*specs), buffer_str);
}

void unsigned_to_array(long val, char *buff, int base){
    char buf[BUFFER_SIZE + 1] = {'\0'};
    int idx = BUFFER_SIZE - 1;
    if (val == 0) {
        buf[idx] = '0';
        idx--;
    }

    for (; val && idx; --idx, val /= base)
        buf[idx] = "0123456789abcdef"[val % base];
    for (int j = 0; buf[idx + 1]; idx++, j++)
        buff[j] = buf[idx + 1];
}

void octal_strategy(Spec *specs, char *buffer_str, va_list arguments){
    uint64_t val = va_arg(arguments, uint64_t);
    switch (specs->length) {
    case 0:
        val = (uint32_t)val;
        break;
    case 'h':
        val = (uint16_t)val;
        break;
    case 'l':
        val = (uint64_t)val;
        break;
    }
    unsigned int oct = 0, i = 1;
    char tmp_buff[100] ={'\0'};
    while(val !=0 ){
        oct += (val%8)*i;
        val /= 8;
        i *=10;
    }
    integer_to_char_array(oct, tmp_buff);
    
    precision_processing(&(*specs), tmp_buff);
    flags_processing(&(*specs), tmp_buff);
    s21_strncat(tmp_buff, buffer_str, s21_strlen(buffer_str)); // !
    s21_strncpy(buffer_str, tmp_buff, s21_strlen(tmp_buff)); // !

}

void hex_strategy(Spec *specs, char *buffer_str, va_list arguments){
    uint64_t val = va_arg(arguments, uint64_t);
    switch (specs->length) {
    case 0:
        val = (uint32_t)val;
        break;
    case 'h':
        val = (uint16_t)val;
        break;
    case 'l':
        val = (uint64_t)val;
        break;
    }
    const char hex_lower_chars[] ="0123456789abcdef";
    const char hex_upper_chars[]="0123456789ABCDEF";
    char hex_string[50];
    int i = 0;
    clean_buffer(hex_string);
    while(val !=0){
        int dig = val %16;
        if (specs->specifier == 'x') hex_string[i++] = hex_lower_chars[dig];
        if (specs->specifier == 'X') hex_string[i++] = hex_upper_chars[dig];
        val /=16;
    }
    
    //reverse
    int end = s21_strlen(hex_string)-1;
    int start = 0;
    while(start<end){
        char temp = hex_string[start];
        hex_string[start] = hex_string[end];
        hex_string[end] = temp;
        start++;
        end--;
    }
    
    hex_string[i] = '\0';

    precision_processing(&(*specs), hex_string);
    flags_processing(&(*specs), hex_string);
    s21_strncat(hex_string, buffer_str, s21_strlen(buffer_str));//!
    s21_strncpy(buffer_str, hex_string, s21_strlen(hex_string)); //!
     
}
void char_strategy(Spec *specs, char *buffer_str, va_list arguments){
    if (specs->length == 'l'){
        wchar_t w_c;
        w_c = va_arg(arguments, wchar_t);
        if (!specs->minus && specs->width){
            char tmp[BUFFER_SIZE] = {'\0'};
            wcstombs(tmp, &w_c, BUFFER_SIZE);
            for (s21_size_t i = 0; i<specs->width - s21_strlen(tmp); i++)
                buffer_str[i] = ' ';
            s21_strncat(buffer_str, tmp, s21_strlen(tmp)); // !
        }
        else if (specs->width){
            wcstombs(buffer_str, &w_c, BUFFER_SIZE);
            for (int i = s21_strlen(buffer_str); i< specs->width; i++)
                buffer_str[i] = ' ';
        }else{
            wcstombs(buffer_str, &w_c, BUFFER_SIZE);
        }
    }
    else {
        char c;
        c = va_arg(arguments, int);
        if(!specs->minus && specs->width){
            for (int i = 0; i< specs->width;i++){
                buffer_str[i] = ' ';
                if (i == specs->width -1)
                    buffer_str[i] = c;
            }
        }else if (specs->width){
            buffer_str[0] = c;
            for (int i = 1; i<specs->width; i++){
                buffer_str[i] = ' ';
            }
        } else{
            buffer_str[0] = c;
        }
    }
}
void string_strategy(Spec *specs, char *buffer_str, va_list arguments){
    
    if(specs->length == 'l'){
        wchar_t *wstr = va_arg(arguments, wchar_t *);
        char tmp[BUFFER_SIZE] = {'\0'};
        char str[BUFFER_SIZE] = {'\0'};
    
        wcstombs(str, wstr, BUFFER_SIZE);
        s21_strncpy(tmp, str, s21_strlen(str));
        if (specs->is_precision_set)
            tmp[specs->precision] = '\0';
        int shift = specs->width-s21_strlen(tmp);
        int len = s21_strlen(tmp);

        if (specs->minus && shift > 0) {
            s21_strncpy(buffer_str, tmp, s21_strlen(tmp)); // !!
            s21_memset(buffer_str + len, ' ', shift);
        } else if (shift > 0) {
            s21_memset(buffer_str, ' ', shift);
            s21_strncpy(buffer_str + shift, tmp, s21_strlen(tmp)); //!!
        } else {
            s21_strncpy(buffer_str, tmp, s21_strlen(tmp)); //!!
    }

    }else{
        
        char *str = va_arg(arguments , char*);
        char tmp[BUFFER_SIZE] = {'\0'};
        s21_strncpy(tmp, str, s21_strlen(str));
        if (specs->is_precision_set)
            tmp[specs->precision] = '\0';

        int shift = specs->width - s21_strlen(tmp);
        int len = s21_strlen(tmp);

        if (specs->minus && shift > 0) {
            s21_strncpy(buffer_str, tmp, s21_strlen(tmp));
            s21_memset(buffer_str + len, ' ', shift);
        } else if (shift > 0) {
            s21_memset(buffer_str, ' ', shift);
            s21_strncpy(buffer_str + shift, tmp, s21_strlen(tmp));
        } else {
            s21_strncpy(buffer_str, tmp, s21_strlen(tmp));
        }
    }
}

void pointer_strategy(Spec *specs, char *buffer_str, va_list arguments){
    *buffer_str++ = '0';
    *buffer_str++ = 'x';
    unsigned_to_array(va_arg(arguments, long), buffer_str, 16);
    precision_processing(specs, buffer_str);
    flags_processing(specs, buffer_str);
}

void float_strategy(Spec *specs, char *buffer_str, va_list arguments){
    long double val = 0;
    if (specs->length == 'L'){
        val = va_arg(arguments, long double);
    }else{
        val = va_arg(arguments, double);
    }

    if (!specs->is_precision_set){
        specs->precision = 6;
    }
    double_to_string(val, buffer_str, *specs);
    flags_processing(specs, buffer_str);
}

void double_to_string(long double val, char *buffer_str, Spec f) {
    char buff[BUFFER_SIZE] = {'\0'};
    int idx = BUFFER_SIZE - 2;
    bool neg = val < 0 ? 1 : 0;
    val = neg ? val * -1 : val;
    long double l = 0, r = modfl(val, &l);
    if (f.precision == 0) {
        l = roundl(val);
        r = 0;
    }
    char fractions[BUFFER_SIZE] = {'\0'};
    for (int i = 0; i < f.precision; i++) {
        r = r * 10;
        fractions[i] = (int)r + '0';
    }
    long long right = roundl(r), left = l;
    if (!right) {
        for (int i = 0; i < f.precision; idx--, i++)
            buff[idx] = '0';
    } else {
        for (int i = s21_strlen(fractions); right || i > 0;
             right /= 10, idx--, i--)
            buff[idx] = (int)(right % 10 + 0.05) + '0';
    }
    if ((f.is_precision_set && f.precision != 0) || (int)r ||
        (!f.is_precision_set && val == 0) || s21_strlen(fractions) || (f.is_precision_set && f.hash && f.precision==0))
        buff[idx--] = '.';
    if (!left) {
        buff[idx] = '0';
        idx--;
    } else {
        for (; left; left /= 10, idx--)
            buff[idx] = (int)(left % 10) + '0';
    }
    for (int i = 0; buff[idx + 1]; idx++, i++) {
        if (neg && i == 0) {
            buffer_str[i] = '-';
            i++;
        }
        buffer_str[i] = buff[idx + 1];
    }
}

void mantiss_strategy(Spec *specs, char *buffer_str, va_list arguments){
    long double val = 0;
    if (specs->length == 'L') val = va_arg(arguments, long double);
    else val = va_arg(arguments, double);
    int pow = 0;
    char sign = (int)val == 0 ? '-' : '+';
    

    if ((int)val - val) for (;(int)val == 0; pow++, val*=10);
    else sign = '+';
    for(; (int)val/10 !=0 ; pow++, val /=10);
    if(!specs->is_precision_set)
        specs->precision = 6;
    double_to_string(val, buffer_str, *specs);
    mantiss(buffer_str, pow, sign, specs);
    flags_processing(specs, buffer_str);
    }

void mantiss(char *buffer_str, int pow, char sign, Spec *specs){ 
    int len = s21_strlen(buffer_str);
    if (specs->specifier == 'e') buffer_str[len] = 'e';
    else if (specs->specifier == 'E') buffer_str[len] = 'E';
    buffer_str[len+1] = sign;
    buffer_str[len+3] = pow %10+'0';
    pow /=10;
    buffer_str[len+2] = pow %10 +'0';
    buffer_str[len+4] = '\0';
}

void gG_strategy(Spec *specs, char *buffer_str, va_list arguments){
    long double val = 0;
    if (specs->length == 'L') val = va_arg(arguments, long double);
    else val = va_arg(arguments, double);
    int pow = 0;
    char sign = (int)val == 0 ? '-' : '+';
    long double orig_val = val;
    
    int flag_g_f = 0;
    if ((int)val - val) for (;(int)val == 0; pow++, val*=10);
    else sign = '+';
    for(; (int)val/10 !=0 ; pow++, val /=10);
    if (specs->precision == 0 && specs->is_precision_set) specs->precision = 1;
    else if (specs->precision == 0 && !specs->is_precision_set) specs->precision = 6;
    if (pow<-4 || pow>= specs->precision-1){
        if (specs->specifier == 'g') specs->specifier ='e';
        if (specs->specifier == 'G') specs->specifier ='E';
        
        double_to_string(val, buffer_str, *specs);
        format_gG_precision(buffer_str, specs->precision, &(*specs), flag_g_f);
        if (!specs->hash)
            remove_trailing_zeroes(buffer_str);
        mantiss(buffer_str, pow, sign, specs);  
    }
    else{
        specs->specifier = 'f';
        flag_g_f=1;
        double_to_string(orig_val, buffer_str, *specs);
        if (!specs->hash)
            remove_trailing_zeroes(buffer_str);
        format_gG_precision(buffer_str, specs->precision, &(*specs), flag_g_f);
    }
    flags_processing(specs, buffer_str);
}

void remove_trailing_zeroes(char *buffer_str){
    int len = s21_strlen(buffer_str);
    char *dot = s21_strchr(buffer_str, '.');
    if (dot) {
        for (int i = len - 1; buffer_str[i] != '.'; i--) {
            if (buffer_str[i] == '0')
                buffer_str[i] = '\0';
            else
                break;
        }
        if (dot[1] == '\0')
            dot[0] = '\0';
    }
}

void format_gG_precision(char *buff, int precision, Spec *specs, int flag_g_f) {
    
    if (specs->specifier == 'f' && flag_g_f){
         precision--;
    }
    
    int sig_digs = 0;
    s21_size_t len = s21_strlen(buff);
    int not_zero_found = 0;
    for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
        if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
            continue;
        else
            not_zero_found = 1;

        if (buff[i] > '0' && buff[i] < '9' && not_zero_found) {
            sig_digs++;
        }
        if (sig_digs == precision && i + 1 < len) {
            int next = buff[i + 1] == '.' ? 2 : 1;
            buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
            buff[i + 1] = '\0';
            break;
        }
    }
}
