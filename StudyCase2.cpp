#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    char city[50];
    int cost;
    char currency[30];
    int priceRange;
    float rating;
    char ratingText[30];
    int votes;
} Resto;

Resto data[7370];
int totalData = 0;

int removeNewline(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            return 1;
        }
        i++;
    }
    return 0; 
}


// ambil data resto
int loadData() {
    FILE *fp = fopen("dataResto.csv", "r");
    if (fp == NULL) {
        printf("dataResto.csv not found!\n");
        return -1;
    }
	
	totalData = 0;
    fscanf(fp, "%*[^\n]\n");

    while (fscanf(fp, "%99[^,],%49[^,],%d,%29[^,],%d,%f,%29[^,],%d\n", data[totalData].name, data[totalData].city, &data[totalData].cost,
        data[totalData].currency, &data[totalData].priceRange, &data[totalData].rating, data[totalData].ratingText, &data[totalData].votes) == 8) {

        totalData++;

        if (totalData >= 7370) break;
    }

    fclose(fp);
    return totalData;
}

//header
int printHeader() {
    printf("\n%-18s %-19s %-14s %-18s %-12s %-8s %-14s %-6s\n", "Restaurant name", "City", "Cost for two", "Currency", "Price range", "Rating", "Rating text", "Votes");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
	return 1;
}

//print resto 1 row
int printRow(Resto r) {
    printf("%-18s %-19s %-14d %-18s %-12d %-8.1f %-14s %-6d\n",r.name, r.city, r.cost, r.currency, r.priceRange, r.rating, r.ratingText, r.votes);
	return 1;
}

// display
int displayData(int n) {
    if (n <= 0){
		return -1;
	}
    if (totalData <= 0){
		return 0;
	}
    if (n > totalData) n = totalData;

    printHeader();
    for (int i = 0; i < n; i++) {
        printRow(data[i]);
    }
	return 1;	
}

//search menu
int searchData() {
    char column[50];
    char strQuery[100];
    int intQuery;
    float floatQuery;
    int found = 0;

    printf("What do you want to find? ");
    fgets(column, sizeof(column), stdin);
    removeNewline(column);

    if (strcmp(column, "Cost for two") == 0 || strcmp(column, "Price range") == 0 || strcmp(column, "Votes") == 0) {
		printf("What data do you want to find? ");
        scanf("%d", &intQuery);
        getchar();

        printHeader();
        for (int i = 0; i < totalData; i++) {
            if ((strcmp(column, "Cost for two") == 0 && data[i].cost == intQuery) || (strcmp(column, "Price range") == 0 && data[i].priceRange == intQuery) ||(strcmp(column, "Votes") == 0 && data[i].votes == intQuery)) {
                printRow(data[i]);
                found++;
            }
        }
    }

    else if (strcmp(column, "Rating") == 0) {
        printf("What data do you want to find? ");
        scanf("%f", &floatQuery);
        getchar();

        printHeader();
        for (int i = 0; i < totalData; i++) {
            if (data[i].rating == floatQuery) {
                printRow(data[i]);
                found++;
            }
        }
    }

    else if (strcmp(column, "Restaurant name") == 0 || strcmp(column, "City") == 0 || strcmp(column, "Currency") == 0 || strcmp(column, "Rating text") == 0) {
        printf("What data do you want to find? ");
        fgets(strQuery, sizeof(strQuery), stdin);
        removeNewline(strQuery);

        printHeader();
        for (int i = 0; i < totalData; i++) {
            if ((strcmp(column, "Restaurant name") == 0 && strcmp(data[i].name, strQuery) == 0) || (strcmp(column, "City") == 0 && strcmp(data[i].city, strQuery) == 0) || (strcmp(column, "Currency") == 0 && strcmp(data[i].currency, strQuery) == 0) || (strcmp(column, "Rating text") == 0 && strcmp(data[i].ratingText, strQuery) == 0)) {
                printRow(data[i]);
                found++;
            }
        }
    }

    else {
        printf("Invalid column name!\n");
        return -1;
    }

    if (found == 0) {
        printf("Data not found!\n");
        return 0;
    }

    return found;
}



