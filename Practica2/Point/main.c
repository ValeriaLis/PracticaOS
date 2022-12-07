#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//функция которая ищет точку с минимальным весом
int min_weight(int amountOfPoints, int **points) {
    int min = points[0][3];
    int index_min = 0;

    for(int i = 0; i < amountOfPoints - 1; i++) {
        if( min > points[i+1][3] ) {
            min = points[i+1][3];
            index_min = i+1;
        }
    }
    return index_min;
}

//поиск ближайшей звезды от первой выбраной
int nearest_point(int amountOfPoints, int **points) {
    int min_point = min_weight(amountOfPoints, points);
    int index_min_distance = 0;
    double min_distance = sqrt(pow(points[0][0]-points[min_point][0], 2) + pow(points[0][1]-points[min_point][1], 2) + pow(points[0][2]-points[min_point][2], 2));

    for (int i = 0; i < amountOfPoints; ++i) {
        double distance = sqrt(pow(points[i][0]-points[min_point][0], 2) + pow(points[i][1]-points[min_point][1], 2) + pow(points[i][2]-points[min_point][2], 2));
        if(min_point == i) {
            continue;
        }
        if(min_distance > distance) {
            min_distance = distance;
            index_min_distance = i;
        }
    }

    if(min_point == 0 && index_min_distance == 0) {
        index_min_distance = 1;
    }

    return index_min_distance;
}

//сумируем вес двух звезд
int **sum_points(int amountOfPoints, int **points) {
    points[nearest_point(amountOfPoints, points)][3] = points[nearest_point(amountOfPoints, points)][3] + points[min_weight(amountOfPoints, points)][3];
    return points;
}

//после всех махинаций удаляем предыдущую звезду
int **delete_point(int amountOfPoints, int **points) {
    int **new_points = (int**)malloc(amountOfPoints * sizeof(int*));
    int index_min_point = min_weight(amountOfPoints, points);

    for (int i = 0; i < amountOfPoints; ++i) {
        new_points[i] = (int*)malloc(4 * sizeof(int));
    }

    for (int i = 0, j = 0; i < amountOfPoints; i++, j++) {
        if(i == index_min_point) {
            j--;
            continue;
        }
        for (int k = 0; k < 4; k++) {
            new_points[j][k] = points[i][k];
        }
    }

    return new_points;
}

//функция для вывода результатов
void print(int amountOfPoints, int **points) {
    for(int i = 0; i < amountOfPoints; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d ", points[i][j]);
        }
        printf("\n");
    }
}


int main() {
    srand(time(NULL));
    int amountOfPoint = 7;
    size_t size = amountOfPoint;
    int **points = (int**)malloc(size* sizeof(int*));
    for (int i = 0; i < amountOfPoint; ++i) {
        points[i] = (int*)malloc(4 * sizeof(int));
    }

    for(int i = 0; i < amountOfPoint; i++) { //генерируем 7 рандомных точек с рандомными координатами и весом
        for(int j = 0; j < 3; j++){
            points[i][j] = rand() % 100;
            points[i][3] = rand() % 1000;
        }
    }
    printf("Initial position of all points\n");
    for(int i = 0; i < amountOfPoint; i++) {
        for(int j = 0; j < 4; j++){
            printf("%d ", points[i][j]);
        }
        printf("\n");
    }
    printf("\n================Calculation start===================\n");
    for (int i = 0, h = amountOfPoint - 1; i < h; i++) {
        printf("---%d---\n", i+1);
        points = delete_point(amountOfPoint, sum_points(amountOfPoint, points));
        amountOfPoint -= 1;
        print(amountOfPoint, points);
        printf("\n");
    }

    printf("=================END==================\n");

    free(points);

    return 0;
}