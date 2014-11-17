#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "answer10.h"

typedef struct Review_t{
    long file_offset;
    int Business_ID;
} Review;

typedef struct Bus_Location_t{
    int Business_ID;
    char* address, *state, *city, *zip;
    struct Bus_Location * next;
} Bus_Location;

typedef struct Bus_Tree_t{
    char* name;
    Bus_Location * locations;
    struct Bus_Tree_t *left;
    struct Bus_Tree_t *right;
} Bus_Tree;

struct YelpDataBST{
    Bus_Tree* locations;
    Review* reviews;
    const char* reviews_path; //file of reviews
    const char* business_path;
};

Bus_Tree* tree_test(const char* businesses_path, const char* reviews_path);
void Bus_Loc_test();
void tree_print(Bus_Tree* root, int indent);
void tree_destroy(Bus_Tree* root);
struct Review* create_review_array(long offset, int id, const char* reviews_path);
struct Location* create_loc_array(Bus_Location* locations, Review* reviews,const char* reviews_path);
int List_length(Bus_Location* list);

int main(int argc, char** argv)
{
    const char* bus_filename = "sample_businesses.tsv";
    const char* rev_filename = "sample_reviews.tsv";
    Bus_Tree* business_tree;
    int i;

    //Bus_Loc_test();
    printf("\n\n***********************\n\n");
    struct YelpDataBST* data = create_business_bst(bus_filename, rev_filename);
    struct Review* review_array = create_review_array(593,2,rev_filename);
    free(review_array);
    struct Location* location_array = create_loc_array(data->locations->locations, data->reviews,rev_filename);
    free(location_array->reviews);
    free(location_array);
    tree_destroy(data->locations);
    free(data);
    return 0;
}