//sort menu (bubble sort)
int sortData() {
    char column[50];
    char order[10];

    if (totalData <= 1){
        return 0;
	}    

    printf("Choose column: ");
    fgets(column, sizeof(column), stdin);
    removeNewline(column);

    printf("Sort ascending (asc) or descending (desc): ");
    fgets(order, sizeof(order), stdin);
    removeNewline(order);

    if (strcmp(order, "asc") != 0 && strcmp(order, "desc") != 0) {
        printf("Invalid sort order!\n");
        return -2;
    }

    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            int swap = 0;

            if (strcmp(column, "Restaurant Name") == 0 || strcmp(column, "Restaurant name") == 0 || strcmp(column, "restaurant name") == 0) {
                swap = (strcmp(order, "asc") == 0) ? strcmp(data[j].name, data[j + 1].name) > 0 :strcmp(data[j].name, data[j + 1].name) < 0;
            }
            else if (strcmp(column, "City") == 0 || strcmp(column, "city") == 0) {
                swap = (strcmp(order, "asc") == 0) ? strcmp(data[j].city, data[j + 1].city) > 0 : strcmp(data[j].city, data[j + 1].city) < 0;
            }
            else if (strcmp(column, "Cost for two") == 0 || strcmp(column, "cost for two") == 0 || strcmp(column, "Cost For two") == 0 || strcmp(column, "Cost For Two") == 0 || strcmp(column, "Cost for 2") == 0 || strcmp(column, "Cost for Two") == 0){
                swap = (strcmp(order, "asc") == 0) ? data[j].cost > data[j + 1].cost : data[j].cost < data[j + 1].cost;
            }
            else if (strcmp(column, "Currency") == 0 || strcmp(column, "currency") == 0) {
                swap = (strcmp(order, "asc") == 0) ? strcmp(data[j].currency, data[j + 1].currency) > 0 : strcmp(data[j].currency, data[j + 1].currency) < 0;
            }
            else if (strcmp(column, "Price range") == 0 || strcmp(column, "price range") == 0 || strcmp(column, "Price Range") == 0) {
                swap = (strcmp(order, "asc") == 0) ? data[j].priceRange > data[j + 1].priceRange : data[j].priceRange < data[j + 1].priceRange;
            }
            else if (strcmp(column, "Rating") == 0 || strcmp(column, "rating") == 0) {
                swap = (strcmp(order, "asc") == 0) ? data[j].rating > data[j + 1].rating : data[j].rating < data[j + 1].rating;
            }
            else if (strcmp(column, "Rating text") == 0 || strcmp(column, "rating text") == 0 || strcmp(column, "Rating Text") == 0) {
                swap = (strcmp(order, "asc") == 0) ? strcmp(data[j].ratingText, data[j + 1].ratingText) > 0 : strcmp(data[j].ratingText, data[j + 1].ratingText) < 0;
            }
            else if (strcmp(column, "Votes") == 0 || strcmp(column, "votes") == 0) {
                swap = (strcmp(order, "asc") == 0) ? data[j].votes > data[j + 1].votes : data[j].votes < data[j + 1].votes;
            }
            else {
                printf("Invalid column name!\n");
                return -1;
            }

            if (swap) {
                Resto temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    int limit = 10;
    if (limit > totalData) limit = totalData;

    printHeader();
    for (int i = 0; i < limit; i++) {
        printRow(data[i]);
    }
    return 1;
}


//export file
int exportData(char filename[]) {
    char file[100];

    if (totalData <= 0){
        return 0;
	}

    sprintf(file, "%s.csv", filename);

    FILE *fp = fopen(file, "w");
    if (fp == NULL) {
        printf("Failed to create file!\n");
        return -1;
    }

    fprintf(fp, "Restaurant name,City,Cost,Currency,Price range,Rating,Rating text,Votes\n");

    for (int i = 0; i < totalData; i++) {
        fprintf(fp, "%s,%s,%d,%s,%d,%.1f,%s,%d\n", data[i].name, data[i].city, data[i].cost, data[i].currency, data[i].priceRange, data[i].rating, data[i].ratingText, data[i].votes);
    }

    fclose(fp);

    printf("Data successfully written to file %s!\n", file);
    return 1;
}




int main() {
    loadData();
    int choice;

    do {
        printf("1. Display data \n");
        printf("2. Search Data \n");
        printf("3. Sort Data \n");
        printf("4. Export Data \n");
        printf("5. Exit \n");
        printf("Your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int n;
            printf("Number of rows: ");
            scanf("%d", &n);
            displayData(n);
        }
        else if (choice == 2) {
            searchData();
        }
        else if (choice == 3) {
            sortData();
        }
        else if (choice == 4) {
            char filename[50];
            printf("File name: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            exportData(filename);
        }

    } while (choice != 5);

    return 0;
}

