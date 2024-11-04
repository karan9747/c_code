#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

struct listing getfields(char* line);
int compare_host_name(const void *a, const void *b);
int compare_price(const void *a, const void *b);
void write_to_file(const char *filename, struct listing *list_items, int count, const char *titleCSV);


struct listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

struct listing getfields(char* line){
    struct listing item;
    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    return item;
}


int main() {
    // Dynamically allocate memory for an array of 100 structures
    int size = 100;  
    int count = 0;   

    struct listing *list_items = (struct listing*)malloc(size * sizeof(struct listing));
    if (list_items == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    FILE *fptr = fopen("listings.csv", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        free(list_items);
        return 1;
    }

    // Dynamically allocate memory for the line
    int line_size = 1024;
    char *line = (char*)malloc(line_size * sizeof(char));
    char *titleCSV = (char*)malloc(line_size * sizeof(char));

    if (line == NULL) {
        printf("Memory allocation failed!\n");
        free(list_items);
        fclose(fptr);
        return 1;
    }

    // Reading lines from the file
    while (fgets(line, line_size, fptr)) {
        // Reallocate memory for list_items if we exceed the current allocated size
        
        if (count == size) {
            size *= 2;  
            struct listing *temp = realloc(list_items, size * sizeof(struct listing));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                free(line); 
                free(list_items); 
                fclose(fptr);
                return 1;
            }
            list_items = temp;
        }

        // Parse the fields and store them in the array
        if(count == 0) {
            //storing heading
            titleCSV = strdup(line);
        }

        list_items[count++] = getfields(line);
    }

    fclose(fptr);
    //sort by hostname
    qsort(list_items, count, sizeof(struct listing), compare_host_name);
    write_to_file("sorted_by_host_name.csv", list_items, count, (const char *)titleCSV);

    // Sort by price
    qsort(list_items, count, sizeof(struct listing), compare_price);
    write_to_file("sorted_by_price.csv", list_items, count, (const char *) titleCSV);

    // Free dynamically allocated memsories
    free(list_items);
    free(line);

    return 0;
}


// Comparison function for sorting by host_name
int compare_host_name(const void *a, const void *b) {
    struct listing *itemA = (struct listing *)a;
    struct listing *itemB = (struct listing *)b;
    return strcmp(itemA->host_name, itemB->host_name);
}

// Comparison function for sorting by price
int compare_price(const void *a, const void *b) {
    struct listing *itemA = (struct listing *)a;
    struct listing *itemB = (struct listing *)b;
    if (itemA->price < itemB->price) return -1;
    if (itemA->price > itemB->price) return 1;
    return 0;
}

// Function to write sorted data to a new file
void write_to_file(const char *filename, struct listing *list_items, int count,  const char *titleCSV) {
    FILE *outfile = fopen(filename, "w");
    if (outfile == NULL) {
        printf("Error opening file %s for writing!\n", filename);
        return;
    }
    fprintf(outfile,"%s",titleCSV);

    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%d,%d,%s,%s,%s,%.6f,%.6f,%s,%.2f,%d,%d,%d,%d\n",
                list_items[i].id, list_items[i].host_id, list_items[i].host_name,
                list_items[i].neighbourhood_group, list_items[i].neighbourhood,
                list_items[i].latitude, list_items[i].longitude, list_items[i].room_type,
                list_items[i].price, list_items[i].minimum_nights, list_items[i].number_of_reviews,
                list_items[i].calculated_host_listings_count, list_items[i].availability_365);
    }

    fclose(outfile);
    printf("Data written to %s successfully!\n", filename);
}