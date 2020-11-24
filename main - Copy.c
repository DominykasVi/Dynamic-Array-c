#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ends_with_txt( char *file_name)
{
    file_name = strrchr(file_name, '.');

    if( file_name != NULL ){
        return( strcmp(file_name, ".txt") );
    }

    return( -1 );
}
char* get_std_char(){
    char *name = malloc(260);
    int ending_value = -1;
    while(ending_value < 0){
        if (fgets(name, 260, stdin)) {
            name[strcspn(name, "\n")] = ' ';
            ending_value = ends_with_txt(name);
            if (ending_value < 0){
                printf("Please enter a valid name:");
                continue;
            }
        }
    }

    return name;
}

char *read_file_content(FILE *file_pointer, int *string_size, int buffer_size)
{
    //int i = 0; //i for how many lines, might be usefull
    char read[buffer_size];
    char *file_content = NULL;
    int length;
    int total_length = 0;
    int write_position = 0;

    while ((fgets(read, buffer_size, file_pointer)) != NULL) {
        //if (i!= 0) {printf("read:%s i = %d string: %s ____ ", read, i-1, file_content);}
        length = strlen(read);
        total_length += length;
        //printf("read: %s len: %d total len: %d\n", read, len, total_len);
        file_content = (char*) realloc(file_content, (sizeof(char*) * total_length));

        strcpy((file_content+write_position), read);
        write_position +=length;
        //printf("i = %d, string: %s\n", i, (file_content+(i*len)));
       // ++i;//i for how many lines, might be usefull
    }
    *string_size = total_length;
    return file_content;
    //printf("\n%s", file_content);
}

int compare_letters(char *word, int word_size){

    if (word_size < 3 ){
        return 0;
    } else if(word[1] == word[word_size-3]){
        return 1;
    } else {
        return 0;
    }
}

char *sort_text(char *file_content){
    char delimiter[] = " \n";
    char *ptr = strtok(file_content, delimiter);
    char *sorted_words = NULL;

    int length = strlen(ptr);
    char save[256];
    strcpy(save, ptr);
    int saved_length = length+1;

    if (compare_letters(save, length)){
        sorted_words = (char*) realloc(sorted_words, sizeof(char*) * (length+1));
        strcpy(sorted_words, save);
        strcpy((sorted_words+length), " ");

        //printf("%s", sorted_words);

    }

    while(ptr != NULL)
    {
        ptr = strtok(NULL, delimiter);
        if (ptr == NULL){
            break;
        }

        length = strlen(ptr);
        strcpy(save, ptr);

        if (compare_letters(save, length)){
            saved_length += length;
            sorted_words = (char*) realloc(sorted_words, sizeof(char*) * (saved_length+1));
            strcpy((sorted_words + (saved_length - length)), save);
            strcpy((sorted_words+saved_length), " ");
            ++saved_length;
            //printf("%s\n", sorted_words);
        }
        //printf("%s\n", sorted_words);
    }
    printf("%s\n", sorted_words);
    return sorted_words;

}



int main() {
    char *file_name;
    int file_open = 0;
    FILE *file_pointer;
    int buffer_size = 256;

    while (file_open == 0){
        printf("Please enter name of the files you want to read in xxx.txt format(filename cannot be longer than 260 characters): ");
        //file_name = get_std_char();
        if ((file_pointer = fopen("text.txt", "r")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else{
            file_open = 1;
        }
    }
    char *file_content = NULL;
    char *saved_array= NULL;
    int string_size = 0;
    int *string_size_pointer = &string_size;

    if (file_pointer) {
        file_content = read_file_content(file_pointer, string_size_pointer, buffer_size);
        saved_array = sort_text(file_content);
    }

    if(file_content != NULL){
        free(file_content);
    }
    fclose(file_pointer);

    file_open = 0;
    while (file_open == 0){
        printf("Please enter name of the files you want to write in xxx.txt format(filename cannot be longer than 260 characters): ");
        //file_name = get_std_char();
        if ((file_pointer = fopen("rez.txt", "r")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else{
            fclose(file_pointer);
            if ((file_pointer = fopen("rez.txt", "w")) == NULL){
                printf("Error writing to file");
                break;
            }
            fprintf(file_pointer, "%s", saved_array);
            file_open = 1;
        }
    }
    fclose(file_pointer);
    if(saved_array != NULL){
        free(saved_array);
    }
    return 0;

}





// try to find out why not working
//    if (file_pointer){
//        int i = 0;
//        char *read;
//        read = (char*) malloc(sizeof(char) * file_size);
//        while ((fgets(file_content, file_size, file_pointer)) != NULL) {
//            //printf("Retrieved line of length %zu:\n", file_content);
//            //printf("%s\n", read);
//            read = realloc(read, sizeof(char) * file_size);
//            strcpy();
//            printf("pointer; %d %s ", file_content, file_content);
//
//            i += 256;
//        }
//        printf("\n\n%s", file_content);
//        fclose(file_pointer);
//        if (file_content)
//            free(file_content);
//
//    }

//char *file_content = NULL;
//int file_size = 0;
//
//
//
//if(file_pointer) {
//fseek(file_pointer, 0, SEEK_END);
//file_size = ftell(file_pointer);
//rewind(file_pointer);
//
//file_content = (char*) malloc(sizeof(char) * file_size);
//fread(file_content, 1, file_size, file_pointer);
//file_content[file_size] = 0;
//fclose(file_pointer);
//}
//*string_size = file_size;
//return file_content;
