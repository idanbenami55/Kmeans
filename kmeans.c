#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024
#define epsilon 0.001

int is_valid_integer(const char *str) {
    if (*str == '\0') {
        return 0;
    }

    if (*str == '-') {
        str++;
        if (*str == '\0') {
            return 0;
        }
    }
    while (*str) {
        if (*str < '0' || *str > '9') {
            return 0;
        }
        str++;
    }
    return 1;
}

int my_isdigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int is_valid_integer_or_float(const char *str) {
    int dot_seen = 0;
    const char *ptr = str;

    if (*ptr == '-') {
        ptr++;
    }

    while (*ptr) {
        if (*ptr == '.') {
            if (dot_seen) {
                return 0; 
            }
            dot_seen = 1;
        } else if (!my_isdigit(*ptr)) {
            return 0; 
        }
        ptr++;
    }

    if (dot_seen) {
        if (*(ptr-1) != '0' || *(ptr-2) != '.') {
            return 0; 
        }
    }

    return 1;
}


double euclideanDistance(double *p1, double *p2, int d) {
    double sum = 0;
    int i = 0;
    for (i = 0; i < d; i++) {
        double diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

int main(int argc, char *argv[]) {
    int K;
    int iter = 200;
    char line[256];
    int cols = 0;
    int rows = 0;
    int i, j, h, rowNum, colNum;
    double **vectors;
    double **centroids;
    double **resultCentroids;

    if (argc < 2) {
        printf("An Error Has Occurred");
        return 1;
    }

    if (!is_valid_integer_or_float(argv[1])) {
        printf("Invalid number of clusters!\n");
        return 1;
    }
    K = atoi(argv[1]);
    if (K < 2) {
        printf("Invalid number of clusters!\n");
        return 1;
    }

    if (argc > 2) {
        if (!is_valid_integer_or_float(argv[2])) {
        printf("Invalid maximum iteration!\n");
        return 1;
        }
        iter = atoi(argv[2]);
        if (iter < 2 || iter > 999) {
            printf("Invalid maximum iteration!\n");
            return 1;
        }
    }



    while (fgets(line, sizeof(line), stdin)) {
        if (rows == 0) {
            int count = 0;
            char *str = line;
            while (*str) {
                if (*str == ',') {
                    count++;
                }
                str++;
            }
            cols = count + 1;
        }
        rows++;
    }

    if (K >= rows) {
        printf("Invalid number of clusters!\n");
        return 1;

    }

    fflush(stdin);

    vectors = (double **)calloc(rows , sizeof(double *));
    if (vectors == NULL) {
        printf("An Error Has Occurred");
        return 1;
    }
    for (i = 0; i < rows; i++) {
        vectors[i] = (double *)calloc(cols , sizeof(double));
        if (vectors[i] == NULL) {
            printf("An Error Has Occurred");
            for (j = 0; j < i; j++) {
                free(vectors[j]);
            }
            free(vectors);
            return 1;
        }
    }

    centroids = (double **)calloc(K , sizeof(double *));
    if (centroids == NULL) {
        printf("An Error Has Occurred");
        for (i = 0; i < rows; i++) {
            free(vectors[i]);
        }
        free(vectors);
        return 1;
    }
    for (i = 0; i < K; i++) {
        centroids[i] = (double *)calloc(cols , sizeof(double));
        if (centroids[i] == NULL) {
            printf("An Error Has Occurred");
            for (j = 0; j < i; j++) {
                free(centroids[j]);
            }
            free(centroids);
            for (j = 0; j < rows; j++) {
                free(vectors[j]);
            }
            free(vectors);
            return 1;
        }
    }

    resultCentroids = (double **)calloc(K , sizeof(double *));
    if (resultCentroids == NULL) {
        printf("An Error Has Occurred");
        for (i = 0; i < K; i++) {
            free(centroids[i]);
        }
        free(centroids);
        for (i = 0; i < rows; i++) {
            free(vectors[i]);
        }
        free(vectors);
        return 1;
    }
    for (i = 0; i < K; i++) {
        resultCentroids[i] = (double *)calloc(cols , sizeof(double));
        if (resultCentroids[i] == NULL) {
            printf("An Error Has Occurred");
            for (j = 0; j < i; j++) {
                free(resultCentroids[j]);
            }
            free(resultCentroids);
            for (i = 0; i < K; i++) {
                free(centroids[i]);
            }
            free(centroids);
            for (i = 0; i < rows; i++) {
                free(vectors[i]);
            }
            free(vectors);
            return 1;
        }
    }

    rewind(stdin);
    rowNum = 0;
    while (fgets(line, sizeof(line), stdin)) {
        char *ptr = line;
        colNum = 0;
        while (*ptr != '\0' && *ptr != '\n') {
            char buffer[32];
            unsigned int k = 0;
            double value;
            while (*ptr != ',' && *ptr != '\0' && *ptr != '\n' && k < sizeof(buffer) - 1) {
                buffer[k++] = *ptr++;
            }
            buffer[k] = '\0';
            if (k > 0) {
                char *end;
                value = strtod(buffer, &end);
            }     
            vectors[rowNum][colNum] = value;
            if (rowNum < K) {
                centroids[rowNum][colNum] = value;
            }

            if (*ptr == ',') {
                ptr++;
            }
            colNum++;
        }
        rowNum++;
    }

    for (j = 0; j < iter; j++) {
        int cnt;
        double **nextCentroids = (double **)calloc(K , sizeof(double *));
        int *counter = (int *)calloc(K , sizeof(int));
        if (nextCentroids == NULL || counter == NULL) {
            printf("An Error Has Occurred");
            if (nextCentroids != NULL) free(nextCentroids);
            if (counter != NULL) free(counter);
            for (j = 0; j < K; j++) {
                free(resultCentroids[j]);
            }
            free(resultCentroids);
            for (j = 0; j < K; i++) {
                free(centroids[i]);
            }
            free(centroids);
            for (j = 0; j < rows; i++) {
                free(vectors[i]);
            }
            free(vectors);    

            return 1;
        }
        for (i = 0; i < K; i++) {
            nextCentroids[i] = (double *)calloc(cols , sizeof(double));
            if (nextCentroids[i] == NULL) {
                printf("An Error Has Occurred");
                for (j = 0; j < i; j++) {
                    free(nextCentroids[j]);
                }
                free(nextCentroids);
                free(counter);

                for (j = 0; j < K; j++) {
                free(resultCentroids[j]);
                }
                free(resultCentroids);
                for (j = 0; j < K; i++) {
                    free(centroids[i]);
                }
                free(centroids);
                for (j = 0; j < rows; i++) {
                    free(vectors[i]);
                }
                free(vectors);
                return 1;
                }
                counter[i] = 0;
        }

        for (i = 0; i < rows; i++) {
            double minDistance;
            int minK;
            minDistance = HUGE_VAL;
            minK = 0;
            for (h = 0; h < K; h++) {
                double CurrEuclideanDis = euclideanDistance(vectors[i], centroids[h], cols);
                if (CurrEuclideanDis <= minDistance) {
                    minDistance = CurrEuclideanDis;
                    minK = h;
                }
            }

            for (h = 0; h < cols; h++) {
                nextCentroids[minK][h] += vectors[i][h];
            }

            counter[minK] += 1;
        }

        for (i = 0; i < K; i++) {
            if (counter[i] != 0) {
                for (h = 0; h < cols; h++) {
                    nextCentroids[i][h] = nextCentroids[i][h] / counter[i];
                }
            }
        }

        cnt = 0;
        for (i = 0; i < K; i++) {
            if (euclideanDistance(nextCentroids[i], centroids[i], cols) < epsilon) {
                cnt += 1;
            }
        }

        if (cnt == K) {
            for (i = 0; i < K; i++) {
                free(nextCentroids[i]);
            }
            free(nextCentroids);
            free(counter);
            break;
        }

        for (i = 0; i < K; i++) {
            free(centroids[i]);
        }
        free(centroids);

        centroids = nextCentroids;
        free(counter);
    }

    for (i = 0; i < K; i++) {
        for (h = 0; h < cols; h++) {
            resultCentroids[i][h] = centroids[i][h];
        }
    }

    for (i = 0; i < K; i++) {
        for (h = 0; h < cols - 1; h++) {
            printf("%.4f,", resultCentroids[i][h]);
        }
        printf("%.4f\n", resultCentroids[i][cols - 1]);
    }

    for (i = 0; i < K; i++) {
        free(resultCentroids[i]);
    }
    free(resultCentroids);

    for (i = 0; i < K; i++) {
        free(centroids[i]);
    }
    free(centroids);

    for (i = 0; i < rows; i++) {
        free(vectors[i]);
    }
    free(vectors);

    return 1;
} 
